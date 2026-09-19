#ifndef ROGUE_RUN_H
#define ROGUE_RUN_H
#include "rng.h"

#define ROGUE_FLOORS 15
#define ROGUE_UPGRADES 24
#define ROGUE_RECIPES 15
#define ROGUE_HISTORY 256
enum RoguePhase { ROGUE_SELECT, ROGUE_REWARD, ROGUE_ROUTE, ROGUE_FIGHT,
                  ROGUE_SHOP, ROGUE_REST, ROGUE_DEAD, ROGUE_COMPLETE };
enum RogueNodeType { ROGUE_NORMAL, ROGUE_ELITE, ROGUE_BOSS, ROGUE_NODE_SHOP, ROGUE_NODE_REST };
typedef struct RogueOfferState {
    unsigned ids[3], sold[3], generation, rerolls, claimed;
} RogueOfferState;
typedef struct RogueEncounter {
    unsigned recipe, stage, enemy_count, fighters[3], stocks[3];
    unsigned tags, damage, defense, speed, scale, starting_percent;
} RogueEncounter;
typedef struct RogueHistoryEvent {
    unsigned kind, floor, cost, generation, before[3], after[3];
} RogueHistoryEvent;
typedef struct RogueRun {
    RogueSeed seed;
    unsigned version, character, act, floor, phase, gold, score;
    unsigned route[ROGUE_FLOORS][2], selected_route[ROGUE_FLOORS];
    unsigned stacks[ROGUE_UPGRADES], specials[4];
    unsigned recent_recipes[4], recent_stages[3], encounters;
    unsigned gold_spent, rerolls_used, history_count, carried_percent;
    unsigned fights_won, death_reason, native_score, reroll_gold_spent;
    RogueRng route_rng, encounter_rng, reward_rng, shop_rng;
    RogueOfferState reward, shop;
    RogueEncounter preview[2], current;
    RogueHistoryEvent history[ROGUE_HISTORY];
} RogueRun;

typedef void (*RogueRunObserver)(const RogueRun*, unsigned event, unsigned a, unsigned b, unsigned c);
void RogueRun_SetObserver(RogueRunObserver observer);
void RogueRun_Init(RogueRun* run, RogueSeed seed, unsigned character);
int RogueRun_ChooseUpgrade(RogueRun* run, unsigned slot);
int RogueRun_ChooseRoute(RogueRun* run, unsigned slot);
int RogueRun_MatchEnd(RogueRun* run, int won, unsigned native_score);
int RogueRun_LeaveService(RogueRun* run);
void RogueRun_Reward(RogueRun* run);
void RogueRun_Shop(RogueRun* run);
unsigned RogueRun_RerollCost(const RogueRun* run, int shop);
int RogueRun_Reroll(RogueRun* run, int shop);
int RogueRun_Buy(RogueRun* run, unsigned slot);
void RogueEncounter_Generate(RogueRun* run, unsigned tier, RogueEncounter* out);
unsigned RogueEncounter_Budget(unsigned act, unsigned floor, unsigned tier);
unsigned RogueEncounter_Threat(const RogueEncounter* encounter);
unsigned RogueRun_Serialize(const RogueRun* run, unsigned char* out, unsigned capacity);
int RogueRun_Deserialize(RogueRun* run, const unsigned char* data, unsigned size);
#endif
