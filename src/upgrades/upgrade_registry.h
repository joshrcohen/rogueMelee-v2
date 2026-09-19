#ifndef ROGUE_UPGRADE_REGISTRY_H
#define ROGUE_UPGRADE_REGISTRY_H
typedef struct RogueUpgradeDef {
    const char* key;
    const char* name;
    const char* description;
    unsigned price, max_stacks, stat, amount;
} RogueUpgradeDef;
extern const RogueUpgradeDef rogue_upgrades[24];
#endif
