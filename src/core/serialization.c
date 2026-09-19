#include "run.h"
#include "offers.h"
#include "../upgrades/upgrade_registry.h"
#include <string.h>

typedef struct Codec { unsigned char* out; const unsigned char* in; unsigned pos, size, ok; } Codec;
static void word(Codec* c, unsigned* value)
{
    unsigned i, v = *value;
    if (c->pos + 4 > c->size) { c->ok = 0; return; }
    if (c->out) for (i = 0; i < 4; ++i) c->out[c->pos + i] = (unsigned char) (v >> (24 - 8 * i));
    else { v = 0; for (i = 0; i < 4; ++i) v = (v << 8) | c->in[c->pos + i]; *value = v; }
    c->pos += 4;
}
static void array(Codec* c, unsigned* p, unsigned count)
{
    unsigned i; for (i = 0; i < count; ++i) word(c, &p[i]);
}
static void offer(Codec* c, RogueOfferState* s)
{
    array(c,s->ids,3); array(c,s->sold,3);
    word(c,&s->generation); word(c,&s->rerolls); word(c,&s->claimed);
}
static void encounter(Codec* c, RogueEncounter* e)
{
    word(c,&e->recipe); word(c,&e->stage); word(c,&e->enemy_count);
    array(c,e->fighters,3); array(c,e->stocks,3);
    word(c,&e->tags); word(c,&e->damage); word(c,&e->defense);
    word(c,&e->speed); word(c,&e->scale); word(c,&e->starting_percent);
}
static void codec(Codec* c, RogueRun* r)
{
    unsigned i, high = (unsigned) (r->seed >> 32), low = (unsigned) r->seed;
#define FIELD(name) word(c, &r->name)
    FIELD(version); word(c,&high); word(c,&low);
    if (c->in) r->seed = ((RogueSeed) high << 32) | low;
    FIELD(character); FIELD(act); FIELD(floor);
    FIELD(phase); FIELD(gold); FIELD(score);
    for (i=0;i<ROGUE_FLOORS;++i) array(c,r->route[i],2);
    array(c,r->selected_route,ROGUE_FLOORS); array(c,r->stacks,ROGUE_UPGRADES);
    array(c,r->specials,4); array(c,r->recent_recipes,4); array(c,r->recent_stages,3);
    FIELD(encounters); FIELD(gold_spent); FIELD(rerolls_used); FIELD(history_count); FIELD(carried_percent);
    FIELD(fights_won); FIELD(death_reason); FIELD(native_score); FIELD(reroll_gold_spent);
    FIELD(route_rng.state); FIELD(route_rng.draws); FIELD(encounter_rng.state); FIELD(encounter_rng.draws);
    FIELD(reward_rng.state); FIELD(reward_rng.draws); FIELD(shop_rng.state); FIELD(shop_rng.draws);
    offer(c,&r->reward); offer(c,&r->shop);
    encounter(c,&r->preview[0]); encounter(c,&r->preview[1]); encounter(c,&r->current);
    for (i=0;i<ROGUE_HISTORY;++i) {
        FIELD(history[i].kind); FIELD(history[i].floor); FIELD(history[i].cost); FIELD(history[i].generation);
        array(c,r->history[i].before,3); array(c,r->history[i].after,3);
    }
#undef FIELD
}

static int valid_encounter(const RogueEncounter* e)
{
    unsigned i;
    if (!e->recipe) return e->enemy_count == 0 && e->stage == 0;
    if (e->recipe > ROGUE_RECIPES || e->stage < 1 || e->stage > 6 ||
        e->enemy_count < 1 || e->enemy_count > 3 || e->damage < 1 || e->damage > 500 ||
        e->defense < 1 || e->defense > 500 || e->speed < 1 || e->speed > 200 ||
        e->scale < 25 || e->scale > 200 || e->starting_percent > 999) return 0;
    for (i = 0; i < e->enemy_count; ++i)
        if (e->fighters[i] >= 26 || e->stocks[i] < 1 || e->stocks[i] > 9) return 0;
    return 1;
}
unsigned RogueRun_Serialize(const RogueRun* run, unsigned char* out, unsigned capacity)
{
    RogueRun copy;
    Codec c;
    if (!run || !out) return 0;
    copy = *run;
    c.out=out; c.in=0; c.pos=0; c.size=capacity; c.ok=1;
    codec(&c,&copy);
    return c.ok ? c.pos : 0;
}
int RogueRun_Deserialize(RogueRun* run, const unsigned char* data, unsigned size)
{
    RogueRun copy;
    Codec c;
    unsigned i,j;
    if (!run || !data) return 0;
    memset(&copy,0,sizeof(copy));
    c.out=0; c.in=data; c.pos=0; c.size=size; c.ok=1;
    codec(&c,&copy);
    if (!c.ok || c.pos != size || copy.version != 3 || copy.character >= 26 || copy.carried_percent > 999 ||
        copy.act < 1 || copy.act > 3 || copy.floor > ROGUE_FLOORS || copy.phase > ROGUE_COMPLETE ||
        (copy.floor == ROGUE_FLOORS && copy.phase != ROGUE_COMPLETE)) return 0;
    for(i=0;i<ROGUE_FLOORS;++i) {
        if(copy.selected_route[i]>1) return 0;
        for(j=0;j<2;++j) if(copy.route[i][j]>ROGUE_NODE_REST) return 0;
    }
    if (copy.fights_won > ROGUE_FLOORS || copy.death_reason > 2 ||
        copy.reroll_gold_spent > copy.gold_spent ||
        copy.gold > 1000000 || copy.score > 100000000 ||
        copy.reward.claimed > 1 || copy.shop.claimed > 1) return 0;
    for (i = 0; i < ROGUE_UPGRADES; ++i)
        if (copy.stacks[i] > rogue_upgrades[i].max_stacks) return 0;
    for(i=0;i<3;++i) if(copy.reward.ids[i]>ROGUE_OFFERS || copy.shop.ids[i]>ROGUE_OFFERS ||
        copy.shop.sold[i]>1 || copy.reward.sold[i]>1) return 0;
    if (!valid_encounter(&copy.current) || !valid_encounter(&copy.preview[0]) ||
        !valid_encounter(&copy.preview[1])) return 0;
    for(i=0;i<4;++i) if(copy.specials[i]) {
        const RogueSpecialDef* special = RogueSpecial_Find(copy.specials[i]);
        if (!special || special->slot != i) return 0;
    }
    if(!copy.route_rng.state || !copy.encounter_rng.state || !copy.reward_rng.state || !copy.shop_rng.state) return 0;
    *run=copy;
    return 1;
}
