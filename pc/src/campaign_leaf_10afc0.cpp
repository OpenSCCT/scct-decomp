// campaign_leaf_10afc0.cpp -- one function at file offset 0x10afc0, preferred VA 0x10a0afc0.
// A destructor: it destroys the arrays of 12-byte elements at offsets 0x1c and 0x10 (the method at
// VA 0x10929260 removes every element, the allocator at VA 0x111c88a0 frees each block).
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a0afc0_Array
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10929260(int Index, int Count, int ElementSize);

    ~UnkType_10a0afc0_Array()
    {
        Unk_10929260(0, ArrayNum, 12);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a0afc0
{
public:
    unsigned char unk_0[0x10];
    UnkType_10a0afc0_Array unk_10;
    UnkType_10a0afc0_Array unk_1c;

    ~UnkType_10a0afc0();
};

// UnkType_10a0afc0::~UnkType_10a0afc0
UnkType_10a0afc0::~UnkType_10a0afc0()
{
}
