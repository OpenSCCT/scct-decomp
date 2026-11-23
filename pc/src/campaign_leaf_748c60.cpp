// campaign_leaf_748c60.cpp -- one function at file offset 0x748c60, preferred VA 0x11048c60. When
// the word at VA 0x1132c7ac is set it releases the copy at VA 0x1132c748 through the stdcall
// function at VA 0x1103c870 and replaces it with a copy of the source's 0xec-byte entries (the
// data at 0x0, the count at 0x4), allocated through the stdcall function at VA 0x1103c830 and
// filled through the stdcall function at VA 0x1103c5d0, storing the count at VA 0x1132c74c;
// without a source, entries or memory it clears both. The type and function names are invented;
// the addresses are the binary's.

#include "campaign_global_1132c7ac.h"
#include "campaign_global_1132c748.h"
#include "campaign_global_1132c74c.h"

void __stdcall Unk_1103c870(void* Pointer);
void* __stdcall Unk_1103c830(unsigned int Size);
void __stdcall Unk_1103c5d0(void* Destination, const void* Source, unsigned int Size);

struct UnkType_11048c60_Source
{
    void* unk_0;
    int unk_4;
};

// Unk_11048c60
void Unk_11048c60(UnkType_11048c60_Source* Source)
{
    void* Data;
    int Count;
    unsigned int Size;
    void* Copy;

    if ( GUnk_1132c7ac == 0 )
    {
        return;
    }
    if ( GUnk_1132c748 != 0 )
    {
        Unk_1103c870(GUnk_1132c748);
    }
    if ( Source != 0 )
    {
        Data = Source->unk_0;
        if ( Data != 0 )
        {
            Count = Source->unk_4;
            if ( Count != 0 )
            {
                Size = Count * 0xec;
                Copy = Unk_1103c830(Size);
                if ( Copy != 0 )
                {
                    Unk_1103c5d0(Copy, Data, Size);
                    GUnk_1132c74c = Count;
                    GUnk_1132c748 = Copy;
                    return;
                }
            }
        }
    }
    GUnk_1132c748 = 0;
    GUnk_1132c74c = 0;
}
