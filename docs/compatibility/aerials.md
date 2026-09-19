# Borrowed aerial compatibility

All 26 playable recipients × 26 playable donors × 5 aerial slots are enumerated in [CSV](aerials.csv) and [JSON](aerials.json). Implementation and runtime validation are separate fields. Each tested row links to archived native evidence and executable/log hashes.

Implemented: **3380**. Runtime-tested: **255**. Failing in the accepted campaign: **0**. Untested: **3125**.

“Implemented” means the generic runtime or named adapter exists; it is not a runtime pass. “Runtime-tested” means the listed controlled lifecycle assertions passed on the recorded executable. “Failing” means an accepted campaign case failed. “Untested” means no accepted full lifecycle case for that exact pair/slot. “Unsupported” is reserved for excluded configurations; none of these 3380 playable combinations is currently classified unsupported. Independent Nana, non-playable boss forms, partner borrowing and other game revisions are outside this table and unsupported.

The 130 identical recipient/donor choices are intentionally excluded from offers: an unequipped slot already provides that native move. Other implemented choices remain eligible, including rows explicitly labeled untested. There is no native fallback reported as a successful borrowed entry.

Coverage checks entry, animation ownership, donor landing rates with/without L-cancel, mixed special transitions, damage, linked grabs, ledges, death and respawn. Stress additionally covers five slots, four specials, three opponents, repeated stocks/equipment changes and transformations. These checks do not certify every visual effect, hitbox, collision, stage or long-duration matchup. Game & Watch article and Link/Young Link bounce adapter assertions are identified per evidence record. Ice Climbers rows cover the leader.

| Recipient | Runtime-tested | Failing | Untested |
| --- | ---: | ---: | ---: |
| captain_falcon | 130 | 0 | 0 |
| donkey_kong | 5 | 0 | 125 |
| fox | 5 | 0 | 125 |
| game_and_watch | 5 | 0 | 125 |
| kirby | 5 | 0 | 125 |
| bowser | 5 | 0 | 125 |
| link | 5 | 0 | 125 |
| luigi | 5 | 0 | 125 |
| mario | 5 | 0 | 125 |
| marth | 5 | 0 | 125 |
| mewtwo | 5 | 0 | 125 |
| ness | 5 | 0 | 125 |
| peach | 5 | 0 | 125 |
| pikachu | 5 | 0 | 125 |
| ice_climbers | 5 | 0 | 125 |
| jigglypuff | 5 | 0 | 125 |
| samus | 5 | 0 | 125 |
| yoshi | 5 | 0 | 125 |
| zelda | 5 | 0 | 125 |
| sheik | 5 | 0 | 125 |
| falco | 5 | 0 | 125 |
| young_link | 5 | 0 | 125 |
| dr_mario | 5 | 0 | 125 |
| roy | 5 | 0 | 125 |
| pichu | 5 | 0 | 125 |
| ganondorf | 5 | 0 | 125 |

Regenerate from the archived current campaign: `py -3 tools/aerial_report.py`. Historical failures and their specific repairs are documented in [the investigation](../aerials-investigation.md).
