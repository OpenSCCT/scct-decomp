// campaign_leaf_100390.cpp -- one function at file offset 0x100390, preferred VA 0x10a00390.
// A destructor: it installs its class's virtual table, calls the base's method at VA 0x10cd7a30,
// destroys the array at offset 0x44 (its method at VA 0x109f34e0 removes every element), the array
// at offset 0x38 (its method at VA 0x109fd520 removes every element), the array at offset 0x2c (its
// method at VA 0x109e0aa0 removes every element), freeing each block through the allocator at VA
// 0x111c88a0, and the base destructor at VA 0x10cdc460 runs last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a00390_Object
{
public:
    virtual ~UnkType_10a00390_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a00390_ArrayA
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_109e0aa0(int Index, int Count, int ElementSize);

    ~UnkType_10a00390_ArrayA()
    {
        Unk_109e0aa0(0, ArrayNum, 12);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a00390_ArrayB
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_109f34e0(int Index, int Count);

    ~UnkType_10a00390_ArrayB()
    {
        Unk_109f34e0(0, ArrayNum);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a00390_ArrayC
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_109fd520(int Index, int Count);

    ~UnkType_10a00390_ArrayC()
    {
        Unk_109fd520(0, ArrayNum);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a00390 : public UnkType_10a00390_Object
{
public:
    unsigned char unk_28[0x2c - 0x28];
    UnkType_10a00390_ArrayA unk_2c;
    UnkType_10a00390_ArrayC unk_38;
    UnkType_10a00390_ArrayB unk_44;

    virtual ~UnkType_10a00390();
};

// UnkType_10a00390::~UnkType_10a00390
UnkType_10a00390::~UnkType_10a00390()
{
    Unk_10cd7a30();
}
