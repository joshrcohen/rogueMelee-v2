#include "special_catalog.h"
const RogueSpecialDef* RogueSpecial_Find(unsigned id)
{
    unsigned i;
    for (i = 0; i < ROGUE_SPECIALS; ++i)
        if (rogue_specials[i].id == id) return &rogue_specials[i];
    return 0;
}
