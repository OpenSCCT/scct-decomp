/* sound_memory.h -- memory services of the sound library (sndmem.c) */
#ifndef SOUND_MEMORY_H
#define SOUND_MEMORY_H

int __stdcall SND_fn_bInitMallocSnd(void);
void *__stdcall SND_fn_pvMallocSnd(unsigned long ulNbBytes);
void *__stdcall SND_fn_pvReAllocSnd(void *pvPtr, unsigned long ulNbBytes);
void __stdcall SND_fn_vFreeSnd(void *pvPtr);
void *__stdcall SND_fn_pvMallocSndAligned(unsigned long ulNbBytes, unsigned long ulAlignment);
void *__stdcall SND_fn_pvReAllocSndAligned(void *pvPtr, unsigned long ulNbBytes,
                                           unsigned long ulAlignment);
void __stdcall SND_fn_vFreeSndAligned(void *pvPtr, unsigned long ulAlignment);
void __stdcall SND_fn_vMemCopySnd(void *ptr_dest, const void *ptr_source, unsigned long ulNbBytes);
void __stdcall SND_fn_vMemMoveSnd(void *ptr_dest, const void *ptr_source, unsigned long ulNbBytes);
void __stdcall SND_fn_vMemsetSnd(void *ptr_dest, unsigned char c, unsigned long ulNbBytes);

#endif
