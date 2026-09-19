"""Additive mode/scene registration; all existing identifiers remain stable."""
EDITS = {
    'src/melee/gm/forward.h': [
        ('    /* 2D */ GM_COUNT,', '    GM_ROGUE,\n    GM_COUNT,'),
        ('    /* +2D */ GS_COUNT', '    GS_ROGUE,\n    GS_COUNT'),
    ],
    'src/melee/gm/gmscdata.c': [
        ('#include "gmscdata.h"', '#include "gmscdata.h"\n#include <melee/rogue/platform/melee/rogue_mode.h>'),
        ('static GameScene scenes[] = {', 'static GameScene scenes[] = {\n    { GS_ROGUE, RogueMode_Frame, RogueMode_Enter, RogueMode_Exit, NULL },'),
        ('static GameMode modes[] = {', 'static GameMode modes[] = {\n    { false, GM_ROGUE, RogueMode_Load, RogueMode_Unload, NULL, RogueMode_States },'),
    ],
}


def apply(clean, work):
    for name, edits in EDITS.items():
        source = (clean / name).read_text()
        for before, after in edits:
            if source.count(before) != 1:
                raise ValueError('Native mode anchor drift: ' + name)
            source = source.replace(before, after)
        (work / name).write_text(source)
