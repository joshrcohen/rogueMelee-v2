#include "rogue_runtime.h"
#include <string.h>

static RogueRuntime runtime;

void RogueRuntime_OnBoot(void)
{
    memset(&runtime, 0, sizeof(runtime));
    runtime.scene_generation = 1;
    runtime.match_generation = 1;
}

int RogueRuntime_IsActive(void) { return runtime.active != 0; }
const RogueRuntime* RogueRuntime_Get(void) { return &runtime; }
void RogueRuntime_SetActive(int active) { runtime.active = active != 0; }

void RogueRuntime_Trace(unsigned event, unsigned value)
{
    RogueTrace* trace = &runtime.trace[runtime.trace_count++ % 32];
    trace->event = event;
    trace->scene = runtime.scene;
    trace->generation = runtime.scene_generation;
    trace->value = value;
}

void RogueRuntime_SceneEnter(unsigned scene)
{
    runtime.scene = scene;
    RogueRuntime_Trace(1, scene);
}

int RogueRuntime_SceneExit(void)
{
    RogueRuntime_Trace(2, runtime.scene_resources);
    if (runtime.scene_resources != 0) return 0;
    runtime.scene_generation++;
    return 1;
}

int RogueRuntime_ResourceAcquire(unsigned generation)
{
    if (generation != runtime.scene_generation) return 0;
    runtime.scene_resources++;
    return 1;
}

int RogueRuntime_ResourceRelease(unsigned generation)
{
    if (generation != runtime.scene_generation || !runtime.scene_resources)
        return 0;
    runtime.scene_resources--;
    return 1;
}
