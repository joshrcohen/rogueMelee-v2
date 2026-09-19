#include "rogue_hooks.h"
#include "../../director/rogue_runtime.h"
#include <dolphin/os.h>

void RogueHooks_OnBoot(void)
{
    RogueRuntime_OnBoot();
#if ROGUE_DEBUG
    OSReport("[rogue] build=0.1.0-dev boot aerials=disabled\n");
#endif
}

void RogueHooks_OnSceneEnter(int scene)
{
    if (!RogueRuntime_IsActive()) return;
    RogueRuntime_SceneEnter((unsigned) scene);
#if ROGUE_DEBUG
    OSReport("[rogue] scene_enter=%d generation=%u\n", scene,
             RogueRuntime_Get()->scene_generation);
#endif
}

void RogueHooks_OnSceneExit(void)
{
    if (!RogueRuntime_IsActive()) return;
    if (!RogueRuntime_SceneExit()) {
#if ROGUE_DEBUG
        OSReport("[rogue] ERROR scene resource leak count=%u\n",
                 RogueRuntime_Get()->scene_resources);
#endif
        RogueRuntime_SetActive(0);
    }
}

void RogueHooks_OnFrame(void)
{
    if (!RogueRuntime_IsActive()) return;
}
