#include "sound_data.h"
#include "sound_file.h"

char *__stdcall SND_fn_szGetSoftDirectory(void)
{
    return g_czSoundSoftDirectory;
}

char *__stdcall SND_fn_szGetCurrentLangDirectory(void)
{
    return g_czCurrentLang;
}

char __stdcall SND_fn_cGetDirectorySeparator(void)
{
    return '\\';
}
