// campaign_leaf_12a690.cpp -- one function at file offset 0x12a690, preferred VA 0x10a2a690.
// A destructor of a class two levels above the object base: each level installs its virtual table
// and calls the base's method at VA 0x10cd7a30. The most derived level destroys the array at offset
// 0x38 (its method at VA 0x10a29500 removes every element), the array at offset 0x2c (its method at
// VA 0x10a29470 removes every element), freeing each block through the allocator at VA 0x111c88a0,
// and the base destructor at VA 0x10cdc460 runs last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a2a690_Object
{
public:
    virtual ~UnkType_10a2a690_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a2a690_Base : public UnkType_10a2a690_Object
{
public:
    unsigned char unk_28[0x2c - 0x28];

    virtual ~UnkType_10a2a690_Base()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a2a690_ArrayA
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a29470(int Index, int Count, int ElementSize);

    ~UnkType_10a2a690_ArrayA()
    {
        Unk_10a29470(0, ArrayNum, 8);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a2a690_ArrayB
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a29500(int Index, int Count, int ElementSize);

    ~UnkType_10a2a690_ArrayB()
    {
        Unk_10a29500(0, ArrayNum, 16);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a2a690 : public UnkType_10a2a690_Base
{
public:
    UnkType_10a2a690_ArrayA unk_2c;
    UnkType_10a2a690_ArrayB unk_38;

    virtual ~UnkType_10a2a690();
};

// UnkType_10a2a690::~UnkType_10a2a690
UnkType_10a2a690::~UnkType_10a2a690()
{
    Unk_10cd7a30();
}
