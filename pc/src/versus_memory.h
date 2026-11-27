#ifndef VERSUS_MEMORY_H
#define VERSUS_MEMORY_H

#include "unreal_types.h"

// Epic's Win32 appMemzero helper from Core/Inc/UnVcWin32.h.
// Versus also emits the complete helper out of line at RVA 0x42a0.
// It clears full DWORDs first, then the remaining zero to three bytes.
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
