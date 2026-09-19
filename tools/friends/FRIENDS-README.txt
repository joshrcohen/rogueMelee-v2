ROGUEMELEE v2 - FRIENDS LAUNCHER
Windows 10/11, 64-bit. Offline mod play; not Slippi online matchmaking.

FIRST TIME
1. Put RogueMelee-v2.exe anywhere convenient and open it.
2. Click Install & Play. Select your ORIGINAL clean Melee NTSC-U 1.02 ISO,
   not an old RogueMelee ISO. Select your actual Dolphin.exe / Slippi Dolphin.exe
   beside its Sys folder, not Slippi Launcher.exe. Click Save.
3. Let the launcher download the patch, verify it, and build a SEPARATE ISO.
   The original ISO is never modified. The patch engine downloads automatically.
4. Configure Controllers if needed, then play. The default is to launch after
   updates. Click Desktop shortcut for a permanent shortcut.
   The currently documented v2 entry is GameCube X at the Melee main menu.

NEXT TIME
Open the same EXE or shortcut. It checks the newest published stable/testing
release, installs it when needed, verifies the game, then launches Dolphin.
Keep your clean source ISO in the same place; it is needed for future updates.
The source game, Dolphin and your save files are NOT distributed or updated by us.
A normal new game build does not require a new launcher EXE.

OPTIONS
- Install / Update only: creates/updates the ISO without launching Dolphin.
- Play installed (offline): launch the verified installed build without GitHub.
- Setup: change paths, select stable-only releases, disable automatic launch/update.
- Controllers: opens Dolphin with this launcher's isolated profile.
- Game folder: find the ISO for manual launching. Manual launches may use a
  different Dolphin profile; the launcher's Controllers button edits its own.
- Restore previous build: roll back one installation. Automatic reinstall of the
  reverted release is paused until a newer release is published, or you click Update.
  Rollback changes the game ISO, not your saves; save compatibility between testing
  game versions depends on the game itself.
- Repair installation: rebuild a damaged install from the clean source. The damaged
  ISO replaces the rollback slot; it is not treated as a verified playable backup.
- Report problem: save a ZIP or copy the current report, including during a freeze.
  Include the seed, floor, character, equipped moves, and steps. Send the report to
  Josh yourself; the launcher never uploads your reports automatically.

NO RELEASES YET
A public repository is not enough. Josh must publish a GitHub Release containing
its .xdelta patch and matching build-manifest.json. Source-code pushes and draft
releases are not installable updates. Keep the EXE and retry after publication.

YOUR FILES
Default game: %LOCALAPPDATA%\RogueMelee-v2\Game\RogueMelee-v2.iso
Settings/cache/profile: %LOCALAPPDATA%\RogueMelee-v2
Latest report: %APPDATA%\RogueMelee-v2\Crash Reports\Last session report.txt
Never remove the DolphinUser directory without backing up saves you want to keep.
The old RogueMelee installation and ordinary Dolphin configuration are not modified.

RVZ
An original .rvz is accepted only when the selected emulator also includes
DolphinTool.exe. It is converted once to a verified local clean-ISO cache. An ISO
is the simplest option. A mismatched/modified source is rejected.

REQUIREMENTS AND TRUST
Internet is needed to fetch releases and the pinned xdelta engine on first use.
No Python, Git, GitHub account, SDK installation, or administrator access is needed
by friends. The EXE uses Windows .NET Framework 4.x (4.8 recommended).
The downloadable self-initializing EXE prepares its embedded interface locally on
first start using Windows' .NET compiler. The publisher produces an equivalent
precompiled EXE that does not need that preparation step.
The launcher is unsigned. Windows/security software may warn; do not disable your
antivirus. Source, hashes, and a Windows build/self-test script are included in the
publisher bundle. Neither form downloads source code to compile or execute.
Patch and reconstructed ISO SHA256 values are checked; xdelta's ZIP has a pinned
upstream SHA256. An error never licenses bypassing those checks.
Allow roughly 5 GB for game, rollback and update workspace plus your original image; RVZ
conversion needs additional space. Close Dolphin before an update. A freeze does
not always produce a process crash: use Report problem before ending Dolphin.

RELEASE SOURCE
https://github.com/joshrcohen/rogueMelee-v2/releases
