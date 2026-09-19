#include "rogue_mode.h"
#include "capabilities.h"
#include "debug_launch.h"
#include "ui_scene.h"
#include "melee_fighter.h"
#include "qa/special_matrix.h"
#include "qa/aerial_matrix.h"
#include "qa/passives.h"
#include "../../director/rogue_director.h"
#include "../../upgrades/upgrade_registry.h"
#include "../../encounters/encounter_registry.h"
#include "../../core/offers.h"
#include "specials/special_engine.h"
#include <melee/ft/types.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftdata.h>
#include <melee/ft/kinds/ftCommon/forward.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/gmscene.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/gmvs.h>
#include <melee/gm/gmregclear.h>
#include <melee/pl/player.h>
#include <melee/lb/forward.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/mn/inlines.h>
#include <dolphin/os.h>
#include <string.h>

static VsModeData selection;
static CSSData css;
static StartMeleeData match;
static MatchExitInfo result;
static RogueUiContext ui;
#define screen ui.text
static unsigned cursor, build_view;
static const char* feedback;
static unsigned qa_cycles, qa_frames, qa_matches, qa_failures;
static unsigned encounter_frames;
static unsigned menu_requested;
static const unsigned stages[6] = { 31, 32, 28, 8, 2, 3 };

static void change_state(unsigned id)
{
    gm_SetNextGameModeStateId(id);
    gm_801A4B60();
}

void RogueMode_Load(void)
{
    RogueSpecialQa_Reset();
    RogueAerialQa_Reset();
    gm_InitVsMode(&selection);
    selection.start.players[0].ckind = CKind_Fox;
    selection.start.players[0].slot_type = Gm_PKind_Human;
    css.unk_0x0 = 0;
#if (ROGUE_DEBUG && ROGUE_QA_MODE) || ROGUE_QA_MODE == 5
    qa_cycles = qa_frames = 0;
    qa_matches = qa_failures = 0;
    RogueDirector_Start(ROGUE_FIXTURE_SEED, ROGUE_LAUNCH_RECIPIENT);
#if ROGUE_QA_MODE == 3
    {
        RogueRun* run = RogueDirector_Run();
        const RogueSpecialDef* special = RogueSpecial_Find(ROGUE_LAUNCH_SPECIAL);
        unsigned tries;
        const unsigned aerials[5]=ROGUE_LAUNCH_AERIALS;
        memcpy(run->aerials,aerials,sizeof(run->aerials));
#if ROGUE_LAUNCH_GOLD >= 0
        run->gold=ROGUE_LAUNCH_GOLD;
#endif
#if ROGUE_QA_PASSIVES
        for (tries = 0; tries < ROGUE_UPGRADES; ++tries) run->stacks[tries] = 1;
#endif
        if (special) run->specials[special->slot] = special->id;
        if (ROGUE_LAUNCH_SERVICE == 1) RogueRun_Shop(run);
        if (ROGUE_LAUNCH_SERVICE == 2) { run->phase=ROGUE_REST; run->carried_percent=60; }
        if (ROGUE_LAUNCH_COMBAT) {
            if (ROGUE_LAUNCH_ENCOUNTER) {
                unsigned tier = rogue_recipes[ROGUE_LAUNCH_ENCOUNTER-1].tier;
                run->route[0][0] = tier;
                for (tries = 0; tries < 128; ++tries) {
                    RogueEncounter_Generate(run, tier, &run->preview[0]);
                    if (run->preview[0].recipe == ROGUE_LAUNCH_ENCOUNTER) break;
                }
                if (run->preview[0].recipe != ROGUE_LAUNCH_ENCOUNTER)
                    OSPanic(__FILE__, __LINE__, "developer recipe unavailable");
            }
            run->phase = ROGUE_ROUTE;
            RogueRun_ChooseRoute(run, 0);
        }
    }
#endif
#endif
}

void RogueMode_Unload(void)
{
#if ROGUE_DEBUG && ROGUE_QA_CYCLES
    OSReport("[rogue] scene_qa cycles=%u resources=%u active=%d\n", qa_cycles,
        RogueRuntime_Get()->scene_resources, RogueRuntime_IsActive());
#endif
    RogueDirector_End();
}

static void enter_css(GameModeState* state)
{
    gmVsMelee_EnterCss(state, &selection, REG_CLASSIC);
}

static void exit_css(GameModeState* state)
{
    gmVsMelee_ExitCss(state, &selection);
    if (css.pending_scene_change == CSSPendingSceneChange_2) return;
    RogueDirector_Start((RogueSeed) OSGetTime(), selection.start.players[0].ckind);
    gm_SetNextGameModeStateId(1);
}

static void enter_match(GameModeState* state)
{
    RogueRun* run = RogueDirector_Run();
    unsigned i;
    u64 audio = 0;
    (void) state;
    memset(&result, 0, sizeof(result));
    RogueFighter_ResetMatch();
    encounter_frames = 0;
    gm_SetupRulesDefaults(&match.rules);
    match.rules.match_kind = MatchKind_Stock;
    match.rules.is_stock = true;
    match.rules.is_vs = true;
    match.rules.is_teams = true;
    match.rules.x4_4 = true; /* Retail Stage Clear and bonus-score presentation. */
    match.rules.x18 = run->score;
    match.rules.item_freq = -1;
    match.rules.stkind = stages[run->current.stage - 1];
    for (i = 0; i < GM_MAX_PLAYERS; ++i) {
        PlayerInitData* player = &match.players[i];
        gm_SetupPlayerDefaults(player);
        player->slot = i;
        if (i > run->current.enemy_count) continue;
        player->ckind = i ? run->current.fighters[i - 1] : run->character;
        player->slot_type = i ? Gm_PKind_Cpu : Gm_PKind_Human;
        player->stocks = i ? run->current.stocks[i - 1] : 3 + run->stacks[10];
#if (ROGUE_DEBUG && ROGUE_QA_MODE == 4) || ROGUE_QA_MODE == 5
        player->stocks = 99;
#endif
        player->team = i ? 1 : 0;
        player->cpu_level = 3 + run->act * 2;
        if (i) {
            player->attack_ratio = run->current.damage / 100.0f;
            player->defense_ratio = 100.0f / run->current.defense;
            player->model_scale = run->current.scale / 100.0f;
            player->damage = run->current.starting_percent;
            player->vs_metal = (run->current.tags & 8) != 0;
            if ((run->current.tags & 1024) && i == 1) {
                player->attack_ratio *= 1.20f;
                player->defense_ratio *= 0.85f;
                player->model_scale *= 1.15f;
            }
        } else {
            player->damage = run->carried_percent;
            player->attack_ratio = 1.0f + run->stacks[14] * 0.05f;
            player->defense_ratio = 1.0f - run->stacks[15] * 0.05f;
        }
        audio |= lbAudioAx_80026E84(player->ckind);
    }
    run->stacks[10] = 0;
    lbAudioAx_80026F2C(24);
    lbAudioAx_8002702C(4, audio);
    lbAudioAx_8002702C(8, lbAudioAx_80026EBC(match.rules.stkind));
    lbAudioAx_80027168();
    gm_LoadAnnouncer();
    OSReport("[rogue] match floor=%u recipe=%u stage=%u enemies=%u\n",
             run->floor, run->current.recipe, run->current.stage, run->current.enemy_count);
}

static void exit_match(GameModeState* state)
{
    int won = result.match_end.outcome == OUTCOME_TEAM_ELIMINATION &&
        result.match_end.player_standings[0].stocks > 0;
    int raw_score = won ? fn_8017F294() : result.match_end.player_standings[0].score;
    unsigned native_score = raw_score > 0 ? raw_score : 0;
    if (won) native_score = native_score > RogueDirector_Run()->score ? native_score - RogueDirector_Run()->score : 0;
    (void) state;
    RogueDirector_Run()->carried_percent = result.match_end.player_standings[0].percent;
    RogueRun_MatchEnd(RogueDirector_Run(), won,
        native_score);
    if (!won && result.match_end.outcome == OUTCOME_NO_CONTEST) RogueDirector_Run()->death_reason = 2;
    RogueSpecialQa_Result(won);
    RogueAerialQa_Result(won);
#if ROGUE_DEBUG && ROGUE_QA_MODE == 2
    qa_matches++;
    if (won != (qa_matches < ROGUE_QA_MATCHES)) qa_failures++;
    qa_frames = 0;
    OSReport("[rogue] transition_qa index=%u won=%d failures=%u\n", qa_matches, won, qa_failures);
#endif
    OSReport("[rogue] match_exit outcome=%u won=%d phase=%u floor=%u\n",
        result.match_end.outcome, won, RogueDirector_Run()->phase, RogueDirector_Run()->floor);
    gm_SetNextGameModeStateId(1);
}

GameModeState RogueMode_States[] = {
#if (ROGUE_DEBUG && ROGUE_QA_MODE) || ROGUE_QA_MODE == 5
    { 0, lbDvdPreload_2, 0, NULL, NULL, { GS_ROGUE, NULL, NULL } },
#else
    { 0, lbDvdPreload_3, 0, enter_css, exit_css, { GS_CSS, &css, &css } },
#endif
    { 1, lbDvdPreload_2, 0, NULL, NULL, { GS_ROGUE, NULL, NULL } },
    { 2, lbDvdPreload_2, 0, enter_match, exit_match, { GS_VS, &match, &result } },
    { GM_GAMEMODESTATE_TERMINATE }
};

static const char* fighter_names[26] = {
    "Captain Falcon", "Donkey Kong", "Fox", "Mr Game and Watch", "Kirby", "Bowser",
    "Link", "Luigi", "Mario", "Marth", "Mewtwo", "Ness", "Peach", "Pikachu",
    "Ice Climbers", "Jigglypuff", "Samus", "Yoshi", "Zelda", "Sheik", "Falco",
    "Young Link", "Dr Mario", "Roy", "Pichu", "Ganondorf"
};
static const char* node_names[5] = { "MATCH", "ELITE", "BOSS", "SHOP", "REST" };
static const char* stage_names[6] = { "Battlefield", "Final Destination", "Dream Land", "Yoshi Story", "Fountain of Dreams", "Pokemon Stadium" };

static void draw(void)
{
    RogueRun* run = RogueDirector_Run();
    unsigned i, floor = run->floor < 15 ? run->floor : 14;
    const char* phases[] = { "CHOOSE A FIGHTER", "CHOOSE AN UPGRADE", "CHOOSE YOUR ROUTE",
        "BATTLE", "SHOP", "REST", "RUN ENDED", "RUN COMPLETE" };
    RogueUi_Update(&ui, run, cursor, build_view);
    RogueText_Begin(&screen);
    for (i = 0; i < 15; ++i) {
        if (i == run->floor) {
            RogueText_Line(&screen, 33+i*39, 5, "NEXT");
            RogueText_Style(&screen, 0.50f, 0xF6CD36);
        }
        RogueText_Line(&screen, 43+i*39, 23, "%u", i+1);
        RogueText_Style(&screen, 0.60f, i == run->floor ? 0x171B30 : 0xE5E9F6);
        if (i % 5 == 4) {
            RogueText_Line(&screen, 33+i*39, 39, "BOSS");
            RogueText_Style(&screen, 0.50f, 0xAAB4CF);
        } else {
            static const char* symbols[5] = { "M", "E", "B", "S", "R" };
            RogueText_Line(&screen, 33+i*39, 39, "%s/%s", symbols[run->route[i][0]], symbols[run->route[i][1]]);
            RogueText_Style(&screen, 0.50f, 0xAAB4CF);
        }
    }
    RogueText_Line(&screen, 24, 61, "ACT %u / 3     FLOOR %u / 15", run->act, floor+1);
    RogueText_Style(&screen, 0.80f, 0xFFFFFF);
    RogueText_Line(&screen, 330, 62, "SCORE %u", run->score);
    RogueText_Style(&screen, 0.55f, 0xDAE2FF);
    RogueText_Line(&screen, 471, 61, "GOLD %u", run->gold);
    RogueText_Style(&screen, 0.85f, 0xF6CD36);
    RogueText_Line(&screen, 212, 102, "%s", build_view ? "CURRENT BUILD" : phases[run->phase]);
    RogueText_Style(&screen, 0.85f, 0xDAE2FF);
    if (build_view) {
        unsigned line = 0;
        const char* slots[4] = { "Neutral", "Side", "Up", "Down" };
        const char* airs[5] = { "Nair", "Fair", "Bair", "Uair", "Dair" };
        for (i = 0; i < 4; ++i) {
            const RogueSpecialDef* special = RogueSpecial_Find(run->specials[i]);
            RogueText_Line(&screen, 32, 133+i*23, "%s: %s", slots[i], special ? special->name : "Native");
            RogueText_Style(&screen, 0.8f, 0xF6CD36);
        }
        for (i = 0; i < 5; ++i) {
            const RogueAerialDef* aerial = RogueAerial_Find(run->aerials[i]);
            RogueText_Line(&screen, 338, 133+i*20, "%s: %s", airs[i], aerial ? fighter_names[aerial->character] : "Native");
            RogueText_Style(&screen, 0.70f, 0xDAE2FF);
        }
        for (i = 0; i < ROGUE_UPGRADES; ++i) if (run->stacks[i]) {
            RogueText_Line(&screen, 32 + (line / 8) * 198, 240 + (line % 8) * 19,
                "%s x%u", rogue_upgrades[i].name, run->stacks[i]);
            RogueText_Style(&screen, 0.7f, 0xDFE5F7);
            line++;
        }
    } else {
        if (run->phase == ROGUE_REWARD || run->phase == ROGUE_SHOP) {
            RogueOfferState* offers = run->phase == ROGUE_SHOP ? &run->shop : &run->reward;
            for (i = 0; i < 3; ++i) {
                unsigned id = offers->ids[i], x = 20+i*204;
                const char* icon = id > ROGUE_AERIAL_OFFER_BASE ? "A" : id > ROGUE_UPGRADES ? "B" : "+";
                RogueText_Line(&screen, x+21, 146, "%s", icon);
                RogueText_Style(&screen, 1.2f, 0xF6CD36);
                RogueText_Line(&screen, x+49, 144, "%s", RogueOffer_Name(id));
                RogueText_Style(&screen, 0.53f, cursor == i ? 0xF6CD36 : 0xFFFFFF);
                RogueText_Line(&screen, x+49, 154, "%s", id > ROGUE_AERIAL_OFFER_BASE ? "AERIAL / COMMON" : id > ROGUE_UPGRADES ? "SPECIAL / COMMON" : "PASSIVE / COMMON");
                RogueText_Style(&screen, 0.50f, 0xAEB9D5);
                if (id > ROGUE_AERIAL_OFFER_BASE) {
                    const RogueAerialDef* move = RogueAerial_Find(id-ROGUE_AERIAL_OFFER_BASE);
                    const RogueAerialDef* previous = RogueAerial_Find(run->aerials[move->slot]);
                    RogueText_Line(&screen, x+12, 183, "%s", RogueOffer_Description(id));
                    RogueText_Style(&screen, 0.65f, 0xBAC3E0);
                    RogueText_Line(&screen, x+12, 199, "%s: %s", offers->sold[i] ? "Equipped" : "Replaces", previous ? fighter_names[previous->character] : "Native");
                    RogueText_Style(&screen, 0.52f, 0xAEB9D5);
                } else RogueText_Wrap(&screen, x+12, 183, 25, RogueOffer_Description(id));
                if (run->phase == ROGUE_SHOP) {
                    if (offers->sold[i]) RogueText_Line(&screen, x+12, 217, "SOLD");
                    else RogueText_Line(&screen, x+12, 217, "%u GOLD", RogueOffer_Price(run,id));
                    RogueText_Style(&screen, 0.65f, offers->sold[i] ? 0x9299AA : run->gold < RogueOffer_Price(run,id) ? 0xD36B72 : 0xF6CD36);
                } else {
                    RogueText_Line(&screen, x+12, 217, "FREE CHOICE");
                    RogueText_Style(&screen, 0.60f, 0xF6CD36);
                }
            }
        } else if (run->phase == ROGUE_ROUTE) {
            for (i = 0; i < 2; ++i) {
                unsigned recipe = run->preview[i].recipe;
                RogueText_Line(&screen, 36+i*320, 146, "%s %s", cursor == i ? ">" : " ", node_names[run->route[floor][i]]);
                RogueText_Style(&screen, 1.0f, cursor == i ? 0xF6CD36 : 0xFFFFFF);
                RogueText_Wrap(&screen, 36+i*320, 190, 25, recipe ? rogue_recipes[recipe-1].name : "Recover and prepare");
            }
        } else {
            RogueText_Line(&screen, 42, 150, "%s", run->phase == ROGUE_DEAD && run->death_reason == 2 ? "RUN ABANDONED" : phases[run->phase]);
            if (run->phase == ROGUE_REST)
                RogueText_Line(&screen, 42, 187, "DAMAGE %u%%   RECOVER %u%%   START: REST", run->carried_percent, 20 + 10 * run->stacks[13]);
            else RogueText_Line(&screen, 42, 187, "SCORE %u   FIGHTS %u", run->score, run->fights_won);
            RogueText_Style(&screen, 0.8f, 0xBAC3E0);
        }
        {
            unsigned choice = run->phase == ROGUE_ROUTE ? cursor % 2 : 0;
            const RogueEncounter* encounter = (run->phase == ROGUE_DEAD || run->phase == ROGUE_COMPLETE) ? &run->current : &run->preview[choice];
            RogueText_Line(&screen, 36, 372, "%s", fighter_names[run->character]);
            RogueText_Style(&screen, 1.0f, 0xFFFFFF);
            RogueText_Line(&screen, 36, 268, "YOUR FIGHTER");
            RogueText_Style(&screen, 0.65f, 0x9DAED5);
            RogueText_Line(&screen, 302, 325, "VS");
            RogueText_Style(&screen, 1.1f, 0xE84956);
            RogueText_Line(&screen, 354, 267, "%s", encounter->recipe ? rogue_recipes[encounter->recipe-1].name : node_names[run->route[floor][choice]]);
            RogueText_Style(&screen, 0.9f, 0xFFFFFF);
            for (i = 0; i < encounter->enemy_count; ++i) {
                RogueText_Line(&screen, 350+i*84, 366, "%s", fighter_names[encounter->fighters[i]]);
                RogueText_Style(&screen, 0.55f, 0xCBD3EC);
            }
            if (encounter->stage) {
                RogueText_Line(&screen, 354, 377, "%s / THREAT %u", stage_names[encounter->stage-1], RogueEncounter_Threat(encounter));
                RogueText_Style(&screen, 0.65f, 0xBBA0E4);
                RogueText_Line(&screen, 354, 393, "DMG %u%%  GUARD %u%%  SPEED %u%%", encounter->damage, encounter->defense, encounter->speed);
                RogueText_Style(&screen, 0.52f, 0xCBD3EC);
                RogueText_Line(&screen, 354, 408, "%s", rogue_recipes[encounter->recipe-1].rule);
                RogueText_Style(&screen, 0.58f, 0xF6CD36);
            }
        }
    }
    RogueText_Line(&screen, 24, 433, "B: %s   A: SELECT", build_view ? "CLOSE BUILD" : "CURRENT BUILD");
    RogueText_Style(&screen, 0.8f, 0xDEE5FB);
    if (run->phase == ROGUE_REWARD || run->phase == ROGUE_SHOP) {
        RogueText_Line(&screen, 389, 433, "X: REROLL  %u GOLD", RogueRun_RerollCost(run, run->phase == ROGUE_SHOP));
        RogueText_Style(&screen, 0.75f, run->gold < RogueRun_RerollCost(run, run->phase == ROGUE_SHOP) ? 0xD36B72 : 0xF6CD36);
    }
    if (feedback) RogueText_Line(&screen, 24, 447, "%s", feedback);
    else if (run->phase == ROGUE_DEAD || run->phase == ROGUE_COMPLETE)
        RogueText_Line(&screen, 24, 447, "A: RETRY    START: MAIN MENU    SEED %08X%08X", (unsigned) (run->seed >> 32), (unsigned) run->seed);
    else RogueText_Line(&screen, 24, 447, "LEFT / RIGHT: CHOOSE    START: CONTINUE    SEED %08X%08X", (unsigned) (run->seed >> 32), (unsigned) run->seed);
    RogueText_Style(&screen, 0.6f, 0x8A99BA);
    RogueText_End(&screen);
}

void RogueMode_Enter(void* data)
{
    (void) data;
    cursor = build_view = 0;
    feedback = NULL;
#if ROGUE_DEBUG && ROGUE_QA_CYCLES
    RogueDirector_Start(ROGUE_FIXTURE_SEED + qa_cycles, CKind_Fox);
    if (qa_cycles % 6 == 1) RogueRun_Shop(RogueDirector_Run());
    else if (qa_cycles % 6 == 2) RogueRun_ChooseUpgrade(RogueDirector_Run(),0);
    else if (qa_cycles % 6 == 3) { RogueDirector_Run()->phase=ROGUE_REST; RogueDirector_Run()->carried_percent=60; }
    else if (qa_cycles % 6 == 4) RogueDirector_Run()->phase = ROGUE_COMPLETE;
    else if (qa_cycles % 6 == 5) RogueDirector_Run()->phase = ROGUE_DEAD;
#endif
    RogueUi_Create(&ui);
    draw();
}

void RogueMode_Exit(void* data)
{
    (void) data;
    RogueUi_Destroy(&ui);
}

void RogueMode_Frame(void)
{
    RogueRun* run = RogueDirector_Run();
    u64 input = mn_80229624(0);
    unsigned count = run->phase == ROGUE_ROUTE ? 2 : 3;
#if ROGUE_DEBUG && ROGUE_QA_CYCLES
    if (++qa_frames == 2) { build_view = 1; draw(); }
    if (qa_frames == 3) { build_view = 0; draw(); }
    if (qa_frames >= 4) {
        qa_frames = 0;
        if (++qa_cycles >= ROGUE_QA_CYCLES) {
            gm_ChangeGameModeAfterCurrentScene(GM_MENU);
            gm_801A4B60();
        } else change_state(0);
    }
    return;
#endif
    { int qa = RogueAerialQa_Progression(); if (qa) { if (qa == 2) change_state(2); return; } }
    { int qa = RogueSpecialQa_Progression(); if (qa) { if (qa == 2) change_state(2); return; } }
    /* The controlled fixture exercises native result computation, not player skill. */
#if ROGUE_DEBUG && ROGUE_QA_MODE == 2
    if (++qa_frames < 60) return;
    qa_frames = 0;
    if (qa_matches >= ROGUE_QA_MATCHES || qa_failures) {
        OSReport("[rogue] match_qa_complete transitions=%u failures=%u phase=%u\n", qa_matches, qa_failures, run->phase);
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
        return;
    }
    if (run->phase == ROGUE_COMPLETE) RogueDirector_Start(ROGUE_FIXTURE_SEED + qa_matches, CKind_Fox);
    if (run->phase == ROGUE_SHOP || run->phase == ROGUE_REST) RogueRun_LeaveService(run);
    if (run->phase == ROGUE_REWARD) RogueRun_ChooseUpgrade(run, 0);
    if (run->phase == ROGUE_ROUTE) RogueRun_ChooseRoute(run, 0);
    if (run->phase == ROGUE_FIGHT) {
        memset(run->specials, 0, sizeof(run->specials));
        run->specials[ROGUE_ABILITY_NEUTRAL] = Rogue_AbilityForOpponent(CKind_Falco, ROGUE_ABILITY_NEUTRAL);
        change_state(2);
    } else draw();
    return;
#endif
    if (run->phase == ROGUE_FIGHT) { change_state(2); return; }
    if (!input) return;
    feedback = NULL;
#if ROGUE_DEBUG
    OSReport("[rogue] ui_input phase=%u mask=%x cursor=%u build=%u\n", run->phase, (unsigned) input, cursor, build_view);
#endif
    if (input & MenuInput_Back) { build_view = !build_view; sfxBack(); }
    if (!build_view) {
        if (input & (MenuInput_Up | MenuInput_Left)) { cursor = (cursor + count - 1) % count; sfxMove(); }
        if (input & (MenuInput_Down | MenuInput_Right)) { cursor = (cursor + 1) % count; sfxMove(); }
        if ((input & MenuInput_XButton) && (run->phase == ROGUE_REWARD || run->phase == ROGUE_SHOP))
            feedback = RogueRun_Reroll(run, run->phase == ROGUE_SHOP) ? "New offers ready" : "Reroll unavailable: check gold or sold slots";
        if (input & MenuInput_AButton) {
            sfxForward();
            if (run->phase == ROGUE_REWARD) RogueRun_ChooseUpgrade(run, cursor);
            else if (run->phase == ROGUE_ROUTE) RogueRun_ChooseRoute(run, cursor % 2);
            else if (run->phase == ROGUE_SHOP)
                feedback = RogueRun_Buy(run, cursor) ? "Added to your build" : "Offer unavailable: check gold or sold status";
            else if (run->phase == ROGUE_DEAD || run->phase == ROGUE_COMPLETE) {
                RogueDirector_Start((RogueSeed) OSGetTime(), run->character);
                cursor = 0;
            }
        }
        if (input & MenuInput_StartButton) {
            if (run->phase == ROGUE_SHOP || run->phase == ROGUE_REST) RogueRun_LeaveService(run);
            else if (run->phase == ROGUE_DEAD || run->phase == ROGUE_COMPLETE) {
                gm_ChangeGameModeAfterCurrentScene(GM_MENU);
                gm_801A4B60();
                return;
            }
        }
        if (run->phase == ROGUE_FIGHT) { change_state(2); return; }
    }
    draw();
}

void RogueMode_MenuFrame(void)
{
    if (RogueCapabilities_Get()->supported && gm_GetCurrentGameMode() == GM_MENU && (gm_GetButtonsTriggered(0) & PAD_BUTTON_X)) {
        menu_requested = 1;
        gm_801A4B60();
    }
}

unsigned RogueMode_MenuDestination(unsigned native_mode)
{
    if (menu_requested) { menu_requested = 0; return GM_ROGUE; }
    return native_mode;
}

void RogueMode_MenuHint(int canvas)
{
    RogueText hint;
    RogueText_Create(&hint, 0, canvas);
    hint.native->pos_x = -9.5f;
    hint.native->pos_y = 11.5f;
    hint.native->pos_z = 17.0f;
    hint.native->font_size.x = hint.native->font_size.y = 0.040f;
    RogueText_Begin(&hint);
    RogueText_Line(&hint, 0, 0, "X: ROGUE RUN");
    RogueText_Style(&hint, 1.0f, 0xF6CD36);
    RogueText_End(&hint);
    /* Ownership is transferred to the retail menu SIS canvas. Its normal
     * HSD_SisLib_803A5E70 teardown destroys this text with the native entries. */
}

bool RogueMode_CharacterUnlocked(u8 kind)
{
    if (gm_GetCurrentGameMode() == GM_ROGUE) return kind < RogueCapabilities_Get()->roster_count;
    return gm_IsCKindUnlocked(kind);
}

void RogueMode_MatchFrame(void)
{
    if (gm_GetDbPauseFlag(1) || gm_GetDbPauseFlag(2)) return;
    RogueSpecialQa_Frame();
    RogueAerialQa_Frame();
    if (RogueRuntime_IsActive() && RogueRuntime_Get()->scene == GS_VS) {
        RogueRun* run = RogueDirector_Run();
        ++encounter_frames;
#if ROGUE_DEBUG && ROGUE_QA_PASSIVES
        if (encounter_frames == 150) RoguePassiveQa_Check();
#endif
        if ((run->current.tags & 64) && encounter_frames % 180 == 0) {
            Fighter_GObj* entity = Player_GetEntity(1);
            Fighter* fighter = entity ? entity->user_data : NULL;
            if (fighter && fighter->ground_or_air == GA_Ground &&
                fighter->motion_id >= ftCo_MS_Wait && fighter->motion_id <= ftCo_MS_WalkFast &&
                ftData_SpecialN[fighter->kind])
                ftData_SpecialN[fighter->kind](entity);
        }
    }
#if ROGUE_DEBUG && ROGUE_QA_MODE == 2
    unsigned i;
    if (!RogueRuntime_IsActive() || RogueRuntime_Get()->scene != GS_VS) return;
    ++qa_frames;
    if (qa_frames == 180 || qa_frames == 360) {
        Fighter_GObj* entity = Player_GetEntity(0);
        Fighter* fighter = entity ? entity->user_data : NULL;
        if (fighter) {
            if (qa_frames == 360) {
                fighter->cur_pos.y += 30.0f;
                ftCommon_8007D5D4(fighter);
                ftCo_Fall_Enter(entity);
            }
            OSReport("[rogue] special_qa id=%u air=%d entered=%d\n",
                RogueDirector_Run()->specials[0], qa_frames == 360,
                Rogue_TrySpecial(entity, ROGUE_ABILITY_NEUTRAL, qa_frames == 360));
        }
    }
    if (qa_frames == 450) {
        unsigned present = 0;
        for (i = 0; i <= RogueDirector_Run()->current.enemy_count; ++i)
            if (Player_GetEntity(i)) present++;
        OSReport("[rogue] match_qa frames=450 fighters=%u expected=%u\n", present,
            RogueDirector_Run()->current.enemy_count + 1);
        if (present != RogueDirector_Run()->current.enemy_count + 1) qa_failures++;
        if (qa_matches + 1 == ROGUE_QA_MATCHES) Player_SetStocks(0, 0);
        else for (i = 1; i <= RogueDirector_Run()->current.enemy_count; ++i) Player_SetStocks(i, 0);
    }
#endif
}
