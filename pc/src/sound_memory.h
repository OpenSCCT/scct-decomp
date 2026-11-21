/* sound_memory.h -- memory services of the sound library (sndmem.c) */
#ifndef SOUND_MEMORY_H
#define SOUND_MEMORY_H

/* The rebuild has no C runtime headers.
   guess: the runtime function SND_fn_vMemMoveSnd forwards to is memmove, by the export's name
   and the argument order; it has not been compared with the runtime library. */
void *__cdecl memmove(void *dest, const void *src, unsigned int count);

/* Reports whether the processor has CPUID and MMX. */
void __cdecl sound_heap_detect_cpu(unsigned long *cpuid, unsigned long *mmx);

/* The allocator the game gives the library is a C++ object; the library calls its first
   three virtual functions. C has no spelling for their convention (`this` in ECX, arguments
   on the stack): the stand-ins below are __fastcall functions that fill EDX with a spare
   argument or wrap a stack argument in a structure. This is open work that belongs in C++.
   The names of the types, the members and the pointer are invented. */
typedef struct SoundAllocator SoundAllocator;
/* FAKEMATCH: wraps one stack argument of a C++ member call; the original passes the value itself. */
typedef struct SoundAllocationArg {
    void *value;
} SoundAllocationArg;
typedef struct SoundAllocatorMethods {
    void *(__fastcall *allocate)(SoundAllocator *self, unsigned long unused_edx, unsigned long size,
                                 const void *tag);
    void *(__fastcall *resize)(SoundAllocator *self, void *unused_edx, void *allocation,
                               unsigned long size, const void *tag);
    void (__fastcall *release)(SoundAllocator *self, SoundAllocationArg allocation);
} SoundAllocatorMethods;
struct SoundAllocator {
    const SoundAllocatorMethods *methods;
};
extern SoundAllocator *sound_allocator;

/* What the library passes with every allocation; file-static in sndmem.c of the sibling
   build. Only its address is used, so its type is not recovered. */
extern char StaticTag[];

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
