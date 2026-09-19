#include "special_matrix.h"
#if ROGUE_DEBUG && ROGUE_QA_MODE == 4
#include "../../../director/rogue_director.h"
#include "../debug_launch.h"
#include "../../../combat/specials/special_catalog.h"
#include "../specials/special_engine.h"
#include <melee/ft/types.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_Damage.h>
#include <melee/ft/kinds/ftCommon/ftCo_Attack100.h>
#include <melee/ft/kinds/ftCommon/ftCo_CatchPull.h>
#include <melee/ft/kinds/ftCommon/ftCo_CapturePulled.h>
#include <melee/ft/kinds/ftCommon/ftCo_CaptureCut.h>
#include <melee/ft/kinds/ftCommon/ftCo_Throw.h>
#include <melee/ft/kinds/ftCommon/forward.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gmscene.h>
#include <melee/pl/player.h>
#include <melee/mp/forward.h>
#include <dolphin/os.h>
#include <string.h>
static unsigned completed, frames, failures, entries, cleanups;
static int floor_line;
static unsigned transform_before;

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
    RogueDirector_Start(ROGUE_FIXTURE_SEED + index, index / ROGUE_SPECIALS);
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
        if (frames == 180) floor_line = fighter->coll_data.floor.index;
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
#if ROGUE_QA_LIFECYCLE
    if (frames == 480) {
        int restored;
        ftCommon_8007D5D4(fighter); ftCo_Fall_Enter(entity);
        if (!Rogue_TrySpecial(entity,special->slot,true)) failures++;
        fighter->coll_data.env_flags = Collide_LeftLedgeGrab;
        fighter->coll_data.ledge_id_left = floor_line;
        ftCliffCommon_80081370(entity);
        restored = Rogue_AbilityDebugRestored(fighter);
        if (!restored || fighter->motion_id != ftCo_MS_CliffCatch) failures++;
        OSReport("[rogue] special_ledge index=%u restored=%u motion=%u\n",index,restored,fighter->motion_id);
    }
    if (frames == 500) {
        fighter->cur_pos.x=0; fighter->cur_pos.y=20;
        ftCommon_8007D5D4(fighter); ftCo_Fall_Enter(entity);
    }
    if (frames == 530) {
        Fighter_GObj* attacker_entity = Player_GetEntity(1);
        Fighter* attacker = attacker_entity->user_data;
        int restored;
        ftCommon_8007D5D4(fighter); ftCo_Fall_Enter(entity);
        if (!Rogue_TrySpecial(entity,special->slot,true)) failures++;
        ftCo_800D8C54(attacker_entity,ftCo_MS_Catch);
        attacker->victim_gobj=entity;
        fn_800D9CE8(attacker_entity);
        fn_800DAADC(entity,attacker_entity);
        fn_800DA1D8(attacker_entity);
        restored=Rogue_AbilityDebugRestored(fighter);
        if (!restored || fighter->victim_gobj != attacker_entity) failures++;
        OSReport("[rogue] special_grab index=%u restored=%u linked=%u\n",index,restored,fighter->victim_gobj==attacker_entity);
    }
    if (frames == 550 && fighter->victim_gobj) ftCo_800DA698(fighter->victim_gobj,true);
    if (frames == 450) {
        int restored;
        fighter->cur_pos.x = 0; fighter->cur_pos.y = 45;
        ftCommon_8007D5D4(fighter);
        ftCo_Fall_Enter(entity);
        if (!Rogue_TrySpecial(entity, special->slot, true)) failures++;
        fighter->dmg.kb_applied = 30.0f;
        fighter->dmg.x1838_percentTemp = 5.0f;
        fighter->dmg.x184c_damaged_hurtbox = 0;
        fighter->dmg.x1860_element = HitElement_Normal;
        fighter->dmg.facing_dir_1 = 1.0f;
        ftCo_8008DCE0(entity, ftCo_MS_DamageAir1, 1.0f);
        restored = Rogue_AbilityDebugRestored(fighter);
        if (!restored) failures++;
        OSReport("[rogue] special_interrupt index=%u restored=%u\n", index, restored);
    }
    if (frames == 600) {
        ftCommon_8007D5D4(fighter);
        ftCo_Fall_Enter(entity);
        if (!Rogue_TrySpecial(entity, special->slot, true)) failures++;
    }
    if (frames >= 600 && frames < 610 && Player_GetStocks(0) == 99) {
        fighter->cur_pos.x = 0; fighter->cur_pos.y = -500;
        fighter->self_vel.y = -100;
    }
    if (frames == 1000) {
        int restored = Rogue_AbilityDebugRestored(fighter);
        int stocks = Player_GetStocks(0);
        if (stocks != 98 || !restored) failures++;
        OSReport("[rogue] special_respawn index=%u stocks=%d restored=%u motion=%u\n", index, stocks, restored, fighter->motion_id);
    }
    if (special->slot == ROGUE_ABILITY_DOWN && (special->donor == Ft_Kind_Zelda || special->donor == Ft_Kind_Seak)) {
        if (frames == 1050 || frames == 1300) {
            if (frames == 1050) transform_before=RogueDirector_Run()->specials[3];
            fighter->cur_pos.x=0; fighter->cur_pos.y=70;
            ftCommon_8007D5D4(fighter); ftCo_Fall_Enter(entity);
            ftColl_8007B760(entity,1000);
            if (!Rogue_TrySpecial(entity,ROGUE_ABILITY_DOWN,true)) failures++;
        }
        if (frames == 1290 || frames == 1540) {
            unsigned after=RogueDirector_Run()->specials[3];
            int valid=(after==transform_before)==(frames==1540);
            if (!valid) failures++;
            OSReport("[rogue] transform_cycle index=%u step=%u before=%u after=%u valid=%u\n",index,frames==1540?2:1,transform_before,after,valid);
        }
        if (frames == 1550) Player_SetStocks(1,0);
    } else if (frames == 1050) Player_SetStocks(1, 0);
#else
    if (frames == 450) Player_SetStocks(1, 0);
#endif
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
