#include "ui_text.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <printf.h>

void RogueText_Create(RogueText* text, int font, int canvas)
{
    text->native = HSD_SisLib_803A6754(font, canvas);
    /* Reserve the scene's bounded SIS stream once. Repeated incremental growth
     * fragments the retail SIS pool when switching between long/short views. */
    {
        SisBlock* buffer = text->native->alloc_data;
        HSD_SisLib_Free(buffer->data);
        buffer->data = HSD_SisLib_Alloc(8192);
        buffer->next = (SisBlock*) buffer->data;
        buffer->size = 8192;
        text->native->sis_buffer = (SIS*) buffer->data;
        *(unsigned char*) buffer->data = 0;
    }
    text->native->font_size.x = text->native->font_size.y = 0.6f;
    text->native->default_kerning = 1;
    text->count = text->used = 0;
}
void RogueText_Begin(RogueText* text)
{
    HSD_SisLib_803A7664(text->native);
    text->used = text->count = 0;
}

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
    HSD_SisLib_803A7548(text->native, text->used, 1.0f, 1.0f);
    { GXColor white = { 235,238,249,255 }; HSD_SisLib_803A74F0(text->native, text->used, &white); }
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

void RogueText_Style(RogueText* text, float scale, unsigned rgb)
{
    GXColor color = { rgb >> 16, rgb >> 8, rgb, 255 };
    HSD_SisLib_803A7548(text->native, text->used - 1, scale, scale);
    HSD_SisLib_803A74F0(text->native, text->used - 1, &color);
}
void RogueText_Wrap(RogueText* text, float x, float y, unsigned columns, const char* value)
{
    char line[64];
    unsigned length, end, count = 0;
    while (*value && count < 3) {
        length = strlen(value);
        end = length > columns ? columns : length;
        if (length > columns) while (end && value[end] != ' ') --end;
        if (!end) end = columns;
        memcpy(line, value, end); line[end] = 0;
        RogueText_Line(text, x, y + count * 14, "%s", line);
        RogueText_Style(text, 0.75f, 0xBAC3E0);
        value += end;
        while (*value == ' ') value++;
        count++;
    }
}
