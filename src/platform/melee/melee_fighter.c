#include "melee_fighter.h"
#include "../../director/rogue_runtime.h"
#include <melee/ft/types.h>
bool Rogue_IsRunPlayer(const Fighter* fighter)
{
    return RogueRuntime_IsActive() && fighter && fighter->player_id == 0;
}
