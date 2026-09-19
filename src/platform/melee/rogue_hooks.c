#include "rogue_hooks.h"
#include "capabilities.h"
#include "rogue_mode.h"
#include "specials/special_engine.h"
#include "../../director/rogue_runtime.h"
#include "../../director/rogue_director.h"
#include "../../build_id.h"
#include <dolphin/os.h>
#include <melee/pl/player.h>
#include <melee/ft/types.h>
#include <melee/gm/gmregclear.h>
static unsigned clear_frames;

#if ROGUE_DEBUG
static void observe_run(const RogueRun* run, unsigned event, unsigned a, unsigned b, unsigned c)
{
    RogueRuntime_Trace(event == 1 ? 13 : 14, a);
    if (event == 1) {
        OSReport("[rogue] encounter seed=%08x%08x floor=%u recipe=%u tags=%x stage=%u rng_draws=%u\n",
            (unsigned) (run->seed >> 32), (unsigned) run->seed, run->floor, a, b, c, run->encounter_rng.draws);
    } else {
        const RogueHistoryEvent* history = &run->history[(run->history_count-1)%ROGUE_HISTORY];
        OSReport("[rogue] reroll shop=%u cost=%u generation=%u gold=%u before=%u,%u,%u after=%u,%u,%u\n",
            a,b,c,run->gold,history->before[0],history->before[1],history->before[2],
            history->after[0],history->after[1],history->after[2]);
    }
}
#endif

unsigned RogueHooks_BootMode(unsigned native_mode)
{
#if ROGUE_DEBUG && ROGUE_QA_MODE
    return GM_ROGUE;
#else
    return native_mode;
#endif
}

void RogueHooks_OnBoot(void)
{
    RogueRuntime_OnBoot();
#if ROGUE_DEBUG
    RogueRun_SetObserver(observe_run);
#endif
#if ROGUE_DEBUG
    OSReport("[rogue] build=0.1.0-dev/%s boot aerials=disabled\n", ROGUE_BUILD_ID);
#endif
}

void RogueHooks_OnSceneEnter(int scene)
{
    RogueCapabilities_Detect();
    if (!RogueCapabilities_Get()->supported) RogueRuntime_SetActive(0);
#if ROGUE_DEBUG
    OSReport("[rogue] native_scene=%d active=%d\n", scene, RogueRuntime_IsActive());
#endif
    if (!RogueRuntime_IsActive()) return;
    RogueRuntime_SceneEnter((unsigned) scene);
    if (scene == GS_VS) clear_frames = 0;
    if (scene == GS_VS && !RogueRuntime_MatchEnter())
        OSPanic(__FILE__, __LINE__, "rogue match lifetime overlap");
#if ROGUE_DEBUG
    OSReport("[rogue] scene_enter=%d generation=%u\n", scene,
             RogueRuntime_Get()->scene_generation);
#endif
}

void RogueHooks_OnSceneExit(void)
{
    if (!RogueRuntime_IsActive()) return;
    if (RogueRuntime_Get()->scene == GS_VS) {
        Rogue_AbilityMatchEnd();
#if ROGUE_DEBUG
        OSReport("[rogue] match_generation=%u resources=%u\n", RogueRuntime_Get()->match_generation, RogueRuntime_Get()->match_resources);
#endif
        if (!RogueRuntime_MatchExit()) OSPanic(__FILE__, __LINE__, "rogue match resource leak");
    }
#if ROGUE_DEBUG
    OSReport("[rogue] scene_exit=%u generation=%u resources=%u\n", RogueRuntime_Get()->scene,
        RogueRuntime_Get()->scene_generation, RogueRuntime_Get()->scene_resources);
#endif
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
    RogueMode_MenuFrame();
    RogueMode_MatchFrame();
    if (!RogueRuntime_IsActive()) return;
}

void RogueHooks_DumpContext(void)
{
#if ROGUE_DEBUG
    const RogueRuntime* runtime = RogueRuntime_Get();
    const RogueRun* run = RogueDirector_Run();
    unsigned i, count = runtime->trace_count < 32 ? runtime->trace_count : 32;
    OSReport("[rogue] crash build=%s active=%u seed=%08x%08x act=%u floor=%u scene=%u recipe=%u tags=%x\n",
        ROGUE_BUILD_ID, runtime->active, (unsigned) (run->seed >> 32), (unsigned) run->seed, run->act, run->floor, runtime->scene, run->current.recipe, run->current.tags);
    OSReport("[rogue] crash specials=%u,%u,%u,%u reward_generation=%u shop_generation=%u\n",
        run->specials[0], run->specials[1], run->specials[2], run->specials[3], run->reward.generation, run->shop.generation);
    for (i = 0; i < count; ++i) {
        const RogueTrace* trace = &runtime->trace[(runtime->trace_count-count+i)%32];
        OSReport("[rogue] trace event=%u scene=%u generation=%u value=%u\n", trace->event, trace->scene, trace->generation, trace->value);
    }
#endif
}

void RogueHooks_OnPause(int paused)
{
#if ROGUE_DEBUG
    Fighter_GObj* entity;
    if (!RogueRuntime_IsActive()) return;
    entity = Player_GetEntity(0);
    RogueRuntime_Trace(paused ? 11 : 12, RogueRuntime_Get()->match_generation);
    OSReport("[rogue] pause=%u match=%u special_active=%u\n", paused,
        RogueRuntime_Get()->match_generation, entity && Rogue_IsAbilityState(entity->user_data));
#else
    (void) paused;
#endif
}

int RogueHooks_AdvanceStageClear(void)
{
#if ROGUE_DEBUG
    if (!RogueRuntime_IsActive()) return 0;
    if (!clear_frames++) OSReport("[rogue] native_stage_clear score=%d match=%u\n", fn_8017F294(), RogueRuntime_Get()->match_generation);
#if ROGUE_QA_MODE == 2 || ROGUE_QA_MODE == 4
    return clear_frames >= 120;
#endif
#endif
    return 0;
}
