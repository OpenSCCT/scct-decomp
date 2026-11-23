// campaign_leaf_0eabd0.cpp -- method at VA 0x109eabd0 of a dynamic array (data pointer at 0x00,
// count at 0x04, capacity at 0x08) of 0x18-byte elements: runs the destructor at VA 0x109e0e20 on
// every element, stores its argument as the capacity, zeroes the count and reallocates the data to
// the new capacity through the allocator global at VA 0x111c88a0 with the tag "FArray". guess: an
// instance of the engine's TArray<T>::Empty. The class, member and method names are invented; the
// offsets, the sizes and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109eabd0_Element
{
public:
    ~UnkType_109eabd0_Element();

private:
    unsigned char unk_00[0x18];
};

class UnkType_109eabd0
{
public:
    void Unk_109eabd0(int Slack);

private:
    UnkType_109eabd0_Element* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_109eabd0::Unk_109eabd0
void UnkType_109eabd0::Unk_109eabd0(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_109eabd0_Element();
    }
    unk_08 = Slack;
    unk_04 = 0;
    unk_00 = (UnkType_109eabd0_Element*)GUnk_111c88a0->Realloc(
        unk_00, Slack * sizeof(UnkType_109eabd0_Element), L"FArray");
}
