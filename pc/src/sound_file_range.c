/* sound_file_range.c -- moves a file's read position (sndfile.c) */
#include "sound_error.h"
#include "sound_file.h"
#include "sound_win32.h"

/* SND_fn_ulSeekFileSnd: origin 0, 1 or 2 counts from the start, the current position or the
   end; returns the new position, or -1 on failure. Any other origin is reported and then
   counts from the start. */
unsigned long __stdcall SND_fn_ulSeekFileSnd(SndFile hFile, long lOffset, int origin)
{
    unsigned long method;
    unsigned long result;
    switch (origin) {
    default:
        SND_fn_vDisplayError(E_uwSndErrorReadingFile, "Bad _eOrigin parameter for SND_fn_lSeekFileSnd.");
        /* fall through */
    case 0:
        method = FILE_BEGIN;
        break;
    case 1:
        method = FILE_CURRENT;
        break;
    case 2:
        method = FILE_END;
        break;
    }
    result = SetFilePointer(hFile, lOffset, 0, method);
    if (result == INVALID_SET_FILE_POINTER || result == ERROR_NEGATIVE_SEEK)
        return INVALID_SET_FILE_POINTER;
    return result;
}
