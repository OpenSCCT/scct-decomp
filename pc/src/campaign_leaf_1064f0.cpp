// campaign_leaf_1064f0.cpp -- one function at file offset 0x1064f0, preferred VA 0x10a064f0.
// A destructor: it destroys the strings at offsets 0x34, 0x1c, 0xc and 0 with the destructor at
// VA 0x1090ba70 and, between them, the array at offset 0x28 (its method at VA 0x1090d050 removes
// every element, the allocator at VA 0x111c88a0 frees the block).
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a064f0_String
{
public:
    void* unk_0;
    int unk_4;
    int unk_8;

    ~UnkType_10a064f0_String();
};

class UnkType_10a064f0_Array
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_1090d050(int Index, int Count);

    ~UnkType_10a064f0_Array()
    {
        Unk_1090d050(0, ArrayNum);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a064f0
{
public:
    UnkType_10a064f0_String unk_0;
    UnkType_10a064f0_String unk_c;
    int unk_18;
    UnkType_10a064f0_String unk_1c;
    UnkType_10a064f0_Array unk_28;
    UnkType_10a064f0_String unk_34;

    ~UnkType_10a064f0();
};

// UnkType_10a064f0::~UnkType_10a064f0
UnkType_10a064f0::~UnkType_10a064f0()
{
}
