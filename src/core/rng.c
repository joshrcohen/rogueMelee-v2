#include "rng.h"

void RogueRng_Init(RogueRng* rng, unsigned seed, unsigned stream)
{
    unsigned x = seed ^ (0x9e3779b9U * (stream + 1));
    x ^= x >> 16; x *= 0x85ebca6bU;
    x ^= x >> 13; x *= 0xc2b2ae35U; x ^= x >> 16;
    rng->state = x ? x : 1;
    rng->draws = 0;
}
unsigned RogueRng_Next(RogueRng* rng)
{
    unsigned x = rng->state;
    x ^= x << 13; x ^= x >> 17; x ^= x << 5;
    rng->state = x; rng->draws++;
    return x;
}
unsigned RogueRng_Bounded(RogueRng* rng, unsigned bound)
{
    unsigned value, threshold;
    if (!bound) return 0;
    threshold = (0U - bound) % bound;
    do { value = RogueRng_Next(rng); } while (value < threshold);
    return value % bound;
}
