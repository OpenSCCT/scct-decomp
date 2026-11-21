/* campaign_sound_lock.c -- enters the sound library's two locks */
#include "sound_error.h"
#include "sound_string.h"
#include "sound_thread.h"
#include "sound_win32.h"

/* SND_fn_vEnterCriticalSectionThreadSnd_: waits for the engine's lock. When the wait fails,
   reports the place the watcher last recorded and waits again. */
void __stdcall SND_fn_vEnterCriticalSectionThreadSnd_(void)
{
    char message[1024];
    if (!g_bSndThreadInitDone) {
        SND_fn_vDisplayError(E_uwSndInitNotDoneError, "");
    }
    if (g_hMutexSnd) {
        if (WaitForSingleObject(g_hMutexSnd, INFINITE) == WAIT_OBJECT_0) {
            g_lMutexSndCount++;
            return;
        }
        GetLastError();
        sprintf(message, "Last call by thread %x (line %d of %s)", g_ulMouchardThread, g_ulMouchardLine,
                g_szMouchardFile);
        SND_fn_vDisplayError(E_uwSndThreadDeadLockError, message);
        WaitForSingleObject(g_hMutexSnd, INFINITE);
    } else {
        SND_fn_vDisplayError(E_uwSndThreadMultiThreadDetectedError,
                             "g_hMutexSnd is NULL; maybe DARE is currenlty not initialized.");
    }
}

/* EnterCriticalSectionTool_: the same for the tools' lock */
void __stdcall EnterCriticalSectionTool_(void)
{
    char message[256];
    if (!g_bSndThreadInitDone) {
        SND_fn_vDisplayError(E_uwSndInitNotDoneError, "");
    }
    if (g_hMutexTool) {
        if (WaitForSingleObject(g_hMutexTool, INFINITE) == WAIT_OBJECT_0) {
            g_lMutexToolCount++;
            return;
        }
        GetLastError();
        sprintf(message, "Last call by thread %x (line %d of %s)", g_ulMouchardToolThread,
                g_ulMouchardToolLine, g_szMouchardToolFile);
        SND_fn_vDisplayError(E_uwSndThreadDeadLockError, message);
        WaitForSingleObject(g_hMutexTool, INFINITE);
    } else {
        SND_fn_vDisplayError(E_uwSndThreadMultiThreadDetectedError,
                             "g_hMutexTool is NULL; maybe DARE is currenlty not initialized.");
    }
}
