/* sound_thread_lifetime.c -- the sound engine and tool mutexes and their watchers */
#include "sound_string.h"
#include "sound_thread.h"
#include "sound_win32.h"

/* SND_fn_vInitThreadSnd */
void __stdcall SND_fn_vInitThreadSnd(void)
{
    g_hMutexSnd = CreateMutexA(0, 1, 0);
    g_hMutexTool = CreateMutexA(0, 1, 0);
    g_lMutexSndCount++;
    g_lMutexToolCount++;
    g_bSndThreadInitDone = 1;
}

/* SND_fn_vDesInitThreadSnd */
void __stdcall SND_fn_vDesInitThreadSnd(void)
{
    void *sound_mutex = g_hMutexSnd;
    void *tool_mutex = g_hMutexTool;
    g_hMutexSnd = 0;
    g_hMutexTool = 0;
    ReleaseMutex(sound_mutex);
    g_lMutexSndCount--;
    CloseHandle(sound_mutex);
    CloseHandle(tool_mutex);
}

/* SND_fn_vMouchardThreadsnd */
void __stdcall SND_fn_vMouchardThreadsnd(const char *file, long line)
{
    strncpy(g_szMouchardFile, file, sizeof(g_szMouchardFile));
    g_ulMouchardLine = line;
    g_ulMouchardThread = GetCurrentThreadId();
}

/* SND_fn_vQuitCriticalSectionThreadSnd */
void __stdcall SND_fn_vQuitCriticalSectionThreadSnd(void)
{
    g_lMutexSndCount--;
    ReleaseMutex(g_hMutexSnd);
}

/* QuitCriticalSectionTool */
void __stdcall QuitCriticalSectionTool(void)
{
    g_lMutexToolCount--;
    ReleaseMutex(g_hMutexTool);
}

/* MouchardThreadTool */
void __stdcall MouchardThreadTool(const char *file, long line)
{
    sprintf(g_szMouchardToolFile, "Enter: %s Line %d\n", file, line);
    g_ulMouchardToolLine = line;
}
