#include "rogue_hud.h"
#include "ui_text.h"
#include "../../director/rogue_director.h"
#include "../../encounters/encounter_registry.h"
#include <melee/if/ifall.h>
#include <melee/gm/gmscene.h>
#include <stdio.h>
#include <string.h>
static RogueText text;
static unsigned generation;
static void line(float x,float y,unsigned color,const char* value)
{
    RogueText_Line(&text,x+2,y+2,"%s",value);
    RogueText_Style(&text,1,0x101624);
    RogueText_Line(&text,x,y,"%s",value);
    RogueText_Style(&text,1,color);
}
static const char* badges[24] = {
    "POWER", "GUARD", "RUN", "AIR", "JUMP", "SHIELD", "REGEN", "WEIGHT",
    "THROW", "LEDGE", "STOCK", "GOLD", "SCORE", "REST", "LAUNCH", "POISE",
    "DASH", "FEATHER", "LAND", "DODGE", "KO HEAL", "THORNS", "DISCOUNT", "FIRST HIT"
};
void RogueHud_Frame(void)
{
    const RogueRun* run = RogueDirector_Run();
    unsigned i, row=0, column=0, count=0;
    char value[96];
    if (generation) { text.native->hidden=ifAll_IsHUDHidden(); return; }
    if (!RogueRuntime_IsActive() || RogueRuntime_Get()->scene != GS_VS ||
        !ifAll_GetHUDGObj()) return;
    for (i=0;i<24;++i) count += run->stacks[i] != 0;
#if !ROGUE_DEBUG
    if (!count && !run->current.tags) return;
#endif
    generation=RogueRuntime_Get()->scene_generation;
    HSD_SisLib_803A62A0(4,"SdMenu.usd","SIS_MenuData");
    HSD_SisLib_803A611C(4,ifAll_GetHUDGObj(),14,15,0,11,0,19);
    RogueText_Create(&text,4,0);
    RogueRuntime_ResourceAcquire(generation);
    text.native->font_size.x=text.native->font_size.y=0.035f;
    text.native->pos_x=-24; text.native->pos_y=-23; text.native->pos_z=0;
    RogueText_Begin(&text);
    if (run->current.tags) {
        sprintf(value,"%s / DMG %u / GUARD %u / SPEED %u",
            rogue_recipes[run->current.recipe-1].name,run->current.damage,run->current.defense,run->current.speed);
        line(0,0,0xF6CD36,value); row++;
    }
    for (i=0;i<24;++i) if (run->stacks[i]) {
        sprintf(value,"%s %u",badges[i],run->stacks[i]);
        line(column*140,row*24,0xDCE6FF,value);
        if (++column==6) { column=0; row++; }
    }
#if ROGUE_DEBUG
    sprintf(value,"DEV / SEED %08X%08X / FLOOR %u / RECIPE %u",
        (unsigned)(run->seed>>32),(unsigned)run->seed,run->floor+1,run->current.recipe);
    line(0,(row+1)*24,0xA4ADBE,value);
#endif
    RogueText_End(&text);
}
void RogueHud_Destroy(void)
{
    if (!generation) return;
    RogueText_Destroy(&text);
    HSD_SisLib_803A5F50(4);
    RogueRuntime_ResourceRelease(generation);
    generation=0;
}
