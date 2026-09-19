#ifndef ROGUE_MODE_H
#define ROGUE_MODE_H
#include <melee/gm/types.h>
extern GameModeState RogueMode_States[];
void RogueMode_Load(void);
void RogueMode_Unload(void);
void RogueMode_Enter(void* data);
void RogueMode_Exit(void* data);
void RogueMode_Frame(void);
void RogueMode_MenuFrame(void);
void RogueMode_MenuHint(int canvas);
bool RogueMode_CharacterUnlocked(u8 kind);
unsigned RogueMode_MenuDestination(unsigned native_mode);
void RogueMode_MatchFrame(void);
#endif
