# Known issues and scope

- The full 26 x 104 ground/air lifecycle matrix passes. It is not exhaustive visual, collision, stage or multiplayer matchup certification. Extended interruption coverage uses Captain Falcon.
- Donkey Kong Hand Slap has no native airborne attack; airborne input returns to native fall.
- Borrowed Zelda/Sheik transformation swaps equipped donor-kit slots while preserving the recipient fighter. The two-way animation cycle is tested.
- Sheik uses the retail Zelda CSS portrait with an explicit Sheik name; retail CSS does not provide a separate Sheik selection portrait.
- Strong Grip currently boosts ordinary native throws; special grabs and cargo throws are outside its bonus. This is reflected in its offer description.
- Borrowed aerials use donor attack/landing animations, commands and landing lag on the recipient skeleton. Full visual, hitbox, collision and stage coverage for every recipient/donor pair is not claimed. The complete implemented/tested/failing/untested matrix is in `docs/compatibility/aerials.md`, `.csv` and `.json`.
- Stress rotates all aerial donors through five equipped slots with a fixed four-special loadout and three opponents. It does not exhaust every simultaneous special/aerial loadout or prove an unlimited memory budget. Validation used Dolphin 2606a; real console behavior is untested.
- Game & Watch's article aerials retain retail landing behavior: neutral/back/up do not use ordinary L-cancel reduction, and up-air uses the donor's back-air landing lag. Link and Young Link down-air use their donor bounce adapter. Recipient movement attributes remain native.
- Ice Climbers equipment belongs to the controlled leader; the partner keeps native aerials. Non-playable recipient/donor forms (including independent Nana, Master Hand and Giga Bowser) are unsupported and never offered. Boss encounters use ordinary playable fighter lifecycles.
- The legacy eventual aerial freeze remains unreproduced; no claim is made that its cause was found or fixed. Separate new-feature cleanup and allocation failures were reproduced, repaired and retained as regression scenarios in `docs/aerials-investigation.md`.
- Deterministic snapshots use version 4 with five aerial IDs. Version 3 snapshots are rejected; this does not add a memory-card run-save feature. Expanding the offer pool intentionally changes seeded rewards and the golden snapshot hash.
- Supported image: clean NTSC-U 1.02 only. Modified images are rejected rather than combined with unknown patches. Slippi compatibility is not claimed.
- Parallel MWCC compilation intermittently produced an upstream `STATIC_ASSERT` parse error on this host. The serialized build (`[build] jobs = 1`) passed unchanged source and reproduced the controller-tested executable. This is recorded separately from gameplay failures.

Release reconstruction and native delivery gates passed; exact tested scope is recorded in IMPLEMENTATION_STATUS.md and docs/qa.
