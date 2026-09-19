#ifndef ROGUE_UI_TEXT_H
#define ROGUE_UI_TEXT_H
#include <sysdolphin/baselib/sislib.h>
typedef struct RogueText { HSD_Text* native; unsigned count, used; } RogueText;
void RogueText_Create(RogueText* text, int font, int canvas);
void RogueText_Begin(RogueText* text);
void RogueText_Line(RogueText* text, float x, float y, const char* fmt, ...);
void RogueText_Style(RogueText* text, float scale, unsigned rgb);
void RogueText_Wrap(RogueText* text, float x, float y, unsigned columns, const char* value);
void RogueText_End(RogueText* text);
void RogueText_Destroy(RogueText* text);
#endif
