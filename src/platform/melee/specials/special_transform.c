#include "special_internal.h"
#include <dolphin/os.h>
bool Rogue_BorrowedTransform(Fighter_GObj* gobj, HSD_GObjEvent finish)
{
    Fighter* fp = GET_FIGHTER(gobj);
    const RogueAbilityDefinition* next;
    FighterKind old_kind, next_kind;
    int slot;
    if (!Rogue_IsAbilityState(fp) || !fighter_state.active) return false;
    old_kind = fighter_state.active->internal_kind;
    if (old_kind != Ft_Kind_Zelda && old_kind != Ft_Kind_Seak) return false;
    next_kind = old_kind == Ft_Kind_Zelda ? Ft_Kind_Seak : Ft_Kind_Zelda;
    next = Rogue_GetAbility(1 + next_kind * 4 + ROGUE_ABILITY_DOWN);
    if (!next || !fighter_state.loaded_sources[next_kind]) return false;
    /* Transform the borrowed kit while retaining the player's base fighter. */
    for (slot = 0; slot < 4; ++slot) {
        const RogueAbilityDefinition* equipped = Rogue_GetAbility(RogueDirector_Run()->specials[slot]);
        if (equipped && equipped->internal_kind == old_kind)
            RogueDirector_Run()->specials[slot] = 1 + next_kind * 4 + slot;
    }
    fighter_state.source_vars[old_kind] = fp->u;
    fp->u = fighter_state.source_vars[next_kind];
    fighter_state.active = next;
    fp->dat_attrs = fighter_state.attrs[next_kind].bytes;
    fp->x24 = gFtDataList[next_kind]->xC;
    fp->x28 = gFtDataList[next_kind]->x10;
    fp->x58C = ftData_Table_Unk0[next_kind].count;
    finish(gobj);
#if ROGUE_DEBUG
    OSReport("[rogue] borrowed_transform from=%u to=%u recipient=%u match=%u\n",old_kind,next_kind,fp->kind,fighter_state.match_generation);
#endif
    return true;
}

