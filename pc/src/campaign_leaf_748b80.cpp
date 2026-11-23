// campaign_leaf_748b80.cpp -- one function at file offset 0x748b80, preferred VA 0x11048b80. When the
// word at VA 0x1132c7ac is set it releases the copy at VA 0x1132c740 through the stdcall function at
// VA 0x1103c870 and replaces it with a copy of the source's 0x18-byte entries (the data at 0x0,
// the count at 0x4), allocated through the stdcall function at VA 0x1103c830 and filled through
// the stdcall function at VA 0x1103c5d0, storing the count at VA 0x1132c744; without a source, entries
// or memory it clears both. The type and function names are invented; the addresses are the
// binary's.

#include "campaign_global_1132c7ac.h"
#include "campaign_global_1132c740.h"
#include "campaign_global_1132c744.h"

void __stdcall Unk_1103c870(void* Pointer);
void* __stdcall Unk_1103c830(unsigned int Size);
void __stdcall Unk_1103c5d0(void* Destination, const void* Source, unsigned int Size);

struct UnkType_11048b80_Source
{
    void* unk_0;
    int unk_4;
};

// Unk_11048b80
void Unk_11048b80(UnkType_11048b80_Source* Source)
{
    void* Data;
    int Count;
    unsigned int Size;
    void* Copy;

    if ( GUnk_1132c7ac == 0 )
    {
        return;
    }
    if ( GUnk_1132c740 != 0 )
    {
        Unk_1103c870(GUnk_1132c740);
    }
    if ( Source != 0 )
    {
        Data = Source->unk_0;
        if ( Data != 0 )
        {
            Count = Source->unk_4;
            if ( Count != 0 )
            {
                Size = Count * 0x18;
                Copy = Unk_1103c830(Size);
                if ( Copy != 0 )
                {
                    Unk_1103c5d0(Copy, Data, Size);
                    GUnk_1132c744 = Count;
                    GUnk_1132c740 = Copy;
                    return;
                }
            }
        }
    }
    GUnk_1132c740 = 0;
    GUnk_1132c744 = 0;
}
