# Launcher validation and first Windows test

## What was actually executed during creation

PASS: native Windows x64 envelope compilation with Clang/LLD, warnings as errors.
PASS: PE subsystem, architecture, imports, manifest/icon and embedded-payload checks.
PASS: static source/packaging integrity checks recorded in CREATION-VALIDATION.txt.

NOT RUN HERE: Windows/.NET UI compilation, the embedded .NET self-tests, Windows GUI
execution, RVZ conversion, real clean-ISO patching, live update, rollback and Dolphin
launch. The creation environment is Linux without Windows/.NET or a user game image.
There was no published v2 release to install at inspection time.

## First step on Josh's Windows computer

```powershell
& .\tools\friends\Build-Launcher.ps1
```

This compiles both the actual UI and a console self-test target using Windows csc.
The tests execute locally and write `build/friends-launcher/launcher-self-tests.txt`.
They cover quoting, checksums, source rejection, settings persistence/atomic updates,
trusted URL checks, draft/prerelease selection, missing/ambiguous manifest fields,
GitHub digest mismatches and file replacement with backup.

## End-to-end acceptance

1. Publish one verified test release through Publish Test Build.bat.
2. Run the precompiled `build/friends-launcher/RogueMelee-v2.exe` or release EXE.
3. Choose the clean source ISO and actual Dolphin.exe. Install to the default output.
4. Compare output SHA256 with the release manifest. Confirm the source MD5 is unchanged.
5. Launch; set up the controller in the isolated profile. Confirm normal Dolphin's
   configuration and memory card files were not altered by the launcher.
6. Close the game. Open Report problem and save a ZIP. Check build, commit and logs.
7. Publish a second unique test release. Reopen the SAME EXE and verify automatic update.
8. Restore previous build. Confirm its ISO hash and that reopening does not undo rollback.
9. Choose Update manually, then confirm a later third release updates normally.
10. Disconnect networking. Verify Play installed succeeds without a network request.
11. Cancel a download/patch; old ISO must remain playable. Reopen after an interrupted
    promotion to check journal recovery. Do not deliberately power off your PC to test.
12. Try the old modded ISO as source: it must be rejected and untouched. Try an existing
    unrelated output filename: it must be refused. Verify update refusal while Dolphin
    is running. Try non-ASCII/spaced paths and high-DPI display scaling.
13. Optional RVZ case: select the clean RVZ and DolphinTool-equipped emulator, verify
    cached ISO MD5, then update again without repeating the conversion.
14. Run from a friend account with no Git/Python/GitHub CLI installed. No admin prompt
    should be needed. A security reputation warning is separate from an admin prompt.

A seed alone is not a full crash reproduction. Include input sequence/build/loadout
and a video where useful. A frozen emulator can still have a live process; exporting
its current log is supported, automatic freeze diagnosis is not claimed.
