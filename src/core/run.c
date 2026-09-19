#include "run.h"
#include "balance.h"
#include "offers.h"
#include "score.h"
#include "../upgrades/upgrade_registry.h"
#include "../encounters/encounter_registry.h"
#include <string.h>

static void history(RogueRun* run, unsigned kind, unsigned cost, unsigned a, unsigned b, unsigned c)
{
    RogueHistoryEvent* event = &run->history[run->history_count % ROGUE_HISTORY];
    memset(event,0,sizeof(*event));
    event->kind=kind; event->floor=run->floor; event->cost=cost;
    event->generation=run->history_count;
    event->after[0]=a; event->after[1]=b; event->after[2]=c;
    run->history_count++;
}

static void offers(RogueRun* run, RogueOfferState* state, RogueRng* rng, int reroll)
{
    unsigned candidates[ROGUE_OFFERS], old[3], count = 0, i, j, pass;
    memcpy(old, state->ids, sizeof(old));
    /* Prefer new eligible IDs; append old ones only if the pool is too small. */
    for (pass = 0; pass < 2; ++pass) {
        unsigned start = count;
        for (i = 0; i < ROGUE_OFFERS; ++i) {
            int previous = 0, locked = 0;
            if (!RogueOffer_Eligible(run, i + 1)) continue;
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
        if (recipe->roster[(run->act - 1 + i) % 3] != 255)
            out->fighters[i] = recipe->roster[(run->act - 1 + i) % 3];
        out->stocks[i] = recipe->stocks;
    }
    if (out->tags & 128U) out->fighters[0] = run->character;
    if (out->tags & 128U) {
        unsigned offense = run->stacks[0] + run->stacks[14] + run->stacks[23];
        unsigned mobility = run->stacks[2] + run->stacks[3] + run->stacks[4];
        /* Bounded counter-build policy uses purchased traits, never live inputs. */
        if (offense > mobility) out->defense += offense > 5 ? 15 : offense * 3;
        else out->speed += mobility > 5 ? 15 : mobility * 3;
    }
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
void RogueRun_Init(RogueRun* run, RogueSeed seed, unsigned character)
{
    unsigned i, j;
    memset(run, 0, sizeof(*run));
    run->version = 3; run->seed = seed; run->character = character % 26;
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
    if (!RogueOffer_Apply(run, id)) return 0;
    history(run,3,0,id,slot,0);
    run->reward.claimed = 1; run->phase = ROGUE_ROUTE;
    return 1;
}
int RogueRun_ChooseRoute(RogueRun* run, unsigned slot)
{
    unsigned type;
    if (run->phase != ROGUE_ROUTE || slot >= 2 || run->floor >= ROGUE_FLOORS) return 0;
    run->selected_route[run->floor] = slot;
    run->current = run->preview[slot];
    history(run,4,0,run->current.recipe,run->current.tags,run->current.stage);
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
    tier = run->route[run->floor][run->selected_route[run->floor]];
    run->native_score = native_score;
    run->score += RogueScore_Combat(native_score,tier,run->stacks[12],won);
    history(run,5,0,won != 0,native_score,run->carried_percent);
    if (!won) { run->death_reason = 1; run->phase = ROGUE_DEAD; return 1; }
    run->fights_won++;
    {
        unsigned gold = tier == ROGUE_BOSS ? ROGUE_BOSS_REWARD : tier == ROGUE_ELITE ? ROGUE_ELITE_REWARD : ROGUE_NORMAL_REWARD;
        run->gold += gold + (gold / 10) * run->stacks[11];
    }
    advance(run); return 1;
}
int RogueRun_LeaveService(RogueRun* run)
{
    if (run->phase != ROGUE_SHOP && run->phase != ROGUE_REST) return 0;
    if (run->phase == ROGUE_REST) {
        unsigned recovery = 20 + 10 * run->stacks[13];
        run->carried_percent = run->carried_percent > recovery ? run->carried_percent - recovery : 0;
        history(run,7,0,recovery,run->carried_percent,0);
    }
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
    run->reroll_gold_spent += cost;
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
    if (!RogueOffer_Eligible(run, id)) return 0;
    price = RogueOffer_Price(run, id);
    if (run->gold < price) return 0;
    run->gold -= price; run->gold_spent += price;
    RogueOffer_Apply(run, id); run->shop.sold[slot] = 1;
    history(run,6,price,id,slot,0);
    return 1;
}
