#include "capabilities.h"
#include "../../core/features.h"
#include <dolphin/dvd.h>
#include <dolphin/os.h>
#include <melee/ft/forward.h>
#include <melee/gm/forward.h>
#include <string.h>
static RogueCapabilities capabilities;
void RogueCapabilities_Detect(void)
{
    const DVDDiskID* id;
    if (capabilities.detected) return;
    id = DVDGetCurrentDiskID();
    if (!id) return;
    capabilities.detected = 1;
    capabilities.supported = memcmp(id->gameName, "GALE", 4) == 0 &&
        memcmp(id->company, "01", 2) == 0 && id->gameVersion == 2 &&
        CKind_Playable_Count == 26;
    capabilities.roster_count = CKind_Playable_Count;
    capabilities.player_slots = GM_MAX_PLAYERS;
    capabilities.stage_count = 6;
    capabilities.borrowed_specials = capabilities.supported;
    capabilities.aerial_swapping = capabilities.supported && ROGUE_ENABLE_AERIALS;
#if ROGUE_DEBUG
    OSReport("[rogue] capabilities supported=%u roster=%u slots=%u stages=%u specials=%u aerials=%u\n",
        capabilities.supported, capabilities.roster_count, capabilities.player_slots,
        capabilities.stage_count, capabilities.borrowed_specials, capabilities.aerial_swapping);
#endif
}
const RogueCapabilities* RogueCapabilities_Get(void) { return &capabilities; }
