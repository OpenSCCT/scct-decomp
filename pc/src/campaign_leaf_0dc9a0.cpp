// campaign_leaf_0dc9a0.cpp -- method at VA 0x109dc9a0 assigning one dynamic array of 0x3c-byte
// records (data pointer at 0x00, count at 0x04) to another one record at a time: unless both are
// the same object, zeroes the count, frees the data through virtual slot 2 of the allocator global
// at VA 0x111c88a0 and clears the pointer, then appends a copy of every record of the other, each
// time raising the count and calling the method at VA 0x10ccb3c0 with the element size; returns the
// array. The class, member and method names are invented; the offsets and the addresses are the
// binary's.

#include "campaign_global_111c88a0.h"

struct UnkType_109dc9a0_Record
{
    unsigned char unk_00[0x3c];
};

class UnkType_109dc9a0
{
public:
    UnkType_109dc9a0& Unk_109dc9a0(const UnkType_109dc9a0& Other);
    void Unk_10ccb3c0(int ElementSize);

    int Add()
    {
        int Index = unk_04;
        unk_04++;
        Unk_10ccb3c0(sizeof(UnkType_109dc9a0_Record));
        return Index;
    }

    UnkType_109dc9a0_Record* unk_00;
    int unk_04;
};

inline void* operator new(unsigned int, UnkType_109dc9a0& Array)
{
    int Index = Array.Add();
    return &Array.unk_00[Index];
}

// UnkType_109dc9a0::Unk_109dc9a0
UnkType_109dc9a0& UnkType_109dc9a0::Unk_109dc9a0(const UnkType_109dc9a0& Other)
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
            new(*this) UnkType_109dc9a0_Record(Other.unk_00[i]);
        }
    }
    return *this;
}
