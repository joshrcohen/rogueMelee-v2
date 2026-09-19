# Aerial freeze investigations

The v6 spec reports an eventual mid-fight freeze in the legacy aerial runtime. This workspace has not reproduced or diagnosed that freeze.

The pinned implementation swaps fighter animation tables `x24`, `x28` and count `x58C`, owns donor load flags beside borrowed-special state, and prepares donor resources over match frames. Investigate table pointers, match heaps, ftData/effect banks and cleanup timing across interruption, landing, KO, respawn, transformation, pause, match exit and repeated scene entry. These are hypotheses, not an established root cause.

That legacy freeze remains **unreproduced and undiagnosed**. Passing tests of the new implementation do not establish its cause or prove it fixed.

## Reproduced failures in the new implementation

Two distinct failures were reproduced during the new aerial work. Before/after logs and executable hashes are preserved under `docs/evidence/aerials/`.

1. **Game & Watch neutral-air cleanup stalled on a non-Game & Watch recipient.** The landing path can call `ftGw_Init_OnDamage` after the motion transition has restored the recipient's variable union. That routine also invokes grounded article removers; their unadapted accesses interpreted the recipient union as Game & Watch item pointers. All those article helpers now use the shared source variable bank. The five Game & Watch aerial lifecycle cases passed afterward. Reproduce the targeted scenario with `soak --scenario aerials --start 15 --iterations 1 --lifecycle`.
2. **Whole donor animation archives exhausted ARAM.** A five-aerial/four-special/three-opponent loadout failed in `memp_kouho`, and an ordinary 100-match fixture failed at match 24. Pure aerial donors now load only equipped attack/landing animation slices into match-owned RAM. When a complete native or special archive cannot fit contiguous ARAM, encounter loading uses the engine's existing RAM-backed animation path. The stock allocator and fitting archive path remain unchanged. The targeted heavy encounter and the 100-match fixture passed afterward. Reproduce the heavy scenario with `soak --scenario aerials --iterations 1 --stress --lifecycle`.

The stress fixture retains both targeted conditions, generation checks, zero-resource assertions at shops and encounter teardown, repeated equipment replacement and stocks, and native/borrowed transformations. Full raw native logs distinguish these observed failures from the older, unspecified mid-fight freeze.
