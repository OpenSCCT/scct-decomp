#include "sound_file.h"
#include "sound_win32.h"

void __stdcall SND_fn_vCloseFileSnd(SndFile hFile)
{
    CloseHandle(hFile);
}

int __stdcall SND_fn_bDeleteFile(const char *szFileName)
{
    return DeleteFileA(szFileName);
}
