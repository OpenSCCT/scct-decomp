// campaign_leaf_0c46f0.cpp -- method at VA 0x109c46f0 of a dynamic array of 12-byte dynamic arrays:
// destroys every element (method at VA 0x109beb60 with 0, its count and the element size 4, then
// frees its data through virtual slot 2 of the allocator global at VA 0x111c88a0), zeroes the
// count, stores its argument as the capacity and calls the method at VA 0x109b8030 with the element
// size. guess: an instance of the engine's TArray<T>::Empty. The class, member and method names are
// invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109c46f0_Element
{
public:
    ~UnkType_109c46f0_Element()
    {
        Unk_109beb60(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109beb60(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c46f0
{
public:
    void Unk_109c46f0(int Slack);
    void Unk_109b8030(int ElementSize);

private:
    UnkType_109c46f0_Element* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_109c46f0::Unk_109c46f0
void UnkType_109c46f0::Unk_109c46f0(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_109c46f0_Element();
    }
    unk_04 = 0;
    unk_08 = Slack;
    Unk_109b8030(sizeof(UnkType_109c46f0_Element));
}
