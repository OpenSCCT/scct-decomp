#include "sound_data.h"
#include "sound_file.h"

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
