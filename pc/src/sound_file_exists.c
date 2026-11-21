#include "sound_file.h"
#include "sound_win32.h"

int __stdcall SND_fn_bTestFileExistSnd(const char *szFileName)
{
    WIN32_FIND_DATAA data;
    void *handle = FindFirstFileA(szFileName, &data);
    if (handle == INVALID_HANDLE_VALUE)
        return 0;
    FindClose(handle);
    return 1;
}
