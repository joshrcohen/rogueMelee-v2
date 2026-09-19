#ifndef ROGUE_SPECIAL_INTERNAL_H
#define ROGUE_SPECIAL_INTERNAL_H
#include "special_engine.h"
#include "../melee_fighter.h"
#include "../../../director/rogue_director.h"
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ftdata.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/forward.h>
#include <melee/ft/kinds/ftFox/types.h>
#include <melee/ft/kinds/ftFox/ftfoxspecialn.h>
#include <melee/ft/kinds/ftCaptain/ftcaptainspecials.h>
#include <melee/ft/kinds/ftDonkey/ftdonkeyspecialhi.h>
#include <melee/ft/kinds/ftGameWatch/ftgamewatch.h>
#include <melee/ft/kinds/ftLink/ftlinkspecialn.h>
#include <melee/ft/kinds/ftLink/ftlinkspecials.h>
#include <melee/ft/kinds/ftPeach/ftpeachspecialhi.h>
#include <melee/ft/kinds/ftMario/ftmariospecials.h>
#include <melee/ft/kinds/ftSamus/inlines.h>
#include <melee/ft/kinds/ftMewtwo/ftmewtwospecialn.h>
#include <melee/ft/kinds/ftPeach/ftpeachspecialn.h>
#include <melee/ft/kinds/ftSeak/ftseakspecials.h>
#include <melee/pl/player.h>
#include <melee/it/it_26B1.h>
#include <stdio.h>
#include <string.h>

/* Host-owned lifetime, never appended to a disc-layout Fighter or shared data. */
typedef struct RogueFighterState {
    Fighter* fighter;
    const RogueAbilityDefinition* active;
    bool loaded[ROGUE_ABILITY_COUNT];
    bool loaded_sources[Ft_Kind_Max];
    void* native_attrs;
    struct Fighter_WaitAnimData* native_anims;
    u8 (*native_anim_flags)[2];
    u32 native_anim_count;
    union { double align; unsigned char bytes[0x424]; } attrs[Ft_Kind_Max];
    union Fighter_FighterVars native_vars;
    union Fighter_FighterVars source_vars[Ft_Kind_Max];
    /* Fighter callbacks fp+0x2190..0x21F8 are contiguous (0x6C bytes). */
    u8 native_callbacks[0x6C];
} RogueFighterState;
extern RogueFighterState fighter_state;

#endif
