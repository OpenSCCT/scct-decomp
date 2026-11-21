/* sound_language_change.c -- sets the current language (snddata.c) */
#include "sound_data.h"
#include "sound_string.h"
#include "sound_thread.h"

/* SND_fn_vSetCurrentLanguage: a change from one language to another also calls
   sound_on_language_changed */
void __stdcall SND_fn_vSetCurrentLanguage(const char *cszLanguage)
{
    SND_fn_vEnterCriticalSectionThreadSnd_();
    SND_fn_vMouchardThreadsnd(SNDDATA_C_FILE, 516);
    if (SND_fn_lStriCmp(g_czCurrentLang, cszLanguage)) {
        if (strcmp(g_czCurrentLang, "") == 0) {
            SND_fn_vStrncpy(g_czCurrentLang, cszLanguage, sizeof(g_czCurrentLang));
        } else {
            SND_fn_vStrncpy(g_czCurrentLang, cszLanguage, sizeof(g_czCurrentLang));
            sound_on_language_changed();
        }
    }
    SND_fn_vQuitCriticalSectionThreadSnd();
}
