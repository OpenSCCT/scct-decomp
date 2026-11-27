#ifndef VERSUS_APP_MEMZERO_H
#define VERSUS_APP_MEMZERO_H

// The retail and editor copies of Clear both expand this Win32 helper twice.
// Its 16-byte core also appears in 128 retail sites, including the zeroed
// allocations at file offsets 0x121817 and 0x14099e.
inline void appMemzero(void *Dest, INT Count)
{
    __asm {
        mov ecx, Count
        mov edi, Dest
        xor eax, eax
        mov ebx, ecx
        shr ecx, 2
        and ebx, 3
        rep stosd
        mov ecx, ebx
        rep stosb
    }
}

#endif
