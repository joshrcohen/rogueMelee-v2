#include "rogue_director.h"
static RogueRun run;
RogueRun* RogueDirector_Run(void) { return &run; }
void RogueDirector_Start(RogueSeed seed, unsigned character)
{
    RogueRun_Init(&run, seed, character);
    RogueRuntime_SetActive(1);
}
void RogueDirector_End(void) { RogueRuntime_SetActive(0); }
