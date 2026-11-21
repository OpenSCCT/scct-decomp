/* sound_file_io.c -- reads, writes and measures a file (sndfile.c) */
#include "sound_file.h"
#include "sound_win32.h"

/* SND_fn_ulReadFileSnd: the number of bytes read, 0 on failure */
unsigned long __stdcall SND_fn_ulReadFileSnd(SndFile hFile, unsigned long ulNbBytes, void *pvBuffer)
{
    unsigned long read = 0;
    if (!ReadFile(hFile, pvBuffer, ulNbBytes, &read, 0)) {
        GetLastError();
        return 0;
    }
    return read;
}

/* SND_fn_ulWriteFileSnd: the number of bytes written, 0 on failure */
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

/* SND_fn_ulGetFileSize */
unsigned long __stdcall SND_fn_ulGetFileSize(SndFile hFile)
{
    return GetFileSize(hFile, 0);
}
