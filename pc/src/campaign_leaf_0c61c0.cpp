// campaign_leaf_0c61c0.cpp -- method at VA 0x109c61c0 of a dynamic array of 12-byte dynamic arrays
// taking an index and a count: destroys each element in that range (method at VA 0x109c1190 with 0
// and its count, then frees its data through virtual slot 2 of the allocator global at VA
// 0x111c88a0), then calls the method at VA 0x109bf4e0 with the index, the count and the element
// size. guess: an instance of the engine's TArray<T>::Remove. The class, member and method names
// are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109c61c0_Element
{
public:
    ~UnkType_109c61c0_Element()
    {
        Unk_109c1190(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109c1190(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c61c0
{
public:
    void Unk_109c61c0(int Index, int Count);
    void Unk_109bf4e0(int Index, int Count, int ElementSize);

private:
    UnkType_109c61c0_Element* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_109c61c0::Unk_109c61c0
void UnkType_109c61c0::Unk_109c61c0(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_109c61c0_Element();
    }
    Unk_109bf4e0(Index, Count, sizeof(UnkType_109c61c0_Element));
}
