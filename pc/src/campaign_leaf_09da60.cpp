// campaign_leaf_09da60.cpp -- method at VA 0x1099da60 assigning one dynamic array of wide
// characters (data pointer at 0x00, count at 0x04, capacity at 0x08) to another: unless both are
// the same object, sets count and capacity to the other's count, reallocates the data through
// virtual slot 1 of the allocator global at VA 0x111c88a0 with the tag "FArray::_WORD" and copies
// the other's characters, or the empty string when it has none; returns the array. guess: the
// engine's FString copy assignment. The class, member and method names are invented; the offsets
// and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

extern "C" void* __cdecl memcpy(void* Dest, const void* Source, unsigned int Count);

class UnkType_1099da60
{
public:
    UnkType_1099da60& Unk_1099da60(const UnkType_1099da60& Other);

    void Realloc()
    {
        unk_00 = (unsigned short*)GUnk_111c88a0->Realloc(
            unk_00, unk_08 * sizeof(unsigned short), L"FArray::_WORD");
    }

    const unsigned short* operator*() const
    {
        return unk_04 ? unk_00 : L"";
    }

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1099da60::Unk_1099da60
UnkType_1099da60& UnkType_1099da60::Unk_1099da60(const UnkType_1099da60& Other)
{
    if ( this != &Other )
    {
        unk_04 = unk_08 = Other.unk_04;
        Realloc();
        if ( unk_04 )
        {
            memcpy(unk_00, *Other, unk_04 * sizeof(unsigned short));
        }
    }
    return *this;
}
