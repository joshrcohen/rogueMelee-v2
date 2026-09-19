#include "aerial_catalog.h"
const RogueAerialDef* RogueAerial_Find(unsigned id)
{
    return id && id <= ROGUE_AERIALS ? &rogue_aerials[id-1] : 0;
}
