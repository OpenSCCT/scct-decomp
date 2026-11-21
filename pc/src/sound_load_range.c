/* sound_load_range.c -- reads part of a file into memory (snddata.c) */
#include "sound_data.h"
#include "sound_file.h"

/* SND_fn_bLoadDataInMem: true when all ulSize bytes at lOffset were read */
int __stdcall SND_fn_bLoadDataInMem(void *pvDest, unsigned long ulSize, const char *szFileName,
                                    long lOffset)
{
    unsigned long count;
    SndFile hFile = SND_fn_hOpenFileReadSnd(szFileName);
    if (hFile != SND_FILE_INVALID) {
        SND_fn_ulSeekFileSnd(hFile, lOffset, 0);
        count = SND_fn_ulReadFileSnd(hFile, ulSize, pvDest);
        SND_fn_vCloseFileSnd(hFile);
        if (count == ulSize)
            return 1;
    }
    return 0;
}
