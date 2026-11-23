// campaign_leaf_0b8220.cpp -- method at VA 0x109b8220 of a dynamic array of wide characters (data
// pointer at 0x00, count at 0x04, capacity at 0x08): when the capacity differs from the count, sets
// it to the count and reallocates the data through virtual slot 1 of the allocator global at VA
// 0x111c88a0 with the tag "FArray::_WORD". guess: the engine's TArray<TCHAR>::Shrink. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109b8220
{
public:
    void Unk_109b8220();
    void Realloc()
    {
        unk_00 = (unsigned short*)GUnk_111c88a0->Realloc(
            unk_00, unk_08 * sizeof(unsigned short), L"FArray::_WORD");
    }

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_109b8220::Unk_109b8220
void UnkType_109b8220::Unk_109b8220()
{
    if ( unk_08 != unk_04 )
    {
        unk_08 = unk_04;
        Realloc();
    }
}
