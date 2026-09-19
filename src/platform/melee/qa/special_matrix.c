#include "special_matrix.h"
#if ROGUE_DEBUG && ROGUE_QA_MODE == 4
#include "../../../director/rogue_director.h"
#include "../../../combat/specials/special_catalog.h"
#include "../specials/special_engine.h"
#include <melee/ft/types.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gmscene.h>
#include <melee/pl/player.h>
#include <dolphin/os.h>
#include <string.h>
static unsigned completed, frames, failures, entries, cleanups;

void RogueSpecialQa_Reset(void) { completed = frames = failures = entries = cleanups = 0; }
int RogueSpecialQa_Progression(void)
{
    RogueRun* run = RogueDirector_Run();
    unsigned index = ROGUE_QA_SPECIAL_START + completed;
    const RogueSpecialDef* special = &rogue_specials[index % ROGUE_SPECIALS];
    if (++frames < 4) return 1;
    frames = 0;
    if (completed >= ROGUE_QA_SPECIAL_COUNT || failures) {
        OSReport("[rogue] special_matrix_complete start=%u count=%u failures=%u\n", ROGUE_QA_SPECIAL_START, completed, failures);
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
        return 1;
    }
    RogueDirector_Start(0x524f4755 + index, index / ROGUE_SPECIALS);
    RogueRun_ChooseUpgrade(run, 0);
    RogueRun_ChooseRoute(run, 0);
    memset(run->specials, 0, sizeof(run->specials));
    memset(run->stacks, 0, sizeof(run->stacks));
    run->specials[special->slot] = special->id;
    run->current.recipe = 1; run->current.stage = 1; run->current.enemy_count = 1;
    run->current.fighters[0] = 13; run->current.stocks[0] = 99;
    run->current.damage = run->current.defense = run->current.speed = run->current.scale = 100;
    run->current.tags = run->current.starting_percent = 0;
    entries = cleanups = 0;
    OSReport("[rogue] special_case index=%u recipient=%u id=%u slot=%u\n", index, run->character, special->id, special->slot);
    return 2;
}
void RogueSpecialQa_Frame(void)
{
    unsigned index = ROGUE_QA_SPECIAL_START + completed;
    const RogueSpecialDef* special = &rogue_specials[index % ROGUE_SPECIALS];
    Fighter_GObj* entity;
    Fighter* fighter;
    if (!RogueRuntime_IsActive() || RogueRuntime_Get()->scene != GS_VS) return;
    frames++;
    entity = Player_GetEntity(0);
    fighter = entity ? entity->user_data : NULL;
    if (!fighter) { failures++; return; }
    if (frames == 180 || frames == 360) {
        int entered;
        Rogue_AbilityCleanup(fighter);
        ftColl_8007B760(entity, 600);
        if (frames == 360) {
            fighter->cur_pos.x = 0; fighter->cur_pos.y = 45;
            ftCommon_8007D5D4(fighter);
            ftCo_Fall_Enter(entity);
        } else ft_8008A2BC(entity);
        entered = Rogue_TrySpecial(entity, special->slot, frames == 360);
        entries += entered != 0;
        if (!entered) failures++;
        OSReport("[rogue] special_entry index=%u air=%u entered=%u\n", index, frames == 360, entered);
    }
    if (frames == 240 || frames == 420) {
        int restored;
        Rogue_AbilityCleanup(fighter);
        restored = Rogue_AbilityDebugRestored(fighter);
        cleanups += restored != 0;
        if (!restored) failures++;
        fighter->cur_pos.x = 0; fighter->cur_pos.y = 45;
        ftCommon_8007D5D4(fighter);
        ftCo_Fall_Enter(entity);
        OSReport("[rogue] special_cleanup index=%u air=%u restored=%u\n", index, frames == 420, restored);
    }
    if (frames == 450) Player_SetStocks(1, 0);
}
void RogueSpecialQa_Result(int won)
{
    if (!won || entries != 2 || cleanups != 2) failures++;
    OSReport("[rogue] special_result index=%u won=%u entries=%u cleanups=%u failures=%u\n",
        ROGUE_QA_SPECIAL_START + completed, won, entries, cleanups, failures);
    completed++; frames = 0;
}
#else
void RogueSpecialQa_Reset(void) {}
int RogueSpecialQa_Progression(void) { return 0; }
void RogueSpecialQa_Frame(void) {}
void RogueSpecialQa_Result(int won) { (void) won; }
#endif
