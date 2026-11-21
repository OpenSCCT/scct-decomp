/* sound_data.h -- the directories the sound library reads its data from (snddata.c) */
#ifndef SOUND_DATA_H
#define SOUND_DATA_H

/* __FILE__ of the original translation unit. */
#define SNDDATA_C_FILE \
    "\\build\\splintercellx-pc\\patch\\SplinterCell2\\technology-group\\sound\\dare\\private" \
    "\\engine\\common\\src\\snddata.c"

/* A directory added with SND_fn_vAddPartialDirectory. The type names are those of the sibling
   build whose list holds "root" directories; the list's name is the later sibling's. */
typedef struct _tdstDataRootDirectory tdstDataRootDirectory;

typedef struct SNDLST2_tdstAnchorToLPDATAROOTDIRDyn {
    tdstDataRootDirectory *hFirstElementDyn;
    tdstDataRootDirectory *hLastElementDyn;
    long lNumberOfElementsDyn;
} SNDLST2_tdstAnchorToLPDATAROOTDIRDyn;

struct _tdstDataRootDirectory {
    char szDirectory[256];
    tdstDataRootDirectory *hNextBrotherDyn;
    tdstDataRootDirectory *hPrevBrotherDyn;
    SNDLST2_tdstAnchorToLPDATAROOTDIRDyn *hFatherDyn;
};

/* File-static in snddata.c of the sibling builds. */
extern char g_czSndMasterDirectory[256];
extern SNDLST2_tdstAnchorToLPDATAROOTDIRDyn gs_stDataPartialDirectoryList;
extern char g_czSoundSoftDirectory[256];
extern char g_czCurrentLang[9];

/* Called when the current language changes after one was already set. */
void __cdecl sound_on_language_changed(void);

void __stdcall SND_fn_vSetMasterDirectory(const char *cszDir);
int __stdcall SND_fn_bGetMasterDirectory(char *szDir, unsigned int size);
int __stdcall SND_fn_bGetOnePartialDirectory(long index, char *szDir, unsigned int size);
void __stdcall SND_fn_vAddPartialDirectory(const char *cszDir);
void __stdcall SND_fn_vRemovePartialDirectory(const char *cszDir);
void __stdcall SND_fn_vPurgeAllDirectories(void);
unsigned long __stdcall SND_fn_ulGetNumberOfPartialDirectory(void);
int __stdcall SND_fn_bIsDataDirectory(const char *cszDir);
char *__stdcall SND_fn_szGetSoftDirectory(void);
void __stdcall SND_fn_vSetSoftDirectory(const char *cszDir);
void __stdcall SND_fn_vSetCurrentLanguage(const char *cszLanguage);
void __stdcall SND_fn_vSetCurrentLangDirectory(const char *cszLanguage);
char *__stdcall SND_fn_szGetCurrentLangDirectory(void);
int __stdcall SND_fn_bLoadDataInMem(void *pvDest, unsigned long ulSize, const char *szFileName,
                                    long lOffset);

#endif
