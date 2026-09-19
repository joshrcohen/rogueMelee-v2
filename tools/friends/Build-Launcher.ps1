# Original launcher code: MIT. Run locally on Windows; no SDK download is required.
[CmdletBinding()]
param([string]$OutputDirectory = '')
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
if (-not $OutputDirectory) { $OutputDirectory = Join-Path (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path 'build\friends-launcher' }
$OutputDirectory = [IO.Path]::GetFullPath($OutputDirectory)
New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
$csc = Join-Path $env:WINDIR 'Microsoft.NET\Framework64\v4.0.30319\csc.exe'
if (-not (Test-Path -LiteralPath $csc)) { $csc = Join-Path $env:WINDIR 'Microsoft.NET\Framework\v4.0.30319\csc.exe' }
if (-not (Test-Path -LiteralPath $csc)) { throw 'The Windows .NET Framework 4.x compiler is unavailable. Use Windows 10/11 with .NET Framework 4.8 enabled.' }
$source = Join-Path $PSScriptRoot 'Launcher.cs'
$common = @('/nologo','/platform:x64','/optimize+','/r:System.dll','/r:System.Core.dll','/r:System.Drawing.dll','/r:System.Windows.Forms.dll','/r:System.Web.Extensions.dll','/r:System.IO.Compression.dll','/r:System.IO.Compression.FileSystem.dll')
$exe = Join-Path $OutputDirectory 'RogueMelee-v2.exe'
$tests = Join-Path $OutputDirectory 'Launcher.SelfTests.exe'
$report = Join-Path $OutputDirectory 'launcher-self-tests.txt'
Write-Host 'Compiling the standalone Windows launcher...'
& $csc @common '/target:winexe' "/win32manifest:$(Join-Path $PSScriptRoot 'app.manifest')" "/win32icon:$(Join-Path $PSScriptRoot 'launcher.ico')" "/out:$exe" $source
if ($LASTEXITCODE -ne 0) { throw 'Launcher compilation failed. Nothing was published.' }
& $csc @common '/target:exe' "/out:$tests" $source
if ($LASTEXITCODE -ne 0) { throw 'Launcher self-test compilation failed. Nothing was published.' }
& $tests '--self-test' '--report' $report
if ($LASTEXITCODE -ne 0 -or -not (Test-Path -LiteralPath $report)) { throw 'Launcher self-tests failed. Nothing was published.' }
Get-Content -LiteralPath $report | Write-Host
(Get-FileHash -LiteralPath $exe -Algorithm SHA256).Hash.ToLowerInvariant() | Set-Content -LiteralPath (Join-Path $OutputDirectory 'launcher.sha256') -Encoding ASCII
Write-Host "Launcher built: $exe"
