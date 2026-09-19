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

## Current development image

After bootstrap, compile the source overlay and launch its output:

```powershell
py -3 tools/rogue.py build --profile debug
py -3 tools/rogue.py test --suite all
py -3 tools/rogue.py run
```

The mode entry is GameCube **X** from the stock main menu. Choose a fighter on the native character-select screen. In progression, left/right selects, A commits, B toggles the build panel, X spends gold on a reroll, and Start leaves a shop/rest or returns from a finished run. Normal menu/CSS/reward/route/combat/loss controller flow has passed. Broader gameplay validation remains in progress; consult the status table.

A fixed-seed interactive layout preview bypasses character selection:

```powershell
py -3 tools/rogue.py build --profile debug --qa-ui
py -3 tools/rogue.py run
```

Native automated fixtures use the workspace's isolated Dolphin profile, temporarily run without a speed limit, and save both successful and failed logs under `build/qa/`. They terminate only the Dolphin process they launch. Do not run two fixtures concurrently against that profile or rebuild its image while Dolphin is using it.

```powershell
py -3 tools/rogue.py soak --scenario scenes --iterations 100
py -3 tools/rogue.py soak --matches 100
py -3 tools/rogue.py soak --scenario specials --start 0 --iterations 104
# Full recipient x special range (long run):
py -3 tools/rogue.py soak --scenario specials --start 0 --iterations 2704 --timeout 7200
```

Matrix index = character-select kind * 104 + sorted special-catalog index. A smaller `--start`/`--iterations` range reproduces a failing combination. The current fixture checks ground/air entry, native attribute/animation restoration, surviving articles, and native match teardown. It does not yet certify all collision, grab, ledge or respawn scenarios. Donkey Kong's Hand Slap has no native airborne attack; its airborne policy consumes the input and returns to native fall.

The authored panel/route asset is emitted as `build/assets/RogueUi.dat` and embedded in the executable. Fighter portraits and font data are loaded from the user's original image. No retail art is copied into repository sources.

## Release packaging

Install Visual Studio C++ Build Tools to compile the pinned xdelta3 utility. `py -3 tools/rogue.py package --profile release` requires a clean committed worktree, runs automated checks, builds the release image and verifies xdelta reconstruction. The final native release gates remain pending; this command is not yet a certified distribution workflow.

`build --target assets` emits the authored DAT and asset manifest without assembling an image. `--target hooks` validates hook ownership and pinned anchors. `--target dol` compiles the executable/map only and records `build/dol-manifest.json`. `--target progression` and `--target specials` link the complete native image, including the selected subsystem and its shared dependencies.

Extended special fixtures add native damage interruption and an actual blast-zone death/respawn:

```powershell
py -3 tools/rogue.py soak --scenario specials --iterations 104 --lifecycle --timeout 900
```

All 104 Captain Falcon cases passed this extended gate. Ledge, grab and pause scenarios remain separate pending checks.

Reproducible developer launches build an isolated debug configuration into the executable, then launch the resulting image:

```powershell
py -3 tools/rogue.py run --scene progression --seed 12345
py -3 tools/rogue.py run --scene encounter --encounter elite_juggernaut --seed 77
py -3 tools/rogue.py run --special fox_down --recipient mario --seed 12345
py -3 tools/rogue.py soak --matches 100 --seed 77
```

Seeds accept unsigned 64-bit decimal values. Character names use lowercase underscores; move keys are listed in `data/specials.json`. Developer launch overrides require debug builds. A plain `run` launches the last verified image without recompiling.

For controlled native passive assertions, run `py -3 tools/rogue.py run --check-passives --seed 77` and look for `passive_behavior checks=20 failures=0` in the owned Dolphin log.
