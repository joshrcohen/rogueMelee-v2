# Borrowed specials baseline

Legacy repository: https://github.com/joshrcohen/rogueMelee at `82377924344f3d38f6ed89aef9a32dda66820b7f`.
Clean decomp: https://github.com/doldecomp/melee at `11749c9ccbaf73bfc28a569650dfec5e18665a74`.

Inputs: `mod/rogue_ability.c`, `mod/rogue_ability.h`, `mod/rogue_ability_registry.c`, `patches/engine.patch`, special QA/tests, `tools/postpatch_ability_fixes*.py`, `tools/postpatch_ability_production_cleanup.py`.

## Reproduction discovery

The pinned legacy commit's `tools/build.py --prepare-only` fails because it references an untracked `tools/postpatch_aerial_shop.py`. A copy was found in the user's adjacent legacy working directory and copied only to the ignored migration oracle. SHA256: `613755dd6b8bfacc5bf71259d4414edb3e5124da9bd350c7c3213357ee0fca95`.

With that supplement the exact legacy prepare command succeeds. It creates `.cache/melee-071b84ed2d2f` inside the oracle. Its two aerial modifications will be classified as excluded. Neither the supplement nor any numbered patch script is a new-build dependency. The local legacy repository was only read, never modified.

Compatibility inventory and runtime parity validation remain pending.
