// campaign_leaf_0d7530.cpp -- method at VA 0x109d7530 of a dynamic array (data pointer at 0x00,
// count at 0x04): zeroes the count, frees the data through virtual slot 2 of the allocator global
// at VA 0x111c88a0 and clears the pointer. guess: an instance of the engine's TArray<T>::Empty.
// The class, member and method names are invented; the offsets and the address are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109d7530
{
public:
    void Unk_109d7530();

private:
    void* unk_00;
    int unk_04;
};

// UnkType_109d7530::Unk_109d7530
void UnkType_109d7530::Unk_109d7530()
{
    unk_04 = 0;
    if ( unk_00 )
    {
        GUnk_111c88a0->Free(unk_00);
    }
    unk_00 = 0;
}
