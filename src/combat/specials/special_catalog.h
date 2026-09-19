#ifndef ROGUE_SPECIAL_CATALOG_H
#define ROGUE_SPECIAL_CATALOG_H
#define ROGUE_SPECIALS 104
/* Portable IDs and metadata. Engine pointers remain in the platform registry. */
typedef struct RogueSpecialDef {
    unsigned id, character, donor, slot, price;
    const char* key;
    const char* name;
} RogueSpecialDef;
extern const RogueSpecialDef rogue_specials[ROGUE_SPECIALS];
const RogueSpecialDef* RogueSpecial_Find(unsigned id);
#endif
