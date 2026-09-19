# RogueMelee v2: friend launcher and testing-release publisher

## One-time setup for Josh

Extract this ZIP **into the root of the new `rogueMelee-v2` repository**. It adds
`Publish Test Build.bat`, this guide, and `tools/friends/`. It does not replace game
code, the existing build scripts, or your clean ISO.

GitHub CLI must be installed and authenticated on your developer PC (`gh auth login`).
Friends do not need it. Keep the repository public. Do not embed tokens in the launcher.

Review and commit the new helper files once, along with any intended game changes:

```powershell
cd C:\path\to\rogueMelee-v2
git add "Publish Test Build.bat" PUBLISHING-README.md tools/friends
git commit -m "Add friend launcher and verified test-release publisher"
git push
```

The existing `tools/rogue.py package --profile release` still requires a clean
worktree and your existing native QA records. This publisher does not bypass them.
If the game build regenerates tracked registries, review/commit/push those changes
and rerun publishing as the repository's existing packaging contract requires.

## Publish the first test build, and every subsequent one

Finish your game changes, test them, commit them and push the current branch. Close
Dolphin so the build is not replacing a file being read by the emulator. Then run:

```powershell
& ".\Publish Test Build.bat"
```

The helper performs these operations in order:

1. Verifies the origin repository, clean worktree, public visibility and remote HEAD commit.
2. Compiles a conventional **single-file .NET Framework launcher EXE on your Windows PC**.
3. Compiles and runs the launcher's real Windows self-tests. A failure stops publishing.
4. Calls the existing v2 release-packaging command, unless you explicitly select the
   existing-package option below. The game build's own QA/hash requirements remain intact.
5. Verifies the patch SHA256, local output SHA256, reconstruction hash and matching commit.
6. Creates a staging directory with an explicit file allowlist. No ISO or retail files are uploaded.
   The public manifest omits developer machine paths.
7. Creates a uniquely tagged **draft prerelease**, uploads all assets, then publishes it.
   An upload failure leaves a draft, not a broken automatic update.

Default tag: `test-YYYYMMDD-HHMMSS-<commit>`, using UTC time.
Friends' launchers include published prereleases by default and select by publication
time, not the hard-coded `v0.1.0` patch filename. Source pushes and ordinary tags alone
are NOT game updates. Use a fresh release tag for each testing build.

After the first successful publication, send friends the `RogueMelee-v2.exe` attached
to that release (or the supplied self-initializing EXE). They keep the same EXE/shortcut
for normal future releases. You need not send a new patch ZIP for every build.

### Advanced commands

```powershell
# Use the already-packaged dist files. They must match CURRENT HEAD and local ISO hashes.
& .\tools\friends\Publish-TestBuild.ps1 -UseExistingPackage

# Explicit unique tag and your own release notes.
& .\tools\friends\Publish-TestBuild.ps1 -Tag test-aerials-001 -NotesFile .\notes.md

# Stable release instead of a prerelease.
& .\tools\friends\Publish-TestBuild.ps1 -Stable -Tag v0.2.0

# Compile and test just the launcher, without packaging or publishing the game.
& .\tools\friends\Build-Launcher.ps1
```

`Build-Launcher.ps1` writes to `build/friends-launcher/`, not `dist/`, because the
existing v2 packager has its own strict `dist` allowlist. Normal publisher staging
lives under ignored `build/friends-publish/`. Do not copy these generated directories
into source control. The script never auto-pushes source or edits existing releases.

## What friends do

They need Windows 10/11 x64, their clean NTSC-U Melee 1.02 ISO, and an existing Dolphin
(or actual Slippi Dolphin) installation to play. No repository, Python, Rust, compiler
installation, GitHub account, or administrator access is required.

Open the EXE, select the clean source and emulator once, leave the separate ISO output
at its default location, and choose Install & Play. Later launches check for updates,
apply them, verify the completed ISO, and launch. For manual emulator use, choose
Install / Update only and open the output ISO yourself.

The launcher uses a separate Dolphin user directory. It tries to import existing
controller mappings once, without importing save data, cheats or global configuration.
The Controllers button opens that profile for configuration. It does not download or
update Dolphin itself. This is offline mod play, not Slippi online matchmaking.

## Release-asset contract

The updater supports the current v2 packaging format directly:

- `build-manifest.json` with mandatory `patch_sha256` and `output_sha256` strings.
- Exactly one `.xdelta` patch asset. If there are multiple, the manifest must specify
  `patch_file` matching one exact asset name.
- Optional `output_bytes`, `source_md5`, `source_dol_sha1`, `git_commit`, and
  `launcher_schema` (supported: absent or `1`).

The helper adds these optional fields and uploads the launcher, notices, instructions
and `SHA256SUMS.txt`. If you publish manually, upload the patch and manifest from the
SAME packaging run. Keep it a draft until all assets are uploaded.

The launcher refuses an incomplete newest release rather than silently installing an
older one. Stable-only can be selected in Setup. Its feed is the most recent 100
published releases returned by GitHub; drafts are always excluded. The normal game
update mechanism does not self-replace the launcher EXE. A future change in patch
format or a launcher bug fix requires distributing a new launcher version explicitly.

## Behavior carried over and improved

The remembered paths / check-update-launch workflow and local session report are
preserved. V2 does NOT use the legacy `rogue.delta` DOL-insertion format: each update
reconstructs a full ISO from the preserved clean source. This prevents repeated DOL
appends from growing the installed game. A verified new game is promoted using an
atomic file replacement on a local NTFS output volume; one previous installation is
retained. Use the default local output folder for this guarantee.

Rollback verifies its backup and pauses automatic reinstall of the rolled-back release
until a newer release appears (manual Update retries it). Offline Play verifies the
installed ISO without accessing GitHub. Repair can rebuild a damaged ISO; it replaces
the existing rollback slot and does not call a damaged backup known-good.

Download and process work runs off the UI thread. Cancellation applies to downloads,
conversion and decoding; final promotion is deliberately non-cancellable. A pending
install journal supports recovery after interruption. Existing unrelated output files
and source images are never blindly overwritten. Updates are blocked while Dolphin
processes are running, including emulators started manually.

## Source and testing transparency

The supplied `RogueMelee-v2.exe` is a compiled native Windows x64 envelope containing
the complete C# UI source, icon and manifest. First launch uses the Windows .NET
Framework compiler to prepare that source locally in a versioned per-user directory;
subsequent launches reuse it. It never downloads C# or runs remote scripts. This
avoids requiring friends to install build tools. Windows components disabled by an
organization's policies can prevent the preparation step.

The publisher builds the SAME UI into a conventional precompiled EXE, runs its
self-tests, and uploads that version. It has no first-run compilation step. Prefer
that published EXE for general distribution after the first Windows build passes.

During creation in the Linux environment, the native envelope was compiled and its PE
structure/payload checked. Windows Forms execution, .NET compilation, the embedded
Windows self-tests and the full real-ISO patch/launch path were NOT executed there.
At inspection time on 2026-09-19 the game repository had no published releases. Do one
Windows end-to-end check of the first published build before broadly distributing it.
`tools/friends/TESTING.md` contains that checklist. This is not a claim that a GUI or
ISO patch was successfully run in the creation environment.

No signing certificate is bundled: both EXEs are unsigned. Windows may show a security
prompt. Do not disable antivirus. The source and checksums are available for review.

## Source references inspected

- v2 packaging: https://github.com/joshrcohen/rogueMelee-v2/blob/codex/greenfield-rebuild/tools/lib/packaging.py
- v2 isolated emulator launch: https://github.com/joshrcohen/rogueMelee-v2/blob/codex/greenfield-rebuild/tools/lib/emulator.py
- v2 getting started: https://github.com/joshrcohen/rogueMelee-v2/blob/codex/greenfield-rebuild/GETTING_STARTED.md
- Previous workflow: https://github.com/joshrcohen/rogueMelee/blob/main/tools/package/RogueMelee.cs
- GitHub releases API: https://docs.github.com/en/rest/releases/releases
- GitHub CLI: https://cli.github.com/manual/gh_release_create and https://cli.github.com/manual/gh_release_edit
- xdelta 3.2.0: https://github.com/jmacd/xdelta/releases/tag/v3.2.0
- Windows csc: https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/compiler-options/
