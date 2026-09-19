#include "encounter_registry.h"
const RogueRecipe rogue_recipes[15] = {
    { "duel", "Duel", 0, 1, 0, 100, 100, 100, 100, 0, 2, 0, 1, 63 },
    { "juggernaut", "Juggernaut", 1, 1, 1, 110, 135, 85, 135, 0, 2, 3, 1, 63 },
    { "glass_cannon", "Glass Cannon", 1, 1, 2, 140, 75, 105, 100, 45, 2, 3, 1, 63 },
    { "speed_demon", "Speed Demon", 1, 1, 4, 105, 85, 130, 95, 0, 2, 3, 1, 63 },
    { "metal_sentinel", "Metal Sentinel", 1, 1, 8, 105, 120, 90, 100, 0, 2, 3, 1, 63 },
    { "tag_team", "Tag Team", 1, 2, 16, 90, 90, 100, 100, 0, 1, 3, 1, 63 },
    { "swarm", "Swarm", 1, 3, 32, 75, 75, 100, 85, 30, 1, 3, 1, 63 },
    { "specialist", "Specialist", 1, 1, 64, 110, 100, 105, 100, 0, 2, 3, 1, 63 },
    { "rival", "Rival", 1, 1, 128, 115, 110, 105, 100, 0, 2, 3, 1, 63 },
    { "champion", "Champion", 2, 1, 256, 120, 120, 110, 110, 0, 3, 3, 1, 63 },
    { "duo_boss", "Twin Champions", 2, 2, 512, 100, 105, 105, 100, 0, 2, 3, 1, 63 },
    { "commander", "Squad Commander", 2, 3, 1024, 85, 90, 100, 100, 0, 1, 3, 1, 63 },
    { "build_check", "Shadow Rival", 2, 1, 128, 125, 110, 110, 100, 0, 3, 3, 1, 63 },
    { "arena", "Arena Guardian", 2, 1, 2048, 115, 115, 110, 110, 0, 3, 3, 1, 3 },
    { "finale", "Act Finale", 2, 2, 4096, 110, 100, 110, 105, 0, 2, 3, 1, 63 },
};
