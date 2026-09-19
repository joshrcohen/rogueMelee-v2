#ifndef ROGUE_RUNTIME_H
#define ROGUE_RUNTIME_H

typedef struct RogueTrace {
    unsigned event, scene, generation, value;
} RogueTrace;
typedef struct RogueRuntime {
    unsigned active, scene, scene_generation, match_generation;
    unsigned scene_resources, match_resources, trace_count;
    RogueTrace trace[32];
} RogueRuntime;

void RogueRuntime_OnBoot(void);
int RogueRuntime_IsActive(void);
void RogueRuntime_SetActive(int active);
void RogueRuntime_SceneEnter(unsigned scene);
int RogueRuntime_SceneExit(void);
void RogueRuntime_Trace(unsigned event, unsigned value);
const RogueRuntime* RogueRuntime_Get(void);
int RogueRuntime_ResourceAcquire(unsigned generation);
int RogueRuntime_ResourceRelease(unsigned generation);
#endif
