<#
Creates a uniquely tagged GitHub testing release. It never pushes source, uploads
an ISO, embeds credentials, publishes a half-uploaded release, or bypasses game QA.
Uses v2's existing package command unless -UseExistingPackage is explicitly passed.
#>
[CmdletBinding()]
param(
    [string]$RepoPath = '',
    [string]$Tag = '',
    [string]$NotesFile = '',
    [switch]$Stable,
    [switch]$UseExistingPackage
)
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$Repository = 'joshrcohen/rogueMelee-v2'
$CleanMD5 = '0e63d4223b01d9aba596259dc155a174'
$CleanDol = '08e0bf20134dfcb260699671004527b2d6bb1a45'
function Run([string]$Program, [string[]]$Arguments) {
    & $Program @Arguments
    if ($LASTEXITCODE -ne 0) { throw "$Program failed (exit $LASTEXITCODE). No completed new release has been published." }
}
function Field($Object, [string]$Name) {
    $property = $Object.PSObject.Properties[$Name]
    if ($null -eq $property) { return $null }
    return $property.Value
}
function Hash([string]$Path) { return (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash.ToLowerInvariant() }
function WriteUtf8([string]$Path, [string]$Text) { [IO.File]::WriteAllText($Path, $Text, (New-Object Text.UTF8Encoding($false))) }
if (-not $RepoPath) { $RepoPath = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path }
$RepoPath = (Resolve-Path -LiteralPath $RepoPath).Path
$here = Get-Location
try {
    Set-Location -LiteralPath $RepoPath
    foreach ($tool in @('git','gh')) { if (-not (Get-Command $tool -ErrorAction SilentlyContinue)) { throw "Install $tool first. For GitHub CLI, use the official cli.github.com installer, then run gh auth login. Friends do not need it." } }
    if (-not (Test-Path -LiteralPath (Join-Path $RepoPath 'tools\rogue.py'))) { throw 'Run this inside the NEW rogueMelee-v2 repository, not the old rogueMelee repository.' }
    $remote = (& git remote get-url origin | Out-String).Trim()
    if ($LASTEXITCODE -ne 0 -or $remote -notmatch 'github\.com[:/]joshrcohen/rogueMelee-v2(?:\.git)?$') { throw "Wrong origin remote: $remote. Expected $Repository." }
    $dirty = (& git status --porcelain | Out-String).Trim()
    if ($LASTEXITCODE -ne 0 -or $dirty) { throw 'Commit the intended game changes AND these launcher/publisher files first. Then git push. Packaging requires a clean committed checkout.' }
    $commit = (& git rev-parse HEAD | Out-String).Trim()
    if ($LASTEXITCODE -ne 0 -or $commit -notmatch '^[0-9a-f]{40}$') { throw 'Cannot resolve the current Git commit.' }
    Run 'gh' @('auth','status')
    $private = (& gh api "repos/$Repository" --jq '.private' | Out-String).Trim()
    if ($LASTEXITCODE -ne 0 -or $private -ne 'false') { throw 'The release repository must be public so friends do not need GitHub credentials.' }
    & gh api "repos/$Repository/commits/$commit" --silent
    if ($LASTEXITCODE -ne 0) { throw 'This commit is not on GitHub yet. Run git push for your current branch, then rerun the publisher. No source is pushed automatically.' }
    if (-not $Tag) { $Tag = 'test-' + [DateTime]::UtcNow.ToString('yyyyMMdd-HHmmss') + '-' + $commit.Substring(0,7) }
    if ($Tag -notmatch '^[A-Za-z0-9][A-Za-z0-9._-]{0,119}$') { throw 'Use a simple tag containing only letters, digits, dot, dash, or underscore (up to 120 characters).' }
    Write-Host "Publishing candidate: $Tag  ($commit)" -ForegroundColor Cyan
    # Produces a fully precompiled EXE and executes real Windows launcher self-tests.
    $launcherDir = Join-Path $RepoPath 'build\friends-launcher'
    & (Join-Path $PSScriptRoot 'Build-Launcher.ps1') -OutputDirectory $launcherDir
    if (-not $UseExistingPackage) {
        if (Get-Command py -ErrorAction SilentlyContinue) { Run 'py' @('-3','tools/rogue.py','package','--profile','release') }
        elseif (Get-Command python -ErrorAction SilentlyContinue) { Run 'python' @('tools/rogue.py','package','--profile','release') }
        else { throw 'Python is needed on the publisher computer to run the existing v2 package command. Friends do not need Python.' }
    }
    $dist = Join-Path $RepoPath 'dist'
    $manifestFile = Join-Path $dist 'build-manifest.json'
    if (-not (Test-Path -LiteralPath $manifestFile)) { throw 'dist/build-manifest.json is missing. Run the v2 package command first.' }
    $meta = Get-Content -LiteralPath $manifestFile -Raw | ConvertFrom-Json
    if ([string](Field $meta 'git_commit') -ne $commit) { throw 'The package belongs to a different commit. Re-run package for the current committed source.' }
    $patches = @(Get-ChildItem -LiteralPath $dist -File -Filter '*.xdelta')
    if ($patches.Count -ne 1) { throw 'dist must contain exactly one .xdelta patch. Move obsolete patches out of dist and package again.' }
    $patch = $patches[0]
    if ($patch.Length -le 0 -or $patch.Length -gt 2147483648) { throw 'Patch size is invalid or exceeds the launcher limit.' }
    $patchHash = Hash $patch.FullName
    $expectedPatch = [string](Field $meta 'patch_sha256')
    $outputHash = [string](Field $meta 'output_sha256')
    $reconstructedHash = [string](Field $meta 'reconstructed_sha256')
    if ($patchHash -ne $expectedPatch -or $outputHash -notmatch '^[0-9a-fA-F]{64}$' -or $outputHash -ne $reconstructedHash) { throw 'Package checksum/reconstruction metadata is missing or inconsistent. Nothing was uploaded.' }
    $output = [string](Field $meta 'output')
    if (-not $output) { throw 'The package manifest has no local output path to verify.' }
    if (-not [IO.Path]::IsPathRooted($output)) { $output = Join-Path $RepoPath $output }
    if (-not (Test-Path -LiteralPath $output)) { throw 'The verified local output ISO is missing. Package again.' }
    if ((Hash $output) -ne $outputHash) { throw 'The local ISO no longer matches the package. Package again before publishing.' }
    $dirty = (& git status --porcelain | Out-String).Trim()
    if ($dirty) { throw 'Packaging changed tracked/generated files. Review and commit those changes, then re-run packaging/publishing.' }
    $stage = Join-Path $RepoPath ('build\friends-publish\' + $Tag)
    if (Test-Path -LiteralPath $stage) { throw "Publishing staging folder already exists: $stage. Use a new tag rather than overwriting a prior candidate." }
    New-Item -ItemType Directory -Path $stage -Force | Out-Null
    Copy-Item -LiteralPath $patch.FullName -Destination (Join-Path $stage $patch.Name)
    $sanitized = [ordered]@{
        launcher_schema = 1
        project = 'rogueMelee-v2'
        release_tag = $Tag
        git_commit = $commit
        source_md5 = $CleanMD5
        source_dol_sha1 = $CleanDol
        patch_file = $patch.Name
        patch_sha256 = $patchHash
        output_sha256 = $outputHash.ToLowerInvariant()
        reconstructed_sha256 = $reconstructedHash.ToLowerInvariant()
        output_bytes = (Get-Item -LiteralPath $output).Length
        launcher_version = '1.0.0'
    }
    WriteUtf8 (Join-Path $stage 'build-manifest.json') (($sanitized | ConvertTo-Json -Depth 6) + "`n")
    Copy-Item -LiteralPath (Join-Path $launcherDir 'RogueMelee-v2.exe') -Destination (Join-Path $stage 'RogueMelee-v2.exe')
    foreach ($notice in @('THIRD_PARTY_NOTICES.md')) { if (-not (Test-Path -LiteralPath (Join-Path $dist $notice))) { throw "Missing $notice in dist." }; Copy-Item -LiteralPath (Join-Path $dist $notice) -Destination (Join-Path $stage $notice) }
    Copy-Item -LiteralPath (Join-Path $PSScriptRoot 'FRIENDS-README.txt') -Destination (Join-Path $stage 'README.txt')
    Copy-Item -LiteralPath (Join-Path $PSScriptRoot 'LICENSE.txt') -Destination (Join-Path $stage 'LAUNCHER-LICENSE.txt')
    $assets = @($patch.Name,'build-manifest.json','RogueMelee-v2.exe','THIRD_PARTY_NOTICES.md','README.txt','LAUNCHER-LICENSE.txt')
    $sums = foreach ($name in $assets) { (Hash (Join-Path $stage $name)) + '  ' + $name }
    WriteUtf8 (Join-Path $stage 'SHA256SUMS.txt') (($sums -join "`n") + "`n")
    $assets += 'SHA256SUMS.txt'
    $notes = Join-Path $stage 'release-notes.md'
    if ($NotesFile) { if (-not (Test-Path -LiteralPath $NotesFile)) { throw "Notes file not found: $NotesFile" }; Copy-Item -LiteralPath $NotesFile -Destination $notes }
    else { WriteUtf8 $notes ("RogueMelee v2 testing build from commit $commit.`n`nRun RogueMelee-v2.exe. Select your ORIGINAL clean NTSC-U Melee 1.02 ISO and actual Dolphin.exe once. Future published builds are checked on launch. No GitHub account or development tools are needed by players.`n`nKeep the clean ISO for future updates. This release contains a verified patch, not a full game image.`n`nReport problems with the launcher's Report problem button.`n") }
    $arguments = @('release','create',$Tag,'--repo',$Repository,'--draft','--target',$commit,'--title',"RogueMelee v2 - $Tag",'--notes-file',$notes)
    if (-not $Stable) { $arguments += '--prerelease' }
    foreach ($name in $assets) { $arguments += Join-Path $stage $name }
    Run 'gh' $arguments
    # Draft is published only after all assets have uploaded successfully.
    $prerelease = if ($Stable) { '--prerelease=false' } else { '--prerelease=true' }
    $latest = if ($Stable) { '--latest' } else { '--latest=false' }
    Run 'gh' @('release','edit',$Tag,'--repo',$Repository,'--draft=false',$prerelease,$latest)
    Write-Host "Published: https://github.com/$Repository/releases/tag/$Tag" -ForegroundColor Green
    Write-Host 'Friends can now reopen the SAME launcher to install this build.'
    Write-Host "A conventional precompiled launcher is also in $launcherDir\RogueMelee-v2.exe"
} finally { Set-Location $here }
