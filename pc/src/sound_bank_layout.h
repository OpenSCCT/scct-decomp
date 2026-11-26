/* sound_bank_layout.h -- the loaded sound data: maps (sndldmap.c), banks (sndldbnk.c) and the
   functions that choose between them (sndldbin.c) */
#ifndef SOUND_BANK_LAYOUT_H
#define SOUND_BANK_LAYOUT_H

#include "sound_resource.h"

/* __FILE__ of the original sndldbin.c. */
#define SNDLDBIN_C_FILE \
    "\\build\\splintercellx-pc\\patch\\SplinterCell2\\technology-group\\sound\\dare\\private" \
    "\\engine\\common\\src\\sndldbin.c"

/* How the project's data is loaded. */
typedef enum _SND_tdeDataLoadMode {
    SND_E_DATALOADMODE_INVALID = -1,
    SND_E_DATALOADMODE_BANK = 0,
    SND_E_DATALOADMODE_MAP = 1
} SND_tdeDataLoadMode;

/* A sound event. Only its identifier and its size are recovered. */
typedef struct _SND_tdstBlockEvent {
    unsigned long Id;               /* the identifier the sound editor gave it */
    unsigned char unk_04[0x64];
} SND_tdstBlockEvent;

typedef struct _tdstBlockEventList {
    SND_tdstBlockEvent *hFirstElementOpt;
    long lNumberOfElementsOpt;
} tdstBlockEventList;

typedef struct _tdstBlockResMemList {
    tdstBlockResourceMem *hFirstElementOpt;
    long lNumberOfElementsOpt;
} tdstBlockResMemList;

/* Only the start of a map's header is recovered. */
typedef struct _tdstMapHeader {
    long lMapId;
    tdstBlockEventList stBlockEventList;
} tdstMapHeader;

typedef struct _tdstMapMemInfo {
    unsigned char unk_00[0xc];
    tdstMapHeader *pstMapHeader;
    tdstBlockResMemList stBlockResMemList;
    unsigned char unk_18[0x10];
} tdstMapMemInfo;

/* A loaded map. The structure continues past bLoaded: the two maps lie 0x78 bytes apart. */
typedef struct _tdstMapMem {
    tdstMapMemInfo stNLoc;          /* data common to every language */
    tdstMapMemInfo stLoc;           /* data of the current language */
    int bLoaded;
} tdstMapMem;

/* File-static in sndldmap.c of the sibling build. */
extern tdstMapMem gs_stMapFix;      /* the map that stays loaded */
extern tdstMapMem gs_stCurrentMap;

/* Only the count of resources is recovered. */
typedef struct _tdstBankHeader {
    unsigned char unk_00[8];
    long resource_count;            /* invented name */
} tdstBankHeader;

/* A loaded bank. */
typedef struct tdstBankElement_ {
    int bLoaded;
    unsigned char unk_04[0x2c];
    tdstBankHeader *pBankHeader;
    SND_tdstBlockEvent *pEventList;
    tdstBlockResourceMem *pResMemList;
} tdstBankElement;

/* A node of the bank list, which is an instance of the library's C++ list of pointers. The
   names of the type and its members are invented. */
typedef struct BankListNode {
    struct BankListNode *next;
    struct BankListNode *previous;
    tdstBankElement *item;
} BankListNode;

/* The C++ object that knows the bank in use. Only one member is recovered; the names of the
   type and the member are invented. */
typedef struct SoundBankManager {
    unsigned char unk_00[0xc];
    tdstBankElement *current;
} SoundBankManager;

/* The start of the project's description. The sibling build's structure has the same
   beginning; the rest is not recovered. */
typedef struct _tdstProjectDesc {
    char cMode[5];
    int bLocalised;
} tdstProjectDesc;

extern tdstProjectDesc g_stProjectDesc;
extern SND_tdeDataLoadMode gs_eLoadProjectType;     /* file-static in sndldbin.c of the sibling */
extern int gs_bInitProjectDone;                     /* file-static in sndldbin.c of the sibling */
extern BankListNode *bank_list_first;               /* invented name */
extern SoundBankManager *bank_manager;              /* invented name */

tdstBankElement *__fastcall sound_current_bank(SoundBankManager *manager);

tdstBlockResourceMem *__stdcall SND_fn_pGetBinRes_Bank(unsigned long _ulBinId);
tdstBlockResourceMem *__stdcall SND_fn_pGetBinRes_Map(unsigned long _ulBinId);
SND_tdstBlockEvent *__cdecl SND_fn_pGetBinEvent_Bank(unsigned long _ulBinId);
SND_tdstBlockEvent *__cdecl SND_fn_pGetBinEvent_Map(unsigned long _ulBinId);
SND_tdstBlockEvent *__cdecl SND_fn_hGetSoundEventHandleFromEditorId_Bank(unsigned long ulEdId);
SND_tdstBlockEvent *__cdecl SND_fn_hGetSoundEventHandleFromEditorId_Map(unsigned long ulEdId);
tdstBlockResourceMem *__stdcall SND_fn_pstGetResFromEdIdSnd_Bank(unsigned long ulEdId);
tdstBlockResourceMem *__stdcall SND_fn_pstGetResFromEdIdSnd_Map(unsigned long ulEdId);

tdstBlockResourceMem *__stdcall SND_fn_pGetBinRes(unsigned long ulBinId);
SND_tdstBlockEvent *__stdcall SND_fn_pGetBinEvent(unsigned long ulBinId);
SND_tdstBlockEvent *__stdcall SND_fn_hGetSoundEventHandleFromEditorId(unsigned long ulEdId);
SND_tdstBlockEvent *__stdcall SND_fn_hGetSoundEventHandleFromSectionName(const char *szSectionName);
tdstBlockResourceMem *__stdcall SND_fn_pstGetResFromEdIdSnd(unsigned long ulEdId);
unsigned long __stdcall SND_fn_ulGetEditorIdFromSoundEventName(const char *szName);

#endif
