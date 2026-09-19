#include "../../src/core/run.h"
#include "../../src/core/offers.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    static RogueRun run;
    unsigned i;
#if ROGUE_ENABLE_AERIALS
    static RogueRun before, restored;
    static unsigned char bytes[16000];
    unsigned n,slot,seed,samples=0;
    for(i=0;i<ROGUE_AERIALS;++i) {
        const RogueAerialDef* move=&rogue_aerials[i];
        unsigned offer=ROGUE_AERIAL_OFFER_BASE+move->id;
        RogueRun_Init(&run,42,(move->character+1)%26);
        for(slot=0;slot<5;++slot) assert(!run.aerials[slot]);
        run.phase=ROGUE_FIGHT;before=run;
        assert(!RogueOffer_Apply(&run,offer));assert(!memcmp(&run,&before,sizeof(run)));
        RogueRun_Shop(&run);run.shop.ids[0]=offer;run.gold=59;before=run;
        assert(!RogueRun_Buy(&run,0));assert(!memcmp(&run,&before,sizeof(run)));
        run.gold=100;
        assert(RogueRun_Buy(&run,0));
        assert(run.gold==40 && run.gold_spent==60 && run.shop.sold[0]);
        assert(run.aerials[move->slot]==move->id);
        assert(!RogueOffer_Eligible(&run,offer));
        before=run;assert(!RogueRun_Buy(&run,0));assert(!memcmp(&run,&before,sizeof(run)));
        n=RogueRun_Serialize(&run,bytes,sizeof(bytes));
        assert(RogueRun_Deserialize(&restored,bytes,n));assert(!memcmp(&run,&restored,sizeof(run)));
        run.aerials[(move->slot+1)%5]=move->id;
        n=RogueRun_Serialize(&run,bytes,sizeof(bytes));assert(!RogueRun_Deserialize(&restored,bytes,n));
        RogueRun_Init(&run,42,move->character);assert(!RogueOffer_Eligible(&run,offer));
        RogueRun_Init(&run,42,(move->character+1)%26);
        run.reward.ids[0]=offer;
        assert(RogueRun_ChooseUpgrade(&run,0));assert(run.aerials[move->slot]==move->id);
    }
    RogueRun_Init(&run,42,0);RogueRun_Shop(&run);run.gold=1000;run.stacks[22]=2;
    for(slot=0;slot<5;++slot) {
        unsigned id=11+slot;
        run.shop.ids[0]=ROGUE_AERIAL_OFFER_BASE+id;run.shop.sold[0]=0;
        assert(RogueOffer_Price(&run,run.shop.ids[0])==54);
        assert(RogueRun_Buy(&run,0));assert(run.aerials[slot]==id);
    }
    run.shop.ids[1]=ROGUE_AERIAL_OFFER_BASE+6;run.shop.sold[1]=0;
    assert(RogueRun_Buy(&run,1));assert(run.aerials[0]==6);
    for(slot=1;slot<5;++slot) assert(run.aerials[slot]==11+slot);
    before=run;
    assert(RogueRun_Reroll(&run,1));
    assert(!memcmp(before.aerials,run.aerials,sizeof(run.aerials)));
    assert(run.shop.sold[0] && run.shop.sold[1]);
    assert(run.shop.ids[0]==before.shop.ids[0] && run.shop.ids[1]==before.shop.ids[1]);
    for(seed=0;seed<100;++seed) {
        RogueRun_Init(&run,seed,seed%26);run.gold=1000;
        for(slot=0;slot<3;++slot) samples+=run.reward.ids[slot]>ROGUE_AERIAL_OFFER_BASE;
        assert(RogueRun_Reroll(&run,0));
        for(slot=0;slot<3;++slot) assert(RogueOffer_Eligible(&run,run.reward.ids[slot]));
        RogueRun_Shop(&run);assert(RogueRun_Reroll(&run,1));
        for(slot=0;slot<3;++slot) {
            assert(RogueOffer_Eligible(&run,run.shop.ids[slot]));
            samples+=run.shop.ids[slot]>ROGUE_AERIAL_OFFER_BASE;
        }
    }
    assert(samples>0);
    puts("PASS: 130 aerial rewards/purchases, five independent slots, atomic failures, replacement, discount, rerolls and snapshots");
#else
    RogueRun_Init(&run,42,0);
    for(i=1;i<=ROGUE_AERIALS;++i) assert(!RogueOffer_Eligible(&run,ROGUE_AERIAL_OFFER_BASE+i));
    for(i=0;i<3;++i) assert(run.reward.ids[i]<=ROGUE_AERIAL_OFFER_BASE);
    RogueRun_Shop(&run);
    for(i=0;i<3;++i) assert(run.shop.ids[i]<=ROGUE_AERIAL_OFFER_BASE);
    puts("PASS: disabled aerials are absent from rewards and shops");
#endif
    return 0;
}
