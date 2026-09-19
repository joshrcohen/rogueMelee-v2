#include "special_internal.h"
#include <melee/ft/fighter.h>
RogueFighterState fighter_state;
bool Rogue_DebugGrantAbility(const char* key)
{
    int i;
    if (!RogueRuntime_IsActive() || !key) return false;
    if (strcmp(key, "fox_reflector") == 0) key = "fox_down";
    if (strcmp(key, "falco_blaster") == 0) key = "falco_neutral";
    for (i = 1; i < ROGUE_ABILITY_COUNT; ++i) {
        const RogueAbilityDefinition* def = Rogue_GetAbility(i);
        if (def && strcmp(def->key, key) == 0) {
            RogueDirector_Run()->specials[def->native_slot] = def->id;
            return true;
        }
    }
    return false;
}

bool Rogue_IsAbilityState(const Fighter* fp)
{
#if ROGUE_DEBUG
    if (fp && fighter_state.fighter == fp && fighter_state.match_generation != RogueRuntime_Get()->match_generation)
        OSPanic(__FILE__, __LINE__, "stale borrowed-special match generation");
#endif
    return fp && fighter_state.fighter == fp &&
           fighter_state.active != NULL;
}

void Rogue_AbilityCleanup(Fighter* fp)
{
    FighterKind source;
    RogueAbilitySlot slot;
    if (!Rogue_IsAbilityState(fp)) return;


    source = fighter_state.active->internal_kind;
    slot = fighter_state.active->native_slot;
    RogueRuntime_Trace(6, fighter_state.active->id);
#if ROGUE_DEBUG
    OSReport("[rogue] special_restore id=%u match=%u\n", fighter_state.active->id, fighter_state.match_generation);
#endif

    /*
     * Tear down source-owned attached state while source attrs/vars are still
     * installed. Free projectiles/items may outlive the animation; their owner
     * callbacks use Rogue_AbilityVars() to reach persistent source state.
     */
    switch (source) {
    case Ft_Kind_Donkey:
        if (slot == ROGUE_ABILITY_UP)
            ftDk_SpecialHi_DestroyAllEffects(fp->gobj);
        break;
    case Ft_Kind_GameWatch:
        ftGw_Init_OnDamage(fp->gobj);
        break;
    case Ft_Kind_Samus:
        if (slot == ROGUE_ABILITY_NEUTRAL)
            ftSamus_UnkAndDestroyAllEF(fp->gobj);
        break;
    case Ft_Kind_Mewtwo:
        if (slot == ROGUE_ABILITY_NEUTRAL) {
            int charge = fp->u.mt.x2234_shadowBallCharge;
            ftMt_SpecialN_OnDeath(fp->gobj);
            fp->u.mt.x2234_shadowBallCharge = charge;
        }
        break;
    case Ft_Kind_Peach:
        if (slot == ROGUE_ABILITY_NEUTRAL)
            ftPe_SpecialN_OnDeath2(fp->gobj);
        else if (slot == ROGUE_ABILITY_UP)
            ftPe_8011D598(fp->gobj);
        break;
    case Ft_Kind_Seak:
        if (slot == ROGUE_ABILITY_SIDE)
            ftSk_SpecialS_CheckAndDestroyChain(fp->gobj);
        break;
    case Ft_Kind_Captain:
    case Ft_Kind_Ganon:
        if (slot == ROGUE_ABILITY_SIDE)
            ftCa_SpecialS_RemoveGFX(fp->gobj);
        break;
    default:
        break;
    }

    if ((source == Ft_Kind_Mario || source == Ft_Kind_DrMario) &&
        slot == ROGUE_ABILITY_SIDE)
        ftMr_SpecialS_RemoveCape(fp->gobj);

    if ((source == Ft_Kind_Fox || source == Ft_Kind_Falco) &&
        slot == ROGUE_ABILITY_NEUTRAL)
        ftFx_SpecialN_RemoveBlaster(fp->gobj);

    fighter_state.source_vars[source] = fp->u;
    fp->u = fighter_state.native_vars;
    memcpy(&fp->grab_cb, fighter_state.native_callbacks,
           sizeof(fighter_state.native_callbacks));
    fp->dat_attrs = fighter_state.native_attrs;
    fp->x24 = fighter_state.native_anims;
    fp->x28 = fighter_state.native_anim_flags;
    fp->x58C = fighter_state.native_anim_count;
    fp->reflecting = false;
    fighter_state.active = NULL;
}

FighterKind Rogue_AbilitySourceKind(const Fighter* fp)
{
    if (!fp) return Ft_Kind_Max;
    if (!Rogue_IsAbilityState(fp))
        return fp->kind;
    if (fighter_state.active != NULL)
        return fighter_state.active->internal_kind;
    return fp->kind;
}

ftData* Rogue_AbilityData(Fighter* fp)
{
    FighterKind source;
    if (!Rogue_IsAbilityState(fp))
        return fp->ft_data;
    source = Rogue_AbilitySourceKind(fp);
    return source >= 0 && source < Ft_Kind_Max ? gFtDataList[source] : fp->ft_data;
}

static FighterKind abilityFamily(FighterKind kind)
{
    switch (kind) {
    case Ft_Kind_Falco: return Ft_Kind_Fox;
    case Ft_Kind_DrMario: return Ft_Kind_Mario;
    case Ft_Kind_CLink: return Ft_Kind_Link;
    case Ft_Kind_Pichu: return Ft_Kind_Pikachu;
    case Ft_Kind_Ganon: return Ft_Kind_Captain;
    case Ft_Kind_Emblem: return Ft_Kind_Mars;
    case Ft_Kind_Nana: return Ft_Kind_Popo;
    default: return kind;
    }
}

union Fighter_FighterVars* Rogue_AbilityVars(Fighter* fp, FighterKind family)
{
    int source;
    if (fighter_state.fighter != fp) return &fp->u;
    family = abilityFamily(family);
    if (fighter_state.active &&
        abilityFamily(fighter_state.active->internal_kind) == family)
        return &fp->u;
    if (abilityFamily(fp->kind) == family)
        return fighter_state.active ? &fighter_state.native_vars : &fp->u;
    /* Projectiles can outlive the animation which created them. Their owner
     * callbacks must update the source's persistent state, never the unrelated
     * base fighter's overlapping union fields. Prefer the equipped clone. */
    for (source = 0; source < ROGUE_ABILITY_SLOTS; ++source) {
        const RogueAbilityDefinition* def = Rogue_GetAbility(RogueDirector_Run()->specials[source]);
        if (def && abilityFamily(def->internal_kind) == family &&
            fighter_state.loaded_sources[def->internal_kind])
            return &fighter_state.source_vars[def->internal_kind];
    }
    for (source = 0; source < Ft_Kind_Max; ++source)
        if (abilityFamily(source) == family && fighter_state.loaded_sources[source])
            return &fighter_state.source_vars[source];
    return &fp->u;
}

void Rogue_AbilityFighterDestroyed(Fighter* fp)
{
    if (fighter_state.fighter != fp) return;
    Rogue_AbilityCleanup(fp);
    RogueRuntime_MatchRelease(fighter_state.match_generation);
    RogueRuntime_Trace(8, fp->kind);
#if ROGUE_DEBUG
    OSReport("[rogue] fighter_context_destroy kind=%u match=%u\n", fp->kind, fighter_state.match_generation);
#endif
    memset(&fighter_state, 0, sizeof(fighter_state));
}

void Rogue_AbilityMatchEnd(void)
{
    /* Retail defers fighter destruction until the next heap reset. Release our
     * donor context while its fighter and articles are still valid. */
    if (fighter_state.fighter) Rogue_AbilityFighterDestroyed(fighter_state.fighter);
}

void Rogue_AbilityTransformed(Fighter* src, Fighter* dst)
{
    if (fighter_state.fighter != src || !Rogue_IsRunPlayer(dst)) return;
    Rogue_AbilityCleanup(src);
    /* Both native forms already exist; all borrowed assets and persistent
     * charge data belong to the run player and survive the entity swap. */
    fighter_state.fighter = dst;
    RogueRuntime_Trace(9, dst->kind);
}

Fighter_GObj* Rogue_AbilityClimberPartner(Fighter* fp)
{
    Fighter_GObj* partner = Player_GetEntityAtIndex(fp->player_id, 1);
    if (partner && GET_FIGHTER(partner)->kind != Ft_Kind_Nana) return NULL;
    return partner;
}

MotionState* Rogue_AbilityMotionState(Fighter* fp, int motion)
{
    const RogueAbilityDefinition* def;
    if (!Rogue_IsAbilityState(fp)) return NULL;


    def = fighter_state.active;
    if (!def) return NULL;
    if (!Rogue_IsRunPlayer(fp) || motion < def->first_state || motion > def->last_state) {
        Rogue_AbilityCleanup(fp);
        return NULL;
    }
    RogueRuntime_Trace(10, motion);
#if ROGUE_DEBUG
    OSReport("[rogue] donor_motion id=%u motion=%d anim=%p\n", def->id, motion, def->states[motion-ftCo_MS_Count].anim_cb);
#endif
    return &def->states[motion - ftCo_MS_Count];
}

int Rogue_AbilityMapBone(Fighter* fp, int bone)
{
    int mapped;
    FighterKind source;
    if (!Rogue_IsAbilityState(fp)) return bone;
    source = Rogue_AbilitySourceKind(fp);
    mapped = ftPartsRemap(fp->kind, source, bone);
    /* Unmapped decorative bones cannot index outside the recipient skeleton. */
    if (mapped < 0 || (unsigned) mapped >= ftPartsTable[fp->kind]->parts_num || !fp->parts[mapped].joint)
        mapped = ftParts_GetBoneIndex(fp, FtPart_TransN);
    return mapped;
}

static bool install_ability(Fighter* fp, RogueAbilitySlot slot)
{
    const RogueAbilityDefinition* def;
    ftData* source;
    if (!Rogue_IsRunPlayer(fp) || slot < 0 || slot >= ROGUE_ABILITY_SLOTS) return false;
    def = Rogue_GetAbility(RogueDirector_Run()->specials[slot]);
    if (!def) { Rogue_AbilityCleanup(fp); return false; }
    if (!def->ground_enter || !def->air_enter) return false;
    if (def->native_slot != slot || fighter_state.fighter != fp ||
        !fighter_state.loaded[def->id]) return false;
    Rogue_AbilityCleanup(fp);
    fighter_state.native_attrs = fp->dat_attrs;
    fighter_state.native_anims = fp->x24;
    fighter_state.native_anim_flags = fp->x28;
    fighter_state.native_anim_count = fp->x58C;
    fighter_state.native_vars = fp->u;
    memcpy(fighter_state.native_callbacks, &fp->grab_cb,
           sizeof(fighter_state.native_callbacks));
    fp->u = fighter_state.source_vars[def->internal_kind];
    fighter_state.active = def;
    source = gFtDataList[def->internal_kind];
    fp->dat_attrs = fighter_state.attrs[def->internal_kind].bytes;
    fp->x24 = source->xC;
    fp->x28 = source->x10;
    fp->x58C = ftData_Table_Unk0[def->internal_kind].count;
    /* Source animation flags already identify the source skeleton. Melee's
     * ftPartsRemap path retargets its FigaTree to the unchanged base fighter. */
    return true;
}

bool Rogue_TrySpecial(Fighter_GObj* gobj, RogueAbilitySlot slot, bool airborne)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!install_ability(fp, slot)) return false;
    (airborne ? fighter_state.active->air_enter : fighter_state.active->ground_enter)(gobj);
    return true;
}

bool Rogue_AbilityResumeFamily(Fighter* fp, FighterKind family, RogueAbilitySlot slot)
{
    const RogueAbilityDefinition* def;
    if (!Rogue_IsRunPlayer(fp)) return false;
    def = Rogue_GetAbility(RogueDirector_Run()->specials[slot]);
    if (def && abilityFamily(def->internal_kind) == abilityFamily(family))
        return install_ability(fp, slot);
    if (abilityFamily(fp->kind) == abilityFamily(family)) {
        Rogue_AbilityCleanup(fp);
        return true;
    }
    return false;
}

int Rogue_AbilityPartIndex(Fighter* fp, int part)
{
    int index = ftParts_GetBoneIndex(fp, part);
    if (Rogue_IsRunPlayer(fp) && ((unsigned) index >= ftPartsTable[fp->kind]->parts_num || !fp->parts[index].joint))
        return ftParts_GetBoneIndex(fp, FtPart_TransN);
    return index;
}

int Rogue_AbilityDebugRestored(Fighter* fp)
{
    return fp && fighter_state.fighter == fp && !fighter_state.active &&
        fp->dat_attrs == fighter_state.native_attrs && fp->x24 == fighter_state.native_anims &&
        fp->x28 == fighter_state.native_anim_flags && fp->x58C == fighter_state.native_anim_count;
}
