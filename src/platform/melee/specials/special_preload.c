#include "special_internal.h"
void Rogue_AbilityFighterCreated(Fighter* fp)
{
    int i;
    if (!Rogue_IsRunPlayer(fp)) return;
    if (fighter_state.fighter) Rogue_AbilityFighterDestroyed(fighter_state.fighter);
    memset(&fighter_state, 0, sizeof(fighter_state));
    fighter_state.fighter = fp;
    fighter_state.match_generation = RogueRuntime_Get()->match_generation;
    RogueRuntime_MatchAcquire(fighter_state.match_generation);
    RogueRuntime_Trace(7, fp->kind);
#if ROGUE_DEBUG
    OSReport("[rogue] fighter_create kind=%u match=%u\n", fp->kind, fighter_state.match_generation);
#endif

    for (i = 1; i < ROGUE_ABILITY_COUNT; ++i) {
        const RogueAbilityDefinition* def = Rogue_GetAbility(i);
        int slot, source;
        bool needed = false;
        if (!def) continue;
        source = def->internal_kind;
        for (slot = 0; slot < ROGUE_ABILITY_SLOTS; ++slot) {
            const RogueAbilityDefinition* equipped = Rogue_GetAbility(RogueDirector_Run()->specials[slot]);
            if (!equipped) continue;
            if (equipped->internal_kind == source ||
                ((source == Ft_Kind_Zelda || source == Ft_Kind_Seak) &&
                 (equipped->internal_kind == Ft_Kind_Zelda || equipped->internal_kind == Ft_Kind_Seak)))
                needed = true;
        }
        if (!needed) continue;
        if (fighter_state.loaded_sources[source]) { fighter_state.loaded[i] = true; continue; }
        /* Fresh match heaps exist here; load dependencies before play starts.
         * Enqueueing asynchronous preloads from mode entry precedes heap setup. */
        /* Match the engine's normal complete fighter preload path. */
        ftLib_80087508(def->internal_kind, 0);
        if (def->attrs_size > sizeof(fighter_state.attrs[source])) continue;
        if (!gFtDataList[source] || !gFtDataList[source]->ext_attr) continue;
        memcpy(fighter_state.attrs[source].bytes, gFtDataList[source]->ext_attr, def->attrs_size);
        {
            void** items = gFtDataList[def->internal_kind]->x48_items;
            void* attrs = fighter_state.attrs[source].bytes;
            switch (def->internal_kind) {
            case Ft_Kind_Koopa:
                it_8026B3F8(items[0], It_Kind_Koopa_Flame);
                break;
            case Ft_Kind_Samus:
                it_8026B3F8(items[0], It_Kind_Samus_Bomb);
                it_8026B3F8(items[1], It_Kind_Samus_Charge);
                it_8026B3F8(items[2], It_Kind_Samus_Missile);
                it_8026B3F8(items[3], It_Kind_Samus_GBeam);
                break;
            case Ft_Kind_Mewtwo:
                it_8026B3F8(items[0], It_Kind_Mewtwo_Disable);
                it_8026B3F8(items[1], It_Kind_Mewtwo_ShadowBall);
                break;
            case Ft_Kind_Ness:
                it_8026B3F8(items[0], It_Kind_Ness_PKFire);
                it_8026B3F8(items[1], It_Kind_Ness_PKFire_Flame);
                it_8026B3F8(items[2], It_Kind_Ness_PKFlush);
                it_8026B3F8(items[3], It_Kind_Ness_PKThunder);
                it_8026B3F8(items[4], It_Kind_Ness_PKThunder1);
                it_8026B3F8(items[5], It_Kind_Ness_PKThunder2);
                it_8026B3F8(items[6], It_Kind_Ness_PKThunder3);
                it_8026B3F8(items[7], It_Kind_Ness_PKThunder4);
                it_8026B3F8(items[8], It_Kind_Ness_PKFlush_Explode);
                it_8026B3F8(items[9], It_Kind_Ness_Bat);
                it_8026B3F8(items[10], It_Kind_Ness_Yoyo);
                break;
            case Ft_Kind_Peach:
                it_8026B3F8(items[0], It_Kind_Peach_Explode);
                it_8026B3F8(items[1], It_Kind_Peach_Turnip);
                it_8026B3F8(items[2], It_Kind_Peach_Parasol);
                it_8026B3F8(items[3], It_Kind_Peach_Toad);
                it_8026B3F8(items[4], It_Kind_Peach_ToadSpore);
                break;
            case Ft_Kind_Yoshi:
                it_8026B3F8(items[0], It_Kind_Yoshi_EggThrow);
                it_8026B3F8(items[1], It_Kind_Yoshi_Star);
                it_8026B3F8(items[2], It_Kind_Yoshi_EggLay);
                break;
            case Ft_Kind_Zelda:
                it_8026B3F8(items[0], It_Kind_Zelda_DinFire);
                it_8026B3F8(items[1], It_Kind_Zelda_DinFire_Explode);
                break;
            case Ft_Kind_Seak:
                it_8026B3F8(items[0], It_Kind_Seak_NeedleThrow);
                it_8026B3F8(items[1], It_Kind_Seak_NeedleHeld);
                it_8026B3F8(items[2], It_Kind_Seak_Vanish);
                it_8026B3F8(items[3], It_Kind_Seak_Chain);
                break;
            case Ft_Kind_GameWatch:
                it_8026B3F8(items[0], It_Kind_GameWatch_Greenhouse);
                it_8026B3F8(items[1], It_Kind_GameWatch_Manhole);
                it_8026B3F8(items[2], It_Kind_GameWatch_Fire);
                it_8026B3F8(items[3], It_Kind_GameWatch_Parachute);
                it_8026B3F8(items[4], It_Kind_GameWatch_Turtle);
                it_8026B3F8(items[5], It_Kind_GameWatch_Breath);
                it_8026B3F8(items[6], It_Kind_GameWatch_Judge);
                it_8026B3F8(items[7], It_Kind_GameWatch_Panic);
                it_8026B3F8(items[8], It_Kind_GameWatch_Chef);
                it_8026B3F8(items[9], It_Kind_GameWatch_Rescue);
                break;
            case Ft_Kind_Kirby:
                it_8026B3F8(items[0], It_Kind_Kirby_CBeam);
                it_8026B3F8(items[1], It_Kind_Kirby_Hammer);
                it_8026B3F8(items[2], It_Kind_Unk1);
                it_8026B3F8(items[3], It_Kind_Unk2);
                break;
            case Ft_Kind_Popo:
                it_8026B3F8(items[0], It_Kind_IceClimber_Ice);
                it_8026B3F8(items[1], It_Kind_IceClimber_Blizzard);
                it_8026B3F8(items[2], It_Kind_IceClimber_GumStrings);
                break;
            case Ft_Kind_Link: case Ft_Kind_CLink: {
                ftLk_DatAttrs* lk = attrs;
                it_8026B3F8(items[0], lk->x48);
                it_8026B3F8(items[1], lk->x2C);
                it_8026B3F8(items[2], lk->xBC);
                it_8026B3F8(items[3], lk->xC);
                it_8026B3F8(items[4], lk->x10);
                break;
            }
            case Ft_Kind_Mario:
                it_8026B3F8(items[0], It_Kind_Mario_Fire);
                it_8026B3F8(items[2], ((ftMario_DatAttrs*)attrs)->specials.cape_kind);
                break;
            case Ft_Kind_DrMario:
                it_8026B3F8(items[1], It_Kind_DrMario_Vitamin);
                it_8026B3F8(items[3], ((ftMario_DatAttrs*)attrs)->specials.cape_kind);
                break;
            case Ft_Kind_Luigi:
                it_8026B3F8(items[0], It_Kind_Luigi_Fire);
                break;
            case Ft_Kind_Pikachu: case Ft_Kind_Pichu: {
                ftPikachuAttributes* pk = attrs;
                it_8026B3F8(items[0], pk->xDC);
                it_8026B3F8(items[1], pk->specialn_itkind);
                it_8026B3F8(items[2], pk->specialairn_itkind);
                break;
            }
            default: break;
            }
        }
        if (def->internal_kind == Ft_Kind_Fox || def->internal_kind == Ft_Kind_Falco) {
            ftFox_DatAttrs* attrs = (ftFox_DatAttrs*) fighter_state.attrs[source].bytes;
            void** items = gFtDataList[def->internal_kind]->x48_items;
            it_8026B3F8(items[0], attrs->x1C_FOX_BLASTER_SHOT_ITKIND);
            it_8026B3F8(items[1], attrs->x20_FOX_BLASTER_GUN_ITKIND);
            it_8026B3F8(items[def->internal_kind == Ft_Kind_Fox ? 2 : 3],
                        def->internal_kind == Ft_Kind_Fox ? It_Kind_Fox_Illusion : It_Kind_Falco_Phantasm);
        }
        fighter_state.loaded[def->id] = true;
        fighter_state.loaded_sources[source] = true;
        RogueRuntime_Trace(5, source);
#if ROGUE_DEBUG
        OSReport("[rogue] donor_preload kind=%u match=%u\n", source, fighter_state.match_generation);
#endif
        if (source == Ft_Kind_Kirby) fighter_state.source_vars[source].kb.hat.kind = Ft_Kind_Kirby;
        if (source == Ft_Kind_GameWatch) {
            fighter_state.source_vars[source].gw.x222C_judgeVar1 = 1;
            fighter_state.source_vars[source].gw.x2230_judgeVar2 = 0;
            fighter_state.source_vars[source].gw.x2234 = 0;
            fighter_state.source_vars[source].gw.x2238_panicCharge = 0;
            fighter_state.source_vars[source].gw.x223C_panicDamage = 0;
            fighter_state.source_vars[source].gw.x2240_chefVar1 = 1;
            fighter_state.source_vars[source].gw.x2244_chefVar2 = 3;
        }
    }
    Rogue_AerialPrepare(fp);
}

