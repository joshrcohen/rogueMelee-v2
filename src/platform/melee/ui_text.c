#include "ui_text.h"
#include <stdarg.h>
#include <stdio.h>
#include <printf.h>

void RogueText_Create(RogueText* text, int font, int canvas)
{
    text->native = HSD_SisLib_803A6754(font, canvas);
    text->native->font_size.x = text->native->font_size.y = 0.6f;
    text->native->default_kerning = 1;
    text->count = text->used = 0;
}
void RogueText_Begin(RogueText* text) { text->used = 0; }

void RogueText_Line(RogueText* text, float x, float y, const char* fmt, ...)
{
    char ascii[96], encoded[128];
    unsigned i, out = 0;
    va_list args;
    va_start(args, fmt);
    vsnprintf(ascii, sizeof(ascii), fmt, args);
    va_end(args);
    ascii[sizeof(ascii) - 1] = 0;
    /* Native SIS expects Shift-JIS for punctuation outside its ASCII subset. */
    for (i = 0; ascii[i] && out < sizeof(encoded) - 3; ++i) {
        unsigned code = 0;
        switch (ascii[i]) {
        case '%': code = 0x93; break;
        case '/': code = 0x5e; break;
        case '(': code = 0x69; break;
        case ')': code = 0x6a; break;
        case '>': code = 0x84; break;
        case '<': code = 0x83; break;
        case '+': code = 0x7b; break;
        }
        if (code) { encoded[out++] = (char) 0x81; encoded[out++] = (char) code; }
        else encoded[out++] = ascii[i];
    }
    encoded[out] = 0;
    if (text->used == text->count) {
        HSD_SisLib_803A6B98(text->native, x / 0.6f, y / 0.6f, "%s", encoded);
        text->count++;
    } else {
        HSD_SisLib_803A70A0(text->native, text->used, "%s", encoded);
        HSD_SisLib_803A746C(text->native, text->used, x / 0.6f, y / 0.6f);
    }
    text->used++;
}

void RogueText_End(RogueText* text)
{
    unsigned i;
    for (i = text->used; i < text->count; ++i)
        HSD_SisLib_803A70A0(text->native, i, "%s", "");
}
void RogueText_Destroy(RogueText* text)
{
    if (text->native) HSD_SisLib_803A5CC4(text->native);
    text->native = NULL;
    text->count = text->used = 0;
}
