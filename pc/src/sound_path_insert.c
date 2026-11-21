/* sound_path_insert.c -- adds a partial directory (snddata.c) */
#include "sound_data.h"
#include "sound_error.h"
#include "sound_file.h"
#include "sound_memory.h"
#include "sound_string.h"
#include "sound_thread.h"

/* SND_fn_vAddPartialDirectory: the directory must end with a separator; it is added once */
void __stdcall SND_fn_vAddPartialDirectory(const char *cszDir)
{
    int iStrLen, i;
    char *czStrTemp;
    tdstDataRootDirectory *pstNewDataRoot;
    if (!cszDir) {
        SND_fn_vDisplayError(47, "Error in SndFile:SND_fn_vAddPartialDirectory : Game send us a NULL pointer string");
        return;
    }
    if (strlen(g_czSndMasterDirectory) == 0) {
        SND_fn_vDisplayError(47, "Error in SndFile:SND_fn_vAddPartialDirectory : Game has not set the Master Directory.");
        return;
    }
    iStrLen = strlen(cszDir);
    czStrTemp = SND_fn_pvMallocSnd(iStrLen + 1);
    if (!czStrTemp) {
        SND_fn_vDisplayError(47, "Error in SND_fn_vAddPartialDirectory : Memory Allocation failed");
        return;
    }
    strcpy(czStrTemp, cszDir);
    for (i = 0; i < iStrLen; ++i) {
        if (czStrTemp[i] == '/' || czStrTemp[i] == '\\')
            czStrTemp[i] = SND_fn_cGetDirectorySeparator();
    }
    if (iStrLen > 0 && czStrTemp[iStrLen - 1] != SND_fn_cGetDirectorySeparator()) {
        SND_fn_vDisplayError(47, "Error in SND_fn_vAddPartialDirectory : path string must include final \\ or /.");
        SND_fn_vFreeSnd(czStrTemp);
        return;
    }
    SND_fn_vEnterCriticalSectionThreadSnd_();
    SND_fn_vMouchardThreadsnd(SNDDATA_C_FILE, 215);
    if (!SND_fn_bIsDataDirectory(czStrTemp)) {
        pstNewDataRoot = SND_fn_pvMallocSnd(sizeof(*pstNewDataRoot));
        if (pstNewDataRoot) {
            SND_fn_vStrncpy(pstNewDataRoot->szDirectory, czStrTemp, sizeof(pstNewDataRoot->szDirectory));
            pstNewDataRoot->hPrevBrotherDyn = 0;
            pstNewDataRoot->hFatherDyn = 0;
            pstNewDataRoot->hNextBrotherDyn = 0;
            pstNewDataRoot->hPrevBrotherDyn = gs_stDataPartialDirectoryList.hLastElementDyn;
            pstNewDataRoot->hFatherDyn = &gs_stDataPartialDirectoryList;
            if (gs_stDataPartialDirectoryList.hFirstElementDyn == 0)
                gs_stDataPartialDirectoryList.hFirstElementDyn = pstNewDataRoot;
            else
                gs_stDataPartialDirectoryList.hLastElementDyn->hNextBrotherDyn = pstNewDataRoot;
            gs_stDataPartialDirectoryList.hLastElementDyn = pstNewDataRoot;
            ++gs_stDataPartialDirectoryList.lNumberOfElementsDyn;
        }
    }
    SND_fn_vQuitCriticalSectionThreadSnd();
    SND_fn_vFreeSnd(czStrTemp);
}
