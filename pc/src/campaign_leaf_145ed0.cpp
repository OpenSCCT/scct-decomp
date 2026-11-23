// campaign_leaf_145ed0.cpp -- one function at file offset 0x145ed0, preferred VA 0x10a45ed0.
// It passes its first argument, the pointer at VA 0x11312050 (created on first use by the
// functions at VA 0x10cdcdb0 and 0x10cd9590 with "Core") and its other eight arguments to the
// function at VA 0x10d01720 and returns its result. It has no this pointer.
// The function names are invented; the offset and the bytes are the binary's.

#include "campaign_global_11312050.h"

void* Unk_10cdcdb0(const unsigned short* Package);
void Unk_10cd9590();
void* Unk_10d01720(void* First, void* Class, int A, int B, int C, int D, int E, int F, int G,
    int H);

inline void* GetUnk11312050()
{
    if ( !GUnk_11312050 )
    {
        GUnk_11312050 = Unk_10cdcdb0(L"Core");
        Unk_10cd9590();
    }
    return GUnk_11312050;
}

// Unk_10a45ed0
void* Unk_10a45ed0(void* First, int A, int B, int C, int D, int E, int F, int G, int H)
{
    return Unk_10d01720(First, GetUnk11312050(), A, B, C, D, E, F, G, H);
}
