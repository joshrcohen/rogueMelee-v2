#ifndef ROGUE_CAPABILITIES_H
#define ROGUE_CAPABILITIES_H
/* Detected once at the first stable scene boundary; immutable thereafter. */
typedef struct RogueCapabilities {
    unsigned detected, supported, roster_count, player_slots, stage_count;
    unsigned borrowed_specials, aerial_swapping;
} RogueCapabilities;
void RogueCapabilities_Detect(void);
const RogueCapabilities* RogueCapabilities_Get(void);
#endif
