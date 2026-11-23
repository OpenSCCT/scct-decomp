// campaign_leaf_100c50.cpp -- one function at file offset 0x100c50, preferred VA 0x10a00c50.
// A destructor: it destroys the array at offset 0x30 (its method at VA 0x109fe690 removes every
// element) and the array of 2-byte elements at offset 0x18 (method at VA 0x10907710), the
// allocator at VA 0x111c88a0 freeing each block.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a00c50_ArrayWords
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10907710(int Index, int Count, int ElementSize);

    ~UnkType_10a00c50_ArrayWords()
    {
        Unk_10907710(0, ArrayNum, 2);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a00c50_ArrayItems
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_109fe690(int Index, int Count);

    ~UnkType_10a00c50_ArrayItems()
    {
        Unk_109fe690(0, ArrayNum);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a00c50
{
public:
    unsigned char unk_0[0x18];
    UnkType_10a00c50_ArrayWords unk_18;
    unsigned char unk_24[0x30 - 0x24];
    UnkType_10a00c50_ArrayItems unk_30;

    ~UnkType_10a00c50();
};

// UnkType_10a00c50::~UnkType_10a00c50
UnkType_10a00c50::~UnkType_10a00c50()
{
}
