#include "offers.h"
#include "../upgrades/upgrade_registry.h"

int RogueOffer_Eligible(const RogueRun* run, unsigned id)
{
    const RogueSpecialDef* special;
    if (!id || id > ROGUE_OFFERS) return 0;
    if (id <= ROGUE_UPGRADES)
        return run->stacks[id - 1] < rogue_upgrades[id - 1].max_stacks;
    if (id > ROGUE_AERIAL_OFFER_BASE) {
#if ROGUE_ENABLE_AERIALS
        const RogueAerialDef* aerial=RogueAerial_Find(id-ROGUE_AERIAL_OFFER_BASE);
        return aerial->character != run->character && run->aerials[aerial->slot] != aerial->id;
#else
        return 0;
#endif
    }
    special = &rogue_specials[id - ROGUE_UPGRADES - 1];
    return special->character != run->character && run->specials[special->slot] != special->id;
}

int RogueOffer_Apply(RogueRun* run, unsigned id)
{
    const RogueSpecialDef* special;
    if (!RogueOffer_Eligible(run, id)) return 0;
    if (id <= ROGUE_UPGRADES) run->stacks[id - 1]++;
    else if (id > ROGUE_AERIAL_OFFER_BASE) {
        const RogueAerialDef* aerial=RogueAerial_Find(id-ROGUE_AERIAL_OFFER_BASE);
        if (run->phase != ROGUE_SHOP && run->phase != ROGUE_REWARD) return 0;
        run->aerials[aerial->slot]=aerial->id;
    } else {
        special = &rogue_specials[id - ROGUE_UPGRADES - 1];
        run->specials[special->slot] = special->id;
    }
    return 1;
}

unsigned RogueOffer_Price(const RogueRun* run, unsigned id)
{
    unsigned price;
    if (!id || id > ROGUE_OFFERS) return 0;
    price = id > ROGUE_AERIAL_OFFER_BASE ? RogueAerial_Find(id-ROGUE_AERIAL_OFFER_BASE)->price : id <= ROGUE_UPGRADES ? rogue_upgrades[id - 1].price : rogue_specials[id - ROGUE_UPGRADES - 1].price;
    return (price * (100 - run->stacks[22] * 5) + 99) / 100;
}

const char* RogueOffer_Name(unsigned id)
{
    if (!id || id > ROGUE_OFFERS) return "No offer";
    if (id > ROGUE_AERIAL_OFFER_BASE) return RogueAerial_Find(id-ROGUE_AERIAL_OFFER_BASE)->name;
    return id <= ROGUE_UPGRADES ? rogue_upgrades[id - 1].name : rogue_specials[id - ROGUE_UPGRADES - 1].name;
}

const char* RogueOffer_Description(unsigned id)
{
    static const char* slots[4] = { "Replace neutral special", "Replace side special", "Replace up special", "Replace down special" };
    if (!id || id > ROGUE_OFFERS) return "";
    if (id > ROGUE_AERIAL_OFFER_BASE) {
        static const char* aerial_slots[5] = { "Equip Nair next fight.", "Equip Fair next fight.", "Equip Bair next fight.", "Equip Uair next fight.", "Equip Dair next fight." };
        return aerial_slots[RogueAerial_Find(id-ROGUE_AERIAL_OFFER_BASE)->slot];
    }
    if (id > ROGUE_UPGRADES && rogue_specials[id - ROGUE_UPGRADES - 1].id == 16) return "Down special. Ground only.";
    return id <= ROGUE_UPGRADES ? rogue_upgrades[id - 1].description : slots[rogue_specials[id - ROGUE_UPGRADES - 1].slot];
}
