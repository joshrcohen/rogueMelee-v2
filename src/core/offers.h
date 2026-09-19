#ifndef ROGUE_OFFERS_H
#define ROGUE_OFFERS_H
#include "run.h"
#include "../combat/specials/special_catalog.h"
#define ROGUE_AERIAL_OFFER_BASE (ROGUE_UPGRADES + ROGUE_SPECIALS)
#define ROGUE_OFFERS (ROGUE_AERIAL_OFFER_BASE + ROGUE_AERIALS)
int RogueOffer_Eligible(const RogueRun* run, unsigned id);
int RogueOffer_Apply(RogueRun* run, unsigned id);
unsigned RogueOffer_Price(const RogueRun* run, unsigned id);
const char* RogueOffer_Name(unsigned id);
const char* RogueOffer_Description(unsigned id);
#endif
