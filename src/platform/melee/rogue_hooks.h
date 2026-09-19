#ifndef ROGUE_HOOKS_H
#define ROGUE_HOOKS_H
void RogueHooks_OnBoot(void);
unsigned RogueHooks_BootMode(unsigned native_mode);
void RogueHooks_OnSceneEnter(int scene);
void RogueHooks_OnSceneExit(void);
void RogueHooks_OnFrame(void);
void RogueHooks_DumpContext(void);
#endif
