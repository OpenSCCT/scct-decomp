/* sound_options.c -- reads and writes the sound library's DARE.INI options */
#include <string.h>
#include "sound_error.h"
#include "sound_options.h"
#include "sound_win32.h"

static char sound_missing_option[] = "None";

/* SND_fn_bGetOptions */
int __stdcall SND_fn_bGetOptions(const char *section, const char *key, char *value,
                                 unsigned long size)
{
    GetPrivateProfileStringA(section, key, sound_missing_option, value, size, sound_ini_path);
    return _stricmp(value, sound_missing_option) != 0;
}

/* SND_fn_vSetOptions */
void __stdcall SND_fn_vSetOptions(const char *section, const char *key, const char *value)
{
    if (!WritePrivateProfileStringA(section, key, value, sound_ini_path))
        SND_fn_vDisplayError(E_uwSndGenericWarning,
                             "Cannot change options in DARE.INI (check if file has write access).");
}
