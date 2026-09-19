# Implementation status

## v0.2.0 borrowed aerials

Regression baseline recorded before aerial work: `490f3f6314879ebb5dddd82032daead2e5b962d5`. The original v0.1.0 release and its evidence remain intact. The user's later aerial scope supersedes the v6 document's aerial deferral.

Five aerial slots are independently equipped through existing rewards, shops and rerolls. Unselected slots remain native; equipment takes effect at the next encounter. Cards show donor, slot, replacement, next-fight timing and shop price or free reward choice. Shop operations keep only IDs, while encounter preparation loads donor resources before control. Aerials and specials share one fighter ownership/restoration boundary; aerial action/landing dispatch remains separate. The existing special entry registry, preload loop and native special QA fixture are preserved.

The complete [compatibility report](docs/compatibility/aerials.md) enumerates 3380 playable recipient/donor/slot combinations: 255 runtime-tested, 3125 untested. Implementation is not treated as runtime certification. The 130 identical recipient/donor choices are omitted from offers; non-playable forms and partner borrowing are unsupported. Dedicated Game & Watch article and Link/Young Link down-air adapters have explicit native assertions. Visual/hitbox/stage coverage remains limited to the recorded checks.

| Current acceptance | Evidence and exact scope |
| --- | --- |
| Automated host/tooling/integration tests | 24 pass; includes all 130 aerial reward/shop choices, independent replacement, rerolls, serialization and enabled/disabled feature builds |
| Existing special regression | All 2704 recipient/special pairs, unchanged fixture, Null renderer for logic coverage; separate 104 extended interruption cases rendered in debug |
| Existing full-run regression | 100 native match transitions rendered in debug; existing core complete-run tests retained, with the intentional version-4/offer-pool golden update |
| Aerial donor lifecycle matrix | 130 cases in debug and 130 in release, rendered; donor landing/L-cancel rates, mixed ownership, damage, linked grabs, ledges, death/respawn |
| Mixed encounter stress | 130 debug and 130 release encounters passed, rendered; roughly 77 minutes of scripted combat per campaign before loading/menu time. Five aerials, four specials, three opponents, repeated stocks and equipment changes, native/borrowed transformations and zero-resource teardown |
| Independent disable switch | Enabled/disabled host tests plus 100 native match transitions with aerials disabled |
| UI and real controller flow | Purchase, five-slot build view, sold-slot preservation on reroll, free reward labels, next-encounter preloads, actual aerial/special button input and natural run end |
| Ordinary Melee restoration | Borrowed encounter → run end → native VS match/results in one session; separate QA-mode-zero VS and Classic gameplay smoke checks |
| Shipping release controller flow | QA-mode-zero release boots through normal menu/CSS/reward/route/combat/natural loss; exact executable hash in `docs/qa/aerials-release-controller.json` |

Archived current native results and compressed full logs are under `docs/evidence/aerials/current`. Recheck them with `py -3 tools/verify_aerial_campaign.py`; this publishes the campaign gate and hashes every compatibility artifact. UI/ordinary-mode logs, movies, screenshots and build hashes are also archived. The final release patch goes in `dist/v0.2.0/`; its reconstruction evidence is recorded after packaging.

The earlier unspecified legacy freeze remains unreproduced and undiagnosed. Two separate new-feature failures—late Game & Watch article cleanup and animation-heap exhaustion—were reproduced, repaired and preserved as targeted regressions. See [the investigation](docs/aerials-investigation.md), [ownership design](docs/AERIAL_DEVELOPMENT.md), and [remaining limitations](KNOWN_ISSUES.md). This campaign is Dolphin validation, not hardware, Slippi or exhaustive matchup certification.

## Historical v0.1.0 baseline

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

Repository: https://github.com/joshrcohen/rogueMelee-v2 (private). No legacy history, retail game image, extracted retail asset or compiler binary is tracked. Aerial swapping was disabled in this baseline.

Release executable source commit: `df14c618168a62acaf310a8d300af525b5118869`. Release/reconstructed image SHA256: `86049e8d532af5c543a761f511817a74f24a106f9ec985ffbf7c0b60a59305c1`. Patch SHA256: `d31cce83ea5e6ca7b632106777359836215fb251c1fd8e177acb5aab08e48d89`. The patch and manifest are in `dist/`; `docs/qa/release-reconstruction.json` records the separate-profile controller check. Subsequent commits only record delivery evidence/documentation.

| Final delivery gate | Result |
| --- | --- |
| Source, debug build, host tests and native acceptance fixtures | PASS |
| Release build, reconstructed patch and release controller smoke | PASS |
| Clean committed and pushed delivery | PASS |
