/* sound_thread.h -- the sound library's locks and their watcher */
#ifndef SOUND_THREAD_H
#define SOUND_THREAD_H

/* Every recovered caller enters a lock and at once tells the watcher ("mouchard") where it
   did so, with the __FILE__ and __LINE__ of the original source. The trailing underscore of
   the two enter functions suggests the pair was one macro. This reconstruction writes both
   calls, the file name as the macro of the translation unit's header, and the line as the
   number the binary holds. */
void __stdcall SND_fn_vEnterCriticalSectionThreadSnd_(void);
void __stdcall SND_fn_vQuitCriticalSectionThreadSnd(void);
void __stdcall SND_fn_vMouchardThreadsnd(const char *file, long line);

void __stdcall EnterCriticalSectionTool_(void);
void __stdcall QuitCriticalSectionTool(void);
void __stdcall MouchardThreadTool(const char *file, long line);

#endif
