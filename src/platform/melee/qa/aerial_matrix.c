#include "aerial_matrix.h"
#if ROGUE_QA_MODE == 5
#include "../../../director/rogue_director.h"
#include "../debug_launch.h"
#include "../../../combat/specials/../aerials/aerial_catalog.h"
#include "../specials/special_engine.h"
#include <melee/ft/types.h>
#include <melee/ft/fighter.h>
#include <melee/ft/kinds/ftZelda/ftzeldaspeciallw.h>
#include <melee/ft/kinds/ftSeak/ftseakspeciallw.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/kinds/ftCommon/ftCo_LandingAir.h>
#include <melee/ft/kinds/ftGameWatch/ftgamewatchattackair.h>
#include "../specials/special_internal.h"
#include "../../../core/offers.h"
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_Damage.h>
#include <melee/ft/kinds/ftCommon/ftCo_Attack100.h>
#include <melee/ft/kinds/ftCommon/ftCo_Attack1.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackAir.h>
#include <melee/ft/kinds/ftGameWatch/forward.h>
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
static int native_form;

static int native_jab(Fighter_GObj* entity)
{
    Fighter* fp=entity->user_data;
    int entered;
    ftCommon_8007D7FC(fp);
    ft_8008A2BC(entity);
    fp->input.pressed_buttons=HSD_PAD_A;
    fp->hitlag_mul=0;
    entered=ftCo_Attack1_CheckInput(entity);
    fp->input.pressed_buttons=0;
    return entered && Rogue_AbilityDebugRestored(fp) &&
        fp->motion_id==(fp->kind==Ft_Kind_GameWatch ? ftGw_MS_Attack11 : ftCo_MS_Attack11);
}


static unsigned case_index(void)
{
    unsigned value=ROGUE_QA_SPECIAL_START+completed;
#if ROGUE_QA_AERIAL_STRESS
    return (value % 26)*130+(value / 26)*26+value%26;
#else
    return value;
#endif
}

void RogueAerialQa_Reset(void) { completed = frames = failures = entries = cleanups = 0; }
int RogueAerialQa_Progression(void)
{
    RogueRun* run = RogueDirector_Run();
    unsigned index = case_index();
    const RogueAerialDef* special = &rogue_aerials[index % ROGUE_AERIALS];
    if (++frames < 4) return 1;
    frames = 0;
    if (fighter_state.fighter || RogueRuntime_Get()->match_resources) failures++;
    if (completed >= ROGUE_QA_SPECIAL_COUNT || failures) {
        OSReport("[rogue] aerial_matrix_complete start=%u count=%u failures=%u\n", ROGUE_QA_SPECIAL_START, completed, failures);
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
        return 1;
    }
#if ROGUE_QA_AERIAL_STRESS
    if (!completed || run->phase==ROGUE_COMPLETE) RogueDirector_Start(ROGUE_FIXTURE_SEED + index,index/ROGUE_AERIALS);
    run->character=index/ROGUE_AERIALS;
    memset(run->stacks,0,sizeof(run->stacks));
    RogueRun_Shop(run);
    run->gold=9999;
    {
        unsigned slot;
        for(slot=0;slot<5;++slot) {
            unsigned donor=(special->character+slot*5+1)%26;
            unsigned id;
            if(donor==run->character) donor=(donor+1)%26;
            id=donor*5+slot+1;
            if(slot==special->slot) id=special->id;
            /* Native-identical entries are direct diagnostic fixtures only. */
            if(rogue_aerials[id-1].character==run->character || run->aerials[slot]==id) run->aerials[slot]=id;
            else {
                run->shop.ids[0]=ROGUE_AERIAL_OFFER_BASE+id;
                run->shop.sold[0]=0;
                if(!RogueRun_Buy(run,0)) failures++;
            }
        }
    }
    if (fighter_state.fighter || RogueRuntime_Get()->match_resources) failures++;
    OSReport("[rogue] aerial_shop_heap index=%u resources=%u fighter=%p\n",index,RogueRuntime_Get()->match_resources,fighter_state.fighter);
    run->phase=ROGUE_FIGHT;
    run->specials[0]=89; /* Falco blaster */
    run->specials[1]=74; /* Marth side */
    run->specials[2]=51; /* Pikachu up */
    run->specials[3]=32; /* Sheik transformation, also prepares Zelda */
#else
    RogueDirector_Start(ROGUE_FIXTURE_SEED + index, index / ROGUE_AERIALS);
    RogueRun_ChooseUpgrade(run, 0);
    RogueRun_ChooseRoute(run, 0);
    memset(run->specials, 0, sizeof(run->specials));
    memset(run->stacks, 0, sizeof(run->stacks));
    memset(run->aerials, 0, sizeof(run->aerials));
    run->aerials[special->slot] = special->id;
    run->specials[ROGUE_ABILITY_NEUTRAL] = 89;
#endif
    run->current.recipe = 1; run->current.stage = 1; run->current.enemy_count = 1;
    run->current.fighters[0] = 13; run->current.stocks[0] = 99;
    run->current.damage = run->current.defense = run->current.speed = run->current.scale = 100;
    run->current.tags = run->current.starting_percent = 0;
#if ROGUE_QA_AERIAL_STRESS
    run->current.enemy_count=3;
    run->current.fighters[1]=8; run->current.fighters[2]=20;
    run->current.stocks[1]=run->current.stocks[2]=99;
#endif
    entries = cleanups = 0;
    OSReport("[rogue] aerial_case index=%u recipient=%u id=%u slot=%u\n", index, run->character, special->id, special->slot);
    return 2;
}
void RogueAerialQa_Frame(void)
{
    unsigned index = case_index();
    const RogueAerialDef* special = &rogue_aerials[index % ROGUE_AERIALS];
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
        if (1) {
            fighter->cur_pos.x = 0; fighter->cur_pos.y = 45;
            ftCommon_8007D5D4(fighter);
            ftCo_Fall_Enter(entity);
        } else ft_8008A2BC(entity);
        entered = Rogue_AerialTryEnter(entity, ftCo_MS_AttackAirN + special->slot);
        entries += entered != 0;
        if (!entered) failures++;
        OSReport("[rogue] aerial_entry index=%u air=%u entered=%u\n", index, frames == 360, entered);
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
        OSReport("[rogue] aerial_cleanup index=%u air=%u restored=%u\n", index, frames == 420, restored);
    }
    if(frames==185) {
        int valid=1, adapted=0;
        if(special->donor==Ft_Kind_GameWatch && (special->slot==0 || special->slot==2 || special->slot==3)) {
            union Fighter_FighterVars* vars=Rogue_AbilityVars(fighter,Ft_Kind_GameWatch);
            adapted=1;
            valid=Rogue_IsAbilityState(fighter) && (special->slot==0 ? vars->gw.x2258_parachuteGObj!=NULL : special->slot==2 ? vars->gw.x225C_turtleGObj!=NULL : vars->gw.x2260_sparkyGObj!=NULL);
        }
        if((special->donor==Ft_Kind_Link || special->donor==Ft_Kind_CLink) && special->slot==4) {
            ftLk_DatAttrs* attrs=fighter->dat_attrs;
            adapted=1;
            valid=Rogue_IsAbilityState(fighter) && fighter->deal_dmg_cb!=NULL;
            if(valid) {
                fighter->deal_dmg_cb(entity);
                valid=fighter->self_vel.y==attrs->attackairlw_hit_vel_y && !fighter->fall_fast && Rogue_IsAbilityState(fighter);
            }
        }
        if(adapted) {
            if(!valid) failures++;
            OSReport("[rogue] aerial_adapter index=%u valid=%u\n",index,valid);
        }
    }
    if (frames == 270 || frames == 300) {
        ftCo_DatAttrs* attrs = gFtDataList[special->donor]->x0;
        float expected, rate, error;
        int cancel = frames == 300;
        int article = special->donor == Ft_Kind_GameWatch && (special->slot == 0 || special->slot == 2 || special->slot == 3);
        switch (special->slot) {
        case 0: expected=attrs->landingairn_lag; break;
        case 1: expected=attrs->landingairf_lag; break;
        case 2: expected=attrs->landingairb_lag; break;
        case 3: expected=article ? attrs->landingairb_lag : attrs->landingairhi_lag; break;
        default: expected=attrs->landingairlw_lag; break;
        }
        fighter->cur_pos.x=0; fighter->cur_pos.y=45;
        ftCommon_8007D5D4(fighter); ftCo_Fall_Enter(entity);
        if (!Rogue_AerialTryEnter(entity,ftCo_MS_AttackAirN+special->slot)) failures++;
        fighter->cmd_vars[0]=1;
        fighter->x67F=cancel ? 0 : 255;
        if (article) {
            if (special->slot==0) ftGw_LandingAirN_Enter(entity);
            if (special->slot==2) ftGw_LandingAirB_Enter(entity);
            if (special->slot==3) ftGw_LandingAirHi_Enter(entity);
        } else {
            if(cancel) { expected=(int)(expected/p_ftCommonData->xE8); if(expected<1)expected=1; }
            ftCo_LandingAir_EnterWithLag(entity);
        }
        rate=(ftAnim_8006F484(entity)+0.1f)/expected;
        error=rate-fighter->frame_speed_mul;
        if(error < -0.001f || error > 0.001f || !Rogue_IsAbilityState(fighter)) failures++;
        OSReport("[rogue] aerial_landing index=%u cancel=%u lag=%f rate=%f expected=%f failures=%u\n",index,cancel,expected,fighter->frame_speed_mul,rate,failures);
    }
    if (frames == 430) {
        int valid;
        valid=native_jab(entity);
        ftCommon_8007D5D4(fighter); ftCo_Fall_Enter(entity);
        valid=valid && Rogue_AbilityDebugRestored(fighter);
        valid=valid && Rogue_AerialTryEnter(entity,ftCo_MS_AttackAirN+special->slot);
        valid=valid && fighter_state.aerial == special && fighter->x24 == (fighter_state.aerial_anims[special->donor] ? fighter_state.aerial_anims[special->donor] : gFtDataList[special->donor]->xC);
        valid=valid && Rogue_TrySpecial(entity,ROGUE_ABILITY_NEUTRAL,true);
        valid=valid && !fighter_state.aerial && fighter_state.active && fighter_state.active->id == 89;
        valid=valid && native_jab(entity);
        if(!valid) failures++;
        OSReport("[rogue] aerial_mixed index=%u valid=%u\n",index,valid);
    }
    if(frames==440) {
        unsigned slot,checked=0;
        int valid=1;
        for(slot=0;slot<5;++slot) if(!fighter_state.aerial_equipped[slot]) {
            ftCommon_8007D5D4(fighter);ftCo_Fall_Enter(entity);
            fighter->input.pressed_buttons=HSD_PAD_A;
            fighter->input.cstick[0].x=fighter->input.cstick[0].y=0;
            fighter->input.lstick[0].x=slot==1 ? fighter->facing_dir : slot==2 ? -fighter->facing_dir : 0;
            fighter->input.lstick[0].y=slot==3 ? 1 : slot==4 ? -1 : 0;
            valid=valid && ftCo_AttackAir_CheckItemThrowInput(entity);
            valid=valid && Rogue_AbilityDebugRestored(fighter);
            checked++;
        }
        fighter->input.pressed_buttons=0;
        fighter->input.lstick[0].x=fighter->input.lstick[0].y=0;
        ftCommon_8007D5D4(fighter);ftCo_Fall_Enter(entity);
        if(!valid) failures++;
        OSReport("[rogue] aerial_native_slots index=%u checked=%u valid=%u\n",index,checked,valid);
    }
#if ROGUE_QA_LIFECYCLE
    if (frames == 480) {
        int restored;
        ftCommon_8007D5D4(fighter); ftCo_Fall_Enter(entity);
        if (!Rogue_AerialTryEnter(entity, ftCo_MS_AttackAirN + special->slot)) failures++;
        fighter->coll_data.env_flags = Collide_LeftLedgeGrab;
        fighter->coll_data.ledge_id_left = floor_line;
        ftCliffCommon_80081370(entity);
        restored = Rogue_AbilityDebugRestored(fighter);
        if (!restored || fighter->motion_id != ftCo_MS_CliffCatch) failures++;
        OSReport("[rogue] aerial_ledge index=%u restored=%u motion=%u\n",index,restored,fighter->motion_id);
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
        if (!Rogue_AerialTryEnter(entity, ftCo_MS_AttackAirN + special->slot)) failures++;
        ftCo_800D8C54(attacker_entity,ftCo_MS_Catch);
        attacker->victim_gobj=entity;
        fn_800D9CE8(attacker_entity);
        fn_800DAADC(entity,attacker_entity);
        fn_800DA1D8(attacker_entity);
        restored=Rogue_AbilityDebugRestored(fighter);
        if (!restored || fighter->victim_gobj != attacker_entity) failures++;
        OSReport("[rogue] aerial_grab index=%u restored=%u linked=%u\n",index,restored,fighter->victim_gobj==attacker_entity);
    }
    if (frames == 550 && fighter->victim_gobj) ftCo_800DA698(fighter->victim_gobj,true);
    if (frames == 450) {
        int restored;
        fighter->cur_pos.x = 0; fighter->cur_pos.y = 45;
        ftCommon_8007D5D4(fighter);
        ftCo_Fall_Enter(entity);
        if (!Rogue_AerialTryEnter(entity, ftCo_MS_AttackAirN + special->slot)) failures++;
        fighter->dmg.kb_applied = 30.0f;
        fighter->dmg.x1838_percentTemp = 5.0f;
        fighter->dmg.x184c_damaged_hurtbox = 0;
        fighter->dmg.x1860_element = HitElement_Normal;
        fighter->dmg.facing_dir_1 = 1.0f;
        ftCo_8008DCE0(entity, ftCo_MS_DamageAir1, 1.0f);
        restored = Rogue_AbilityDebugRestored(fighter);
        if (!restored) failures++;
        OSReport("[rogue] aerial_interrupt index=%u restored=%u\n", index, restored);
    }
    if (frames == 600) {
        ftCommon_8007D5D4(fighter);
        ftCo_Fall_Enter(entity);
        if (!Rogue_AerialTryEnter(entity, ftCo_MS_AttackAirN + special->slot)) failures++;
    }
    if (frames >= 600 && frames < 610 && Player_GetStocks(0) == 99) {
        fighter->cur_pos.x = 0; fighter->cur_pos.y = -500;
        fighter->self_vel.y = -100;
    }
    if (frames == 1000) {
        int restored = Rogue_AbilityDebugRestored(fighter);
        int stocks = Player_GetStocks(0);
        if (stocks != 98 || !restored) failures++;
        OSReport("[rogue] aerial_respawn index=%u stocks=%d restored=%u motion=%u\n", index, stocks, restored, fighter->motion_id);
    }
#if ROGUE_QA_AERIAL_STRESS
    if (frames == 1050) {
        unsigned slot;
        int valid=1;
        fighter->cur_pos.x=0; fighter->cur_pos.y=45;
        ftCommon_8007D5D4(fighter); ftCo_Fall_Enter(entity);
        for(slot=0;slot<5;++slot) {
            const RogueAerialDef* equipped=RogueAerial_Find(RogueDirector_Run()->aerials[slot]);
            valid=valid && Rogue_AerialTryEnter(entity,ftCo_MS_AttackAirN+slot);
            valid=valid && fighter_state.aerial==equipped && fighter->x24==(fighter_state.aerial_anims[equipped->donor] ? fighter_state.aerial_anims[equipped->donor] : gFtDataList[equipped->donor]->xC);
        }
        ftCo_Fall_Enter(entity);
        valid=valid && Rogue_AbilityDebugRestored(fighter);
        if(!valid) failures++;
        OSReport("[rogue] aerial_five_donors index=%u valid=%u\n",index,valid);
    }
    if (frames==1100) {
        ftCommon_8007D5D4(fighter); ftCo_Fall_Enter(entity);
        if(!Rogue_AerialTryEnter(entity,ftCo_MS_AttackAirN+special->slot)) failures++;
    }
    if(frames>=1100 && frames<1110 && Player_GetStocks(0)==98) {
        fighter->cur_pos.x=0;fighter->cur_pos.y=-500;fighter->self_vel.y=-100;
    }
    if(frames==1500) {
        int valid=Player_GetStocks(0)==97 && Rogue_AbilityDebugRestored(fighter);
        if(!valid) failures++;
        OSReport("[rogue] aerial_second_stock index=%u valid=%u\n",index,valid);
    }
    if(frames==1560 || frames==1820) {
        fighter->cur_pos.x=0;fighter->cur_pos.y=70;
        ftCommon_8007D5D4(fighter);ftCo_Fall_Enter(entity);
        ftColl_8007B760(entity,1000);
        if(!Rogue_TrySpecial(entity,ROGUE_ABILITY_DOWN,true)) failures++;
    }
    if(frames==1800 || frames==2060) {
        int valid=RogueDirector_Run()->specials[3]==(frames==1800 ? 80 : 32);
        valid=valid && Rogue_AerialTryEnter(entity,ftCo_MS_AttackAirN+special->slot);
        ftCo_Fall_Enter(entity);
        valid=valid && Rogue_AbilityDebugRestored(fighter);
        if(!valid) failures++;
        OSReport("[rogue] aerial_transform index=%u step=%u valid=%u\n",index,frames==1800?1:2,valid);
    }
    if(RogueDirector_Run()->character==18 || RogueDirector_Run()->character==19) {
        if(frames==2100 || frames==2360) {
            if(frames==2100) native_form=fighter->kind;
            fighter->cur_pos.x=0;fighter->cur_pos.y=70;
            ftCommon_8007D5D4(fighter);ftCo_Fall_Enter(entity);
            ftColl_8007B760(entity,1000);
            if(fighter->kind==Ft_Kind_Zelda) ftZd_SpecialAirLw_Enter(entity);
            else ftSk_SpecialAirLw_Enter(entity);
        }
        if(frames==2340 || frames==2600) {
            int valid=(fighter->kind==native_form)==(frames==2600);
            valid=valid && Rogue_AerialTryEnter(entity,ftCo_MS_AttackAirN+special->slot);
            ftCo_Fall_Enter(entity);
            valid=valid && Rogue_AbilityDebugRestored(fighter);
            if(!valid) failures++;
            OSReport("[rogue] aerial_native_transform index=%u step=%u valid=%u\n",index,frames==2340?1:2,valid);
        }
        if(frames==2650) { Player_SetStocks(1,0);Player_SetStocks(2,0);Player_SetStocks(3,0); }
    } else if(frames==2100) { Player_SetStocks(1,0);Player_SetStocks(2,0);Player_SetStocks(3,0); }
#else
    if (frames == 1050) Player_SetStocks(1, 0);
#endif
#else
    if (frames == 450) Player_SetStocks(1, 0);
#endif
}
void RogueAerialQa_Result(int won)
{
    if (!won || entries != 2 || cleanups != 2) failures++;
    OSReport("[rogue] aerial_result index=%u won=%u entries=%u cleanups=%u failures=%u\n",
        case_index(), won, entries, cleanups, failures);
    completed++; frames = 0;
}
#else
void RogueAerialQa_Reset(void) {}
int RogueAerialQa_Progression(void) { return 0; }
void RogueAerialQa_Frame(void) {}
void RogueAerialQa_Result(int won) { (void) won; }
#endif
