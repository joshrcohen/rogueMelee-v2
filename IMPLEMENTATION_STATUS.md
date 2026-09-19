# Implementation status

Read all 35 sections, all tables and the embedded progression reference from the supplied v6 DOCX on 2026-09-19. The workspace initially contained only `.iso/`. Work remains active; this is not a release certification.

| Work package | Status and evidence |
| --- | --- |
| WP0 repository, dependencies, image validation | PASS: pinned dependency locks, tooling checks, original ISO MD5 and DOL SHA1 verified |
| WP1 upstream baseline | PASS: all 1126 upstream objects and exact retail DOL; separately assembled image boots in Dolphin 2606a |
| WP2 platform/runtime spine | Partial: additive mode, named hooks, scene/match generations and ownership guards; clean-1.02 capabilities are detected once at scene entry and cached; unsupported profiles leave the entry shortcut inactive |
| WP3 deterministic run core | Host tests PASS: 64-bit seeds, four isolated streams, 100 complete runs twice, serialization v3, golden snapshot `4a55e066` |
| WP4 borrowed specials | Partial: 104 entries compile; all Captain Falcon cases pass. Full 26 x 104 matrix is running; extended interruption/respawn scenarios remain open |
| WP5 playable run lifecycle | Native 100-match soak PASS (99 wins, final loss). Normal menu/CSS/reward/route/combat/natural-loss controller flow PASS. Targeted passive behavior checks remain open |
| WP6 native progression UI | 100 mixed scene lifetimes PASS; controller build/reroll/selection flow PASS. Header spacing corrected and visually verified; final reward/shop visual review remains open |
| WP7 economy/rerolls | Deterministic core tests PASS: separate reward/shop streams, escalating prices, sold-slot preservation, purchase/rest/history behavior |
| WP8 encounters | 8 elite and 6 boss families implemented with curated rosters, visible rules, modifier composition and build-sensitive rivals; host distribution tests pass; final native recipe review pending |
| WP9 diagnostics/soak | 100 scene and 100 match gates PASS; crash context and lifecycle traces implemented. 104 native damage-interruption and blast-zone death/respawn cases PASS on Captain Falcon; full matrix, ledge/grab/pause coverage remain open |
| WP10 release reconstruction | Pinned xdelta tool built and synthetic roundtrip tested. Real release build, patch reconstruction and package validation remain open |

All 21 automated tests pass. Native evidence is recorded with exact executable/image/log hashes in `docs/qa/`; these are historical tested builds, not certification of every later source change.

The 100-match evidence is `docs/qa/100-matches.json`; all borrowed contexts were released before match generation advanced. The normal controller fixture and its limitations are recorded in `docs/qa/normal-controller-flow.json`.

The special matrix first passed 1,252 recipient/move pairs, then exposed Peach's native float flag overwriting a borrowed Fox Blaster item pointer. Native grounded-state updates now target Peach's saved native state. The isolated failing pair passes. The next segment reached 1,504 successful pairs, then found Charge Shot storing a donor hand-bone index on Ice Climbers. Remapping the persistent attachment at creation fixes the isolated case; the remaining 1,200 pairs are being tested. Earlier fixes cover Hand Slap's absent airborne attack and returning Link-family boomerang context/bone handling. Extended hitstun, death/respawn, ledge, grab, pause and transform coverage is still required.

All 24 passive definitions have initial native implementations. General match stability does not substitute for targeted behavior validation. No aerial swapping is enabled.

The UI uses authored JOBJ geometry and the user's retail font/portrait assets. No retail art or game image is committed. SIS storage is bounded and reused; scene exits report zero owned resources in the completed lifecycle gates.

Baseline DOL SHA1: `08e0bf20134dfcb260699671004527b2d6bb1a45`.
Baseline ISO SHA256: `0de05981a34156b9cedcef73c73d4244ac05cf6149ab3c9cfed917698819e464`.
Immutable input MD5: `0e63d4223b01d9aba596259dc155a174`.

Migration oracle preparation and its locally supplied missing supplement are documented in `docs/migration/specials-baseline.md`. Generated decomp worktrees and retail data remain ignored build inputs.

Additional matrix fix: Jigglypuff's native accessory callbacks accessed the donor variable union, interpreting Mario's cape pointer as her hat. Saved native bank access fixes isolated case 1561. The full matrix has resumed from there. Thumb-joint lookups for cape attachments now use the validated recipient fallback.

Developer seed/scene/encounter/special/recipient options and targeted asset/hook/DOL build modes are implemented. The native developer fixture passed with a full-width seed, Mario recipient, Fox Reflector and Juggernaut encounter (`docs/qa/developer-launch.json`). The extended fixture's precise evidence is `docs/qa/extended-0-104.json`.

Controller-driven native pause/unpause passed with an equipped borrowed special, followed by interruption, respawn and teardown (`docs/qa/pause-controller.json`). The donor animation was inactive at the pause point; this is not evidence of pausing every move mid-animation. Frame-driven fixture and specialist-pressure timers now stop while native pause flags are set.
