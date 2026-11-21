#include "sound_file.h"
#include "sound_win32.h"

unsigned long __stdcall SND_fn_ulReadFileSnd(SndFile hFile, unsigned long ulNbBytes, void *pvBuffer)
{
    unsigned long read = 0;
    if (!ReadFile(hFile, pvBuffer, ulNbBytes, &read, 0)) {
        GetLastError();
        return 0;
    }
    return read;
}

unsigned long __stdcall SND_fn_ulWriteFileSnd(SndFile hFile, unsigned long ulNbBytes,
                                              const void *pvBuffer)
{
    unsigned long written = 0;
    if (!WriteFile(hFile, pvBuffer, ulNbBytes, &written, 0)) {
        GetLastError();
        return 0;
    }
    return written;
}

unsigned long __stdcall SND_fn_ulGetFileSize(SndFile hFile)
{
    return GetFileSize(hFile, 0);
}
