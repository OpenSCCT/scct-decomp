/* sound_file.h -- file services of the sound library (sndfile.c) */
#ifndef SOUND_FILE_H
#define SOUND_FILE_H

/* A file of the sound library: a Win32 file handle on this target. The typedef's name is
   invented. */
typedef void *SndFile;

/* What SND_fn_hOpenFileReadSnd returns for a file it cannot open. The macro's name is
   invented. */
#define SND_FILE_INVALID ((SndFile)-1)

SndFile __stdcall SND_fn_hOpenFileReadSnd(const char *szFileName);
SndFile __stdcall SND_fn_hOpenFileWriteSnd(const char *szFileName);
unsigned long __stdcall SND_fn_ulReadFileSnd(SndFile hFile, unsigned long ulNbBytes, void *pvBuffer);
unsigned long __stdcall SND_fn_ulWriteFileSnd(SndFile hFile, unsigned long ulNbBytes,
                                              const void *pvBuffer);
unsigned long __stdcall SND_fn_ulSeekFileSnd(SndFile hFile, long lOffset, int origin);
unsigned long __stdcall SND_fn_ulGetFileSize(SndFile hFile);
void __stdcall SND_fn_vCloseFileSnd(SndFile hFile);
int __stdcall SND_fn_bTestFileExistSnd(const char *szFileName);
int __stdcall SND_fn_bDeleteFile(const char *szFileName);
char __stdcall SND_fn_cGetDirectorySeparator(void);

#endif
