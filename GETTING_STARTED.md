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

The mode entry is GameCube **X** from the stock main menu. Choose a fighter on the native character-select screen. In progression, left/right selects, A commits, B toggles the build panel, X spends gold on a reroll, and Start leaves a shop/rest or returns from a finished run. Normal controller entry and full gameplay remain under validation; consult the status table.

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
