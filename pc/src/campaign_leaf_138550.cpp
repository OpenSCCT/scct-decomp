// campaign_leaf_138550.cpp -- one function at file offset 0x138550, preferred VA 0x10a38550.
// It appends the double its argument refers to to an array of doubles, growing the block through
// the allocator at VA 0x111c88a0 (tag "FArray"), and returns the new element's index.
// The class, method and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a38550
{
public:
    double* Data;
    int ArrayNum;
    int ArrayMax;

    int Unk_10a38550(const double& Item);
};

// UnkType_10a38550::Unk_10a38550
int UnkType_10a38550::Unk_10a38550(const double& Item)
{
    int Index = ArrayNum;
    if ( ++ArrayNum > ArrayMax )
    {
        ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 2;
        Data = (double*)GUnk_111c88a0->Realloc(Data, ArrayMax * sizeof(double), L"FArray");
    }
    Data[Index] = Item;
    return Index;
}
