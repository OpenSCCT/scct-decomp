#include "sound_data.h"
#include "sound_error.h"
#include "sound_file.h"
#include "sound_string.h"
#include "sound_thread.h"

int __stdcall SND_fn_bIsDataDirectory(const char *cszDir)
{
    char szTempDir[256];
    unsigned int length;
    tdstDataRootDirectory *pstDataRootDir;
    SND_fn_vEnterCriticalSectionThreadSnd_();
    SND_fn_vMouchardThreadsnd(SNDDATA_C_FILE, 390);
    if (!SND_fn_lStriCmp(g_czSndMasterDirectory, cszDir)) {
        SND_fn_vQuitCriticalSectionThreadSnd();
        return 1;
    }
    if (SND_fn_lStriCmp(g_czCurrentLang, "")) {
        SND_fn_vStrncpy(szTempDir, g_czSndMasterDirectory, sizeof(szTempDir));
        if (strlen(szTempDir) + 12 < sizeof(szTempDir)) {
            strcat(szTempDir, g_czCurrentLang);
            length = strlen(szTempDir);
            szTempDir[length] = SND_fn_cGetDirectorySeparator();
            szTempDir[length + 1] = 0;
            if (!SND_fn_lStriCmp(szTempDir, cszDir)) {
                SND_fn_vQuitCriticalSectionThreadSnd();
                return 1;
            }
        } else {
            SND_fn_vQuitCriticalSectionThreadSnd();
            SND_fn_vDisplayError(E_uwSndMemoryAllocError, "Invalid size of path.");
            return 0;
        }
    }

    pstDataRootDir = gs_stDataPartialDirectoryList.hFirstElementDyn;
    if (gs_stDataPartialDirectoryList.hFirstElementDyn) {
        do {
            if (!SND_fn_lStriCmp(pstDataRootDir->szDirectory, cszDir)) {
                SND_fn_vQuitCriticalSectionThreadSnd();
                return 1;
            }
            if (SND_fn_lStriCmp(g_czCurrentLang, "")) {
                SND_fn_vStrncpy(szTempDir, pstDataRootDir->szDirectory, sizeof(szTempDir));
                if (strlen(szTempDir) + 12 < sizeof(szTempDir)) {
                    strcat(szTempDir, g_czCurrentLang);
                    length = strlen(szTempDir);
                    szTempDir[length] = SND_fn_cGetDirectorySeparator();
                    szTempDir[length + 1] = 0;
                    if (!SND_fn_lStriCmp(szTempDir, cszDir)) {
                        SND_fn_vQuitCriticalSectionThreadSnd();
                        return 1;
                    }
                } else {
                    SND_fn_vQuitCriticalSectionThreadSnd();
                    SND_fn_vDisplayError(E_uwSndMemoryAllocError, "Invalid size of path.");
                    return 0;
                }
            }
            pstDataRootDir = pstDataRootDir->hNextBrotherDyn;
        } while (pstDataRootDir);
    }
    SND_fn_vQuitCriticalSectionThreadSnd();
    return 0;
}
