# Borrowed aerial development

## Regression baseline

Recorded before continuing aerial integration: **490f3f6314879ebb5dddd82032daead2e5b962d5** (`Record verified release reconstruction and native controller acceptance`). The passing v0.1.0 release was built from **df14c61**. Its reconstructed ISO SHA-256 is `86049e8d532af5c543a761f511817a74f24a106f9ec985ffbf7c0b60a59305c1`.

Existing special-move and full-run fixtures are regression gates; their historical results do not certify aerials. At baseline recording, no new aerial combinations were certified. The current campaign is published separately below. The previous freeze is not claimed fixed by this implementation.

## Required acceptance

- Independently equip five aerial slots; leave unequipped slots native.
- Keep purchases pointer-free and load donor assets only on a valid match heap before player control.
- Share the existing fighter snapshot/restoration boundary, with separate aerial action/landing dispatch.
- Publish all recipient × donor × slot statuses and runtime evidence; exclude unsupported entries from acquisition.
- Check mixed special/aerial/native transitions, interruptions, landing/L-cancel, stock and encounter changes, transformations, multi-fighter encounters and ordinary Melee restoration.
- Retain an independent aerial feature switch and test both debug and release builds.

## Ownership and resource design

The existing special installation sequence is factored into `Rogue_BorrowBegin`. One `RogueFighterState` owns either an active special or an active aerial. It snapshots/restores donor attributes, animation table/flags/count, fighter-variable union and the same existing callback range. Starting either borrowed type first restores the previous owner. Aerial state and landing dispatch live in `aerial_runtime.c`; aerials do not enter the special state-range machine. The original special preload loop, entry functions, registry and special QA fixture remain in place.

An encounter snapshots five pointer-free equipped IDs. Purchases/rerolls modify only run data; attack input reads that encounter snapshot. Native slots return to the engine's ordinary recipient dispatch. An equipped move without prepared donor data panics rather than silently claiming a native substitute succeeded.

Preparation runs at controlled-fighter creation on the valid match heap, before player control. A donor already prepared for specials uses its existing complete archive. A pure aerial donor loads its data/effect dependencies and only the selected attack and landing animation slices into private RAM, keeping the engine's shared animation records unchanged. Game & Watch registers its three aerial articles. A narrow encounter loader can use the engine's RAM-backed full-archive format when contiguous ARAM cannot fit a native/special archive. Fitting archives and ordinary Melee keep the original loader. No attack-input path calls the blocking file loader.

Animation tables/slices and overflow archives carry match-generation accounting. Fighter/encounter teardown restores the native owner, releases every allocation and clears stored pointers; no match pointer is persisted in run data or carried into a shop. Changing donors becomes effective only when the next encounter prepares its snapshot. Native transformation transfers the shared owner context between existing forms; the next borrowed entry snapshots that form's native data.

## Move behavior

Common aerials use donor animation commands and the existing bone-remapping facade. Recipient movement attributes stay native. Landing lag comes from the donor, then the existing Soft Landing bonus, then native L-cancel reduction. Game & Watch neutral/back/up retain their custom article/landing states and retail L-cancel exception; its up-air uses back-air lag as retail does. Link/Young Link down-air installs their real native bounce callbacks. Game & Watch's late article removers use the shared variable bank even after recipient restoration.

All five slots are offered independently by rewards, shops and their existing rerolls. Cards name donor/slot, replacement and shop price; the build panel lists each slot. Identical donor/recipient offers are omitted. Version 4 snapshots add five IDs and reject older versions; the offer-pool expansion intentionally changes deterministic reward output and the golden hash to `6445a236`.

## Evidence and limits

The complete [compatibility table](compatibility/aerials.md) distinguishes implementation from exact runtime coverage. Passing native campaign inputs and compressed full logs are archived in `evidence/aerials/current`; result JSONs retain executable/image/log hashes, profiles and wall time. `qa/aerials-validation.json` records the accepted campaign. Historical new-feature failures and repaired scenarios remain in [the investigation](aerials-investigation.md).

Controlled fixtures test lifecycles and selected adapter behavior, not exhaustive visual/collision fidelity across all 3380 combinations. Ice Climbers coverage applies to the leader. The prior unspecified legacy freeze remains undiagnosed. `ROGUE_ENABLE_AERIALS=0` / `build --disable-aerials` independently disables aerial acquisition, dispatch and the added archive fallback, while preserving specials.

Final implementation source commit: `5ec52a365c75a7846470993c2c37ba6202f877c7`. Both debug and release passed the 130-case donor matrix and 130-encounter stress schedule (520 total fixture encounters, 255 unique exact combinations). The unchanged special fixture passed all 2704 pairs, with 104 additional extended cases. Both the enabled full-run regression and aerial-disabled build passed 100 native match transitions. The verified v0.2.0 patch and reconstructed controller acceptance are recorded in `qa/aerials-release-reconstruction.json`; later documentation commits do not change the release executable.
