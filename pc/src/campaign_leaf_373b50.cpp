// campaign_leaf_373b50.cpp -- one function at file offset 0x373b50, preferred VA 0x10c73b50. It
// removes Count 12-byte elements from Index of the array at 0x0: each element is itself an array,
// whose 4-byte elements it removes with the method at 0x10929170 before freeing its data through
// the allocator at 0x111c88a0 and clearing it, and then the method at 0x10c724a0 removes the
// elements. The class, method, local and parameter names are invented; the offsets and the bytes
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10929170
{
public:
    ~UnkType_10929170()
    {
        Unk_10929170(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10929170(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c73b50
{
public:
    void Unk_10c724a0(int Index, int Count, int Size);
    void Unk_10c73b50(int Index, int Count);

    UnkType_10929170* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10c73b50::Unk_10c73b50
void UnkType_10c73b50::Unk_10c73b50(int Index, int Count)
{
    int Element;

    for ( Element = Index; Element < Index + Count; Element++ )
    {
        unk_0[Element].~UnkType_10929170();
    }
    Unk_10c724a0(Index, Count, sizeof(UnkType_10929170));
}
