/* sound_filename_exists.c -- searches the master and partial directories for a file (snddata.c) */
#include "sound_data.h"
#include "sound_file.h"
#include "sound_string.h"

/* SND_fn_bFileNameExist */
int __stdcall SND_fn_bFileNameExist(const char *filename)
{
    char path[256];
    SndFile file;
    tdstDataRootDirectory *directory;
    SND_fn_vStrncpy(path, g_czSndMasterDirectory, sizeof(path));
    strcat(path, filename);
    file = SND_fn_hOpenFileReadSnd(path);
    if (file != SND_FILE_INVALID) {
        SND_fn_vCloseFileSnd(file);
        return 1;
    }
    directory = gs_stDataPartialDirectoryList.hFirstElementDyn;
    if (gs_stDataPartialDirectoryList.hFirstElementDyn) {
        do {
            SND_fn_vStrncpy(path, directory->szDirectory, sizeof(path));
            strcat(path, filename);
            file = SND_fn_hOpenFileReadSnd(path);
            if (file != SND_FILE_INVALID) {
                SND_fn_vCloseFileSnd(file);
                return 1;
            }
            directory = directory->hNextBrotherDyn;
        } while (directory);
    }
    return 0;
}
