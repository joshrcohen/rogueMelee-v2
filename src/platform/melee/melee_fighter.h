#ifndef ROGUE_MELEE_FIGHTER_H
#define ROGUE_MELEE_FIGHTER_H
#include <melee/ft/forward.h>
bool Rogue_IsRunPlayer(const Fighter* fighter);
void RogueFighter_Created(Fighter* fighter);
float RogueFighter_AdjustDamage(Fighter* fighter, float damage);
#endif
