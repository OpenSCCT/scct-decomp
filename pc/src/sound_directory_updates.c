#include "sound_data.h"
#include "sound_string.h"
#include "sound_thread.h"

unsigned long __stdcall SND_fn_ulGetNumberOfPartialDirectory(void)
{
    unsigned long total;
    SND_fn_vEnterCriticalSectionThreadSnd_();
    SND_fn_vMouchardThreadsnd(SNDDATA_C_FILE, 363);
    total = gs_stDataPartialDirectoryList.lNumberOfElementsDyn + 1;
    SND_fn_vQuitCriticalSectionThreadSnd();
    return total;
}

void __stdcall SND_fn_vSetSoftDirectory(const char *cszDir)
{
    SND_fn_vEnterCriticalSectionThreadSnd_();
    SND_fn_vMouchardThreadsnd(SNDDATA_C_FILE, 496);
    SND_fn_vStrncpy(g_czSoundSoftDirectory, cszDir, sizeof(g_czSoundSoftDirectory));
    SND_fn_vQuitCriticalSectionThreadSnd();
}

void __stdcall SND_fn_vSetCurrentLangDirectory(const char *cszLanguage)
{
    SND_fn_vStrncpy(g_czCurrentLang, cszLanguage, sizeof(g_czCurrentLang));
}
