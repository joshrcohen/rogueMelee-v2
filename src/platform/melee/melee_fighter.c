#include "melee_fighter.h"
#include "../../director/rogue_runtime.h"
#include "../../director/rogue_director.h"
#include "specials/special_engine.h"
#include <melee/ft/types.h>
bool Rogue_IsRunPlayer(const Fighter* fighter)
{
    return RogueRuntime_IsActive() && fighter && fighter->player_id == 0 && !fighter->is_sub_fighter;
}

void RogueFighter_Created(Fighter* fighter)
{
    RogueRun* run = RogueDirector_Run();
    ftCo_DatAttrs* attr = &fighter->co_attrs;
    if (RogueRuntime_IsActive() && run->phase == ROGUE_FIGHT) {
        float ground = fighter->player_id == 0 ? 1.0f + run->stacks[2] * 0.06f : run->current.speed * 0.01f;
        float air = fighter->player_id == 0 ? 1.0f + run->stacks[3] * 0.06f : ground;
        attr->walk_max_vel *= ground;
        attr->dash_initial_velocity *= ground;
        attr->dash_max_velocity *= ground;
        attr->ground_max_horizontal_velocity *= ground;
        attr->air_drift_max *= air;
        attr->air_max_horizontal_velocity *= air;
        if (fighter->player_id == 0) {
            float jump = 1.0f + run->stacks[4] * 0.025f;
            float landing = 1.0f - run->stacks[18] * 0.05f;
            attr->jump_v_initial_velocity *= jump;
            attr->hop_v_initial_velocity *= jump;
            attr->weight *= 1.0f + run->stacks[7] * 0.05f;
            attr->dash_accel_mul *= 1.0f + run->stacks[16] * 0.06f;
            attr->dash_accel_base *= 1.0f + run->stacks[16] * 0.06f;
            attr->terminal_velocity *= 1.0f - run->stacks[17] * 0.05f;
            attr->normal_landing_lag *= landing;
            attr->landingairn_lag *= landing;
            attr->landingairf_lag *= landing;
            attr->landingairb_lag *= landing;
            attr->landingairhi_lag *= landing;
            attr->landingairlw_lag *= landing;
        }
    }
    Rogue_AbilityFighterCreated(fighter);
}

float RogueFighter_AdjustDamage(Fighter* fighter, float damage)
{
    RogueRun* run = RogueDirector_Run();
    if (!RogueRuntime_IsActive() || run->phase != ROGUE_FIGHT || damage <= 0) return damage;
    if (fighter->player_id == 0) {
        damage *= 1.0f - run->stacks[1] * 0.08f;
        if (fighter->dmg.x18c4_source_ply > 0 && fighter->dmg.x18c4_source_ply < 4)
            damage *= run->current.damage * 0.01f;
    } else {
        if (fighter->dmg.x18c4_source_ply == 0) damage *= 1.0f + run->stacks[0] * 0.08f;
        damage *= 100.0f / run->current.defense;
    }
    return damage;
}
