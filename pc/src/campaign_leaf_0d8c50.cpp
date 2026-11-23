// campaign_leaf_0d8c50.cpp -- method at VA 0x109d8c50 assigning one dynamic array of bytes (data
// pointer at 0x00, count at 0x04, capacity at 0x08) to another one byte at a time: unless both are
// the same object, zeroes the count, frees the data through virtual slot 2 of the allocator global
// at VA 0x111c88a0 and clears the pointer, then appends every byte of the other, each time raising
// the count and calling the method at VA 0x10ccb3c0 with the element size 1; returns the array. The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109d8c50
{
public:
    UnkType_109d8c50& Unk_109d8c50(const UnkType_109d8c50& Other);
    void Unk_10ccb3c0(int ElementSize);

    int Add()
    {
        int Index = unk_04;
        unk_04++;
        Unk_10ccb3c0(sizeof(unsigned char));
        return Index;
    }

    unsigned char* unk_00;
    int unk_04;
    int unk_08;
};

inline void* operator new(unsigned int, UnkType_109d8c50& Array)
{
    int Index = Array.Add();
    return &Array.unk_00[Index];
}

// UnkType_109d8c50::Unk_109d8c50
UnkType_109d8c50& UnkType_109d8c50::Unk_109d8c50(const UnkType_109d8c50& Other)
{
    if ( this != &Other )
    {
        unk_04 = 0;
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        for ( int i = 0; i < Other.unk_04; i++ )
        {
            new(*this) unsigned char(Other.unk_00[i]);
        }
    }
    return *this;
}
