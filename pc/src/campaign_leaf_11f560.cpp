// campaign_leaf_11f560.cpp -- one function at file offset 0x11f560, preferred VA 0x10a1f560.
// A destructor: it installs its class's virtual table, calls the base's method at VA 0x10cd7a30,
// destroys the array at offset 0x2ec (its method at VA 0x10a1f060 removes every element), the array
// at offset 0x214 (its method at VA 0x10a1efd0 removes every element), the string at offset 0x134
// (destructor at VA 0x1090ba70), the array at offset 0xb4 (its method at VA 0x10a1ef40 removes
// every element), the array at offset 0x6c (its method at VA 0x109a7030 removes every element),
// freeing each block through the allocator at VA 0x111c88a0, and the base destructor at VA
// 0x10cdc460 runs last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a1f560_Object
{
public:
    virtual ~UnkType_10a1f560_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a1f560_ArrayA
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_109a7030(int Index, int Count, int ElementSize);

    ~UnkType_10a1f560_ArrayA()
    {
        Unk_109a7030(0, ArrayNum, 16);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a1f560_ArrayB
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a1ef40(int Index, int Count, int ElementSize);

    ~UnkType_10a1f560_ArrayB()
    {
        Unk_10a1ef40(0, ArrayNum, 8);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a1f560_ArrayC
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a1efd0(int Index, int Count, int ElementSize);

    ~UnkType_10a1f560_ArrayC()
    {
        Unk_10a1efd0(0, ArrayNum, 8);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a1f560_ArrayD
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a1f060(int Index, int Count, int ElementSize);

    ~UnkType_10a1f560_ArrayD()
    {
        Unk_10a1f060(0, ArrayNum, 148);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a1f560_String
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    ~UnkType_10a1f560_String();
};

class UnkType_10a1f560 : public UnkType_10a1f560_Object
{
public:
    unsigned char unk_28[0x6c - 0x28];
    UnkType_10a1f560_ArrayA unk_6c;
    unsigned char unk_78[0xb4 - 0x78];
    UnkType_10a1f560_ArrayB unk_b4;
    unsigned char unk_c0[0x134 - 0xc0];
    UnkType_10a1f560_String unk_134;
    unsigned char unk_140[0x214 - 0x140];
    UnkType_10a1f560_ArrayC unk_214;
    unsigned char unk_220[0x2ec - 0x220];
    UnkType_10a1f560_ArrayD unk_2ec;

    virtual ~UnkType_10a1f560();
};

// UnkType_10a1f560::~UnkType_10a1f560
UnkType_10a1f560::~UnkType_10a1f560()
{
    Unk_10cd7a30();
}
