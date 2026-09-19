# Development log

## Initial inspection

Read the complete v6 execution specification and extracted its UI reference into ignored scratch storage. Located the supplied ISO and an existing Dolphin installation. No legacy working directory has been modified.

## WP0 and baseline build

Implemented read-only ISO/DOL validation, environment-over-config paths, tooling tests, pinned dependency metadata, and an automated baseline bootstrap. Built the exact upstream DOL, extracted retail files with gc_fst into ignored storage, assembled a separate ISO, emitted hashes and a symbol map, and rechecked input immutability. Found and documented the legacy oracle's missing untracked aerial preparation script.

## Runtime and core groundwork

Added named source hooks with exact anchor validation and duplicate-site rejection, regenerated decomp worktrees, generation-checked scene resources and a 32-event trace. The debug image builds. Added a pointer-free C run model, generated TOML registries, weighted encounters with recent-history suppression, deterministic reward/shop rerolls, sold-slot preservation and explicit big-endian serialization. Host scenario tests pass; native gameplay integration and emulator soak remain open.

## Special port and native scene integration

Ported 104 special definitions, preload, restoration, transforms and named source compatibility adapters without aerial runtime. Added compiled-ELF registry checks and migration coverage checks. Added a native mode/scene registration and provisional SIS progression, plus a debug-only real scene lifetime fixture. Dolphin completed 100 scene entries/exits and returned to its native menu with zero tracked scene resources.

Fixed DOL-growth/FST overlap with a checked disc-extent assembler and regression test. Fixed an implicit movie DMA alignment assumption exposed by executable relocation. Native match fixture and normal CSS entry remain under validation.
