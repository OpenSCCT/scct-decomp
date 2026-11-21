/* sound_thread.h -- the sound library's locks and their watcher */
#ifndef SOUND_THREAD_H
#define SOUND_THREAD_H

/* The library has two locks, each a Win32 mutex: one for the engine ("Snd") and one for the
   tools that render sound ("Tool"). Every recovered caller enters a lock and at once tells
   the lock's watcher ("mouchard") where it did so, with the __FILE__ and __LINE__ of the
   original source; when a later wait on the mutex fails, the enter function reports that
   place as the last one to take the lock. The trailing underscore of the two enter functions
   and the pairing at every call site suggest that each pair was one macro, but no build names
   it. This reconstruction writes both calls, the file name as the macro of the translation
   unit's header, and the line as the number the binary holds. */

/* The names g_hMutexSnd and g_hMutexTool are the ones the library's own error messages
   print. No symbol or string names the other globals: their names are invented. */
extern void *g_hMutexSnd;                   /* Win32 mutex */
extern long g_lMutexSndCount;               /* times the lock is held */
extern char g_szMouchardFile[128];          /* where the lock was last taken */
extern unsigned long g_ulMouchardLine;
extern unsigned long g_ulMouchardThread;    /* Win32 thread identifier */

extern void *g_hMutexTool;                  /* Win32 mutex */
extern long g_lMutexToolCount;
/* The watcher's text for the last place the tool lock was taken. Its length is not
   established: the next global lies 256 bytes after it. */
extern char g_szMouchardToolFile[];
extern unsigned long g_ulMouchardToolLine;
extern unsigned long g_ulMouchardToolThread;

/* Set once the locks exist. */
extern int g_bSndThreadInitDone;

void __stdcall SND_fn_vEnterCriticalSectionThreadSnd_(void);
void __stdcall SND_fn_vQuitCriticalSectionThreadSnd(void);
void __stdcall SND_fn_vMouchardThreadsnd(const char *file, long line);

void __stdcall EnterCriticalSectionTool_(void);
void __stdcall QuitCriticalSectionTool(void);
void __stdcall MouchardThreadTool(const char *file, long line);

#endif
