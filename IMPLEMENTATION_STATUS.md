# Implementation status

## Execution baseline

Read all 35 sections, all tables and the embedded progression reference from the supplied v6 DOCX on 2026-09-19. Workspace originally contained only `.iso/`.

| Work package | Status | Evidence |
| --- | --- | --- |
| WP0 repository, dependencies and image validation | PASS | `py -3 tools/rogue.py doctor`; `py -3 tools/rogue.py test --suite tooling` (4 tests); `py -3 tools/rogue.py verify-image` (both fixed hashes match) |
| WP1 upstream baseline and no-op ISO | PASS | `py -3 tools/rogue.py bootstrap` exit 0; upstream 1126/1126 objects and DOL hash check pass; Dolphin 2606a renders native memory-card startup prompt |
| WP2 hook/platform/runtime spine | Partial, gate pending | Debug source-overlay ISO builds; 5 named hooks; 100 real progression scene lifetimes completed in Dolphin with zero tracked resources and return to stock main menu. Complete facade and broader shop/results lifetime coverage remain pending |
| WP3 deterministic run core | Host tests PASS, integration pending | `py -3 tools/rogue.py test --suite core`: 100 full runs twice, 50 reroll-isolation seeds, 1000 encounters, serialization roundtrip, fixed snapshot `0ae8dc69` |
| WP4 borrowed-special migration | Compiles; runtime gate pending | 104 compiled registry entries verified; named compatibility adapters in 96 source files; three specials tests pass |
| WP5 playable run lifecycle | In progress | Additive native mode, CSS, progression and team-match setup compile; emulator match lifecycle fixture under validation |
| WP6 native progression UI | Pending | |
| WP7 economy and rerolls | Pending | |
| WP8 elite and boss recipes | Pending | |
| WP9 diagnostics and soak | Pending | |
| WP10 release reconstruction | Pending | |

Baseline DOL SHA1: `08e0bf20134dfcb260699671004527b2d6bb1a45`.
Baseline output ISO SHA256: `0de05981a34156b9cedcef73c73d4244ac05cf6149ab3c9cfed917698819e464`.
Input MD5 was rechecked after assembly and remains `0e63d4223b01d9aba596259dc155a174`.

`gc_fst` and `hgecko` build with committed Cargo locks; `cdat` builds with MSVC and explicit little-endian defines. No standalone devkitPPC compiler is on PATH; the decomp supplies its pinned MWCC and GNU binutils. Emulator and release gates are not yet passed.

Migration oracle preparation succeeded after supplying the pinned script's missing aerial supplement from the local legacy archive; see docs/migration/specials-baseline.md. Special registry, preload, state restoration, transforms and compatibility adapters are now ported; runtime certification remains pending.

The run core currently has 24 upgrade definitions, 8 elite recipes, 6 boss recipes, 15 floors and four isolated RNG streams. Upgrade combat effects, the native scene loop, borrowed-special offers and the full UI are not connected yet. A separate native scene lifetime test now exists (`soak`); combat, broader scene coverage and long-run stability gates remain open.
