# Implementation status

The entire supplied v6 DOCX was read, including all 35 sections, tables and the embedded progression reference. This is a fresh repository; the legacy project was used only as a pinned read-only special-move migration oracle. The source ISO remains unchanged and ignored.

| Work package | Result | Evidence |
| --- | --- | --- |
| WP0 fresh repository and image validation | PASS | Fresh Git history; private GitHub remote; pinned dependencies; read-only ISO/DOL validation |
| WP1 reproducible upstream baseline | PASS | Exact retail DOL, 1126 upstream objects, separately assembled bootable image |
| WP2 platform/runtime | PASS | Named exact-anchor hooks, ownership/conflict tests, cached clean-1.02 capabilities, native VS/Classic smoke tests |
| WP3 deterministic core | PASS | 100 complete runs twice, isolated RNG streams, big-endian pointer-free serialization; golden 866924df |
| WP4 borrowed specials | PASS | 104 compiled entries; 1225 inventoried legacy hunks with zero unclassified fixes; all 2704 recipient/move pairs pass ground/air lifecycle checks |
| WP5 playable loop | PASS | Normal controller menu/CSS/reward/route/combat/loss; 100-match soak with native Stage Clear and score integration; 20 native passive assertions plus economy/rest host checks |
| WP6 native progression UI | PASS | Authored JOBJ panels and retail portraits/fonts; 100 reward/shop/route/rest/win/loss lifetimes; reviewed score, shop, rest and combat status layouts |
| WP7 economy/rerolls | PASS | Escalating costs, isolated reward/shop RNG, sold-slot preservation, purchases, healing and run history tested |
| WP8 encounters | PASS | 8 elite and 6 boss families; curated rosters/stages, weights, cooldowns, act/floor eligibility and compatible threat budgets; 4500 budget cases and 1000 family samples |
| WP9 diagnostics/lifecycle | PASS | 104 hitstun/ledge/grab/death/respawn cases; two-way borrowed transform; controller pause/unpause; debug traces, build/seed context and compact combat indicators |
| WP10 release reconstruction | PASS | 940519-byte xdelta reconstructs exact release SHA256; reconstructed image passes normal controller flow in a separate profile |

All 21 automated tests pass. Native evidence and exact executable/image/log hashes are in `docs/qa`. These are historical tested builds, not a claim that every later source change was rerun through every test. The full matrix combines successfully completed intervals around three repaired recipient-specific defects; see `specials-full-matrix.json`. Extended interruptions use Captain Falcon; pause was tested with an equipped special outside its active animation. Natural borrowed transformation completion is recorded separately.

Native Stage Clear and combat HUD ownership passed 100 consecutive matches with zero tracked resources at scene/match teardown. The latest UI lifetime fixture covers six screen phases. Controlled passive assertions call native damage, shield, collision and KO paths; they do not replace natural-controller coverage of every passive. Known intentional limitations are listed in `KNOWN_ISSUES.md`.

Original input MD5: `0e63d4223b01d9aba596259dc155a174`. Original DOL SHA1: `08e0bf20134dfcb260699671004527b2d6bb1a45`. Input SHA256: `0de05981a34156b9cedcef73c73d4244ac05cf6149ab3c9cfed917698819e464`.

Repository: https://github.com/joshrcohen/rogueMelee-v2 (private). No legacy history, retail game image, extracted retail asset or compiler binary is tracked. Aerial swapping remains disabled.

Release executable source commit: `df14c618168a62acaf310a8d300af525b5118869`. Release/reconstructed image SHA256: `86049e8d532af5c543a761f511817a74f24a106f9ec985ffbf7c0b60a59305c1`. Patch SHA256: `d31cce83ea5e6ca7b632106777359836215fb251c1fd8e177acb5aab08e48d89`. The patch and manifest are in `dist/`; `docs/qa/release-reconstruction.json` records the separate-profile controller check. Subsequent commits only record delivery evidence/documentation.

| Final delivery gate | Result |
| --- | --- |
| Source, debug build, host tests and native acceptance fixtures | PASS |
| Release build, reconstructed patch and release controller smoke | PASS |
| Clean committed and pushed delivery | PASS |
