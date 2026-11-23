// campaign_leaf_0b8340.cpp -- method at VA 0x109b8340 assigning one dynamic array of 2-byte words
// (data pointer at 0x00, count at 0x04) to another one word at a time: unless both are the same
// object, zeroes the count, frees the data through virtual slot 2 of the allocator global at VA
// 0x111c88a0 and clears the pointer, then appends every word of the other, each time raising the
// count and calling the method at VA 0x10ccb3c0 with the element size 2; returns the array. The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109b8340
{
public:
    UnkType_109b8340& Unk_109b8340(const UnkType_109b8340& Other);
    void Unk_10ccb3c0(int ElementSize);

    int Add()
    {
        int Index = unk_04;
        unk_04++;
        Unk_10ccb3c0(sizeof(unsigned short));
        return Index;
    }

    unsigned short* unk_00;
    int unk_04;
};

inline void* operator new(unsigned int, UnkType_109b8340& Array)
{
    int Index = Array.Add();
    return &Array.unk_00[Index];
}

// UnkType_109b8340::Unk_109b8340
UnkType_109b8340& UnkType_109b8340::Unk_109b8340(const UnkType_109b8340& Other)
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
            new(*this) unsigned short(Other.unk_00[i]);
        }
    }
    return *this;
}
