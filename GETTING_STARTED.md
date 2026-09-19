# Getting started

Use Windows PowerShell with Git, Python 3.11+, Rust/Cargo, Ninja, Visual Studio C++ Build Tools, and Dolphin installed. Ninja must be on PATH, or set its absolute path in ignored `config/local.toml`. The build downloads the pinned compiler/tool dependencies. GitHub access is required to clone the private repository.

## Build and play

```powershell
git clone https://github.com/joshrcohen/rogueMelee-v2.git
cd rogueMelee-v2
$env:MELEE_ISO_PATH = 'C:\Games\Super Smash Bros. Melee (USA) (En,Ja) (v1.02).iso'
$env:DOLPHIN_PATH = 'C:\Tools\Dolphin-x64\Dolphin.exe'
py -3 tools/rogue.py doctor
py -3 tools/rogue.py test --suite tooling
py -3 tools/rogue.py verify-image
py -3 tools/rogue.py bootstrap
py -3 tools/rogue.py build --profile debug
py -3 tools/rogue.py test --suite all
py -3 tools/rogue.py run
```

Replace the two paths with your own files. The input must be clean NTSC-U 1.02: MD5 `0e63d4223b01d9aba596259dc155a174`, original DOL SHA1 `08e0bf20134dfcb260699671004527b2d6bb1a45`. Input validation is read-only. The output is `build/output/rogueMelee.iso`; its symbol map and manifest are alongside it or under `build/`. Bootstrap first proves the exact unmodified baseline; the subsequent build adds Rogue mode.

Alternatively, copy `config/local.example.toml` to `config/local.toml` and edit paths. Environment values override local configuration. Caches, local configuration, input and generated images stay outside Git.

Press GameCube **X** at the main menu, select a fighter, then play a 15-floor run across three acts. On progression: left/right selects, **A** commits, **B** toggles the build panel, **X** rerolls rewards/shop offers for the displayed escalating cost, and **Start** leaves a shop/rest or returns from a finished run. Native Stage Clear shows bonus scoring after wins. Stocks reset each encounter; damage carries until healed. Native Classic and VS remain available. See `KNOWN_ISSUES.md` for tested scope and intentional limitations.

Dolphin uses the workspace-owned `build/dolphin-user` profile. Configure your controller there if necessary. The validated keyboard mapping is A=X, B=Z, X=C, Start=Enter, main stick=arrow keys. Global Dolphin configuration is untouched. Do not rebuild an image while an emulator is reading it, or run two fixtures against the same profile.

## Reproduce validation

```powershell
py -3 tools/rogue.py soak --scenario scenes --iterations 100
py -3 tools/rogue.py soak --matches 100 --timeout 1200
py -3 tools/rogue.py soak --scenario specials --start 0 --iterations 2704 --timeout 7200
py -3 tools/rogue.py soak --scenario specials --iterations 104 --lifecycle --timeout 1200
py -3 tools/rogue.py run --check-passives --seed 77
```

Soaks run native Dolphin fixtures without a speed limit, record success/failure logs and exact hashes in `build/qa`, then terminate only their own emulator. Matrix index = character-select kind * 104 + sorted special-catalog index. `--start` and `--iterations` reproduce a subset. The extended fixture adds native hitstun, ledge hold, linked grab/release, blast-zone death/respawn, and full two-way transformations for transform moves. The passive fixture prints `passive_behavior checks=20 failures=0`; close its emulator after inspection.

Recorded historical evidence lives in `docs/qa`. The full matrix aggregates successfully completed intervals from the builds that exposed and repaired three recipient-specific defects; it is not a claim that every matchup or visual effect was exhaustively tested.

## Developer launch and focused builds

```powershell
py -3 tools/rogue.py run --scene progression --seed 12345
py -3 tools/rogue.py run --scene shop --seed 77
py -3 tools/rogue.py run --scene rest --seed 77
py -3 tools/rogue.py run --scene encounter --encounter elite_juggernaut --seed 77
py -3 tools/rogue.py run --special fox_down --recipient mario --seed 12345
py -3 tools/rogue.py build --target hooks
py -3 tools/rogue.py build --target assets
py -3 tools/rogue.py build --target dol
```

Seeds accept unsigned 64-bit decimal values. Character names use lowercase underscores; special keys are in `data/specials.json`. Launch overrides compile a debug fixture. Plain `run` launches the last verified image. `assets` emits the authored DAT, `hooks` validates ownership/anchors, and `dol` compiles only the executable/map. `progression` and `specials` targets link a complete image because the subsystems share native dependencies. Release builds omit developer shortcuts and the debug HUD line; normal Rogue entry remains available.

## Release patch

```powershell
# Requires a clean committed checkout and passing recorded native gates.
py -3 tools/rogue.py package --profile release
```

Packaging runs automated checks, verifies locked dependencies, builds release, encodes an xdelta, reconstructs a fresh image, compares hashes, and revalidates the original input. Only the patch, manifest, notices and instructions enter `dist/`; no full image or extracted retail assets are distributed. The pinned xdelta tool is compiled locally using MSVC.

Apply the resulting patch to your clean image:

```powershell
& .\build\tools\xdelta3.exe -d -s $env:MELEE_ISO_PATH .\dist\rogueMelee-v0.1.0.xdelta .\patched.iso
Get-FileHash .\patched.iso -Algorithm SHA256
```

Compare with `output_sha256` in `dist/build-manifest.json`, then open the reconstructed image in Dolphin. Aerial swapping is disabled in v0.1.0.
