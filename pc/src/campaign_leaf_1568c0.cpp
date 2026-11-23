// campaign_leaf_1568c0.cpp -- one function at file offset 0x1568c0, preferred VA 0x10a568c0.
// A destructor of a class two levels above the object base: each level installs its virtual table;
// the base level calls the base's method at VA 0x10cd7a30. The most derived level frees the block
// at offset 0x54 and destroys the arrays at offsets 0x94 and 0x70 (their methods at VA 0x10907710
// and VA 0x10a54a40 remove every element), freeing each block through the allocator at
// VA 0x111c88a0, and the base destructor at VA 0x10cdc460 runs last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a568c0_Object
{
public:
    virtual ~UnkType_10a568c0_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a568c0_Base : public UnkType_10a568c0_Object
{
public:
    unsigned char unk_28[0x54 - 0x28];
    void* unk_54;
    unsigned char unk_58[0x70 - 0x58];

    virtual ~UnkType_10a568c0_Base()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a568c0_ArrayA
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10907710(int Index, int Count, int ElementSize);

    ~UnkType_10a568c0_ArrayA()
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

class UnkType_10a568c0_ArrayB
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a54a40(int Index, int Count, int ElementSize);

    ~UnkType_10a568c0_ArrayB()
    {
        Unk_10a54a40(0, ArrayNum, 28);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a568c0 : public UnkType_10a568c0_Base
{
public:
    UnkType_10a568c0_ArrayB unk_70;
    unsigned char unk_7c[0x94 - 0x7c];
    UnkType_10a568c0_ArrayA unk_94;

    virtual ~UnkType_10a568c0();
};

// UnkType_10a568c0::~UnkType_10a568c0
UnkType_10a568c0::~UnkType_10a568c0()
{
    if ( unk_54 )
    {
        GUnk_111c88a0->Free(unk_54);
    }
}
