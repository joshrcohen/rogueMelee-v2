#include "../../src/core/run.h"
#include "../../src/core/score.h"
#include "../../src/core/offers.h"
#include "../../src/encounters/encounter_registry.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void unique(const RogueOfferState* s)
{
    unsigned i,j;
    for(i=0;i<3;++i) for(j=i+1;j<3;++j)
        assert(!s->ids[i] || !s->ids[j] || s->ids[i]!=s->ids[j]);
}
int main(void)
{
    static RogueRun a,b,c;
    static unsigned char first[16000],second[16000];
    unsigned seed,i,j,n,seen=0,checksum=2166136261U;
    for(seed=0;seed<100;++seed) {
        RogueRun_Init(&a,seed,seed%26); RogueRun_Init(&b,seed,seed%26);
        while(a.phase!=ROGUE_COMPLETE) {
            assert(memcmp(&a,&b,sizeof(a))==0);
            unique(&a.reward);
            if(a.phase==ROGUE_REWARD) {
                RogueRun_Reroll(&a,0); RogueRun_Reroll(&b,0);
                assert(RogueRun_ChooseUpgrade(&a,0)); assert(RogueRun_ChooseUpgrade(&b,0));
                assert(!RogueRun_ChooseUpgrade(&a,0));
            } else if(a.phase==ROGUE_ROUTE) {
                assert(RogueRun_ChooseRoute(&a,seed%2)); assert(RogueRun_ChooseRoute(&b,seed%2));
            } else if(a.phase==ROGUE_FIGHT) {
                assert(a.current.enemy_count>=1 && a.current.enemy_count<=3);
                assert(RogueRun_MatchEnd(&a,1,123)); assert(RogueRun_MatchEnd(&b,1,123));
            } else {
                if(a.phase==ROGUE_SHOP) { RogueRun_Reroll(&a,1); RogueRun_Reroll(&b,1); }
                assert(RogueRun_LeaveService(&a)); assert(RogueRun_LeaveService(&b));
            }
        }
        n=RogueRun_Serialize(&a,first,sizeof(first)); assert(n);
        assert(RogueRun_Serialize(&b,second,sizeof(second))==n);
        assert(memcmp(first,second,n)==0);
        assert(RogueRun_Deserialize(&c,first,n)); assert(memcmp(&a,&c,sizeof(a))==0);
        assert(!RogueRun_Deserialize(&c,first,n-1));
        for(i=0;i<n;++i) checksum=(checksum^first[i])*16777619U;
    }
    for(seed=0;seed<50;++seed) {
        RogueRun_Init(&a,seed,0); b=a; b.gold=10000;
        for(i=0;i<5;++i) {
            unsigned old[3]; memcpy(old,b.reward.ids,sizeof(old));
            assert(RogueRun_Reroll(&b,0)); unique(&b.reward);
            for(j=0;j<3;++j) assert(b.reward.ids[j]!=old[0] && b.reward.ids[j]!=old[1] && b.reward.ids[j]!=old[2]);
        }
        assert(memcmp(&a.route,&b.route,sizeof(a.route))==0);
        assert(memcmp(&a.encounter_rng,&b.encounter_rng,sizeof(a.encounter_rng))==0);
        assert(memcmp(&a.preview,&b.preview,sizeof(a.preview))==0);
        RogueRun_Shop(&b); assert(RogueRun_Buy(&b,0)); j=b.shop.ids[0];
        assert(!RogueRun_Buy(&b,0)); assert(RogueRun_Reroll(&b,1));
        assert(b.shop.ids[0]==j && b.shop.sold[0]); unique(&b.shop);
        assert(memcmp(&a.encounter_rng,&b.encounter_rng,sizeof(a.encounter_rng))==0);
    }
    RogueRun_Init(&a,99,0);
    for(i=0;i<1000;++i) {
        unsigned previous=a.recent_recipes[0];
        RogueEncounter_Generate(&a,i%2+1,&a.current);
        assert(a.current.recipe!=previous);
        assert(a.current.enemy_count>=1 && a.current.enemy_count<=3);
        assert(rogue_recipes[a.current.recipe-1].stage_mask & (1U << (a.current.stage-1)));
        seen |= 1U << (a.current.recipe-1);
    }
    assert((seen & 0x7ffeU)==0x7ffeU);
    RogueRun_Init(&a,0,0); a.gold=0; b=a;
    assert(!RogueRun_Reroll(&a,0)); assert(memcmp(&a,&b,sizeof(a))==0);
    assert(RogueRun_ChooseUpgrade(&a,0)); assert(RogueRun_ChooseRoute(&a,0));
    assert(RogueRun_MatchEnd(&a,0,0)); assert(a.phase==ROGUE_DEAD);
    fprintf(stderr,"Catalog snapshot=%08x\n",checksum);
    assert(checksum==0x4a55e066U);
    /* Version 3 serializes all 64 master-seed bits, independent of host layout. */
    RogueRun_Init(&a,((RogueSeed) 0x12345678U << 32) | 42,0);
    RogueRun_Init(&b,42,0);
    assert(memcmp(&a.route_rng,&b.route_rng,sizeof(a.route_rng)) != 0);
    n=RogueRun_Serialize(&a,first,sizeof(first));
    assert(RogueRun_Deserialize(&c,first,n)); assert(c.seed==a.seed);
    RogueRun_Init(&a,42,0); a.phase=ROGUE_REST; a.carried_percent=83; a.stacks[13]=2;
    assert(RogueRun_LeaveService(&a)); assert(a.carried_percent==43);
    a.phase=ROGUE_REST; a.carried_percent=5;
    assert(RogueRun_LeaveService(&a)); assert(a.carried_percent==0);
    a.phase=ROGUE_SHOP; a.carried_percent=83;
    assert(RogueRun_LeaveService(&a)); assert(a.carried_percent==83);
    assert(RogueScore_Combat(40,ROGUE_ELITE,2,1)==348);
    assert(RogueScore_Combat(40,ROGUE_ELITE,2,0)==48);
    RogueRun_Init(&a,42,0);
    assert(RogueRun_ChooseUpgrade(&a,0));
    assert(a.history_count==1 && a.history[0].kind==3);
    assert(RogueRun_ChooseRoute(&a,0));
    assert(a.history_count==2 && a.history[1].kind==4);
    assert(RogueRun_MatchEnd(&a,1,40));
    assert(a.fights_won==1 && a.native_score==40 && a.history[2].kind==5);
    RogueRun_Init(&a,42,0);
    assert(RogueRun_ChooseUpgrade(&a,0)); assert(RogueRun_ChooseRoute(&a,0));
    memset(a.stacks,0,sizeof(a.stacks));
    a.stacks[11]=a.stacks[12]=a.stacks[22]=1;
    assert(RogueOffer_Price(&a,1)==34);
    assert(RogueRun_MatchEnd(&a,1,100));
    assert(a.gold==83 && a.score==220);
    for(i=0;i<ROGUE_SPECIALS;++i) {
        RogueRun_Init(&a,42,(rogue_specials[i].character+1)%26);
        a.reward.ids[0]=ROGUE_UPGRADES+i+1;
        assert(RogueRun_ChooseUpgrade(&a,0));
        assert(a.specials[rogue_specials[i].slot]==rogue_specials[i].id);
        assert(!RogueOffer_Eligible(&a,ROGUE_UPGRADES+i+1));
        assert(RogueSpecial_Find(rogue_specials[i].id)==&rogue_specials[i]);
    }
    RogueRun_Init(&a,1,0); c=a; b=a; b.stacks[0]=4;
    n=RogueRun_Serialize(&b,first,sizeof(first));
    assert(!RogueRun_Deserialize(&c,first,n)); assert(memcmp(&a,&c,sizeof(a))==0);
    b=a; b.preview[0].defense=0; n=RogueRun_Serialize(&b,first,sizeof(first));
    assert(!RogueRun_Deserialize(&c,first,n)); assert(memcmp(&a,&c,sizeof(a))==0);
    b=a; b.death_reason=3; n=RogueRun_Serialize(&b,first,sizeof(first));
    assert(!RogueRun_Deserialize(&c,first,n)); assert(memcmp(&a,&c,sizeof(a))==0);
    b=a; b.fights_won=16; n=RogueRun_Serialize(&b,first,sizeof(first));
    assert(!RogueRun_Deserialize(&c,first,n)); assert(memcmp(&a,&c,sizeof(a))==0);
    printf("PASS: 100 complete runs twice; 50 reroll-isolation seeds; 1000 encounters; snapshot=%08x\n",checksum);
    return 0;
}
