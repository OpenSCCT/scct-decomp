// campaign_leaf_0be6a0.cpp -- method at VA 0x109be6a0 assigning one dynamic array of wide
// characters (data pointer at 0x00, count at 0x04, capacity at 0x08) to another one character at a
// time: unless both are the same object, sets the count to 0 and the capacity to the other's count,
// reallocates the data through virtual slot 1 of the allocator global at VA 0x111c88a0 with the tag
// "FArray::_WORD", then appends every character of the other, growing the capacity to the count
// plus three eighths of it plus 2 when it runs out; returns the array. guess: an instance of the
// engine's TArray<TCHAR> assignment. The class, member and method names are invented; the offsets
// and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109be6a0
{
public:
    UnkType_109be6a0& Unk_109be6a0(const UnkType_109be6a0& Other);
    void Realloc()
    {
        unk_00 = (unsigned short*)GUnk_111c88a0->Realloc(
            unk_00, unk_08 * sizeof(unsigned short), L"FArray::_WORD");
    }

    void Empty(int Slack)
    {
        unk_04 = 0;
        unk_08 = Slack;
        Realloc();
    }

    int Add()
    {
        int Index = unk_04;
        if ( ++unk_04 > unk_08 )
        {
            unk_08 = unk_04 + 3 * unk_04 / 8 + 2;
            Realloc();
        }
        return Index;
    }

    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

inline void* operator new(unsigned int, UnkType_109be6a0& Array)
{
    int Index = Array.Add();
    return &Array.unk_00[Index];
}

// UnkType_109be6a0::Unk_109be6a0
UnkType_109be6a0& UnkType_109be6a0::Unk_109be6a0(const UnkType_109be6a0& Other)
{
    if ( this != &Other )
    {
        Empty(Other.unk_04);
        for ( int i = 0; i < Other.unk_04; i++ )
        {
            new(*this) unsigned short(Other.unk_00[i]);
        }
    }
    return *this;
}
