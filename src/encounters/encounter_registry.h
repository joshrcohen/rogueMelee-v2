#ifndef ROGUE_ENCOUNTER_REGISTRY_H
#define ROGUE_ENCOUNTER_REGISTRY_H
typedef struct RogueRecipe {
    const char* key;
    const char* name;
    const char* rule;
    unsigned tier, enemies, tags, damage, defense, speed, scale, percent;
    unsigned stocks, cooldown, weight, stage_mask;
    unsigned roster[3];
    unsigned min_act, max_act, min_floor, max_floor, threat_cost;
    unsigned mutation_mask, incompatible_tags;
} RogueRecipe;
extern const RogueRecipe rogue_recipes[15];
#endif
