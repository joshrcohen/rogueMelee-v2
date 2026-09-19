#include "passives.h"
#include "../../../director/rogue_director.h"
#include "../debug_launch.h"
#if ROGUE_DEBUG && ROGUE_QA_PASSIVES
#include "../melee_fighter.h"
#include <melee/ft/fighter.h>
#include <melee/ft/types.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/kinds/ftCommon/forward.h>
#include <melee/pl/player.h>
#include <dolphin/os.h>
static unsigned checks;
static void equal(const char* name, float actual, float expected)
{
    if (actual < expected-0.025f || actual > expected+0.025f)
        OSPanic(__FILE__,__LINE__,"passive %s actual=%f expected=%f",name,actual,expected);
    checks++;
}
void RoguePassiveQa_Check(void)
{
    Fighter* player = Player_GetEntity(0)->user_data;
    Fighter* enemy = Player_GetEntity(1)->user_data;
    ftCo_DatAttrs* base = player->ft_data->x0;
    float before, enemy_before;
    int motion, hurt, timer, hurt_state;
    checks = 0;
    equal("ground speed",player->co_attrs.dash_max_velocity,base->dash_max_velocity*1.06f);
    equal("air speed",player->co_attrs.air_drift_max,base->air_drift_max*1.06f);
    equal("jump",player->co_attrs.jump_v_initial_velocity,base->jump_v_initial_velocity*1.025f);
    equal("weight",player->co_attrs.weight,base->weight*1.05f);
    equal("acceleration",player->co_attrs.dash_accel_base,base->dash_accel_base*1.06f);
    equal("fall speed",player->co_attrs.terminal_velocity,base->terminal_velocity*0.95f);
    equal("landing",player->co_attrs.landingairn_lag,base->landingairn_lag*0.95f);
    equal("shield capacity",player->shield_health,p_ftCommonData->x260_startShieldHealth*1.1f);
    equal("shield recovery",RogueFighter_ShieldRecovery(player,1),1.08f);
    equal("ledge timer",RogueFighter_LedgeFrames(player,30),35);
    equal("next stock",Player_GetStocks(0),4);
    equal("knockback",Player_GetAttackRatio(0),1.05f);
    equal("poise",Player_GetDefenseRatio(0),0.95f);
    RogueFighter_ResetMatch();
    enemy->dmg.x18c4_source_ply = 0;
    before = enemy->dmg.x1830_percent;
    Fighter_TakeDamage_8006CC7C(enemy,10);
    equal("opening and power",enemy->dmg.x1830_percent-before,12.42f);
    before = enemy->dmg.x1830_percent;
    Fighter_TakeDamage_8006CC7C(enemy,10);
    equal("opening consumed",enemy->dmg.x1830_percent-before,10.8f);
    motion = enemy->motion_id; enemy->motion_id = ftCo_MS_ThrownF;
    before = enemy->dmg.x1830_percent;
    Fighter_TakeDamage_8006CC7C(enemy,10);
    equal("throw damage",enemy->dmg.x1830_percent-before,11.88f);
    enemy->motion_id = motion;
    player->dmg.x18c4_source_ply = 1;
    before = player->dmg.x1830_percent; enemy_before = enemy->dmg.x1830_percent;
    Fighter_TakeDamage_8006CC7C(player,10);
    equal("damage reduction",player->dmg.x1830_percent-before,9.2f);
    equal("retaliation",enemy->dmg.x1830_percent-enemy_before,0.368f);
    before = player->dmg.x18F0;
    RogueFighter_OnKO(0,0,1);
    equal("KO healing",player->dmg.x18F0-before,8);
    motion = player->motion_id; hurt = player->x1988; timer = player->x1990; hurt_state = player->x198C;
    player->motion_id = ftCo_MS_EscapeAir; player->x1988 = 2; player->x1990 = 0;
    ftColl_8007B62C(player->gobj,0);
    equal("dodge extension",player->x1990,2);
    player->motion_id = motion; player->x1988 = hurt; player->x1990 = timer; player->x198C = hurt_state;
    OSReport("[rogue] passive_behavior checks=%u failures=0\n",checks);
}
#else
void RoguePassiveQa_Check(void) {}
#endif
