#ifndef ROGUE_DIRECTOR_H
#define ROGUE_DIRECTOR_H
#include "../core/run.h"
#include "rogue_runtime.h"
RogueRun* RogueDirector_Run(void);
void RogueDirector_Start(unsigned seed, unsigned character);
void RogueDirector_End(void);
#endif
