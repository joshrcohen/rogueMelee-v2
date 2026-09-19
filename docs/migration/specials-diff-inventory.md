# Special migration diff inventory

Generated from the pinned prepared oracle. Classification is evidence inventory, not proof that an adapter has been ported or tested.

| File and hunk | Categories | Port status |
| --- | --- | --- |
| `configure.py` -575,0 +576,20 @@ config.libs = [ | excluded-legacy-build-flow | Excluded |
| `configure.py` -1636 +1656 @@ config.libs = [ | excluded-legacy-build-flow | Excluded |
| `configure.py` -2078,0 +2099,128 @@ def generate_compile_commands(objects: dict[str, Object], build_config: BuildCon | excluded-legacy-build-flow | Excluded |
| `src/Runtime/eabi_save_restore.s` -107,0 +108,4 @@ blr | excluded-legacy-build-flow | Excluded |
| `src/melee/ft/fighter.c` -0,0 +1,2 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/ft/fighter.c` -1,0 +4,2 @@ | special-interface | Pending |
| `src/melee/ft/fighter.c` -233,0 +238 @@ void Fighter_UnkInitReset_80067C98(Fighter* fp) | lifecycle-cleanup | Pending |
| `src/melee/ft/fighter.c` -420 +425 @@ void Fighter_UnkInitReset_80067C98(Fighter* fp) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/fighter.c` -933,0 +939 @@ Fighter_GObj* Fighter_Create(struct plAllocInfo* input) | donor-preload | Pending |
| `src/melee/ft/fighter.c` -950,0 +957,6 @@ void Fighter_ChangeMotionState(Fighter_GObj* gobj, FtMotionId msid, | state-table-redirect, donor-compatibility | Pending |
| `src/melee/ft/fighter.c` -1181 +1193,3 @@ void Fighter_ChangeMotionState(Fighter_GObj* gobj, FtMotionId msid, | state-table-redirect | Pending |
| `src/melee/ft/fighter.c` -1259 +1273,5 @@ void Fighter_ChangeMotionState(Fighter_GObj* gobj, FtMotionId msid, | donor-compatibility | Pending |
| `src/melee/ft/fighter.c` -1882,0 +1901 @@ void Fighter_Spaghetti_8006AD10(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/fighter.c` -2654,0 +2674 @@ void Fighter_TakeDamage_8006CC7C(Fighter* fp, float damage_amount) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/fighter.c` -2823,3 +2843,4 @@ void Fighter_ProcessHit_8006D1EC(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/fighter.c` -2827 +2848 @@ void Fighter_ProcessHit_8006D1EC(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/fighter.c` -2840 +2861 @@ void Fighter_ProcessHit_8006D1EC(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/fighter.c` -3097,0 +3119,2 @@ void Fighter_Unload_8006DABC(void* user_data) | lifecycle-cleanup | Pending |
| `src/melee/ft/ft_0D31.c` -0,0 +1 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ft_0D31.c` -29,0 +31,14 @@ const Quaternion lbl_803B7500 = { 0, 3.1415927f, 0, 0 }; | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ft_0D31.c` -44,0 +60 @@ bool ftCo_800D3158(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ft_0D31.c` -48,0 +65 @@ bool ftCo_800D3158(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ft_0D31.c` -55,0 +73 @@ bool ftCo_800D3158(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ft_0D31.c` -74,0 +93 @@ bool ftCo_800D3158(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ft_0D31.c` -139,0 +159,5 @@ void ftCo_800D34E0(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftaction.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/ftaction.c` -244 +245 @@ void ftAction_80071028(Fighter_GObj* gobj, CommandInfo* cmd) | bone-animation-data | Pending |
| `src/melee/ft/ftaction.c` -270,0 +272,7 @@ void ftAction_80071028(Fighter_GObj* gobj, CommandInfo* cmd) | bone-animation-data, donor-compatibility | Pending |
| `src/melee/ft/ftaction.c` -318 +326 @@ void ftAction_8007121C(Fighter_GObj* gobj, CommandInfo* cmd) | bone-animation-data | Pending |
| `src/melee/ft/ftaction.c` -669 +677 @@ void ftAction_80071CCC(Fighter_GObj* gobj, CommandInfo* cmd) | bone-animation-data | Pending |
| `src/melee/ft/ftaction.c` -686,2 +694,6 @@ void ftAction_80071D40(Fighter_GObj* gobj, CommandInfo* cmd) | donor-compatibility | Pending |
| `src/melee/ft/ftaction.c` -991,2 +1003,9 @@ void ftAction_800727C8(Fighter_GObj* gobj, CommandInfo* cmd) | donor-compatibility | Pending |
| `src/melee/ft/ftaction.c` -998,2 +1017,8 @@ void ftAction_8007283C(Fighter_GObj* gobj, CommandInfo* cmd) | donor-compatibility | Pending |
| `src/melee/ft/ftaction.c` -1004,0 +1030,20 @@ void ftAction_80072894(Fighter_GObj* gobj, CommandInfo* cmd) | donor-compatibility | Pending |
| `src/melee/ft/ftaction.c` -1173 +1218 @@ void ftAction_80072CD8(Fighter_GObj* gobj, CommandInfo* cmd) | bone-animation-data | Pending |
| `src/melee/ft/ftaction.c` -1175 +1220 @@ void ftAction_80072CD8(Fighter_GObj* gobj, CommandInfo* cmd) | bone-animation-data | Pending |
| `src/melee/ft/ftaction.c` -1296,0 +1342,2 @@ void ftAction_80073118(Fighter_GObj* gobj, CommandInfo* cmd) | bone-animation-data, donor-compatibility | Pending |
| `src/melee/ft/ftafterimage.c` -4,0 +5 @@ | special-interface | Pending |
| `src/melee/ft/ftafterimage.c` -30 +31,5 @@ static inline itSword_UnkBytes* ftCo_800C2600_get_params(Fighter* fp) | donor-compatibility | Pending |
| `src/melee/ft/ftafterimage.c` -42 +47 @@ static inline itSword_UnkBytes* ftCo_800C2600_get_params(Fighter* fp) | bone-animation-data | Pending |
| `src/melee/ft/ftafterimage.c` -115,0 +121,4 @@ void ftCo_800C2600(Fighter_GObj* gobj, u32 arg1) | bone-animation-data | Pending |
| `src/melee/ft/ftafterimage.c` -383,0 +393 @@ void ftCo_800C2FD8(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/ftafterimage.c` -386,0 +397,4 @@ void ftCo_800C2FD8(Fighter_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/ftafterimage.c` -426,2 +440,8 @@ void ftCo_800C2FD8(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/ftafterimage.c` -441 +461,2 @@ void ftCo_800C2FD8(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/ftafterimage.c` -446 +467,4 @@ void ftCo_800C2FD8(Fighter_GObj* gobj) | bone-animation-data, donor-compatibility | Pending |
| `src/melee/ft/ftafterimage.c` -447,0 +472,6 @@ void ftCo_800C2FD8(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/ftanim.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/ftanim.c` -1062,0 +1064,4 @@ void ftAnim_800704F0(Fighter_GObj* gobj, int tobj_idx, float frame) | donor-compatibility | Pending |
| `src/melee/ft/ftchangeparam.c` -0,0 +1 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftchangeparam.c` -152,0 +154 @@ void ftCo_800D0FA0(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftchangeparam.c` -173,0 +176 @@ void ftCo_800D105C(Fighter_GObj* fgp) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -0,0 +1 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -1,0 +3,2 @@ | special-interface | Pending |
| `src/melee/ft/ftcoll.c` -580 +583 @@ static inline float inlineB3(Fighter* fp0, HitCapsule* hit0, Fighter* fp1) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -764 +767 @@ void ftColl_80077464(Item* item, HitCapsule* hit, Fighter* fp) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -820,2 +823,2 @@ void ftColl_80077464(Item* item, HitCapsule* hit, Fighter* fp) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -825 +828 @@ void ftColl_80077464(Item* item, HitCapsule* hit, Fighter* fp) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -1158,0 +1162,3 @@ bool ftColl_80077C60(Item* item, HitCapsule* hit, Fighter* fp, | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -2234,0 +2241,3 @@ void ftColl_8007925C(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -2235,0 +2245 @@ void ftColl_8007925C(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -2445 +2455 @@ float ftColl_80079C70(Fighter* fp, Fighter* attacker, HitCapsule* hit, | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -2775,0 +2786,11 @@ void ftColl_8007A06C(Fighter_GObj* gobj, void* dmg_ptr, void* log, size_t idx, | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -2879,0 +2901 @@ void ftColl_8007A06C(Fighter_GObj* gobj, void* dmg_ptr, void* log, size_t idx, | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -2900,0 +2923 @@ void ftColl_8007A06C(Fighter_GObj* gobj, void* dmg_ptr, void* log, size_t idx, | excluded-legacy-modifier | Excluded |
| `src/melee/ft/ftcoll.c` -3115,0 +3139,3 @@ void ftColl_8007B128(Fighter_GObj* fighter_gobj, int bone_id, | bone-animation-data, donor-compatibility | Pending |
| `src/melee/ft/ftcoll.c` -3127,0 +3154,5 @@ void ftColl_8007B128(Fighter_GObj* fighter_gobj, int bone_id, | donor-compatibility | Pending |
| `src/melee/ft/ftcoll.c` -3142 +3173 @@ void ftColl_8007B1B8(Fighter_GObj* gobj, ShieldDesc* shield, HSD_GObjEvent cb) | bone-animation-data | Pending |
| `src/melee/ft/ftcoll.c` -3158 +3189 @@ void ftColl_CreateReflectHit(Fighter_GObj* gobj, ReflectDesc* reflect, | bone-animation-data | Pending |
| `src/melee/ft/ftcoll.c` -3168 +3199 @@ void ftColl_CreateAbsorbHit(Fighter_GObj* gobj, AbsorbDesc* absorb) | bone-animation-data | Pending |
| `src/melee/ft/ftcommon.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/ftcommon.c` -1088,0 +1090,6 @@ void ftCommon_8007E83C(HSD_GObj* gobj, s32 arg1, float div) | donor-compatibility | Pending |
| `src/melee/ft/ftcommon.c` -1261,0 +1269 @@ void ftCommon_8007EFC8(HSD_GObj* gobj, void (*arg1)(HSD_GObj*)) | transform-subfighter | Pending |
| `src/melee/ft/ftcommon.c` -1390,0 +1399 @@ void ftCommon_8007EFC8(HSD_GObj* gobj, void (*arg1)(HSD_GObj*)) | transform-subfighter | Pending |
| `src/melee/ft/ftlib.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/ftlib.c` -1028 +1029 @@ void ftLib_8008770C(HSD_GObj* gobj, void* dst) | donor-compatibility | Pending |
| `src/melee/ft/ftlib.c` -1037 +1038 @@ void ftLib_80087744(HSD_GObj* gobj, void* dst) | donor-compatibility | Pending |
| `src/melee/ft/ftparts.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/ftparts.c` -697 +698,24 @@ Fighter_Part ftParts_GetBoneIndex(Fighter* fp, Fighter_Part part) | donor-compatibility | Pending |
| `src/melee/ft/inlines.h` -2,0 +3 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/ft/inlines.h` -138 +139,2 @@ static inline void getAccelAndTarget(Fighter* fp, float* accel, | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecialn.c` -38 +39 @@ static inline void ftCaptain_SpecialN_CreateWindEffect(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecialn.c` -157,2 +158,2 @@ static inline void doPhys(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecialn.c` -161,2 +162,2 @@ static inline void doPhys(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -31,2 +32,2 @@ void ftCa_SpecialS_RemoveGFX(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -63 +64 @@ void ftCa_SpecialS_Enter(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -65,2 +66,2 @@ void ftCa_SpecialS_Enter(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -70,2 +71,2 @@ void ftCa_SpecialS_Enter(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -76 +77 @@ void ftCa_SpecialS_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -96 +97 @@ static inline void setupAirStart(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -98,2 +99,2 @@ static inline void setupAirStart(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -103,2 +104,2 @@ static inline void setupAirStart(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -110 +111 @@ static inline void setupAirStart(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -217,2 +218,2 @@ void ftCa_SpecialS_Anim(HSD_GObj* gobj) | donor-variable-bank, donor-compatibility | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -220 +221 @@ void ftCa_SpecialS_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -222 +223 @@ void ftCa_SpecialS_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -226 +227 @@ void ftCa_SpecialS_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -228 +229 @@ void ftCa_SpecialS_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -260,2 +261,2 @@ void ftCa_SpecialAirS_Anim(HSD_GObj* gobj) | donor-variable-bank, donor-compatibility | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -263 +264 @@ void ftCa_SpecialAirS_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -265 +266 @@ void ftCa_SpecialAirS_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -269 +270 @@ void ftCa_SpecialAirS_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCaptain/ftcaptainspecials.c` -271 +272 @@ void ftCa_SpecialAirS_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_09F7.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_09F7.c` -75 +76 @@ block_2: | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_09F7.c` -87 +88 @@ block_5: | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_09F7.c` -90,0 +92 @@ block_7: | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_09F7.c` -146 +148 @@ block_12: | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_Attack100.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_Attack100.c` -51 +52,2 @@ bool ftCo_800D6824(Fighter_GObj* gobj) | special-input | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_Attack100.c` -74 +76,2 @@ bool ftCo_800D68C0(Fighter_GObj* gobj) | special-input | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_Attack100.c` -97 +100,2 @@ bool ftCo_Attack100_CheckInput(Fighter_GObj* gobj) | special-input | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_Attack100.c` -110 +114,2 @@ bool ftCo_800D69C4(Fighter_GObj* gobj) | special-input | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_AttackAir.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_AttackAir.c` -75,0 +77,3 @@ static void decideFighter(Fighter_GObj* gobj) | excluded-aerial | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_Damage.c` -0,0 +1 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_Damage.c` -142 +143 @@ void ftCo_Damage_CalcKnockback(Fighter* fp) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_Damage.c` -286 +287 @@ void ftCo_8008DCE0(Fighter_GObj* gobj, int arg1, float facing_dir) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_Guard.c` -0,0 +1 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_Guard.c` -183 +184 @@ static inline float inlineB0(Fighter* fp) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_Guard.c` -420 +421 @@ bool ftCo_800925A4(HSD_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_Guard.c` -632,0 +634 @@ void ftCo_80092E50(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_Guard.c` -686 +688 @@ void ftCo_80092F2C(HSD_GObj* gobj, bool arg1) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_Guard.c` -877,0 +880 @@ void ftCo_80093790(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_JumpAerialF1.c` -95,0 +96,4 @@ void ftCo_800D74A4(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_JumpAerialF1.c` -97 +101 @@ void ftCo_800D74A4(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_LandingAir.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_LandingAir.c` -52,0 +54 @@ void ftCo_LandingAir_EnterWithLag(Fighter_GObj* gobj) | excluded-aerial | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_SpecialAir.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_SpecialAir.c` -19 +20,2 @@ bool ftCo_SpecialAir_CheckInput(Fighter_GObj* gobj) | special-input | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_SpecialAir.c` -27 +29,2 @@ bool ftCo_SpecialAir_CheckInput(Fighter_GObj* gobj) | special-input | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_SpecialAir.c` -39 +42,2 @@ bool ftCo_SpecialAir_CheckInput(Fighter_GObj* gobj) | special-input | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_SpecialAir.c` -52 +56,2 @@ bool ftCo_SpecialAir_CheckInput(Fighter_GObj* gobj) | special-input | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_SpecialS.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_SpecialS.c` -48 +49,2 @@ static void doEnter(Fighter_GObj* gobj) | special-input | Pending |
| `src/melee/ft/kinds/ftCommon/ftCo_Thrown.c` -0,0 +1 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_Thrown.c` -193,0 +195 @@ void ftCo_800DE854(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftCommon/ftCo_Thrown.c` -202,3 +204,3 @@ void ftCo_800DE854(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialhi.c` -49 +50 @@ void ftDk_SpecialHi_Enter(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialhi.c` -65 +66 @@ void ftDk_SpecialAirHi_Enter(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspeciallw.c` -100 +101 @@ static void ftDonkey_8010DE88_inner(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspeciallw.c` -168 +169 @@ void ftDk_SpecialLw_8010E0CC(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspeciallw.c` -179 +180 @@ void ftDk_SpecialLw_8010E148(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -52 +53 @@ void ftDk_SpecialN_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -56,2 +57,2 @@ void ftDk_SpecialN_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -80 +81 @@ void ftDk_SpecialAirN_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -84,2 +85,2 @@ void ftDk_SpecialAirN_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -123,2 +124,2 @@ void ftDk_SpecialNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -127 +128 @@ void ftDk_SpecialNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -154 +155 @@ void ftDk_SpecialN_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -157 +158 @@ void ftDk_SpecialN_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -187 +188 @@ void ftDk_SpecialN_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -205 +206 @@ void ftDk_SpecialNFull_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -208 +209 @@ void ftDk_SpecialNFull_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -222 +223 @@ void ftDk_SpecialNFull_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -242,2 +243,2 @@ void ftDk_SpecialAirNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -246 +247 @@ void ftDk_SpecialAirNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -275 +276 @@ void ftDk_SpecialAirN_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -278 +279 @@ void ftDk_SpecialAirN_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -302 +303 @@ void ftDk_SpecialAirN_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -326 +327 @@ void ftDk_SpecialAirNFull_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -329 +330 @@ void ftDk_SpecialAirNFull_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -334 +335 @@ void ftDk_SpecialAirNFull_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -355,2 +356,2 @@ void ftDk_SpecialNLoop_IASA(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -385,2 +386,2 @@ void ftDk_SpecialAirNLoop_IASA(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftDonkey/ftdonkeyspecialn.c` -564 +565 @@ void ftDk_SpecialN_DestroyAllEffectsPlus(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspeciallw.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspeciallw.c` -40 +41 @@ void ftFx_SpecialLw_CreateLoopGFX(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspeciallw.c` -54 +55 @@ void ftFx_SpecialLw_CreateStartGFX(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspeciallw.c` -67 +68 @@ void ftFx_SpecialLw_CreateReflectGFX(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -131,2 +132,2 @@ void ftFx_SpecialN_ClearBlaster(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -141,3 +142,3 @@ void ftFx_SpecialN_RemoveBlaster(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -172 +173 @@ static inline void ftFox_SpecialN_FireBlasterShot(HSD_GObj* gobj, Fighter* fp, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -221 +222 @@ static inline void ftFox_SpecialN_SpawnBlaster(HSD_GObj* gobj, Fighter* fp, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -224 +225 @@ static inline void ftFox_SpecialN_SpawnBlaster(HSD_GObj* gobj, Fighter* fp, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -273,2 +274,2 @@ static inline void ftFox_SpecialN_UpdateBlaster(Fighter* fp) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -276 +277 @@ static inline void ftFox_SpecialN_UpdateBlaster(Fighter* fp) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -291 +292 @@ static inline void ftFox_SpecialN_StartAnimation(HSD_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -315 +316 @@ static inline void ftFox_SpecialN_FinishLoopTransition(Fighter* fp) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -320 +321 @@ static inline void ftFox_SpecialN_FinishEndTransition(Fighter* fp) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -368,2 +369,2 @@ static inline void ftFox_SpecialN_RemoveBlasterNULL(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -377 +378 @@ static inline bool ftFox_SpecialN_UpdateEndAnimation(HSD_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -381 +382 @@ static inline bool ftFox_SpecialN_UpdateEndAnimation(HSD_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -383 +384 @@ static inline bool ftFox_SpecialN_UpdateEndAnimation(HSD_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -555 +556 @@ void ftFx_Throw_Anim(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -559 +560 @@ void ftFx_Throw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -565 +566 @@ void ftFx_Throw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -571 +572 @@ void ftFx_Throw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -573 +574 @@ void ftFx_Throw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -580 +581 @@ void ftFx_Throw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -584 +585 @@ void ftFx_Throw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -588 +589 @@ void ftFx_Throw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -616 +617 @@ void ftFx_Throw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -656,2 +657,2 @@ void ftFx_Throw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecialn.c` -672 +673 @@ void ftFx_Throw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecials.c` -35 +36 @@ void ftFx_SpecialS_CreateGFX(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftFox/ftfoxspecials.c` -254 +255 @@ static inline void ftFox_SpecialS_CreateGhostItem(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatch.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatch.c` -633,0 +635 @@ void ftGw_Init_8014A7F4(HSD_GObj* gobj, ItemModStruct* item_mod) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatch.c` -635 +637,4 @@ void ftGw_Init_8014A7F4(HSD_GObj* gobj, ItemModStruct* item_mod) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialhi.c` -40,2 +41,2 @@ void ftGw_SpecialHi_ItemRescueSetup(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialhi.c` -43 +44,2 @@ void ftGw_SpecialHi_ItemRescueSetup(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialhi.c` -46 +48 @@ void ftGw_SpecialHi_ItemRescueSetup(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialhi.c` -78 +80 @@ void ftGw_SpecialHi_ItemRescueSetNULL(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialhi.c` -88,2 +90,2 @@ void ftGw_SpecialHi_ItemRescueRemove(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialhi.c` -99,2 +101,2 @@ static void ftGw_SpecialHi_ItemRescueEnterHitlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialhi.c` -109,2 +111,2 @@ static void ftGw_SpecialHi_ItemRescueExitHitlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -29 +30 @@ void ftGw_SpecialLw_ItemPanicSetup(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -35 +36 @@ void ftGw_SpecialLw_ItemPanicSetup(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -37 +38 @@ void ftGw_SpecialLw_ItemPanicSetup(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -40 +41 @@ void ftGw_SpecialLw_ItemPanicSetup(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -56 +57 @@ void ftGw_SpecialLw_ItemPanicSetFlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -66,2 +67,2 @@ void ftGw_SpecialLw_ItemPanicRemove(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -77,2 +78,2 @@ void ftGw_SpecialLw_ItemPanicEnterHitlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -87,2 +88,2 @@ void ftGw_SpecialLw_ItemPanicExitHitlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -113 +114 @@ void ftGw_SpecialLw_UpdateBucketModel(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -153 +154 @@ void ftGw_SpecialLw_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -171 +172 @@ void ftGw_SpecialAirLw_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -457 +458 @@ void ftGw_SpecialLwCatch_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -478 +479 @@ void ftGw_SpecialAirLwCatch_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -548,2 +549,2 @@ void ftGw_SpecialLw_AbsorbThink_DecideAction(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -551 +552 @@ void ftGw_SpecialLw_AbsorbThink_DecideAction(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -678 +679 @@ void ftGw_SpecialLwShoot_ReleaseOil(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -686,2 +687,2 @@ void ftGw_SpecialLwShoot_ReleaseOil(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -712 +713 @@ void ftGw_SpecialAirLwShoot_ReleaseOil(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.c` -721,2 +722,2 @@ void ftGw_SpecialAirLwShoot_ReleaseOil(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialn.c` -61,2 +62,2 @@ static void ftGw_SpecialN_CreateSausage(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialn.c` -73,2 +74,2 @@ static void ftGw_SpecialN_CreateSausage(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecialn.c` -76 +77 @@ static void ftGw_SpecialN_CreateSausage(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -39 +40 @@ void ftGw_SpecialS_ItemJudgementSetup(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -42,2 +43,2 @@ void ftGw_SpecialS_ItemJudgementSetup(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -52 +53 @@ void ftGw_SpecialS_ItemJudgementSetup(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -69 +70 @@ void ftGw_SpecialS_ItemJudgementSetFlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -80,2 +81,2 @@ void ftGw_SpecialS_ItemJudgementRemove(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -91,2 +92,2 @@ static void ftGw_SpecialS_ItemJudgementEnterHitlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -100,2 +101,2 @@ static void ftGw_SpecialS_ItemJudgementExitHitlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -136,2 +137,2 @@ int ftGw_SpecialS_GetRandomInt(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -160,2 +161,2 @@ int ftGw_SpecialS_GetRandomInt(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -187 +188 @@ void ftGw_SpecialS_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -207 +208 @@ void ftGw_SpecialAirS_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -271,2 +272,2 @@ void ftGw_SpecialAirS_Phys(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -312 +313 @@ static inline void ftGameWatch_SpecialS_SetCall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -338 +339 @@ static void ftGw_SpecialS_GroundToAir(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -354 +355 @@ static void ftGw_SpecialAirS_AirToGround(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftGameWatch/ftgamewatchspecials.c` -358 +359 @@ static void ftGw_SpecialAirS_AirToGround(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -1,0 +2 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -2816,0 +2818,2 @@ void ftKb_UnkMtxFunc0(Fighter_GObj* gobj, int arg1, Mtx mtx) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -2818 +2821 @@ void ftKb_UnkMtxFunc0(Fighter_GObj* gobj, int arg1, Mtx mtx) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -2827,2 +2830,2 @@ void ftKb_UnkMtxFunc0(Fighter_GObj* gobj, int arg1, Mtx mtx) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -2832 +2835 @@ void ftKb_UnkMtxFunc0(Fighter_GObj* gobj, int arg1, Mtx mtx) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -2839,0 +2843,2 @@ HSD_JObj* ftKb_Init_UnkMotionStates6(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -2841,2 +2846,2 @@ HSD_JObj* ftKb_Init_UnkMotionStates6(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -3162 +3167,4 @@ void ftKb_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -3164,2 +3172,2 @@ void ftKb_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -3177,2 +3185,2 @@ void ftKb_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -3183 +3191 @@ void ftKb_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -3185,2 +3193,2 @@ void ftKb_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -3190 +3198 @@ void ftKb_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -3193,2 +3201,2 @@ void ftKb_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -3197 +3205 @@ void ftKb_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -3205,2 +3213,5 @@ void ftKb_Init_UnkCallbackPairs0_0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirby.c` -3213,2 +3224,5 @@ void ftKb_Init_UnkCallbackPairs0_1(Fighter_GObj* gobj, int arg1, float arg2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c` -33 +34 @@ void ftKb_SpecialNCa_800F99BC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c` -50 +51 @@ void ftKb_SpecialNCa_800F9A54(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c` -128 +129 @@ void ftKb_CaSpecialN_Phys(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c` -130,2 +131,2 @@ void ftKb_CaSpecialN_Phys(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c` -134,2 +135,2 @@ void ftKb_CaSpecialN_Phys(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c` -162 +163 @@ void ftKb_CaSpecialAirN_Phys(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c` -164,2 +165,2 @@ void ftKb_CaSpecialAirN_Phys(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c` -168,2 +169,2 @@ void ftKb_CaSpecialAirN_Phys(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c` -212 +213 @@ void ftKb_CaSpecialN_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialcaptain.c` -237 +238 @@ void ftKb_CaSpecialAirN_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -40 +41 @@ void ftKb_SpecialNDk_800FF8EC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -44,2 +45,2 @@ void ftKb_SpecialNDk_800FF8EC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -73 +74 @@ void ftKb_SpecialNDk_800FFA10(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -77,2 +78,2 @@ void ftKb_SpecialNDk_800FFA10(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -122,2 +123,2 @@ void ftKb_DkSpecialNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -126 +127 @@ void ftKb_DkSpecialNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -160 +161 @@ void ftKb_DkSpecialN_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -163 +164 @@ void ftKb_DkSpecialN_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -200 +201 @@ void ftKb_DkSpecialN_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -222 +223 @@ void ftKb_DkSpecialNFull_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -225 +226 @@ void ftKb_DkSpecialNFull_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -246 +247 @@ void ftKb_DkSpecialNFull_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -272,2 +273,2 @@ void ftKb_DkSpecialAirNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -276 +277 @@ void ftKb_DkSpecialAirNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -311 +312 @@ void ftKb_DkSpecialAirN_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -314 +315 @@ void ftKb_DkSpecialAirN_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -337 +338 @@ void ftKb_DkSpecialAirN_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -365 +366 @@ void ftKb_DkSpecialAirNFull_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -368 +369 @@ void ftKb_DkSpecialAirNFull_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -373 +374 @@ void ftKb_DkSpecialAirNFull_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -399,2 +400,2 @@ void ftKb_DkSpecialNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -431,2 +432,2 @@ void ftKb_DkSpecialAirNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.c` -606 +607 @@ void ftKb_SpecialNPr_80100DE0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -43 +44 @@ void ftKb_SpecialNFx_800FDC00(Fighter_GObj* gobj, Vec3* vec) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -59 +60 @@ void ftKb_SpecialNFx_800FDC70(Fighter_GObj* gobj, Vec3* vec) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -79 +80 @@ bool ftKb_SpecialNFx_800FDD14(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -95 +96 @@ ftFx_SpecialNIndex ftKb_SpecialNFx_800FDD4C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -147 +148 @@ bool ftKb_SpecialNFx_800FDDF4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -198,2 +199,2 @@ void ftKb_SpecialNFx_800FDEB4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -210,3 +211,3 @@ void ftKb_SpecialNFx_800FDEE0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -240 +241 @@ void ftKb_SpecialNFx_800FDF30(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -249 +250 @@ void ftKb_SpecialNFx_800FDF30(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -262 +263 @@ void ftKb_SpecialNFx_800FDF30(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -281 +282 @@ static inline FtMotionId ftKbGetStartMotionId(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -317 +318 @@ void ftKb_SpecialNFx_800FE100(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -330 +331 @@ void ftKb_SpecialNFx_800FE100(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -345 +346 @@ static inline FtMotionId ftKbGetAirStartMotionId(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -374 +375 @@ void ftKb_SpecialNFx_800FE240(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -387 +388 @@ void ftKb_SpecialNFx_800FE240(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -402 +403 @@ static inline FtMotionId ftKbGetLoopMotionId(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -419,2 +420,2 @@ void ftKb_FxSpecialNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -422 +423 @@ void ftKb_FxSpecialNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -430 +431 @@ void ftKb_FxSpecialNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -438 +439 @@ static inline FtMotionId ftKbGetEndMotionId(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -456,2 +457,2 @@ void ftKb_FxSpecialNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -459 +460 @@ void ftKb_FxSpecialNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -470 +471 @@ void ftKb_FxSpecialNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -476 +477 @@ void ftKb_FxSpecialNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -489 +490 @@ void ftKb_FxSpecialNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -495 +496 @@ void ftKb_FxSpecialNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -498 +499 @@ void ftKb_FxSpecialNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -510 +511 @@ static inline FtMotionId ftKbGetAirLoopMotionId(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -527,2 +528,2 @@ void ftKb_FxSpecialAirNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -530 +531 @@ void ftKb_FxSpecialAirNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -538 +539 @@ void ftKb_FxSpecialAirNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -546 +547 @@ static inline FtMotionId ftKbGetAirEndMotionId(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -565,2 +566,2 @@ void ftKb_FxSpecialAirNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -568 +569 @@ void ftKb_FxSpecialAirNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -580 +581 @@ void ftKb_FxSpecialAirNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -586 +587 @@ void ftKb_FxSpecialAirNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -604 +605 @@ void ftKb_FxSpecialAirNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -611 +612 @@ void ftKb_FxSpecialAirNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -614 +615 @@ void ftKb_FxSpecialAirNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -618 +619 @@ void ftKb_FxSpecialAirNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -726 +727 @@ bool ftKb_SpecialNNs_800FEC78(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -740,2 +741,2 @@ void ftKb_SpecialNNs_800FECBC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialfox.c` -751,3 +752,3 @@ void ftKb_SpecialNNs_800FECE8(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.c` -72 +73 @@ void fn_8010CE5C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.c` -82 +83 @@ void fn_8010CE5C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.c` -84 +85 @@ void fn_8010CE5C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.c` -105 +106 @@ void fn_8010CFB0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.c` -107 +108 @@ void fn_8010CFB0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.c` -120 +121 @@ void ftKb_SpecialNGw_8010D074(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.c` -126,2 +127,2 @@ void ftKb_SpecialNGw_8010D0A8(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.c` -135,2 +136,2 @@ void fn_8010D100(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.c` -143,2 +144,2 @@ void ftKb_SpecialNGw_8010D130(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialhi.c` -46 +47 @@ void fn_800F21E8(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -33,2 +34,2 @@ void ftKb_SpecialNIc_80108CE8(Fighter_GObj* gobj, Item_GObj* it_gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -42,2 +43,2 @@ void ftKb_SpecialNIc_80108D04(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -46,2 +47,2 @@ void ftKb_SpecialNIc_80108D04(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -60 +61 @@ void ftKb_SpecialNIc_80108D64(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -82,2 +83,2 @@ void ftKb_SpecialNIc_80108E14(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -85,2 +86,2 @@ void ftKb_SpecialNIc_80108E14(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -88 +89 @@ void ftKb_SpecialNIc_80108E14(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -137,2 +138,2 @@ void ftKb_PpSpecialN_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -141,2 +142,2 @@ void ftKb_PpSpecialN_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -156,2 +157,2 @@ void ftKb_PpSpecialAirN_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -160,2 +161,2 @@ void ftKb_PpSpecialAirN_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -165,2 +166,2 @@ void ftKb_PpSpecialAirN_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -183 +184 @@ void fn_801090D4(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -185,2 +186,2 @@ void fn_801090D4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -189 +190 @@ void fn_801090D4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -197,2 +198,2 @@ void fn_801090D4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.c` -204,2 +205,2 @@ void fn_801090D4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -40 +41 @@ void ftKb_SpecialNKp_800FA588(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -66 +67 @@ void ftKb_SpecialNKp_800FA588(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -76 +77 @@ void ftKb_SpecialNKp_800FA588(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -97,3 +98,3 @@ void ftKb_SpecialNKp_800FA7D4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -101,3 +102,3 @@ void ftKb_SpecialNKp_800FA7D4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -187 +188 @@ void ftKb_KpSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -238 +239 @@ void ftKb_KpSpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -303 +304 @@ void ftKb_KpSpecialN_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -319,3 +320,3 @@ void ftKb_KpSpecialN_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -323,3 +324,3 @@ void ftKb_KpSpecialN_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -357 +358 @@ void ftKb_KpSpecialAirN_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -373,3 +374,3 @@ void ftKb_KpSpecialAirN_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialkoopa.c` -377,3 +378,3 @@ void ftKb_KpSpecialAirN_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -23,2 +24,2 @@ ftLk_SpecialNIndex ftKb_SpecialNLk800FB394(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -59,2 +60,2 @@ void ftKb_SpecialNLk800FB418(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -69,2 +70,2 @@ void ftKb_SpecialNLk800FB444(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -87,2 +88,2 @@ static inline void ftKb_SpecialNLk_UnsetArrow(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -97,2 +98,2 @@ static inline void ftKb_SpecialNLk_UnsetBow(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -108 +109 @@ bool ftKb_SpecialNLk800FB470(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -147 +148 @@ bool ftKb_SpecialNLk800FB500(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -152,2 +153,2 @@ bool ftKb_SpecialNLk800FB500(Fighter_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -163 +164 @@ bool ftKb_SpecialNLk800FB500(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -178 +179 @@ bool ftKb_SpecialNLk800FB5F4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -182,2 +183,2 @@ bool ftKb_SpecialNLk800FB5F4(Fighter_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -193 +194 @@ bool ftKb_SpecialNLk800FB5F4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -213 +214 @@ void ftKb_SpecialNLk800FB6DC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -218,2 +219,2 @@ void ftKb_SpecialNLk800FB6DC(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -223 +224 @@ void ftKb_SpecialNLk800FB6DC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -233 +234 @@ void ftKb_SpecialNLk800FB6DC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -245,3 +246,3 @@ void ftKb_SpecialNLk800FB800(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -255,3 +256,3 @@ void ftKb_SpecialNLk800FB840(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -286 +287 @@ void ftKb_SpecialNLk800FB880(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -327 +328 @@ void ftKb_SpecialNLk800FBA00(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -342 +343 @@ void ftKb_SpecialNLk800FBA00(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -374 +375 @@ void ftKb_LkSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -394,2 +395,2 @@ void ftKb_LkSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -431,2 +432,2 @@ void ftKb_LkSpecialNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -467,2 +468,2 @@ void ftKb_LkSpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -489 +490 @@ void ftKb_LkSpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -518,2 +519,2 @@ void ftKb_LkSpecialAirNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -532 +533 @@ void ftKb_LkSpecialAirNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -558 +559 @@ void ftKb_LkSpecialNStart_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -594 +595 @@ void ftKb_LkSpecialNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -630 +631 @@ void ftKb_LkSpecialAirNStart_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallink.c` -666 +667 @@ void ftKb_LkSpecialAirNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallw.c` -121,2 +122,2 @@ void ftKb_SpecialHi_800F346C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallw.c` -370 +371 @@ void ftKb_SpecialLw_Enter(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallw.c` -400 +401 @@ void ftKb_SpecialAirLw_Enter(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallw.c` -515 +516 @@ void ftKb_SpecialLw_IASA(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspeciallw.c` -537 +538 @@ void ftKb_SpecialAirLw_IASA(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmario.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmario.c` -38 +39 @@ void ftKb_SpecialN_800F9110(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmario.c` -84 +85 @@ static inline s32 fn_800F9260_inline(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmario.c` -90,2 +91,2 @@ static inline s32 fn_800F9260_inline(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmario.c` -111 +112 @@ void fn_800F9260(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmario.c` -116 +117 @@ void fn_800F9260(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmario.c` -187 +188 @@ void ftKb_SpecialNLg_800F951C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmario.c` -209 +210 @@ void ftKb_SpecialNLg_800F9598(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -32 +33 @@ void fn_8010B1F4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -34 +35 @@ void fn_8010B1F4(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -36 +37 @@ void fn_8010B1F4(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -40 +41 @@ void fn_8010B1F4(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -42 +43 @@ void fn_8010B1F4(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -68 +69 @@ static inline void setupStartAccessory(HSD_GObj* gobj, Vec3* scale) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -93 +94 @@ void ftKb_SpecialNMs_8010B2FC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -109 +110 @@ void ftKb_SpecialNMs_8010B2FC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -131 +132 @@ void ftKb_SpecialNMs_8010B4A0(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -151 +152 @@ void ftKb_SpecialNMs_8010B4A0(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -175 +176 @@ void ftKb_MsSpecialNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -190 +191 @@ void ftKb_MsSpecialAirNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -209 +210 @@ void ftKb_MsSpecialNStart_Phys(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -225 +226 @@ void ftKb_MsSpecialAirNStart_Phys(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -252 +253 @@ static inline FtMotionId getAirSpecialMotionId(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -271 +272 @@ static inline FtMotionId getGroundSpecialMotionId(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -292 +293 @@ void ftKb_MsSpecialNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -309 +310 @@ void ftKb_MsSpecialAirNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -428 +429 @@ void ftKb_MsSpecialNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -463 +464 @@ void ftKb_MsSpecialAirNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -567 +568 @@ void ftKb_SpecialNPe_8010C148(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -571 +572 @@ void ftKb_SpecialNPe_8010C148(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -585 +586 @@ void ftKb_SpecialNPe_8010C1E8(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmars.c` -589 +590 @@ void ftKb_SpecialNPe_8010C1E8(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -44 +45 @@ s32 ftKb_SpecialNMt_80106F44(Fighter_GObj* gobj, s32* out_charge, s32* out_max) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -47 +48 @@ s32 ftKb_SpecialNMt_80106F44(Fighter_GObj* gobj, s32* out_charge, s32* out_max) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -112,2 +113,2 @@ void ftKb_SpecialNMt_80107040(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -122 +123 @@ void ftKb_SpecialNMt_80107040(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -136,3 +137,3 @@ void ftKb_SpecialNMt_8010709C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -143 +144 @@ void ftKb_SpecialNMt_8010709C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -146 +147 @@ void ftKb_SpecialNMt_8010709C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -167,3 +168,3 @@ void ftKb_SpecialNMt_80107130(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -174 +175 @@ void ftKb_SpecialNMt_80107130(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -177 +178 @@ void ftKb_SpecialNMt_80107130(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -180 +181 @@ void ftKb_SpecialNMt_80107130(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -195 +196 @@ static inline void ftKb_SpecialNMt_SetRecoil(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -202 +203 @@ static inline void ftKb_SpecialNMt_SetRecoil(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -216 +217 @@ void ftKb_SpecialNMt_801071FC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -224 +225 @@ void ftKb_SpecialNMt_801071FC(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -230 +231 @@ void ftKb_SpecialNMt_801071FC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -235 +236 @@ void ftKb_SpecialNMt_801071FC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -241 +242 @@ void ftKb_SpecialNMt_801071FC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -259 +260 @@ void ftKb_SpecialNMt_80107410(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -326 +327 @@ void ftKb_SpecialNMt_80107568(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -344 +345 @@ void ftKb_SpecialNMt_80107638(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -360 +361 @@ void ftKb_MtSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -364 +365 @@ void ftKb_MtSpecialNStart_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -369 +370 @@ void ftKb_MtSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -373 +374 @@ void ftKb_MtSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -378 +379 @@ void ftKb_MtSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -396 +397 @@ static inline void ftKb_SpecialNMt_CreateHeldShadow(Fighter_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -402 +403 @@ static inline void ftKb_SpecialNMt_CreateHeldShadow(Fighter_GObj* gobj, | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -407 +408 @@ static inline void ftKb_SpecialNMt_CreateHeldShadow(Fighter_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -411 +412 @@ static inline void ftKb_SpecialNMt_CreateHeldShadow(Fighter_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -439,2 +440,2 @@ void ftKb_MtSpecialNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -446 +447 @@ void ftKb_MtSpecialNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -449 +450 @@ void ftKb_MtSpecialNLoop_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -464 +465 @@ void ftKb_MtSpecialNLoopFull_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -472,3 +473,3 @@ void ftKb_MtSpecialNCancel_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -479 +480 @@ void ftKb_MtSpecialNCancel_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -508 +509 @@ void ftKb_MtSpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -512 +513 @@ void ftKb_MtSpecialAirNStart_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -517 +518 @@ void ftKb_MtSpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -521 +522 @@ void ftKb_MtSpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -527 +528 @@ void ftKb_MtSpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -563,2 +564,2 @@ void ftKb_MtSpecialAirNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -570 +571 @@ void ftKb_MtSpecialAirNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -573 +574 @@ void ftKb_MtSpecialAirNLoop_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -588 +589 @@ void ftKb_MtSpecialAirNLoopFull_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -601 +602 @@ void ftKb_MtSpecialAirNCancel_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -603,2 +604,2 @@ void ftKb_MtSpecialAirNCancel_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -609 +610 @@ void ftKb_MtSpecialAirNCancel_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -642,3 +643,3 @@ void ftKb_MtSpecialNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -649 +650 @@ void ftKb_MtSpecialNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -672,3 +673,3 @@ void ftKb_MtSpecialNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -679 +680 @@ void ftKb_MtSpecialNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -695,3 +696,3 @@ void ftKb_MtSpecialNLoopFull_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -702 +703 @@ void ftKb_MtSpecialNLoopFull_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -725,3 +726,3 @@ void ftKb_MtSpecialNLoopFull_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -732 +733 @@ void ftKb_MtSpecialNLoopFull_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -773,3 +774,3 @@ void ftKb_MtSpecialAirNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -780 +781 @@ void ftKb_MtSpecialAirNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -809,3 +810,3 @@ void ftKb_MtSpecialAirNLoopFull_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.c` -816 +817 @@ void ftKb_MtSpecialAirNLoopFull_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -233,2 +234,2 @@ void ftKb_SpecialN_800F5BA4(Fighter* fp) | donor-variable-bank, donor-compatibility | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -246,2 +247,2 @@ void ftKb_SpecialN_800F5C34(Fighter* fp) | donor-variable-bank, donor-compatibility | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -275,2 +276,2 @@ void ftKb_SpecialN_800F5D04(Fighter_GObj* gobj, bool arg1) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -278 +279 @@ void ftKb_SpecialN_800F5D04(Fighter_GObj* gobj, bool arg1) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -290 +291 @@ void ftKb_SpecialN_800F5D04(Fighter_GObj* gobj, bool arg1) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -343 +344 @@ void ftKb_SpecialN_800F5F68(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -346 +347 @@ void ftKb_SpecialN_800F5F68(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -348,3 +349,3 @@ void ftKb_SpecialN_800F5F68(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -370,5 +371,5 @@ void ftKb_SpecialN_800F6070(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -394 +395 @@ void fn_800F6178(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -405 +406 @@ static void fn_800F6210(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -417 +418 @@ static void fn_800F6280(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -428 +429 @@ static void fn_800F6318(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -466 +467 @@ void fn_800F64C8(Fighter_GObj* gobj, float anim_start) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -729 +730 @@ void ftKb_SpecialN_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -748 +749 @@ void ftKb_SpecialAirN_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -1012,2 +1013,2 @@ static inline void ftKb_SpecialNDrink_Anim_inline(Fighter_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -1067,2 +1068,2 @@ void ftKb_SpecialAirNDrink_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -1150,2 +1151,2 @@ void ftKb_SpecialNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -1165,2 +1166,2 @@ void ftKb_SpecialAirNLoop_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -1279 +1280 @@ void ftKb_EatWait_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -1312,2 +1313,2 @@ void ftKb_EatWait_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -1423 +1424 @@ void ftKb_SpecialAirNCaptureWait_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialn.c` -1774,2 +1775,2 @@ void ftKb_SpecialN_800F9090(HSD_GObj* gobj) | donor-variable-bank, donor-compatibility | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -28,2 +29,2 @@ static void ftKb_NsSpecialNStart_Anim_inline(HSD_GObj* gobj, Vec3* flash_pos) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -35 +36 @@ static void ftKb_NsSpecialNStart_Anim_inline(HSD_GObj* gobj, Vec3* flash_pos) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -62 +63 @@ void ftKb_SpecialNNs_800FED38(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -79 +80 @@ static inline void ftKb_SetNsFlashAttr(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -103 +104 @@ void ftKb_SpecialNNs_800FEDD0(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -129 +130 @@ void ftKb_NsSpecialNHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -136 +137 @@ void ftKb_NsSpecialNHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -149,2 +150,2 @@ void ftKb_NsSpecialNHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -153 +154 @@ void ftKb_NsSpecialNHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -193 +194 @@ void ftKb_NsSpecialAirNHold_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -200 +201 @@ void ftKb_NsSpecialAirNHold_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -213,2 +214,2 @@ void ftKb_NsSpecialAirNHold_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -217 +218 @@ void ftKb_NsSpecialAirNHold_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -274,2 +275,2 @@ void ftKb_NsSpecialNHold_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialness.c` -313,2 +314,2 @@ void ftKb_NsSpecialAirNHold_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -36,2 +37,2 @@ static void fn_8010C288(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -39 +40 @@ static void fn_8010C288(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -56 +57 @@ void fn_8010C344(HSD_GObj* arg0) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -68 +69 @@ void ftKb_SpecialNPe_8010C3C0(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -74,2 +75,2 @@ void ftKb_SpecialNPe_8010C3F4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -83,2 +84,2 @@ void fn_8010C44C(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -91,2 +92,2 @@ void ftKb_SpecialNPe_8010C47C(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -191,2 +192,2 @@ void ftKb_PeSpecialAirLw_Phys(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -239 +240 @@ void ftKb_SpecialNPe_8010C8D8(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -263 +264 @@ void ftKb_SpecialNPe_8010C9CC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -271 +272 @@ void ftKb_SpecialNPe_8010C9CC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -360 +361 @@ void ftKb_SpecialNGw_8010CCD4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -368 +369 @@ void ftKb_SpecialNGw_8010CD44(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpeach.c` -390,2 +391,2 @@ void fn_8010CD88(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpikachu.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpikachu.c` -28 +29 @@ static void doEnter(Fighter_GObj* gobj, ftKirby_MotionState pk_msid, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpikachu.c` -68 +69 @@ void ftKb_PkSpecialN_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpikachu.c` -114 +115 @@ void ftKb_PkSpecialAirN_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpikachu.c` -147 +148 @@ void ftKb_PkSpecialAirN_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpurin.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpurin.c` -47,3 +48,3 @@ static inline void ftKb_PrScaleAnimStep(Fighter_GObj* gobj, Vec3* scale) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpurin.c` -53 +54 @@ static inline void ftKb_PrScaleAnimStep(Fighter_GObj* gobj, Vec3* scale) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpurin.c` -61 +62 @@ static void ftKb_PrRestoreScale(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpurin.c` -218 +219 @@ void ftKb_SpecialNPr_8010131C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpurin.c` -554 +555 @@ static inline void ftKb_AirScaleAnimStep(Fighter_GObj* gobj, Vec3* scale, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpurin.c` -589 +590 @@ void ftKb_PrSpecialAirN_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpurin.c` -597 +598 @@ void ftKb_PrSpecialAirN_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialpurin.c` -600 +601 @@ void ftKb_PrSpecialAirN_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -45 +46 @@ static inline void fn_800F53AC_SpawnEffect(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -53 +54 @@ static inline void fn_800F53AC_CleanupItem(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -56 +57 @@ static inline void fn_800F53AC_CleanupItem(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -67 +68 @@ void fn_800F53AC(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -69 +70 @@ void fn_800F53AC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -71 +72 @@ void fn_800F53AC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -73 +74 @@ void fn_800F53AC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -92,3 +93,3 @@ void ftKb_SpecialAirLw_800F5524(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -114 +115 @@ void ftKb_SpecialAirS_Enter(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -116 +117 @@ void ftKb_SpecialAirS_Enter(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -156,3 +157,3 @@ void ftKb_SpecialS_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -169,3 +170,3 @@ void ftKb_SpecialAirS_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -173 +174 @@ void ftKb_SpecialAirS_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecials.c` -209 +210 @@ HSD_Joint* ftKb_SpecialN_800F5898(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -45 +46 @@ int ftKb_SpecialNSs_800FCC14(Fighter_GObj* gobj, int* out1, int* out2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -49 +50 @@ int ftKb_SpecialNSs_800FCC14(Fighter_GObj* gobj, int* out1, int* out2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -108,3 +109,3 @@ static inline void ftKb_SpecialNSs_it_802B5974(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -119 +120 @@ static inline void ftKb_SpecialNSs_DestroyChargeShot(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -136,2 +137,2 @@ void ftKb_SpecialNSs_800FCD04(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -148 +149 @@ void ftKb_SpecialNSs_800FCD60(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -157 +158 @@ static inline void ftKb_SpecialNSs_800FCDE0_inline(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -172,2 +173,2 @@ static inline void ftKb_SpecialNSs_UnsetChargeShot(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -183 +184 @@ void ftKb_SpecialNSs_800FCDE0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -189 +190 @@ void ftKb_SpecialNSs_800FCDE0(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -192,2 +193,2 @@ void ftKb_SpecialNSs_800FCDE0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -199 +200 @@ void ftKb_SpecialNSs_800FCDE0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -244 +245 @@ void ftKb_SsSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -252 +253 @@ void ftKb_SsSpecialNStart_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -254 +255 @@ void ftKb_SsSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -260 +261 @@ void ftKb_SsSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -265 +266 @@ void ftKb_SsSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -291,2 +292,2 @@ void ftKb_SsSpecialNHold_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -302,2 +303,2 @@ void ftKb_SsSpecialNHold_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -305 +306 @@ void ftKb_SsSpecialNHold_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -337 +338 @@ void ftKb_SsSpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -345 +346 @@ void ftKb_SsSpecialAirNStart_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -347 +348 @@ void ftKb_SsSpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialsamus.c` -353 +354 @@ void ftKb_SsSpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -39 +40 @@ bool ftKb_SpecialNSk_80105FF0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -51 +52 @@ s32 ftKb_SpecialNSk_80106020(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -61,2 +62,2 @@ void ftKb_SpecialNSk_8010603C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -64 +65 @@ void ftKb_SpecialNSk_8010603C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -84 +85 @@ void ftKb_SpecialNSk_8010603C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -88 +89 @@ void ftKb_SpecialNSk_8010603C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -104,2 +105,2 @@ void ftKb_SpecialNSk_8010612C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -127,2 +128,2 @@ void ftKb_SpecialNSk_801061E4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -141 +142 @@ void ftKb_SkSpecialNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -161 +162 @@ void ftKb_SkSpecialNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -163,2 +164,2 @@ void ftKb_SkSpecialNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -174 +175 @@ void ftKb_SkSpecialNCancel_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -192 +193 @@ void ftKb_SkSpecialNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -209 +210 @@ void ftKb_SkSpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -230 +231 @@ void ftKb_SkSpecialAirNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -232,2 +233,2 @@ void ftKb_SkSpecialAirNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -247 +248 @@ void ftKb_SkSpecialAirNCancel_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -271 +272 @@ void ftKb_SkSpecialAirNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -409 +410 @@ void ftKb_SkSpecialNEnd_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -454 +455 @@ void ftKb_SkSpecialAirNEnd_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -473 +474 @@ void fn_80106DB0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialseak.c` -499 +500 @@ void fn_80106DB0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -130 +131 @@ void ftKb_SpecialNYs_801093B4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -133,3 +134,3 @@ void ftKb_SpecialNYs_801093B4(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -146 +147 @@ void ftKb_SpecialNYs_8010941C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -149 +150 @@ void ftKb_SpecialNYs_8010941C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -167 +168 @@ void ftKb_SpecialNYs_801094FC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -170 +171 @@ void ftKb_SpecialNYs_801094FC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -380 +381 @@ void ftKb_YsSpecialN1_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -390 +391 @@ void ftKb_YsSpecialAirNCapture2_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -413 +414 @@ void ftKb_YsSpecialAirNCapture1_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -415 +416 @@ void ftKb_YsSpecialAirNCapture1_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -433 +434 @@ void ftKb_YsSpecialNCapture1_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -441 +442 @@ void ftKb_YsSpecialNCapture1_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -443 +444 @@ void ftKb_YsSpecialNCapture1_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -468 +469 @@ void ftKb_YsSpecialAirCapture2_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -470 +471 @@ void ftKb_YsSpecialAirCapture2_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -488 +489 @@ void ftKb_YsSpecialAirCapture1_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -496 +497 @@ void ftKb_YsSpecialAirCapture1_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -498 +499 @@ void ftKb_YsSpecialAirCapture1_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -512 +513 @@ void ftKb_YsSpecialNCapture2_0_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -565 +566 @@ void ftKb_YsSpecialNCapture2_1_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -589 +590 @@ void ftKb_YsSpecialAirN2_1_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialyoshi.c` -642 +643 @@ void ftKb_YsSpecialAirN2_0_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialzelda.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKirby/ftkirbyspecialzelda.c` -60 +61 @@ void fn_80105AB0(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -65 +66 @@ void ftKp_SpecialLw_80134ACC(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -70 +71 @@ void ftKp_SpecialLw_80134ACC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -77 +78 @@ void ftKp_SpecialLw_80134ACC(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -79 +80 @@ void ftKp_SpecialLw_80134ACC(Fighter_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -85 +86 @@ void ftKp_SpecialLw_80134ACC(Fighter_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -90 +91 @@ void ftKp_SpecialLw_80134ACC(Fighter_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -105,3 +106,3 @@ void ftKp_SpecialLw_80134D78(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -109,3 +110,3 @@ void ftKp_SpecialLw_80134D78(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -262,3 +263,3 @@ void ftKp_SpecialN_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -266,3 +267,3 @@ void ftKp_SpecialN_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -304,3 +305,3 @@ void ftKp_SpecialAirN_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftKoopa/ftkoopaspecialn.c` -308,3 +309,3 @@ void ftKp_SpecialAirN_IASA(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialhi.c` -31,2 +32,2 @@ static void onAccessory4(HSD_GObj* gobj) | bone-animation-data, donor-compatibility | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialhi.c` -34 +35 @@ static void onAccessory4(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -51 +52 @@ ftLk_SpecialNIndex ftLk_SpecialN_GetIndex(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -71,3 +72,3 @@ void ftLk_SpecialN_UnsetArrow(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -86,3 +87,3 @@ void ftLk_SpecialN_UnsetFv14(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -119,3 +120,3 @@ void ftLk_SpecialN_ProcessFv10(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -130,3 +131,3 @@ void ftLk_SpecialN_ProcessFv14(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -144 +145 @@ static inline bool isDrawback(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -152 +153 @@ static inline bool isDrawback(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -172 +173 @@ static inline bool isDrawn(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -182 +183 @@ static inline bool isDrawn(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -217,2 +218,2 @@ static inline void animate(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -239,2 +240,2 @@ static inline void animate_nopad(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -507 +508 @@ static inline void doEndColl(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecialn.c` -517 +518 @@ static inline void doEndColl(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -54 +55 @@ void on21EC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -56 +57 @@ void on21EC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -108,2 +109,2 @@ bool ftLk_SpecialS_RemoveBoomerang0(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -116,4 +117,4 @@ void ftLk_SpecialS_RemoveBoomerang1(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -182 +183 @@ void onAccessory4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -184 +185 @@ void onAccessory4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -190,2 +191,2 @@ void onAccessory4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -195,2 +196,2 @@ void onAccessory4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -208 +209 @@ void ftLk_SpecialS_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -226 +227 @@ void ftLk_SpecialAirS_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -262,2 +263,2 @@ static void doS2Anim(HSD_GObj* gobj, HSD_GObjEvent cb) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -325,2 +326,2 @@ void ftLk_SpecialS2_IASA(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -344,2 +345,2 @@ void ftLk_SpecialAirS2_IASA(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -398,2 +399,2 @@ void ftLk_SpecialS2_Coll(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLink/ftlinkspecials.c` -428,2 +429,2 @@ void ftLk_SpecialAirS2_Coll(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLuigi/ftluigispeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftLuigi/ftluigispeciallw.c` -103 +104 @@ void ftLg_SpecialAirLw_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLuigi/ftluigispeciallw.c` -136 +137 @@ void ftLg_SpecialAirLw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLuigi/ftluigispeciallw.c` -215 +216 @@ void ftLg_SpecialAirLw_Phys(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLuigi/ftluigispeciallw.c` -295 +296 @@ static inline void ftLuigi_SpecialAirLw_AirToGround(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftLuigi/ftluigispecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftLuigi/ftluigispecials.c` -450 +451 @@ static inline void ftLuigi_SpecialS_Setup(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospeciallw.c` -102 +103 @@ void ftMr_SpecialAirLw_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospeciallw.c` -139 +140 @@ void ftMr_SpecialAirLw_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospeciallw.c` -217 +218 @@ void ftMr_SpecialAirLw_Phys(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospeciallw.c` -291 +292 @@ static void doAirCollIfUnk(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecialn.c` -31,2 +32,2 @@ static int pickMegavitamin(Fighter* fp, const int* arr, int outpos) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecialn.c` -46 +47 @@ int ftMr_SpecialN_VitaminRandom(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecialn.c` -119 +120 @@ void ftMr_SpecialN_ItemFireSpawn(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecials.c` -27 +28 @@ static void setCallbacks(Fighter* fp) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecials.c` -57 +58 @@ void ftMr_SpecialS_CreateCape(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecials.c` -60 +61 @@ void ftMr_SpecialS_CreateCape(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecials.c` -70 +71 @@ void ftMr_SpecialS_Reset(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecials.c` -79,2 +80,2 @@ void ftMr_SpecialS_RemoveCape(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecials.c` -88,2 +89,2 @@ void ftMr_SpecialS_EnterHitlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecials.c` -96,2 +97,2 @@ void ftMr_SpecialS_ExitHitlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecials.c` -229,2 +230,2 @@ void ftMr_SpecialAirS_Phys(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMario/ftmariospecials.c` -297 +298 @@ void ftMr_SpecialAirS_AirToGround(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMars/ftmarsspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftMars/ftmarsspecialn.c` -63 +64 @@ static inline void doStartAnim(HSD_GObj* gobj, HSD_GObjEvent cb) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftMars/ftmarsspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftMars/ftmarsspecials.c` -56,2 +57,2 @@ void ftMs_SpecialAirS_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMars/ftmarsspecials.c` -166 +167 @@ void ftMs_SpecialS_80137748(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMars/ftmarsspecials.c` -263 +264 @@ void ftMs_SpecialS_801379D0(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMars/ftmarsspecials.c` -404 +405 @@ void ftMs_SpecialS_80137D60(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMars/ftmarsspecials.c` -539 +540 @@ void ftMs_SpecialS_8013809C(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospeciallw.c` -59 +60 @@ void ftMt_SpecialLw_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospeciallw.c` -79 +80 @@ void ftMt_SpecialAirLw_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospeciallw.c` -152 +153 @@ static inline void ftMewtwo_SpecialLw_SetCall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospeciallw.c` -220 +221 @@ void ftMt_SpecialLw_CreateDisable(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospeciallw.c` -225 +226 @@ void ftMt_SpecialLw_CreateDisable(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -50 +51 @@ s32 ftMt_SpecialN_GetChargeLevel(HSD_GObj* gobj, s32* chargeLevel, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -54 +55 @@ s32 ftMt_SpecialN_GetChargeLevel(HSD_GObj* gobj, s32* chargeLevel, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -124 +125 @@ static inline void ftMewtwo_SpecialN_ClearGObj(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -126 +127 @@ static inline void ftMewtwo_SpecialN_ClearGObj(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -138,2 +139,2 @@ void ftMt_SpecialN_SetNULL(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -151,3 +152,3 @@ static inline void ftMewtwo_SpecialN_RemoveHeldShadowBall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -157 +158 @@ static inline void ftMewtwo_SpecialN_RemoveHeldShadowBall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -159 +160 @@ static inline void ftMewtwo_SpecialN_RemoveHeldShadowBall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -163 +164 @@ static inline void ftMewtwo_SpecialN_RemoveHeldShadowBall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -192,3 +193,3 @@ void ftMt_SpecialN_OnDeath(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -198 +199 @@ void ftMt_SpecialN_OnDeath(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -200 +201 @@ void ftMt_SpecialN_OnDeath(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -204 +205 @@ void ftMt_SpecialN_OnDeath(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -207 +208 @@ void ftMt_SpecialN_OnDeath(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -220 +221 @@ static void ftMewtwo_SpecialN_GetPos(Fighter* fp, Vec3* sp38) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -233 +234 @@ static void ftMewtwo_SpecialN_SetRecoil(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -240 +241 @@ static void ftMewtwo_SpecialN_SetRecoil(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -269 +270 @@ void ftMt_SpecialN_ReleaseShadowBall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -279,2 +280,2 @@ void ftMt_SpecialN_ReleaseShadowBall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -283 +284 @@ void ftMt_SpecialN_ReleaseShadowBall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -291,2 +292,2 @@ void ftMt_SpecialN_ReleaseShadowBall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -302 +303 @@ void ftMt_SpecialN_ReleaseShadowBall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -304 +305 @@ void ftMt_SpecialN_ReleaseShadowBall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -309 +310 @@ void ftMt_SpecialN_ReleaseShadowBall(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -331,2 +332,2 @@ void ftMt_SpecialN_PlayChargeSFX(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -405 +406 @@ static inline void ftMewtwo_SpecialN_ChangeAction(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -443 +444 @@ static inline void ftMewtwo_SpecialAirN_ChangeAction(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -476 +477 @@ void ftMt_SpecialNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -480 +481 @@ void ftMt_SpecialNStart_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -485 +486 @@ void ftMt_SpecialNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -489 +490 @@ void ftMt_SpecialNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -494 +495 @@ void ftMt_SpecialNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -513 +514 @@ static inline void ftMewtwo_SpecialN_CreateHeldShadow(HSD_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -519 +520 @@ static inline void ftMewtwo_SpecialN_CreateHeldShadow(HSD_GObj* gobj, | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -524 +525 @@ static inline void ftMewtwo_SpecialN_CreateHeldShadow(HSD_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -528 +529 @@ static inline void ftMewtwo_SpecialN_CreateHeldShadow(HSD_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -560,2 +561,2 @@ void ftMt_SpecialNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -568 +569 @@ void ftMt_SpecialNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -572 +573 @@ void ftMt_SpecialNLoop_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -589 +590 @@ void ftMt_SpecialNLoopFull_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -598,3 +599,3 @@ static inline void ftMewtwo_SpecialN_RemoveShadowBall2(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -643 +644 @@ void ftMt_SpecialAirNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -647 +648 @@ void ftMt_SpecialAirNStart_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -652 +653 @@ void ftMt_SpecialAirNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -656 +657 @@ void ftMt_SpecialAirNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -662 +663 @@ void ftMt_SpecialAirNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -703,2 +704,2 @@ void ftMt_SpecialAirNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -711 +712 @@ void ftMt_SpecialAirNLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -716 +717 @@ void ftMt_SpecialAirNLoop_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -733 +734 @@ void ftMt_SpecialAirNLoopFull_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -1143 +1144 @@ static inline void ftMewtwo_SpecialN_LaunchShadowBall(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecialn.c` -1147,2 +1148,2 @@ static inline void ftMewtwo_SpecialN_LaunchShadowBall(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecials.c` -115 +116 @@ void ftMt_SpecialAirS_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecials.c` -117 +118 @@ void ftMt_SpecialAirS_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftMewtwo/ftmewtwospecials.c` -241 +242 @@ void ftMt_SpecialAirS_AirToGround(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNana/ftnanaspecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftNana/ftnanaspecialhi.c` -82 +83 @@ void fn_80123218(Fighter_GObj* nana_gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -95 +96 @@ void ftNs_SpecialHiStopGFX(HSD_GObj* gobj) // Removes GFX | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -134 +135 @@ bool ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -142 +143 @@ bool ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -145 +146 @@ bool ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -147 +148 @@ bool ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -156 +157 @@ bool ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -185,2 +186,2 @@ void ftNs_SpecialHi_ItemPKThunderRemove(HSD_GObj* gobj) // OnTakeDamage? | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -201 +202 @@ void ftNs_SpecialHi_ItemPKThunderRemove(HSD_GObj* gobj) // OnTakeDamage? | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -221,3 +222,3 @@ void ftNs_SpecialHi_TakeDamage(HSD_GObj* gobj) // OnTakeDamage again? | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -238 +239 @@ void ftNs_SpecialHi_TakeDamage(HSD_GObj* gobj) // OnTakeDamage again? | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -256 +257 @@ void ftNs_SpecialHi_ItemPKThunderCheckOwn(HSD_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -258 +259 @@ void ftNs_SpecialHi_ItemPKThunderCheckOwn(HSD_GObj* gobj, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -564 +565 @@ block_stuff: { | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -649 +650 @@ void ftNs_SpecialHiStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -659 +660 @@ void ftNs_SpecialHiStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -674 +675 @@ void ftNs_SpecialHiStart_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -676 +677 @@ void ftNs_SpecialHiStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -698 +699 @@ void ftNs_SpecialHiHold_Anim(HSD_GObj* gobj) // Ness's grounded PK Thunder | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -704 +705 @@ void ftNs_SpecialHiHold_Anim(HSD_GObj* gobj) // Ness's grounded PK Thunder | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -723 +724 @@ void ftNs_SpecialHiHold_Anim(HSD_GObj* gobj) // Ness's grounded PK Thunder | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -726 +727 @@ void ftNs_SpecialHiHold_Anim(HSD_GObj* gobj) // Ness's grounded PK Thunder | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -731 +732 @@ void ftNs_SpecialHiHold_Anim(HSD_GObj* gobj) // Ness's grounded PK Thunder | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -747 +748 @@ void ftNs_SpecialHiHold_Anim(HSD_GObj* gobj) // Ness's grounded PK Thunder | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -775,2 +776,2 @@ void ftNs_SpecialHi_Anim(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -798 +799 @@ void ftNs_SpecialHi_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -820 +821 @@ void ftNs_SpecialAirHiStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -829 +830 @@ void ftNs_SpecialAirHiStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -844 +845 @@ void ftNs_SpecialAirHiStart_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -846 +847 @@ void ftNs_SpecialAirHiStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -864 +865 @@ void ftNs_SpecialAirHiHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -872 +873 @@ void ftNs_SpecialAirHiHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -892 +893 @@ void ftNs_SpecialAirHiHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -896 +897 @@ void ftNs_SpecialAirHiHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -925 +926 @@ void ftNs_SpecialAirHiHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -942 +943 @@ void ftNs_SpecialAirHiHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -985 +986 @@ void ftNs_SpecialAirHi_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -1431 +1432 @@ void ftNs_SpecialHi_Coll(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -1587 +1588 @@ void ftNs_SpecialAirHi_Coll(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialhi.c` -1753 +1754 @@ void ftNs_SpecialAirHiRebound_Coll(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspeciallw.c` -101 +102 @@ void ftNs_SpecialLwStart_Anim( | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspeciallw.c` -135 +136 @@ void ftNs_SpecialAirLwStart_Anim( | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspeciallw.c` -770 +771 @@ void ftNs_SpecialAirLwHit_Anim( | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -37 +38 @@ bool ftNs_SpecialN_CheckSpecialNHold(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -64,2 +65,2 @@ void ftNs_SpecialN_SetNULL(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -87,3 +88,3 @@ void ftNs_SpecialN_ItemPKFlushSetNULL(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -102 +103 @@ void ftNs_PKFlash_Init(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -105 +106 @@ void ftNs_PKFlash_Init(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -112 +113 @@ void ftNs_PKFlash_Init(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -147 +148 @@ void ftNs_SpecialNStart_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -181 +182 @@ void ftNs_SpecialAirNStart_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -219 +220 @@ void ftNs_SpecialNRelease_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -225 +226 @@ void ftNs_SpecialNRelease_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -243,2 +244,2 @@ void ftNs_SpecialNRelease_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -248 +249 @@ void ftNs_SpecialNRelease_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -268 +269 @@ static inline void SetPKFlashAttr(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -314 +315 @@ void ftNs_SpecialAirNRelease_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -320 +321 @@ void ftNs_SpecialAirNRelease_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -334,2 +335,2 @@ void ftNs_SpecialAirNRelease_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -339 +340 @@ void ftNs_SpecialAirNRelease_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -416,2 +417,2 @@ void ftNs_SpecialNRelease_IASA(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecialn.c` -470,2 +471,2 @@ void ftNs_SpecialAirNRelease_IASA(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftNess/ftnessspecials.c` -46 +47 @@ void ftNs_SpecialS_ItemPKFireSpawn( | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -38,0 +40,21 @@ void ftPe_SpecialHi_8011D424(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -41 +63 @@ void ftPe_SpecialHi_8011D424(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -43 +65 @@ void ftPe_SpecialHi_8011D424(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -47 +69 @@ void ftPe_SpecialHi_8011D424(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -53,4 +75,4 @@ void ftPe_SpecialHi_8011D424(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -70 +92 @@ bool ftPe_8011D518(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -74 +96 @@ bool ftPe_8011D518(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -77 +99 @@ bool ftPe_8011D518(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -91,2 +113,2 @@ void ftPe_8011D598(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -100,2 +122,2 @@ static void ensureUnkItem(HSD_GObj* gobj, HSD_GObjEvent cb) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialhi.c` -205,0 +228,20 @@ void ftPe_SpecialHiStart_Anim(HSD_GObj* gobj) | state-table-redirect, donor-compatibility | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspeciallw.c` -64,2 +65,2 @@ void ftPe_SpecialLw_UnsetVeg(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspeciallw.c` -72 +73 @@ void ftPe_SpecialLw_8011CFA0(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspeciallw.c` -78 +79 @@ void ftPe_SpecialLw_8011CFA0(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspeciallw.c` -101 +102 @@ static void setupVeg(ItemKind kind, HSD_GObj* gobj, Fighter* fp, Vec3* pos) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspeciallw.c` -120 +121 @@ static void spawnVeg(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -70,2 +71,2 @@ void onAccessory4(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -74,2 +75,2 @@ void onAccessory4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -88 +89 @@ static void doHitAccessory4(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -106 +107 @@ void ftPe_SpecialN_DoDeath2(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -114,2 +115,2 @@ void ftPe_SpecialN_OnDeath2(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -123,2 +124,2 @@ static void onEnterHitlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -131,2 +132,2 @@ static void onExitHitlag(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -225,2 +226,2 @@ void ftPe_SpecialAirN_Phys(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -258 +259 @@ static void setupColl(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -291 +292 @@ static void doAirColl(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -361 +362 @@ void doAirHitColl(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -369 +370 @@ static void setupHitColl(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecialn.c` -390,2 +391,2 @@ static void onUnkHit(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecials.c` -343 +344 @@ static void doPostEnd(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPeach/ftpeachspecials.c` -362 +363 @@ static void doPostEnd_SmallerStack(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPikachu/ftpikachuspecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftPikachu/ftpikachuspecialhi.c` -184 +185 @@ void ftPk_SpecialHiStart1_Anim(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftPikachu/ftpikachuspecialhi.c` -194 +195 @@ void ftPk_SpecialHiStart1_Anim(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftPikachu/ftpikachuspecialhi.c` -223 +224 @@ void ftPk_SpecialAirHiStart1_Anim(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftPikachu/ftpikachuspecialhi.c` -233 +234 @@ void ftPk_SpecialAirHiStart1_Anim(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -59 +60 @@ void ftPp_SpecialS_80120E68(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -94 +95 @@ bool ftPp_SpecialS_80120FE0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -110 +111 @@ bool ftPp_SpecialS_80120FE0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -117 +118 @@ bool ftPp_SpecialS_80120FE0(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -133 +134 @@ void ftPp_SpecialS_801210C8(Fighter_GObj* arg0) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -135,3 +136,3 @@ void ftPp_SpecialS_801210C8(Fighter_GObj* arg0) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -146 +147 @@ void ftPp_SpecialS_8012114C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -154,2 +155,2 @@ void ftPp_SpecialS_80121164(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -175,4 +176,4 @@ void ftPp_SpecialHi_Enter(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -199,4 +200,4 @@ void ftPp_SpecialAirHi_Enter(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -209 +210 @@ static inline bool checkNanaInRange(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -308 +309 @@ void ftPp_SpecialHiStart_0_Phys(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -319 +320 @@ void ftPp_SpecialHiStart_0_Phys(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -337 +338 @@ void ftPp_SpecialAirHiStart_0_Phys(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -348 +349 @@ void ftPp_SpecialAirHiStart_0_Phys(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -413 +414 @@ void ftPp_SpecialHiThrow_0_Anim(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -451 +452 @@ void ftPp_SpecialAirHiThrow_0_Anim(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -488 +489 @@ void ftPp_SpecialHiThrow_0_Phys(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -499 +500 @@ void ftPp_SpecialHiThrow_0_Phys(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -522 +523 @@ void ftPp_SpecialAirHiThrow_0_Phys(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -533 +534 @@ void ftPp_SpecialAirHiThrow_0_Phys(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -788 +789 @@ void ftPp_SpecialHiThrow2_Phys(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -799 +800 @@ void ftPp_SpecialHiThrow2_Phys(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -806 +807 @@ static inline void ftPp_SpecialAirHiThrow2_Phys_inline(Fighter_GObj* gobj, | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialhi.c` -837 +838 @@ void ftPp_SpecialAirHiThrow2_Phys(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospeciallw.c` -25 +26 @@ void ftPp_SpecialHi_80122898(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospeciallw.c` -28 +29 @@ void ftPp_SpecialHi_80122898(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospeciallw.c` -70 +71 @@ void ftPp_SpecialLw_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospeciallw.c` -73 +74 @@ void ftPp_SpecialLw_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospeciallw.c` -87 +88 @@ void ftPp_SpecialAirLw_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospeciallw.c` -90 +91 @@ void ftPp_SpecialAirLw_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospeciallw.c` -183 +184 @@ void fn_80122D2C(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospeciallw.c` -193 +194 @@ void fn_80122D2C(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospeciallw.c` -195 +196 @@ void fn_80122D2C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospeciallw.c` -198 +199 @@ void fn_80122D2C(Fighter_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialn.c` -124,2 +125,2 @@ void ftPp_SpecialAirN_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialn.c` -127,2 +128,2 @@ void ftPp_SpecialAirN_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialn.c` -133,2 +134,2 @@ void ftPp_SpecialAirN_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialn.c` -142,2 +143,2 @@ static inline void inlineA0(Fighter_GObj* gobj, Fighter* other_fp) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialn.c` -161 +162 @@ void ftPp_SpecialN_8011F500(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialn.c` -163,2 +164,2 @@ void ftPp_SpecialN_8011F500(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialn.c` -167 +168 @@ void ftPp_SpecialN_8011F500(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialn.c` -173,2 +174,2 @@ void ftPp_SpecialN_8011F500(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecialn.c` -176 +177 @@ void ftPp_SpecialN_8011F500(Fighter_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecials.c` -135 +136 @@ static inline void inlineA2(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecials.c` -144 +145 @@ static inline void inlineA2(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecials.c` -178 +179 @@ static inline void inlineB0(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecials.c` -188 +189 @@ static inline void inlineB0(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecials.c` -246 +247 @@ void ftPp_SpecialS2_Anim(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPopo/ftpopospecials.c` -290 +291 @@ void ftPp_SpecialAirS2_Anim(Fighter_GObj* gobj) | transform-subfighter | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecialn.c` -70 +71 @@ void ftPr_SpecialS_8013D658(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecialn.c` -227 +228 @@ void ftPr_SpecialS_8013DC64(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecialn.c` -262,3 +263,3 @@ static inline void scaleAnimStep(HSD_GObj* gobj, Vec3* scale) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecialn.c` -268 +269 @@ static inline void scaleAnimStep(HSD_GObj* gobj, Vec3* scale) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecialn.c` -576 +577 @@ ftPr_SpecialAirNChargeRelease_Anim_inline(HSD_GObj* gobj, Vec3* scale, | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecialn.c` -612 +613 @@ void ftPr_SpecialAirNChargeRelease_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecialn.c` -621 +622 @@ void ftPr_SpecialAirNChargeRelease_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecialn.c` -625 +626 @@ void ftPr_SpecialAirNChargeRelease_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecialn.c` -1279 +1280 @@ static inline void ftPr_SpecialAirNChargeRelease_Coll_inline(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftPurin/ftpurinspecials.c` -97 +98 @@ void ftPr_SpecialAirS_Phys(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialhi.c` -40,2 +41,2 @@ void ftSs_SpecialHi_Enter(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialhi.c` -58,2 +59,2 @@ void ftSs_SpecialAirHi_Enter(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialhi.c` -66 +67 @@ static void ftSamus_DestroyAllUnsetx2444(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspeciallw0.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspeciallw0.c` -272 +273 @@ int ftSs_SpecialLw_80129100(HSD_GObj* gobj, int* arg1, int* arg2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspeciallw0.c` -276 +277 @@ int ftSs_SpecialLw_80129100(HSD_GObj* gobj, int* arg1, int* arg2) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspeciallw1.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspeciallw1.c` -35 +36 @@ void ftSs_SpecialLw_8012ADF0(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -39 +40 @@ static void ftSamus_801293BC_inner(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -49,2 +50,2 @@ void ftSs_SpecialN_801291F0(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -63 +64 @@ void ftSs_SpecialN_80129258(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -78 +79 @@ static bool ftSs_SpecialN_801292E4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -83 +84 @@ static bool ftSs_SpecialN_801292E4(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -87 +88 @@ static bool ftSs_SpecialN_801292E4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -91 +92 @@ static bool ftSs_SpecialN_801292E4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -109 +110 @@ static void ftSs_SpecialN_801293BC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -114 +115 @@ static void ftSs_SpecialN_801293BC(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -122,2 +123,2 @@ static void ftSs_SpecialN_801293BC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -128 +129 @@ static void ftSs_SpecialN_801293BC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -179 +180 @@ void ftSs_SpecialNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -210,2 +211,2 @@ void ftSs_SpecialNHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -222,2 +223,2 @@ void ftSs_SpecialNHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -225 +226 @@ void ftSs_SpecialNHold_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -410 +411 @@ int ftSs_SpecialS_8012A068(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecialn.c` -422,2 +423,2 @@ void ftSs_SpecialS_8012A074(Fighter_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftSamus/ftsamusspecials.c` -171 +172 @@ void ftSs_SpecialS_8012A640(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialhi.c` -66 +67 @@ void ftSk_SpecialHi_80112F48(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialhi.c` -76 +77 @@ void ftSk_SpecialHi_80112FA8(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialhi.c` -89 +90 @@ void fn_80113038(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspeciallw.c` -29 +30 @@ static void fn_80114034(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspeciallw.c` -40 +41 @@ static void fn_801140B0(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspeciallw.c` -77 +78 @@ void ftSk_SpecialLw_Enter(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspeciallw.c` -101 +102 @@ void ftSk_SpecialAirLw_Enter(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -35,3 +36,3 @@ void ftSk_SpecialN_80111FBC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -57 +58 @@ void ftSk_SpecialN_80111FBC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -65 +66 @@ void ftSk_SpecialN_80111FBC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -82,2 +83,2 @@ static inline void doEnter(Fighter_GObj* gobj, ftSeak_MotionState msid) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -105 +106 @@ void ftSk_SpecialNStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -125 +126 @@ void ftSk_SpecialNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -127,2 +128,2 @@ void ftSk_SpecialNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -138 +139 @@ void ftSk_SpecialNCancel_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -156 +157 @@ void ftSk_SpecialNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -168 +169 @@ void ftSk_SpecialAirNStart_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -187 +188 @@ void ftSk_SpecialAirNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -189,2 +190,2 @@ void ftSk_SpecialAirNLoop_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -202 +203 @@ void ftSk_SpecialAirNCancel_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -227 +228 @@ void ftSk_SpecialAirNEnd_Anim(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -369 +370 @@ void ftSk_SpecialNEnd_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -415 +416 @@ void ftSk_SpecialAirNEnd_Coll(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -429 +430 @@ void shootNeedles(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecialn.c` -456 +457 @@ void shootNeedles(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -86 +87 @@ void ftSk_SpecialS_80110610(HSD_GObj* gobj, s32 arg1, float arg2) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -99,0 +101,7 @@ void ftSk_SpecialS_80110610(HSD_GObj* gobj, s32 arg1, float arg2) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -136,2 +144,2 @@ void ftSk_SpecialS_80110788(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -148,2 +156,2 @@ void ftSk_SpecialS_80110788(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -153 +161 @@ void ftSk_SpecialS_80110788(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -169 +177 @@ void ftSk_SpecialS_80110788(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -171 +179 @@ void ftSk_SpecialS_80110788(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -181 +189 @@ void ftSk_SpecialS_80110788(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -206,2 +214,2 @@ void ftSk_SpecialS_80110788(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -232 +240 @@ void ftSk_SpecialS_UpdateHitboxes(HSD_GObj* gobj, Vec3* new_pos, s32 hitbox_id) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -331 +339 @@ void ftSk_SpecialS_80110BCC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -347,2 +355,2 @@ void ftSk_SpecialS_80110BCC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -352,2 +360,2 @@ void ftSk_SpecialS_80110BCC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -397 +405 @@ void ftSk_SpecialS_80110E4C(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -408 +416 @@ void ftSk_SpecialS_CheckAndDestroyChain(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -412 +420 @@ void ftSk_SpecialS_CheckAndDestroyChain(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -418 +426 @@ void ftSk_SpecialS_CheckAndDestroyChain(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -427,2 +435,2 @@ void ftSk_SpecialS_80110EE8(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -436,2 +444,2 @@ void ftSk_SpecialS_ChainSomething(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -473 +481 @@ void ftSk_SpecialS_80110F70(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -478,3 +486,3 @@ void ftSk_SpecialS_80110F70(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -482,3 +490,3 @@ void ftSk_SpecialS_80110F70(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -488,3 +496,3 @@ void ftSk_SpecialS_80110F70(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -519,3 +527,3 @@ static inline void ftSk_SpecialS_SpawnChain(HSD_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -523 +531 @@ static inline void ftSk_SpecialS_SpawnChain(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -543 +551 @@ bool ftSk_SpecialS_CheckInitChain(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -554 +562 @@ bool ftSk_SpecialS_CheckInitChain(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -646 +654 @@ void ftSk_SpecialS_80111440(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -666 +674 @@ void ftSk_SpecialS_801114E4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -801 +809 @@ void ftSk_SpecialS_80111830(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -823 +831 @@ void ftSk_SpecialS_80111830(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -847 +855 @@ void ftSk_SpecialS_80111988(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -874 +882 @@ void ftSk_SpecialSEnd_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -885 +893 @@ void ftSk_SpecialSEnd_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -913 +921 @@ void ftSk_SpecialAirSEnd_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -920 +928 @@ void ftSk_SpecialAirSEnd_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -978 +986 @@ void ftSk_SpecialS_80111CB0(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -998 +1006 @@ void ftSk_SpecialS_80111D54(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -1021 +1029 @@ void ftSk_SpecialS_80111DF8(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -1045 +1053 @@ void ftSk_SpecialS_80111EB4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -1062 +1070 @@ bool ftSk_SpecialS_80111F70(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftSeak/ftseakspecials.c` -1077 +1085 @@ int ftSk_SpecialS_80111FA0(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshi.c` -426 +426 @@ void ftYs_Init_8012B8A4(HSD_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftYoshi/ftyoshi.c` -434,0 +435,3 @@ void ftYs_Init_8012B918(HSD_GObj* gobj) | donor-compatibility | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshiguard.c` -0,0 +1 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftYoshi/ftyoshiguard.c` -23,0 +25 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftYoshi/ftyoshiguard.c` -264,0 +267,2 @@ void ftYs_Shield_8012C600(Fighter_GObj* gobj, bool arg1) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftYoshi/ftyoshiguard.c` -366 +370,4 @@ void ftYs_Shield_8012C914(Fighter_GObj* gobj) | excluded-legacy-modifier | Excluded |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialhi.c` -30 +31 @@ static void setDamageCallbacks(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialhi.c` -96,3 +97,3 @@ void fn_8012E110(Fighter_GObj* gobj) | donor-variable-bank, bone-animation-data | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialhi.c` -102 +103 @@ void fn_8012E110(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialhi.c` -114 +115 @@ void fn_8012E110(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialhi.c` -117 +118 @@ void fn_8012E110(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialhi.c` -127,2 +128,2 @@ void ftYs_SpecialS_8012E270(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialhi.c` -130 +131 @@ void ftYs_SpecialS_8012E270(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialhi.c` -143 +144 @@ void ftYs_SpecialHi_Enter(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialhi.c` -161 +162 @@ void ftYs_SpecialAirHi_Enter(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispeciallw.c` -34 +35 @@ void fn_8012E644(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecialn.c` -125 +126 @@ HSD_Joint* ftYs_SpecialN_8012CDD4(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -116 +117 @@ static inline void fn_8012EC7C_inline(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -132 +133 @@ static inline void ftYs_SpecialS_UpdateScale(Fighter_GObj* gobj, Vec3* scale) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -134 +135 @@ static inline void ftYs_SpecialS_UpdateScale(Fighter_GObj* gobj, Vec3* scale) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -136 +137 @@ static inline void ftYs_SpecialS_UpdateScale(Fighter_GObj* gobj, Vec3* scale) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -140 +141 @@ static inline void ftYs_SpecialS_UpdateScale(Fighter_GObj* gobj, Vec3* scale) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -153,3 +154,3 @@ static inline void ftYs_SpecialS_UpdateScale2(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -159 +160 @@ static inline void ftYs_SpecialS_UpdateScale2(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -195 +196 @@ void fn_8012EC7C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -212 +213 @@ void fn_8012EDE8(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -317 +318 @@ void ftYs_SpecialS_8012F35C(Fighter_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -584 +585 @@ void ftYs_SpecialAirSEnd_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftYoshi/ftyoshispecials.c` -720 +721 @@ void ftYs_SpecialAirSLanding_Anim(Fighter_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecialhi.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecialhi.c` -44 +45 @@ void ftZd_SpecialHi_801396E0(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecialhi.c` -64 +65 @@ void ftZd_SpecialHi_8013979C(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspeciallw.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspeciallw.c` -34 +35 @@ void ftZd_SpecialLw_8013ADB4(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspeciallw.c` -50 +51 @@ void ftZd_SpecialLw_8013AE30(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspeciallw.c` -87 +88 @@ static void ftZelda_SpecialLw_StartAction_Helper(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspeciallw.c` -334 +335 @@ s32 ftZd_SpecialLw_8013B540(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspeciallw.c` -348 +349 @@ bool ftZd_SpecialLw_8013B574(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspeciallw.c` -370,2 +371,2 @@ void ftZd_SpecialLw_8013B5C4(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspeciallw.c` -384,3 +385,3 @@ void ftZd_SpecialLw_8013B5EC(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecialn.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecialn.c` -27 +28 @@ void ftZd_SpecialN_8013A830(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecialn.c` -41 +42 @@ void ftZd_SpecialN_8013A8AC(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -0,0 +1 @@ | special-interface | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -49 +50 @@ void ftZd_SpecialS_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -77 +78 @@ void ftZd_SpecialAirS_Enter(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -100 +101 @@ void ftZd_SpecialSStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -102 +103 @@ void ftZd_SpecialSStart_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -110 +111 @@ void ftZd_SpecialSStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -116 +117 @@ void ftZd_SpecialSStart_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -143 +144 @@ void ftZd_SpecialSLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -145 +146 @@ void ftZd_SpecialSLoop_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -153 +154 @@ void ftZd_SpecialSLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -159 +160 @@ void ftZd_SpecialSLoop_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -170 +171 @@ void ftZd_SpecialSLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -178 +179 @@ void ftZd_SpecialSLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -181 +182 @@ void ftZd_SpecialSLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -204 +205 @@ void ftZd_SpecialSEnd_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -228 +229 @@ void ftZd_SpecialAirSStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -230 +231 @@ void ftZd_SpecialAirSStart_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -238 +239 @@ void ftZd_SpecialAirSStart_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -244 +245 @@ void ftZd_SpecialAirSStart_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -270 +271 @@ void ftZd_SpecialAirSLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -272 +273 @@ void ftZd_SpecialAirSLoop_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -280 +281 @@ void ftZd_SpecialAirSLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -286 +287 @@ void ftZd_SpecialAirSLoop_Anim(HSD_GObj* gobj) | bone-animation-data | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -297 +298 @@ void ftZd_SpecialAirSLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -304 +305 @@ void ftZd_SpecialAirSLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -307 +308 @@ void ftZd_SpecialAirSLoop_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/ft/kinds/ftZelda/ftzeldaspecials.c` -331 +332 @@ void ftZd_SpecialAirSEnd_Anim(HSD_GObj* gobj) | donor-variable-bank | Pending |
| `src/melee/gm/forward.h` -65 +65,2 @@ typedef enum GameModeKind { | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1601.c` -0,0 +1 @@ | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1601.c` -2357,0 +2359 @@ bool gm_IsCKindUnlocked(u8 ckind) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1601.c` -3890 +3892,3 @@ f32 gm_80168B34(CharacterKind ckind, int arg1, int arg2) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_17C0.c` -2,0 +3 @@ | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1832.c` -5,0 +6 @@ | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1832.c` -383,0 +385,8 @@ void fn_80184AB8(HSD_GObj* arg0) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1832.c` -1180,0 +1190,4 @@ void gm_Scene_IntroEasy_OnFrame(void) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1879.c` -1,0 +2 @@ | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1879.c` -36,0 +38,6 @@ | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1879.c` -312,0 +320 @@ static inline void gm_80187F48_OnEnter_inline(gm_80187F48_EnterData* arg0) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1879.c` -349 +357,4 @@ static inline void gm_80187F48_OnEnter_inline(gm_80187F48_EnterData* arg0) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1879.c` -391,0 +403 @@ void gm_Scene_IntroNormal_OnEnter(void* arg0) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1879.c` -397,0 +410 @@ void gm_Scene_IntroNormal_OnLeave(void* arg0) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1879.c` -403,0 +417 @@ void gm_Scene_IntroNormal_OnFrame(void) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1879.h` -7,0 +8,2 @@ | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_19EF.c` -356,0 +357 @@ static inline s32 fn_8019F9C4_GetCharIdx(CharacterKind arg0) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_19EF.c` -368,2 +369,8 @@ static inline void fn_8019F9C4_LoadSymbols(u32 arg0) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gm_1A3F.c` -93 +93,4 @@ void preloadState(GameModeState* state) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gmboot.c` -0,0 +1 @@ | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gmboot.c` -81 +82 @@ void bootOnLeave(GameModeState* data) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gmscdata.c` -0,0 +1 @@ | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gmscdata.c` -743,0 +745 @@ static GameMode modes[] = { | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gmvs.c` -0,0 +1 @@ | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/gmvs.c` -1565 +1566 @@ void gm_Scene_Vs_OnFrame(void) | excluded-legacy-build-flow | Excluded |
| `src/melee/gm/types.h` -1208,2 +1208,2 @@ typedef struct TmSettingTable { | excluded-legacy-build-flow | Excluded |
| `src/melee/gr/grheal.c` -0,0 +1 @@ | excluded-legacy-build-flow | Excluded |
| `src/melee/gr/grheal.c` -302 +303,2 @@ void stageGObj1_GObjProc(Ground_GObj* ground) | excluded-legacy-build-flow | Excluded |
| `src/melee/gr/grizumi.c` -13,0 +14 @@ | excluded-legacy-build-flow | Excluded |
| `src/melee/gr/grizumi.c` -755,2 +756,7 @@ void grIzumi_801CCEA0(HSD_GObj* gobj, int renderpass) | excluded-legacy-build-flow | Excluded |
| `src/melee/gr/grizumi.c` -758 +763,0 @@ void grIzumi_801CCEA0(HSD_GObj* gobj, int renderpass) | excluded-legacy-build-flow | Excluded |
| `src/melee/it/item.c` -0,0 +1 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/it/item.c` -1,0 +3 @@ | excluded-legacy-modifier | Excluded |
| `src/melee/it/item.c` -206,0 +209 @@ static void Item_80267130(HSD_GObj* gobj, SpawnItem* spawnItem) | excluded-legacy-modifier | Excluded |
| `src/melee/it/item.c` -1769,0 +1773,8 @@ static bool OnGiveDamageThink(HSD_GObj* gobj, Item* item_data) | excluded-legacy-modifier | Excluded |
| `src/melee/mn/mnmain.c` -772,2 +772,14 @@ static void mn_80229A7C(MainMenuData* data, MenuKind menu_kind, int selection) | excluded-legacy-build-flow | Excluded |
| `src/melee/mn/mnmain.c` -777 +789,6 @@ static void mn_80229A7C(MainMenuData* data, MenuKind menu_kind, int selection) | excluded-legacy-build-flow | Excluded |
| `src/melee/mn/mnmain.c` -1161,0 +1179,25 @@ void mn_8022ADD8(HSD_GObj* gp, bool selection_changed) | excluded-legacy-build-flow | Excluded |
| `src/melee/mn/mnmain.c` -1186,0 +1229 @@ void fn_8022AF10(HSD_GObj* gp) | excluded-legacy-build-flow | Excluded |
| `src/melee/mn/mnmain.c` -1330,0 +1374 @@ void fn_8022AFEC(HSD_GObj* gp) | excluded-legacy-build-flow | Excluded |
| `src/melee/mn/mnmain.c` -1431 +1475 @@ HSD_GObj* mn_8022B3A0(u8 state) | excluded-legacy-build-flow | Excluded |
| `src/melee/mn/mnmain.c` -1435,0 +1480,2 @@ HSD_GObj* mn_8022B3A0(u8 state) | excluded-legacy-build-flow | Excluded |
| `src/melee/mn/mnmain.c` -1506,0 +1553,10 @@ HSD_GObj* mn_8022B3A0(u8 state) | excluded-legacy-build-flow | Excluded |
| `src/melee/mn/mnmain.c` -2160 +2216 @@ void mn_8022CC28(HSD_GObj* gp) | excluded-legacy-build-flow | Excluded |
| `src/melee/mn/mnmain.h` -19,0 +20,2 @@ typedef struct _MainMenuData { | excluded-legacy-build-flow | Excluded |
