# Development log

## Initial inspection

Read the complete v6 execution specification and extracted its UI reference into ignored scratch storage. Located the supplied ISO and an existing Dolphin installation. No legacy working directory has been modified.

## WP0 and baseline build

Implemented read-only ISO/DOL validation, environment-over-config paths, tooling tests, pinned dependency metadata, and an automated baseline bootstrap. Built the exact upstream DOL, extracted retail files with gc_fst into ignored storage, assembled a separate ISO, emitted hashes and a symbol map, and rechecked input immutability. Found and documented the legacy oracle's missing untracked aerial preparation script.
