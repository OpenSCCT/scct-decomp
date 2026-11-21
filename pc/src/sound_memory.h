/* sound_memory.h -- memory services of the sound library (sndmem.c) */
#ifndef SOUND_MEMORY_H
#define SOUND_MEMORY_H

/* The rebuild has no C runtime headers.
   guess: the runtime function SND_fn_vMemMoveSnd forwards to is memmove, by the export's name
   and the argument order; it has not been compared with the runtime library. */
void *__cdecl memmove(void *dest, const void *src, unsigned int count);

/* Reports whether the processor has CPUID and MMX. */
void __cdecl sound_heap_detect_cpu(unsigned long *cpuid, unsigned long *mmx);

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
