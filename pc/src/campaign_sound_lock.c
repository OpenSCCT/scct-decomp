/* DARE sound library: enter the sound thread lock. When the wait fails the
   message names the last thread to take the lock, as recorded by
   SND_fn_vMouchardThreadsnd. */
typedef void *HANDLE;
__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(HANDLE handle, unsigned long milliseconds);
__declspec(dllimport) unsigned long __stdcall GetLastError(void);
int __cdecl sprintf(char *buffer, const char *format, ...);
void __stdcall SND_fn_vDisplayError(unsigned code, const char *message);

extern int g_bSndThreadInitDone;
extern HANDLE g_hMutexSnd;
extern long g_lMutexSndCount;
extern char g_szMouchardFile[];
extern unsigned long g_ulMouchardLine;
extern unsigned long g_ulMouchardThread;
extern HANDLE g_hMutexTool;
extern long g_lMutexToolCount;
extern char g_szMouchardToolFile[];
extern unsigned long g_ulMouchardToolLine;
extern unsigned long g_ulMouchardToolThread;

void __stdcall SND_fn_vEnterCriticalSectionThreadSnd_(void)
{
    char message[1024];
    if (!g_bSndThreadInitDone)
        SND_fn_vDisplayError(4, "");
    if (g_hMutexSnd) {
        if (WaitForSingleObject(g_hMutexSnd, 0xffffffff) == 0) {
            g_lMutexSndCount++;
            return;
        }
        GetLastError();
        sprintf(message, "Last call by thread %x (line %d of %s)", g_ulMouchardThread, g_ulMouchardLine, g_szMouchardFile);
        SND_fn_vDisplayError(2, message);
        WaitForSingleObject(g_hMutexSnd, 0xffffffff);
    } else {
        SND_fn_vDisplayError(31, "g_hMutexSnd is NULL; maybe DARE is currenlty not initialized.");
    }
}

void __stdcall EnterCriticalSectionTool_(void)
{
    char message[256];
    if (!g_bSndThreadInitDone)
        SND_fn_vDisplayError(4, "");
    if (g_hMutexTool) {
        if (WaitForSingleObject(g_hMutexTool, 0xffffffff) == 0) {
            g_lMutexToolCount++;
            return;
        }
        GetLastError();
        sprintf(message, "Last call by thread %x (line %d of %s)", g_ulMouchardToolThread, g_ulMouchardToolLine, g_szMouchardToolFile);
        SND_fn_vDisplayError(2, message);
        WaitForSingleObject(g_hMutexTool, 0xffffffff);
    } else {
        SND_fn_vDisplayError(31, "g_hMutexTool is NULL; maybe DARE is currenlty not initialized.");
    }
}
