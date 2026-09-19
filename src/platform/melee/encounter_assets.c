#include "encounter_assets.h"
#include "../../director/rogue_runtime.h"
#include "../../core/features.h"
#include <melee/ft/ftdata.h>
#include <melee/lb/lbfile.h>
#include <sysdolphin/baselib/memory.h>
#include <dolphin/os.h>
extern char* ftData_803C23E4[Ft_Kind_Max];
int Rogue_AramCanFit(unsigned bytes);
static void* archives[Ft_Kind_Max];
static unsigned generation;

int Rogue_AnimationArchiveLoad(int kind, void** data, size_t* size)
{
    unsigned current;
    if (!ROGUE_ENABLE_AERIALS || !RogueRuntime_IsActive() || !RogueRuntime_Get()->match_active) return 0;
    *size=lbFileGetSize(ftData_803C23E4[kind]);
    if (Rogue_AramCanFit((*size+31U)&~31U)) return 0;
    current=RogueRuntime_Get()->match_generation;
    if (generation && generation!=current) OSPanic(__FILE__,__LINE__,"stale encounter animation archive");
    generation=current;
    /* The engine already accepts RAM-backed animation archives. Retain the
     * ordinary ARAM loader whenever it fits; spill only at encounter loading.
     * This does not change special entry, animation contents or callbacks. */
    if (!archives[kind]) {
        archives[kind]=HSD_MemAlloc((*size+31U)&~31U);
        RogueRuntime_MatchAcquire(generation);
        lbFile_8001668C(ftData_803C23E4[kind],archives[kind],size);
        OSReport("[rogue] animation_ram kind=%u bytes=%u match=%u\n",kind,*size,generation);
    }
    *data=archives[kind];
    return 1;
}

void Rogue_EncounterAssetsRelease(void)
{
    int kind,i;
    for(kind=0;kind<Ft_Kind_Max;++kind) if(archives[kind]) {
        if(ftData_Table_Unk0[kind].data==archives[kind]) {
            ftData_Table_Unk0[kind].data=NULL;
            if(gFtDataList[kind])
                for(i=0;i<ftData_Table_Unk0[kind].count;++i) gFtDataList[kind]->xC[i].x14=0;
        }
        HSD_Free(archives[kind]);
        archives[kind]=NULL;
        RogueRuntime_MatchRelease(generation);
    }
    generation=0;
}
