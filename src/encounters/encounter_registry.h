#ifndef ROGUE_ENCOUNTER_REGISTRY_H
#define ROGUE_ENCOUNTER_REGISTRY_H
typedef struct RogueRecipe {
    const char* key;
    const char* name;
    const char* rule;
    unsigned tier, enemies, tags, damage, defense, speed, scale, percent;
    unsigned stocks, cooldown, weight, stage_mask;
    unsigned roster[3];
} RogueRecipe;
extern const RogueRecipe rogue_recipes[15];
#endif
