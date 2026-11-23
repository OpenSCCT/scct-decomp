// campaign_leaf_12f800.cpp -- one function at file offset 0x12f800, preferred VA 0x10a2f800.
// A destructor: it installs its class's virtual table, calls the base's method at VA 0x10cd7a30,
// destroys the member at offset 0xcc (destructor at VA 0x10ade980), the array at offset 0x98 (its
// method at VA 0x10929170 removes every element), the array at offset 0x8c (its method at VA
// 0x10929170 removes every element), the array at offset 0x58 (its method at VA 0x1090d050 removes
// every element), the array at offset 0x4c (its method at VA 0x10a2f110 removes every element), the
// array at offset 0x40 (its method at VA 0x109beb60 removes every element), the array at offset
// 0x34 (its method at VA 0x109beb60 removes every element), the array at offset 0x28 (its method at
// VA 0x109beb60 removes every element), freeing each block through the allocator at VA 0x111c88a0,
// and the base destructor at VA 0x10cdc460 runs last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a2f800_Object
{
public:
    virtual ~UnkType_10a2f800_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a2f800_ArrayA
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_1090d050(int Index, int Count);

    ~UnkType_10a2f800_ArrayA()
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

class UnkType_10a2f800_ArrayB
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10929170(int Index, int Count, int ElementSize);

    ~UnkType_10a2f800_ArrayB()
    {
        Unk_10929170(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a2f800_ArrayC
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_109beb60(int Index, int Count, int ElementSize);

    ~UnkType_10a2f800_ArrayC()
    {
        Unk_109beb60(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a2f800_ArrayD
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a2f110(int Index, int Count, int ElementSize);

    ~UnkType_10a2f800_ArrayD()
    {
        Unk_10a2f110(0, ArrayNum, 20);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a2f800_Member
{
public:
    int unk_0;

    ~UnkType_10a2f800_Member();
};

class UnkType_10a2f800 : public UnkType_10a2f800_Object
{
public:
    UnkType_10a2f800_ArrayC unk_28;
    UnkType_10a2f800_ArrayC unk_34;
    UnkType_10a2f800_ArrayC unk_40;
    UnkType_10a2f800_ArrayD unk_4c;
    UnkType_10a2f800_ArrayA unk_58;
    unsigned char unk_64[0x8c - 0x64];
    UnkType_10a2f800_ArrayB unk_8c;
    UnkType_10a2f800_ArrayB unk_98;
    unsigned char unk_a4[0xcc - 0xa4];
    UnkType_10a2f800_Member unk_cc;

    virtual ~UnkType_10a2f800();
};

// UnkType_10a2f800::~UnkType_10a2f800
UnkType_10a2f800::~UnkType_10a2f800()
{
    Unk_10cd7a30();
}
