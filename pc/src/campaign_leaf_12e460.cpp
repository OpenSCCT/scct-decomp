// campaign_leaf_12e460.cpp -- one function at file offset 0x12e460, preferred VA 0x10a2e460.
// A destructor: it installs its class's virtual table, calls the base's method at VA 0x10cd7a30,
// destroys the array at offset 0x118 (its method at VA 0x10a2d0c0 removes every element), the array
// at offset 0x108 (its method at VA 0x10929a90 removes every element), the array at offset 0xd0
// (its method at VA 0x10a2d150 removes every element), the array at offset 0x68 (its method at VA
// 0x10a2d1e0 removes every element), the array at offset 0x5c (its method at VA 0x10a2d150 removes
// every element), the array at offset 0x4c (its method at VA 0x10a2d0c0 removes every element), the
// array at offset 0x40 (its method at VA 0x10929a90 removes every element), the array at offset
// 0x34 (its method at VA 0x10929a90 removes every element), freeing each block through the
// allocator at VA 0x111c88a0, and the base destructor at VA 0x10cdc460 runs last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a2e460_Object
{
public:
    virtual ~UnkType_10a2e460_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a2e460_ArrayA
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10929a90(int Index, int Count, int ElementSize);

    ~UnkType_10a2e460_ArrayA()
    {
        Unk_10929a90(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a2e460_ArrayB
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a2d0c0(int Index, int Count, int ElementSize);

    ~UnkType_10a2e460_ArrayB()
    {
        Unk_10a2d0c0(0, ArrayNum, 12);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a2e460_ArrayC
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a2d150(int Index, int Count, int ElementSize);

    ~UnkType_10a2e460_ArrayC()
    {
        Unk_10a2d150(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a2e460_ArrayD
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a2d1e0(int Index, int Count, int ElementSize);

    ~UnkType_10a2e460_ArrayD()
    {
        Unk_10a2d1e0(0, ArrayNum, 64);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a2e460 : public UnkType_10a2e460_Object
{
public:
    unsigned char unk_28[0x34 - 0x28];
    UnkType_10a2e460_ArrayA unk_34;
    UnkType_10a2e460_ArrayA unk_40;
    UnkType_10a2e460_ArrayB unk_4c;
    unsigned char unk_58[0x5c - 0x58];
    UnkType_10a2e460_ArrayC unk_5c;
    UnkType_10a2e460_ArrayD unk_68;
    unsigned char unk_74[0xd0 - 0x74];
    UnkType_10a2e460_ArrayC unk_d0;
    unsigned char unk_dc[0x108 - 0xdc];
    UnkType_10a2e460_ArrayA unk_108;
    unsigned char unk_114[0x118 - 0x114];
    UnkType_10a2e460_ArrayB unk_118;

    virtual ~UnkType_10a2e460();
};

// UnkType_10a2e460::~UnkType_10a2e460
UnkType_10a2e460::~UnkType_10a2e460()
{
    Unk_10cd7a30();
}
