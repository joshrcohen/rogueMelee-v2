#include "rogue_mode.h"
#include "../../director/rogue_director.h"
#include "../../upgrades/upgrade_registry.h"
#include "../../encounters/encounter_registry.h"
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gmscene.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/gmvs.h>
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
static HSD_Text* screen;
static unsigned generation, cursor, build_view;
static unsigned qa_cycles, qa_frames;
static const unsigned stages[6] = { 31, 32, 28, 8, 2, 3 };

static void change_state(unsigned id)
{
    gm_SetNextGameModeStateId(id);
    gm_801A4B60();
}

void RogueMode_Load(void)
{
    gm_InitVsMode(&selection);
    selection.start.players[0].ckind = CKind_Fox;
    selection.start.players[0].slot_type = Gm_PKind_Human;
    css.unk_0x0 = 0;
#if ROGUE_DEBUG && ROGUE_QA_MODE
    qa_cycles = qa_frames = 0;
    RogueDirector_Start(0x524f4755, CKind_Fox);
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
    RogueDirector_Start((unsigned) OSGetTick(), selection.start.players[0].ckind);
    gm_SetNextGameModeStateId(1);
}

static void enter_match(GameModeState* state)
{
    RogueRun* run = RogueDirector_Run();
    unsigned i;
    u64 audio = 0;
    (void) state;
    memset(&result, 0, sizeof(result));
    gm_SetupRulesDefaults(&match.rules);
    match.rules.match_kind = MatchKind_Stock;
    match.rules.is_stock = true;
    match.rules.is_vs = true;
    match.rules.is_teams = true;
    match.rules.item_freq = -1;
    match.rules.stkind = stages[run->current.stage - 1];
    for (i = 0; i < GM_MAX_PLAYERS; ++i) {
        PlayerInitData* player = &match.players[i];
        gm_SetupPlayerDefaults(player);
        player->slot = i;
        if (i > run->current.enemy_count) continue;
        player->ckind = i ? run->current.fighters[i - 1] : run->character;
        player->slot_type = i ? Gm_PKind_Cpu : Gm_PKind_Human;
        player->stocks = i ? run->current.stocks[i - 1] : 3;
        player->team = i ? 1 : 0;
        player->cpu_level = 3 + run->act * 2;
        if (i) {
            player->attack_ratio = run->current.damage / 100.0f;
            player->defense_ratio = run->current.defense / 100.0f;
            player->model_scale = run->current.scale / 100.0f;
            player->damage = run->current.starting_percent;
        }
        audio |= lbAudioAx_80026E84(player->ckind);
    }
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
    (void) state;
    RogueRun_MatchEnd(RogueDirector_Run(), won, 0);
    OSReport("[rogue] match_exit outcome=%u won=%d phase=%u floor=%u\n",
        result.match_end.outcome, won, RogueDirector_Run()->phase, RogueDirector_Run()->floor);
    gm_SetNextGameModeStateId(1);
}

GameModeState RogueMode_States[] = {
#if ROGUE_DEBUG && ROGUE_QA_MODE
    { 0, lbDvdPreload_2, 0, NULL, NULL, { GS_ROGUE, NULL, NULL } },
#else
    { 0, lbDvdPreload_3, 0, enter_css, exit_css, { GS_CSS, &css, &css } },
#endif
    { 1, lbDvdPreload_2, 0, NULL, NULL, { GS_ROGUE, NULL, NULL } },
    { 2, lbDvdPreload_2, 0, enter_match, exit_match, { GS_VS, &match, &result } },
    { GM_GAMEMODESTATE_TERMINATE }
};

static void draw(void)
{
    RogueRun* run = RogueDirector_Run();
    unsigned i;
    const char* phases[] = { "Select", "Choose an upgrade", "Choose your route",
        "Battle", "Shop", "Rest", "Run ended", "Run complete" };
    if (screen) HSD_SisLib_803A5CC4(screen);
    screen = HSD_SisLib_803A6754(4, 0);
    screen->font_size.x = screen->font_size.y = 0.6f;
    screen->default_kerning = 1;
    HSD_SisLib_803A6B98(screen, 35, 25, "rogueMelee   Act %u / 3   Floor %u / 15", run->act, run->floor + 1);
    HSD_SisLib_803A6B98(screen, 35, 65, "%s   Gold %u   Seed %08X", phases[run->phase], run->gold, run->seed);
    if (build_view) {
        unsigned line = 0;
        for (i = 0; i < ROGUE_UPGRADES; ++i) if (run->stacks[i]) {
            HSD_SisLib_803A6B98(screen, 35 + (line / 10) * 300, 110 + (line % 10) * 25,
                              "%s x%u", rogue_upgrades[i].name, run->stacks[i]);
            line++;
        }
    } else if (run->phase == ROGUE_REWARD || run->phase == ROGUE_SHOP) {
        RogueOfferState* offers = run->phase == ROGUE_SHOP ? &run->shop : &run->reward;
        for (i = 0; i < 3; ++i) {
            unsigned id = offers->ids[i];
            const RogueUpgradeDef* def = id ? &rogue_upgrades[id - 1] : NULL;
            HSD_SisLib_803A6B98(screen, 35, 130 + i * 75, "%s %s %s", cursor == i ? ">" : " ",
                def ? def->name : "No offers", offers->sold[i] ? "(Sold)" : "");
            if (def) HSD_SisLib_803A6B98(screen, 55, 158 + i * 75, "%s", def->description);
        }
        HSD_SisLib_803A6B98(screen, 35, 380, "X: Reroll (%u gold)", RogueRun_RerollCost(run, run->phase == ROGUE_SHOP));
    } else if (run->phase == ROGUE_ROUTE) {
        for (i = 0; i < 2; ++i) {
            unsigned recipe = run->preview[i].recipe;
            HSD_SisLib_803A6B98(screen, 35, 150 + i * 80, "%s %s", cursor == i ? ">" : " ",
                recipe ? rogue_recipes[recipe - 1].name : run->route[run->floor][i] == ROGUE_NODE_SHOP ? "Shop" : "Rest");
        }
    }
    HSD_SisLib_803A6B98(screen, 35, 430, "A: Choose   B: Build   Start: Continue");
}

void RogueMode_Enter(void* data)
{
    (void) data;
    cursor = build_view = 0;
    screen = NULL;
    generation = RogueRuntime_Get()->scene_generation;
    HSD_SisLib_803A62A0(4, "SdMenu.usd", "SIS_MenuData");
    HSD_SisLib_803A611C(4, NULL, 7, 8, 128, 5, 128, 0);
    RogueRuntime_ResourceAcquire(generation);
    draw();
}

void RogueMode_Exit(void* data)
{
    (void) data;
    HSD_SisLib_803A5F50(4);
    screen = NULL;
    RogueRuntime_ResourceRelease(generation);
}

void RogueMode_Frame(void)
{
    RogueRun* run = RogueDirector_Run();
    u64 input = mn_80229624(0);
    unsigned count = run->phase == ROGUE_ROUTE ? 2 : 3;
#if ROGUE_DEBUG && ROGUE_QA_CYCLES
    if (++qa_frames >= 2) {
        qa_frames = 0;
        if (++qa_cycles >= ROGUE_QA_CYCLES) {
            gm_ChangeGameModeAfterCurrentScene(GM_MENU);
            gm_801A4B60();
        } else change_state(0);
    }
    return;
#endif
    /* The controlled fixture exercises native result computation, not player skill. */
#if ROGUE_DEBUG && ROGUE_QA_MODE == 2
    if (run->floor == 0 && ++qa_frames == 60) {
        RogueRun_ChooseUpgrade(run, 0);
        RogueRun_ChooseRoute(run, 0);
        qa_frames = 0;
        change_state(2);
    }
    return;
#endif
    if (!input) return;
    if (input & MenuInput_Back) build_view = !build_view;
    if (!build_view) {
        if (input & (MenuInput_Up | MenuInput_Left)) cursor = (cursor + count - 1) % count;
        if (input & (MenuInput_Down | MenuInput_Right)) cursor = (cursor + 1) % count;
        if (input & MenuInput_XButton) RogueRun_Reroll(run, run->phase == ROGUE_SHOP);
        if (input & MenuInput_Confirm) {
            if (run->phase == ROGUE_REWARD) RogueRun_ChooseUpgrade(run, cursor);
            else if (run->phase == ROGUE_ROUTE) RogueRun_ChooseRoute(run, cursor % 2);
            else if (run->phase == ROGUE_SHOP) RogueRun_Buy(run, cursor);
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
    if (gm_GetCurrentGameMode() == GM_MENU && (mn_80229624(0) & MenuInput_XButton)) {
        gm_ChangeGameModeAfterCurrentScene(GM_ROGUE);
        gm_801A4B60();
    }
}

void RogueMode_MatchFrame(void)
{
#if ROGUE_DEBUG && ROGUE_QA_MODE == 2
    unsigned i;
    if (!RogueRuntime_IsActive() || RogueRuntime_Get()->scene != GS_VS) return;
    if (++qa_frames == 300) {
        unsigned present = 0;
        for (i = 0; i <= RogueDirector_Run()->current.enemy_count; ++i)
            if (Player_GetEntity(i)) present++;
        OSReport("[rogue] match_qa frames=300 fighters=%u expected=%u\n", present,
            RogueDirector_Run()->current.enemy_count + 1);
        for (i = 1; i <= RogueDirector_Run()->current.enemy_count; ++i)
            Player_SetStocks(i, 0);
    }
#endif
}
