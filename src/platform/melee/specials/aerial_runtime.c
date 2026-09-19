#include "special_internal.h"
#include <melee/lb/lbfile.h>
#include <dolphin/dvd.h>
#include <sysdolphin/baselib/memory.h>
extern char* ftData_803C23E4[Ft_Kind_Max];
#include <melee/ft/kinds/ftCommon/ftCo_AttackAir.h>
#include <melee/ft/kinds/ftGameWatch/forward.h>
void Rogue_LinkAerialDownEnter(Fighter_GObj* gobj);
#include <melee/ft/kinds/ftGameWatch/ftgamewatchattackair.h>

static int aerial_motion(const RogueAerialDef* def, bool landing)
{
    if (def->donor == Ft_Kind_GameWatch) {
        switch (def->slot) {
        case 0: return landing ? ftGw_MS_LandingAirN : ftGw_MS_AttackAirN;
        case 2: return landing ? ftGw_MS_LandingAirB : ftGw_MS_AttackAirB;
        case 3: return landing ? ftGw_MS_LandingAirHi : ftGw_MS_AttackAirHi;
        }
    }
    return (landing ? ftCo_MS_LandingAirN : ftCo_MS_AttackAirN) + def->slot;
}

void Rogue_AerialPrepare(Fighter* fp)
{
    int slot;
    if (!ROGUE_ENABLE_AERIALS || fighter_state.fighter != fp) return;
    memcpy(fighter_state.aerial_equipped, RogueDirector_Run()->aerials, sizeof(fighter_state.aerial_equipped));
    for (slot = 0; slot < ROGUE_AERIAL_SLOTS; ++slot) {
        const RogueAerialDef* def = RogueAerial_Find(fighter_state.aerial_equipped[slot]);
        const RogueAbilityDefinition* donor;
        int source, landing, file;
        if (!def) continue;
        source = def->donor;
        /* A special or native actor may already own the complete archive. */
        if (fighter_state.loaded_sources[source] && !fighter_state.aerial_anims[source]) continue;
        donor = Rogue_GetAbility(1 + source * 4);
        if (!donor || donor->attrs_size > sizeof(fighter_state.attrs[source]))
            OSPanic(__FILE__, __LINE__, "invalid aerial donor attributes");
        if (!fighter_state.aerial_anims[source]) {
            ftData_8008572C(source);
            if (!gFtDataList[source] || !gFtDataList[source]->ext_attr)
                OSPanic(__FILE__, __LINE__, "missing aerial donor data");
            if (ftData_UnkBytePerCharacter[source] != (u8)-1)
                efAsync_LoadSync(ftData_UnkBytePerCharacter[source]);
            memcpy(fighter_state.attrs[source].bytes,gFtDataList[source]->ext_attr,donor->attrs_size);
            if (source == Ft_Kind_GameWatch) {
                void** items=gFtDataList[source]->x48_items;
                it_8026B3F8(items[3],It_Kind_GameWatch_Parachute);
                it_8026B3F8(items[4],It_Kind_GameWatch_Turtle);
                it_8026B3F8(items[5],It_Kind_GameWatch_Breath);
            }
            fighter_state.loaded_sources[source]=true;
            if (ftData_Table_Unk0[source].data) continue;
            fighter_state.aerial_anims[source]=HSD_MemAlloc(ftData_Table_Unk0[source].count*sizeof(Fighter_WaitAnimData));
            RogueRuntime_MatchAcquire(fighter_state.match_generation);
            memcpy(fighter_state.aerial_anims[source],gFtDataList[source]->xC,ftData_Table_Unk0[source].count*sizeof(Fighter_WaitAnimData));
        }
        /* Read only this equipped attack and landing. Do not populate the
         * engine's full-archive flag or mutate its shared animation records. */
        file=DVDConvertPathToEntrynum(lbFileGetFullName(ftData_803C23E4[source]));
        if (file < 0) OSPanic(__FILE__, __LINE__, "missing aerial animation file");
        for (landing=0;landing<2;++landing) {
            int motion=aerial_motion(def,landing!=0);
            MotionState* state=motion<ftCo_MS_Count ? &fp->x1C_actionStateList[motion] : &donor->states[motion-ftCo_MS_Count];
            Fighter_WaitAnimData* anim;
            unsigned offset, skip, bytes;
            void* blob;
            if (state->anim_id<0 || state->anim_id>=ftData_Table_Unk0[source].count)
                OSPanic(__FILE__, __LINE__, "invalid aerial animation index");
            anim=&fighter_state.aerial_anims[source][state->anim_id];
            if (!anim->x8) continue;
            if (anim->x8<0 || anim->x8>0x8000 || anim->x4<0)
                OSPanic(__FILE__, __LINE__, "invalid aerial animation slice");
            offset=(unsigned)anim->x4 & ~31U;
            skip=(unsigned)anim->x4-offset;
            bytes=((unsigned)anim->x8+skip+31U)&~31U;
            blob=HSD_MemAlloc(bytes);
            fighter_state.aerial_blobs[slot][landing]=blob;
            RogueRuntime_MatchAcquire(fighter_state.match_generation);
            lbFile_800161C4(file,offset,(uintptr_t)blob,bytes,0x21,1);
            anim->x14=(u32)blob+skip;
        }
#if ROGUE_DEBUG
        OSReport("[rogue] aerial_preload kind=%u slot=%u sliced=1 match=%u\n",source,slot,fighter_state.match_generation);
#endif
    }
}

void Rogue_AerialRelease(void)
{
    int source,slot,landing;
    for(slot=0;slot<ROGUE_AERIAL_SLOTS;++slot)
        for(landing=0;landing<2;++landing)
            if(fighter_state.aerial_blobs[slot][landing]) {
                HSD_Free(fighter_state.aerial_blobs[slot][landing]);
                RogueRuntime_MatchRelease(fighter_state.match_generation);
            }
    for(source=0;source<Ft_Kind_Max;++source)
        if(fighter_state.aerial_anims[source]) {
            HSD_Free(fighter_state.aerial_anims[source]);
            RogueRuntime_MatchRelease(fighter_state.match_generation);
        }
}

bool Rogue_AerialTryEnter(Fighter_GObj* gobj, int motion)
{
    Fighter* fp = GET_FIGHTER(gobj);
    const RogueAerialDef* def;
    int slot = motion - ftCo_MS_AttackAirN;
    if (!ROGUE_ENABLE_AERIALS || !Rogue_IsRunPlayer(fp) || fighter_state.fighter != fp || slot < 0 || slot >= ROGUE_AERIAL_SLOTS) return false;
    def = RogueAerial_Find(fighter_state.aerial_equipped[slot]);
    if (!def) return false;
    if (!fighter_state.loaded_sources[def->donor])
        OSPanic(__FILE__, __LINE__, "equipped aerial has no match-owned donor");
    Rogue_BorrowBegin(fp, def->donor);
    fighter_state.aerial = def;
    if(fighter_state.aerial_anims[def->donor]) fp->x24=fighter_state.aerial_anims[def->donor];
    if ((def->donor == Ft_Kind_Link || def->donor == Ft_Kind_CLink) && slot == 4)
        Rogue_LinkAerialDownEnter(gobj);
    else ftCo_AttackAir_EnterFromMsid(gobj, aerial_motion(def, false));
    if (def->donor == Ft_Kind_GameWatch) {
        if (slot == 0) fp->accessory4_cb = ftGw_AttackAirN_ItemParachuteSetup;
        if (slot == 2) fp->accessory4_cb = ftGw_AttackAirN_ItemTurtleSetup;
        if (slot == 3) fp->accessory4_cb = ftGw_AttackAirN_ItemSparkySetup;
    }
#if ROGUE_DEBUG
    OSReport("[rogue] aerial_enter id=%u recipient=%u match=%u\n", def->id, fp->kind, fighter_state.match_generation);
#endif
    return true;
}

MotionState* Rogue_AerialMotionState(Fighter* fp, int motion)
{
    const RogueAerialDef* def = fighter_state.aerial;
    if (!def || (motion != aerial_motion(def, false) && motion != aerial_motion(def, true))) {
        Rogue_AbilityCleanup(fp);
        return NULL;
    }
    if (motion < ftCo_MS_Count) return &fp->x1C_actionStateList[motion];
    return &Rogue_GetAbility(1 + def->donor * 4)->states[motion - ftCo_MS_Count];
}

float Rogue_AerialLandingLag(Fighter* fp, int motion, float native_lag)
{
    ftCo_DatAttrs* attrs;
    float lag, scale;
    const RogueAerialDef* def = fighter_state.aerial;
    if (!Rogue_IsAbilityState(fp) || !def || motion != aerial_motion(def, false)) return native_lag;
    attrs = gFtDataList[def->donor]->x0;
    switch (def->slot) {
    case 0: lag = attrs->landingairn_lag; break;
    case 1: lag = attrs->landingairf_lag; break;
    case 2: lag = attrs->landingairb_lag; break;
    case 3: lag = def->donor == Ft_Kind_GameWatch ? attrs->landingairb_lag : attrs->landingairhi_lag; break;
    default: lag = attrs->landingairlw_lag; break;
    }
    scale = 1.0f - RogueDirector_Run()->stacks[18] * 0.05f;
    if (scale < 0.5f) scale = 0.5f;
    return lag * scale;
}
