#include "encounter_registry.h"
const RogueRecipe rogue_recipes[15] = {
    { "duel", "Duel", "STANDARD DUEL", 0, 1, 0, 100, 100, 100, 100, 0, 2, 0, 1, 63, { 255, 255, 255 }, 1, 3, 0, 14, 2, 7, 0 },
    { "juggernaut", "Juggernaut", "GIANT / HEAVY / SLOW", 1, 1, 1, 110, 135, 85, 135, 0, 2, 3, 1, 63, { 1, 5, 25 }, 1, 3, 0, 14, 6, 3, 6 },
    { "glass_cannon", "Glass Cannon", "HIGH POWER / FRAGILE", 1, 1, 2, 140, 75, 105, 100, 45, 2, 3, 1, 63, { 13, 24, 20 }, 1, 3, 0, 14, 6, 5, 0 },
    { "speed_demon", "Speed Demon", "FAST / LIGHTWEIGHT", 1, 1, 4, 105, 85, 130, 95, 0, 2, 3, 1, 63, { 2, 0, 19 }, 1, 3, 0, 14, 6, 5, 9 },
    { "metal_sentinel", "Metal Sentinel", "METAL BODY", 1, 1, 8, 105, 120, 90, 100, 0, 2, 3, 1, 63, { 8, 6, 16 }, 1, 3, 0, 14, 6, 3, 0 },
    { "tag_team", "Tag Team", "COMPLEMENTARY DUO", 1, 2, 16, 90, 90, 100, 100, 0, 1, 3, 1, 63, { 2, 20, 13 }, 1, 3, 0, 14, 6, 7, 0 },
    { "swarm", "Swarm", "THREE LIGHT OPPONENTS", 1, 3, 32, 75, 75, 100, 85, 30, 1, 3, 1, 63, { 24, 7, 4 }, 1, 3, 0, 14, 6, 7, 0 },
    { "specialist", "Specialist", "PROJECTILE PRESSURE", 1, 1, 64, 110, 100, 105, 100, 0, 2, 3, 1, 63, { 16, 6, 20 }, 1, 3, 0, 14, 6, 7, 0 },
    { "rival", "Rival", "YOUR FIGHTER / BUILD COUNTER", 1, 1, 128, 115, 110, 105, 100, 0, 2, 3, 1, 63, { 255, 255, 255 }, 1, 3, 0, 14, 6, 7, 0 },
    { "champion", "Champion", "CURATED CHAMPION / 3 STOCKS", 2, 1, 256, 120, 120, 110, 110, 0, 3, 3, 1, 63, { 25, 9, 5 }, 1, 3, 0, 14, 10, 7, 0 },
    { "duo_boss", "Twin Champions", "TWIN CHAMPIONS", 2, 2, 512, 100, 105, 105, 100, 0, 2, 3, 1, 63, { 8, 7, 23 }, 1, 3, 0, 14, 10, 7, 0 },
    { "commander", "Squad Commander", "STRONG LEADER / TWO SUPPORTS", 2, 3, 1024, 85, 90, 100, 100, 0, 1, 3, 1, 63, { 25, 2, 20 }, 1, 3, 0, 14, 10, 7, 0 },
    { "build_check", "Shadow Rival", "DOMINANT BUILD COUNTER", 2, 1, 128, 125, 110, 110, 100, 0, 3, 3, 1, 63, { 255, 255, 255 }, 1, 3, 0, 14, 10, 7, 0 },
    { "arena", "Arena Guardian", "CURATED FLAT ARENA", 2, 1, 2048, 115, 115, 110, 110, 0, 3, 3, 1, 3, { 16, 6, 10 }, 1, 3, 0, 14, 10, 7, 0 },
    { "finale", "Act Finale", "ACT-SPECIFIC DUO", 2, 2, 4096, 110, 100, 110, 105, 0, 2, 3, 1, 63, { 9, 23, 25 }, 1, 3, 0, 14, 10, 7, 0 },
};
