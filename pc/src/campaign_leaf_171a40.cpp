// campaign_leaf_171a40.cpp -- one function at file offset 0x171a40, preferred VA 0x10a71a40.
// A destructor of a class two levels above the object base: each level installs its virtual table
// and calls the base's method at VA 0x10cd7a30. The most derived level destroys the array at offset
// 0x98 (its method at VA 0x10a712c0 removes every element), the array at offset 0x6c (its method at
// VA 0x10907710 removes every element), freeing each block through the allocator at VA 0x111c88a0,
// and the base destructor at VA 0x10cdc460 runs last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a71a40_Object
{
public:
    virtual ~UnkType_10a71a40_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a71a40_Base : public UnkType_10a71a40_Object
{
public:
    unsigned char unk_28[0x6c - 0x28];

    virtual ~UnkType_10a71a40_Base()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a71a40_ArrayA
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10907710(int Index, int Count, int ElementSize);

    ~UnkType_10a71a40_ArrayA()
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

class UnkType_10a71a40_ArrayB
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a712c0(int Index, int Count, int ElementSize);

    ~UnkType_10a71a40_ArrayB()
    {
        Unk_10a712c0(0, ArrayNum, 28);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a71a40 : public UnkType_10a71a40_Base
{
public:
    UnkType_10a71a40_ArrayA unk_6c;
    unsigned char unk_78[0x98 - 0x78];
    UnkType_10a71a40_ArrayB unk_98;

    virtual ~UnkType_10a71a40();
};

// UnkType_10a71a40::~UnkType_10a71a40
UnkType_10a71a40::~UnkType_10a71a40()
{
    Unk_10cd7a30();
}
