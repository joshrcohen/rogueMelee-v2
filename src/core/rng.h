#ifndef ROGUE_RNG_H
#define ROGUE_RNG_H
typedef struct RogueRng { unsigned state, draws; } RogueRng;
void RogueRng_Init(RogueRng* rng, unsigned seed, unsigned stream);
unsigned RogueRng_Next(RogueRng* rng);
unsigned RogueRng_Bounded(RogueRng* rng, unsigned bound);
#endif
