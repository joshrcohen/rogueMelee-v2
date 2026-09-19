# Getting started

Development is in progress; consult IMPLEMENTATION_STATUS.md before treating any command as a release workflow.

Use Windows PowerShell, Git and Python 3.11 or later. Supply your own clean NTSC-U v1.02 image using `MELEE_ISO_PATH` or ignored `config/local.toml`. Generated images will be written under `build/`, never over the input.

Install Rust/Cargo and Ninja for the baseline build. Copy `config/local.example.toml` to `config/local.toml` and set local paths. If Ninja is not on PATH, add `ninja = "C:/path/to/ninja.exe"` under `[paths]`.

```powershell
py -3 tools/rogue.py doctor
py -3 tools/rogue.py test --suite tooling
py -3 tools/rogue.py verify-image
py -3 tools/rogue.py bootstrap
```

Bootstrap currently produces an unmodified retail baseline at `build/output/rogueMelee.iso`, with `build/output/GALE01.map` and `build/build-manifest.json`. This is pipeline validation, not the finished rogue mode.
