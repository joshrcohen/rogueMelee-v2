# Third party notices

Retail Melee data is supplied locally by the user and is not redistributed.

The pinned doldecomp/melee source is a local build/reference dependency, not redistributed in this repository. Legacy joshrcohen/rogueMelee is an explicitly requested migration source for borrowed specials only. Its history and patch pipeline are not imported.

Exact revisions are recorded in deps/manifest.toml and deps/lock.json.

- gc_fst and hgecko, Alexander Harrison: MIT OR Apache-2.0.
- cdat, Alexander Harrison: Apache-2.0.
- xdelta3 3.1.0, Joshua MacDonald: GPL-2.0-or-later. Built from https://github.com/jmacd/xdelta at commit 4b4aed71a959fe11852e45242bb6524be85d3709. Its executable and source are local tooling, not included in the patch package. The source license is xdelta3/COPYING in that checkout. Generated VCDIFF patches do not contain xdelta program code.

The repository and release package do not redistribute compiler binaries, Melee source, extracted retail assets, or a full retail image. Native portrait/font assets are loaded from the user's disc image at runtime. RogueUi.dat is generated from original project-authored geometry.
