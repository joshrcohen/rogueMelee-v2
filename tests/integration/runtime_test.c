#include "../../src/director/rogue_runtime.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    unsigned i, generation;
    RogueRuntime_OnBoot();
    assert(!RogueRuntime_IsActive());
    RogueRuntime_SetActive(1);
    for (i = 0; i < 100; ++i) {
        generation = RogueRuntime_Get()->scene_generation;
        RogueRuntime_SceneEnter(i % 3);
        assert(RogueRuntime_ResourceAcquire(generation));
        assert(!RogueRuntime_SceneExit());
        assert(RogueRuntime_ResourceRelease(generation));
        assert(!RogueRuntime_ResourceRelease(generation));
        assert(RogueRuntime_SceneExit());
        assert(!RogueRuntime_ResourceAcquire(generation));
        assert(!RogueRuntime_ResourceRelease(generation));
        assert(!RogueRuntime_Get()->scene_resources);
    }
    assert(RogueRuntime_Get()->trace_count == 300);
    for (i = 0; i < 100; ++i) {
        generation = RogueRuntime_Get()->match_generation;
        assert(RogueRuntime_MatchEnter());
        assert(!RogueRuntime_MatchEnter());
        assert(RogueRuntime_MatchAcquire(generation));
        assert(!RogueRuntime_MatchExit());
        assert(RogueRuntime_MatchRelease(generation));
        assert(!RogueRuntime_MatchRelease(generation));
        assert(RogueRuntime_MatchExit());
        assert(!RogueRuntime_MatchAcquire(generation));
        assert(!RogueRuntime_MatchRelease(generation));
        assert(!RogueRuntime_MatchExit());
    }
    RogueRuntime_SetActive(0);
    assert(!RogueRuntime_IsActive());
    puts("PASS: 100 host resource lifetimes, stale handles and double release rejected");
    return 0;
}
