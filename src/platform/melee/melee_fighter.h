#ifndef ROGUE_MELEE_FIGHTER_H
#define ROGUE_MELEE_FIGHTER_H
#include <melee/ft/forward.h>
bool Rogue_IsRunPlayer(const Fighter* fighter);
void RogueFighter_Created(Fighter* fighter);
float RogueFighter_AdjustDamage(Fighter* fighter, float damage);
float RogueFighter_ShieldCapacity(Fighter* fighter, float base);
float RogueFighter_ShieldRecovery(Fighter* fighter, float base);
int RogueFighter_LedgeFrames(Fighter* fighter, int base);
void RogueFighter_ResetMatch(void);
void RogueFighter_OnKO(int attacker, int partner, int victim);
void RogueFighter_HurtState(Fighter* fighter, int state);
#endif
