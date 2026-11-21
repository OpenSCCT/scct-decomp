#include "sound_data.h"
#include "sound_memory.h"
#include "sound_string.h"
#include "sound_thread.h"

static __forceinline void remove_data_root_directory(tdstDataRootDirectory *pstDataRootDir)
{
    if (pstDataRootDir->hNextBrotherDyn)
        pstDataRootDir->hNextBrotherDyn->hPrevBrotherDyn = pstDataRootDir->hPrevBrotherDyn;
    if (pstDataRootDir->hPrevBrotherDyn)
        pstDataRootDir->hPrevBrotherDyn->hNextBrotherDyn = pstDataRootDir->hNextBrotherDyn;
    if (pstDataRootDir->hFatherDyn) {
        --pstDataRootDir->hFatherDyn->lNumberOfElementsDyn;
        if (pstDataRootDir->hFatherDyn->hFirstElementDyn == pstDataRootDir)
            pstDataRootDir->hFatherDyn->hFirstElementDyn = pstDataRootDir->hNextBrotherDyn;
        if (pstDataRootDir->hFatherDyn->hLastElementDyn == pstDataRootDir)
            pstDataRootDir->hFatherDyn->hLastElementDyn = pstDataRootDir->hPrevBrotherDyn;
    }
    pstDataRootDir->hNextBrotherDyn = 0;
    pstDataRootDir->hPrevBrotherDyn = 0;
    pstDataRootDir->hFatherDyn = 0;
    SND_fn_vFreeSnd(pstDataRootDir);
}

void __stdcall SND_fn_vRemovePartialDirectory(const char *cszDir)
{
    tdstDataRootDirectory *pstDataRootDir;
    tdstDataRootDirectory *pstNext;
    SND_fn_vEnterCriticalSectionThreadSnd_();
    SND_fn_vMouchardThreadsnd(SNDDATA_C_FILE, 297);
    pstDataRootDir = gs_stDataPartialDirectoryList.hFirstElementDyn;
    if (pstDataRootDir)
        pstNext = pstDataRootDir->hNextBrotherDyn;
    while (pstDataRootDir) {
        if (!SND_fn_lStriCmp(pstDataRootDir->szDirectory, cszDir)) {
            remove_data_root_directory(pstDataRootDir);
            break;
        }
        pstDataRootDir = pstNext;
        if (pstDataRootDir)
            pstNext = pstDataRootDir->hNextBrotherDyn;
    }
    SND_fn_vQuitCriticalSectionThreadSnd();
}

void __stdcall SND_fn_vPurgeAllDirectories(void)
{
    tdstDataRootDirectory *pstDataRootDir;
    tdstDataRootDirectory *pstNext;
    SND_fn_vEnterCriticalSectionThreadSnd_();
    SND_fn_vMouchardThreadsnd(SNDDATA_C_FILE, 328);
    SND_fn_vMemsetSnd(g_czSndMasterDirectory, 0, sizeof(g_czSndMasterDirectory));
    pstDataRootDir = gs_stDataPartialDirectoryList.hFirstElementDyn;
    if (pstDataRootDir)
        pstNext = pstDataRootDir->hNextBrotherDyn;
    while (pstDataRootDir) {
        remove_data_root_directory(pstDataRootDir);
        pstDataRootDir = pstNext;
        if (pstDataRootDir)
            pstNext = pstDataRootDir->hNextBrotherDyn;
    }
    SND_fn_vQuitCriticalSectionThreadSnd();
}
