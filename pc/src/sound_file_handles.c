/* sound_file_handles.c -- closes and deletes files (sndfile.c) */
#include "sound_file.h"
#include "sound_win32.h"

/* SND_fn_vCloseFileSnd */
void __stdcall SND_fn_vCloseFileSnd(SndFile hFile)
{
    CloseHandle(hFile);
}

/* SND_fn_bDeleteFile */
int __stdcall SND_fn_bDeleteFile(const char *szFileName)
{
    return DeleteFileA(szFileName);
}
