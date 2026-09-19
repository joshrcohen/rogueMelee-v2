# rogueMelee v0.2.0

A fresh, native Melee NTSC-U 1.02 roguelike: 15 floors across three acts, 104 borrowed specials, 130 aerial choices across five independent slots, 24 passives, deterministic rewards and shops, and curated elite/boss encounters.

Press GameCube **X** on the main menu to enter. The original game modes remain available. See [GETTING_STARTED.md](GETTING_STARTED.md) for build and play instructions, [IMPLEMENTATION_STATUS.md](IMPLEMENTATION_STATUS.md) for evidence, and [KNOWN_ISSUES.md](KNOWN_ISSUES.md) for tested scope.

The user supplies the clean ISO. No retail game image, extracted artwork, compiler binary, or legacy Git history is committed. Generated outputs and caches stay ignored. Release distribution uses a verified xdelta patch. Aerials can be disabled independently with `build --disable-aerials`; see the [compatibility report](docs/compatibility/aerials.md) for the exact tested subset and remaining untested combinations.
