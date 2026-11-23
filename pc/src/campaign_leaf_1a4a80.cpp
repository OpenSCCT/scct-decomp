// campaign_leaf_1a4a80.cpp -- function at VA 0x10aa4a80 with no this pointer. When the flag at VA
// 0x111fa6e0 is set it returns true. Otherwise it sets the flag from the stdcall function at VA
// 0x10efb800 called with 0, calls the stdcall function at VA 0x10efb7f0 with 0x0f, creates the
// object the global at VA 0x111fa6dc points to (0x2754 bytes from the allocator at VA 0x111c88a0,
// tag "new", constructor at VA 0x10b08aa0), clears the flag when that fails, and returns the flag.
// The function names are invented; the tag is the binary's.

#include "campaign_global_111c88a0.h"
#include "campaign_global_111fa6dc.h"
#include "campaign_global_111fa6e0.h"

inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

bool __stdcall Unk_10efb800(int Value);
bool __stdcall Unk_10efb7f0(int Value);

// Unk_10aa4a80
bool Unk_10aa4a80()
{
    if ( GUnk_111fa6e0 )
    {
        return true;
    }
    GUnk_111fa6e0 = Unk_10efb800(0) != 0;
    Unk_10efb7f0(0xf);
    GUnk_111fa6dc = new(L"new") UnkType_111fa6dc;
    if ( GUnk_111fa6dc == 0 )
    {
        GUnk_111fa6e0 = false;
    }
    return GUnk_111fa6e0;
}
