#include "run.h"
#include "balance.h"
#include "../upgrades/upgrade_registry.h"
#include "../encounters/encounter_registry.h"
#include <string.h>

static void offers(RogueRun* run, RogueOfferState* state, RogueRng* rng, int reroll)
{
    unsigned candidates[ROGUE_UPGRADES], old[3], count = 0, i, j, pass;
    memcpy(old, state->ids, sizeof(old));
    /* Prefer new eligible IDs; append old ones only if the pool is too small. */
    for (pass = 0; pass < 2; ++pass) {
        unsigned start = count;
        for (i = 0; i < ROGUE_UPGRADES; ++i) {
            int previous = 0, locked = 0;
            if (run->stacks[i] >= rogue_upgrades[i].max_stacks) continue;
            for (j = 0; j < 3; ++j) {
                if (old[j] == i + 1 && reroll) previous = 1;
                if (state->sold[j] && old[j] == i + 1) locked = 1;
            }
            if (!locked && previous == (int) pass) candidates[count++] = i + 1;
        }
        /* Shuffle each preference group independently. */
        {
            unsigned end = count;
            for (i = end; i > start + 1; --i) {
                unsigned pick = start + RogueRng_Bounded(rng, i - start);
                unsigned tmp = candidates[i - 1]; candidates[i - 1] = candidates[pick]; candidates[pick] = tmp;
            }
        }
    }
    j = 0;
    for (i = 0; i < 3; ++i) if (!state->sold[i]) state->ids[i] = j < count ? candidates[j++] : 0;
}

void RogueEncounter_Generate(RogueRun* run, unsigned tier, RogueEncounter* out)
{
    unsigned pool[ROGUE_RECIPES], count = 0, i, j, pick, total = 0;
    const RogueRecipe* recipe;
    memset(out, 0, sizeof(*out));
    for (i = 0; i < ROGUE_RECIPES; ++i) {
        int recent = 0;
        if (rogue_recipes[i].tier != tier) continue;
        for (j = 0; j < rogue_recipes[i].cooldown && j < 4; ++j)
            if (run->recent_recipes[j] == i + 1) recent = 1;
        if (!recent) pool[count++] = i;
    }
    if (!count) for (i = 0; i < ROGUE_RECIPES; ++i)
        if (rogue_recipes[i].tier == tier) pool[count++] = i;
    for (i = 0; i < count; ++i) total += rogue_recipes[pool[i]].weight;
    pick = RogueRng_Bounded(&run->encounter_rng, total);
    for (i = 0; i + 1 < count && pick >= rogue_recipes[pool[i]].weight; ++i)
        pick -= rogue_recipes[pool[i]].weight;
    out->recipe = pool[i] + 1; recipe = &rogue_recipes[pool[i]];
    out->enemy_count = recipe->enemies;
    out->tags = recipe->tags;
    out->damage = recipe->damage + (run->act - 1) * 5;
    out->defense = recipe->defense; out->speed = recipe->speed;
    out->scale = recipe->scale; out->starting_percent = recipe->percent;
    count = 0;
    for (i = 0; i < 6; ++i) if ((recipe->stage_mask & (1U << i)) && run->recent_stages[0] != i + 1)
        pool[count++] = i + 1;
    if (!count) for (i = 0; i < 6; ++i) if (recipe->stage_mask & (1U << i)) pool[count++] = i + 1;
    out->stage = pool[RogueRng_Bounded(&run->encounter_rng, count)];
    for (i = 0; i < out->enemy_count; ++i) {
        out->fighters[i] = RogueRng_Bounded(&run->encounter_rng, 26);
        out->stocks[i] = recipe->stocks;
    }
    if (out->tags & 128U) out->fighters[0] = run->character;
    if (out->tags & 1024U) out->stocks[0]++;
    for (i = 3; i > 0; --i) run->recent_recipes[i] = run->recent_recipes[i - 1];
    run->recent_recipes[0] = out->recipe;
    for (i = 2; i > 0; --i) run->recent_stages[i] = run->recent_stages[i - 1];
    run->recent_stages[0] = out->stage;
    run->encounters++;
}

static void previews(RogueRun* run)
{
    unsigned i;
    for (i = 0; i < 2; ++i) {
        unsigned tier = run->route[run->floor][i];
        memset(&run->preview[i], 0, sizeof(run->preview[i]));
        if (tier <= ROGUE_BOSS) RogueEncounter_Generate(run, tier, &run->preview[i]);
    }
}

void RogueRun_Reward(RogueRun* run)
{
    memset(&run->reward, 0, sizeof(run->reward));
    offers(run, &run->reward, &run->reward_rng, 0);
    run->phase = ROGUE_REWARD;
}
void RogueRun_Shop(RogueRun* run)
{
    memset(&run->shop, 0, sizeof(run->shop));
    offers(run, &run->shop, &run->shop_rng, 0);
    run->phase = ROGUE_SHOP;
}
void RogueRun_Init(RogueRun* run, unsigned seed, unsigned character)
{
    unsigned i, j;
    memset(run, 0, sizeof(*run));
    run->version = 1; run->seed = seed; run->character = character % 26;
    run->act = 1; run->gold = ROGUE_STARTING_GOLD;
    RogueRng_Init(&run->route_rng, seed, 0);
    RogueRng_Init(&run->encounter_rng, seed, 1);
    RogueRng_Init(&run->reward_rng, seed, 2);
    RogueRng_Init(&run->shop_rng, seed, 3);
    for (i = 0; i < ROGUE_FLOORS; ++i) for (j = 0; j < 2; ++j) {
        unsigned roll = RogueRng_Bounded(&run->route_rng, 10);
        run->route[i][j] = i % 5 == 4 ? ROGUE_BOSS : roll < 5 ? ROGUE_NORMAL : roll < 8 ? ROGUE_ELITE : roll == 8 ? ROGUE_NODE_SHOP : ROGUE_NODE_REST;
    }
    /* First floor always supports a combat introduction. */
    run->route[0][0] = run->route[0][1] = ROGUE_NORMAL;
    previews(run); RogueRun_Reward(run);
}
int RogueRun_ChooseUpgrade(RogueRun* run, unsigned slot)
{
    unsigned id;
    if (run->phase != ROGUE_REWARD || slot >= 3 || run->reward.claimed) return 0;
    id = run->reward.ids[slot];
    if (!id || run->stacks[id - 1] >= rogue_upgrades[id - 1].max_stacks) return 0;
    run->stacks[id - 1]++; run->reward.claimed = 1; run->phase = ROGUE_ROUTE;
    return 1;
}
int RogueRun_ChooseRoute(RogueRun* run, unsigned slot)
{
    unsigned type;
    if (run->phase != ROGUE_ROUTE || slot >= 2 || run->floor >= ROGUE_FLOORS) return 0;
    run->selected_route[run->floor] = slot;
    run->current = run->preview[slot];
    type = run->route[run->floor][slot];
    if (type == ROGUE_NODE_SHOP) RogueRun_Shop(run);
    else run->phase = type == ROGUE_NODE_REST ? ROGUE_REST : ROGUE_FIGHT;
    return 1;
}
static void advance(RogueRun* run)
{
    run->floor++;
    if (run->floor >= ROGUE_FLOORS) { run->phase = ROGUE_COMPLETE; return; }
    run->act = run->floor / 5 + 1;
    previews(run); RogueRun_Reward(run);
}
int RogueRun_MatchEnd(RogueRun* run, int won, unsigned native_score)
{
    unsigned tier;
    if (run->phase != ROGUE_FIGHT) return 0;
    if (!won) { run->phase = ROGUE_DEAD; return 1; }
    tier = run->route[run->floor][run->selected_route[run->floor]];
    run->score += native_score;
    run->gold += tier == ROGUE_BOSS ? ROGUE_BOSS_REWARD : tier == ROGUE_ELITE ? ROGUE_ELITE_REWARD : ROGUE_NORMAL_REWARD;
    advance(run); return 1;
}
int RogueRun_LeaveService(RogueRun* run)
{
    if (run->phase != ROGUE_SHOP && run->phase != ROGUE_REST) return 0;
    advance(run); return 1;
}
unsigned RogueRun_RerollCost(const RogueRun* run, int shop)
{
    unsigned uses = shop ? run->shop.rerolls : run->reward.rerolls;
    unsigned base = shop ? ROGUE_SHOP_REROLL_BASE : ROGUE_UPGRADE_REROLL_BASE;
    unsigned step = shop ? ROGUE_SHOP_REROLL_STEP : ROGUE_UPGRADE_REROLL_STEP;
    if (uses > (0xffffffffU - base) / step) return 0xffffffffU;
    return base + step * uses;
}
int RogueRun_Reroll(RogueRun* run, int shop)
{
    RogueOfferState* state = shop ? &run->shop : &run->reward;
    RogueHistoryEvent* event;
    unsigned cost = RogueRun_RerollCost(run, shop), i, available = 0;
    if (run->phase != (unsigned) (shop ? ROGUE_SHOP : ROGUE_REWARD) || state->claimed || run->gold < cost) return 0;
    for (i = 0; i < 3; ++i) if (!state->sold[i]) available++;
    if (!available) return 0;
    event = &run->history[run->history_count % ROGUE_HISTORY];
    memset(event, 0, sizeof(*event));
    event->kind = shop ? 2 : 1; event->floor = run->floor; event->cost = cost;
    memcpy(event->before, state->ids, sizeof(event->before));
    offers(run, state, shop ? &run->shop_rng : &run->reward_rng, 1);
    run->gold -= cost; run->gold_spent += cost; run->rerolls_used++;
    state->rerolls++; state->generation++;
    event->generation = state->generation;
    memcpy(event->after, state->ids, sizeof(event->after));
    run->history_count++;
    return 1;
}
int RogueRun_Buy(RogueRun* run, unsigned slot)
{
    unsigned id, price;
    if (run->phase != ROGUE_SHOP || slot >= 3 || run->shop.sold[slot]) return 0;
    id = run->shop.ids[slot];
    if (!id || run->stacks[id - 1] >= rogue_upgrades[id - 1].max_stacks) return 0;
    price = rogue_upgrades[id - 1].price;
    if (run->gold < price) return 0;
    run->gold -= price; run->gold_spent += price;
    run->stacks[id - 1]++; run->shop.sold[slot] = 1;
    return 1;
}
