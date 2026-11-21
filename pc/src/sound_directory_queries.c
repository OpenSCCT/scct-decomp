/* sound_directory_queries.c -- directory getters (snddata.c) and the path separator
   (sndfile.c) */
#include "sound_data.h"
#include "sound_file.h"

/* SND_fn_szGetSoftDirectory */
char *__stdcall SND_fn_szGetSoftDirectory(void)
{
    return g_czSoundSoftDirectory;
}

/* SND_fn_szGetCurrentLangDirectory */
char *__stdcall SND_fn_szGetCurrentLangDirectory(void)
{
    return g_czCurrentLang;
}

/* SND_fn_cGetDirectorySeparator */
char __stdcall SND_fn_cGetDirectorySeparator(void)
{
    return '\\';
}
