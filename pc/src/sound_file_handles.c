/* sound_file_handles.c -- opens, closes and deletes files (sndfile.c) */
#include "sound_file.h"
#include "sound_win32.h"

/* SND_fn_hOpenFileReadSnd */
SndFile __stdcall SND_fn_hOpenFileReadSnd(const char *szFileName)
{
    SndFile file = CreateFileA(szFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if (file == INVALID_HANDLE_VALUE)
        return SND_FILE_INVALID;
    return file;
}

/* SND_fn_vCloseFileSnd */
void __stdcall SND_fn_vCloseFileSnd(SndFile hFile)
{
    CloseHandle(hFile);
}

/* SND_fn_hOpenFileWriteSnd */
SndFile __stdcall SND_fn_hOpenFileWriteSnd(const char *szFileName)
{
    SndFile file = CreateFileA(szFileName, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    if (file == INVALID_HANDLE_VALUE)
        return SND_FILE_INVALID;
    return file;
}

/* SND_fn_bDeleteFile */
int __stdcall SND_fn_bDeleteFile(const char *szFileName)
{
    return DeleteFileA(szFileName);
}
