#ifndef ROGUE_UI_SCENE_H
#define ROGUE_UI_SCENE_H
#include "ui_text.h"
#include "ui_asset_data.h"
#include "../../core/run.h"
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
typedef struct RogueUiContext {
    unsigned generation;
    void* storage;
    HSD_Archive archive;
    HSD_GObj* camera;
    HSD_GObj* model;
    HSD_JObj* joints[ROGUE_UI_JOINTS];
    HSD_Archive* portrait_archive;
    HSD_GObj* portraits[4];
    RogueText text;
} RogueUiContext;
void RogueUi_Create(RogueUiContext* ui);
void RogueUi_Update(RogueUiContext* ui, const RogueRun* run, unsigned cursor, int build);
void RogueUi_Destroy(RogueUiContext* ui);
#endif
