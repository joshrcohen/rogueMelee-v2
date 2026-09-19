# Deferred aerial investigation

The v6 spec reports an eventual mid-fight freeze in the legacy aerial runtime. This workspace has not reproduced or diagnosed that freeze.

The pinned implementation swaps fighter animation tables `x24`, `x28` and count `x58C`, owns donor load flags beside borrowed-special state, and prepares donor resources over match frames. Investigate table pointers, match heaps, ftData/effect banks and cleanup timing across interruption, landing, KO, respawn, transformation, pause, match exit and repeated scene entry. These are hypotheses, not an established root cause.

No aerial runtime or offer is included in this repository. Reintroduction requires a deterministic legacy reproduction, generation/heap ownership instrumentation and a separate long-session test campaign after the run and borrowed-special gates pass.
