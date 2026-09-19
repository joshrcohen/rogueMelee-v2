#include "score.h"
#include "balance.h"
unsigned RogueScore_Combat(unsigned native_score, unsigned tier, unsigned stacks, int won)
{
    unsigned earned = native_score;
    if (won) earned += tier == 2 ? ROGUE_SCORE_BOSS_CLEAR : tier == 1 ? ROGUE_SCORE_ELITE_CLEAR : ROGUE_SCORE_NORMAL_CLEAR;
    return earned + earned * stacks / 10;
}
