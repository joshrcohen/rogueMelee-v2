#ifndef ROGUE_AERIAL_CATALOG_H
#define ROGUE_AERIAL_CATALOG_H
#define ROGUE_AERIAL_SLOTS 5
#define ROGUE_AERIALS 130
typedef struct RogueAerialDef {
    unsigned id, character, donor, slot, price;
    const char* key;
    const char* name;
} RogueAerialDef;
extern const RogueAerialDef rogue_aerials[ROGUE_AERIALS];
const RogueAerialDef* RogueAerial_Find(unsigned id);
#endif
