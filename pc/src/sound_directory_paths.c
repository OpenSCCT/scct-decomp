/* sound_directory_paths.c -- reads the master directory and the partial directories
   (snddata.c) */
#include "sound_data.h"
#include "sound_error.h"
#include "sound_string.h"
#include "sound_thread.h"

/* SND_fn_bGetMasterDirectory */
int __stdcall SND_fn_bGetMasterDirectory(char *szDir, unsigned int size)
{
    if (!szDir) {
        SND_fn_vDisplayError(47, "Error in SND_fn_vGetMasterDirectory : the function receive a NULL pointer string");
        return 0;
    }
    SND_fn_vEnterCriticalSectionThreadSnd_();
    SND_fn_vMouchardThreadsnd(SNDDATA_C_FILE, 146);
    SND_fn_vStrncpy(szDir, g_czSndMasterDirectory, size);
    SND_fn_vQuitCriticalSectionThreadSnd();
    return 1;
}

/* SND_fn_bGetOnePartialDirectory */
int __stdcall SND_fn_bGetOnePartialDirectory(long index, char *szDir, unsigned int size)
{
    tdstDataRootDirectory *pstDataRootDir;
    if (!szDir) {
        SND_fn_vDisplayError(E_uwSndGenericWarning, "Invalid string pointer.");
        return 0;
    }
    SND_fn_vEnterCriticalSectionThreadSnd_();
    SND_fn_vMouchardThreadsnd(SNDDATA_C_FILE, 257);
    if ((unsigned long)index < (unsigned long)gs_stDataPartialDirectoryList.lNumberOfElementsDyn) {
        pstDataRootDir = gs_stDataPartialDirectoryList.hFirstElementDyn;
        while (index > 0) {
            --index;
            pstDataRootDir = pstDataRootDir->hNextBrotherDyn;
        }
        SND_fn_vStrncpy(szDir, pstDataRootDir->szDirectory, size);
        SND_fn_vQuitCriticalSectionThreadSnd();
        return 1;
    }
    SND_fn_vDisplayError(E_uwSndGenericWarning,
                         "Partial directory element number is bigger than current number of PArtial directories.");
    SND_fn_vQuitCriticalSectionThreadSnd();
    return 0;
}
