// campaign_leaf_153b70.cpp -- one function at file offset 0x153b70, preferred VA 0x10a53b70.
// A destructor of a class two levels above the object base: each level installs its virtual table
// and calls the base's method at VA 0x10cd7a30. The most derived level destroys the array at offset
// 0x164 (its method at VA 0x10a50e60 removes every element), the array at offset 0xe4 (its method
// at VA 0x10a50dd0 removes every element), the array at offset 0xd8 (its method at VA 0x10a50dd0
// removes every element), the array at offset 0xcc (its method at VA 0x109a6fa0 removes every
// element), the array at offset 0xc0 (its method at VA 0x10a50d40 removes every element), the array
// at offset 0xb4 (its method at VA 0x10a50cb0 removes every element), the array at offset 0xa8 (its
// method at VA 0x10a50c20 removes every element), the array at offset 0x9c (its method at VA
// 0x10a50b90 removes every element), the array at offset 0x90 (its method at VA 0x10a50b00 removes
// every element), freeing each block through the allocator at VA 0x111c88a0, and the base
// destructor at VA 0x10cdc460 runs last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a53b70_Object
{
public:
    virtual ~UnkType_10a53b70_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a53b70_Base : public UnkType_10a53b70_Object
{
public:
    unsigned char unk_28[0x90 - 0x28];

    virtual ~UnkType_10a53b70_Base()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a53b70_ArrayA
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_109a6fa0(int Index, int Count, int ElementSize);

    ~UnkType_10a53b70_ArrayA()
    {
        Unk_109a6fa0(0, ArrayNum, 16);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a53b70_ArrayB
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a50b00(int Index, int Count, int ElementSize);

    ~UnkType_10a53b70_ArrayB()
    {
        Unk_10a50b00(0, ArrayNum, 72);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a53b70_ArrayC
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a50b90(int Index, int Count, int ElementSize);

    ~UnkType_10a53b70_ArrayC()
    {
        Unk_10a50b90(0, ArrayNum, 12);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a53b70_ArrayD
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a50c20(int Index, int Count, int ElementSize);

    ~UnkType_10a53b70_ArrayD()
    {
        Unk_10a50c20(0, ArrayNum, 16);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a53b70_ArrayE
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a50cb0(int Index, int Count, int ElementSize);

    ~UnkType_10a53b70_ArrayE()
    {
        Unk_10a50cb0(0, ArrayNum, 28);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a53b70_ArrayF
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a50d40(int Index, int Count, int ElementSize);

    ~UnkType_10a53b70_ArrayF()
    {
        Unk_10a50d40(0, ArrayNum, 16);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a53b70_ArrayG
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a50dd0(int Index, int Count, int ElementSize);

    ~UnkType_10a53b70_ArrayG()
    {
        Unk_10a50dd0(0, ArrayNum, 8);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a53b70_ArrayH
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a50e60(int Index, int Count, int ElementSize);

    ~UnkType_10a53b70_ArrayH()
    {
        Unk_10a50e60(0, ArrayNum, 28);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a53b70 : public UnkType_10a53b70_Base
{
public:
    UnkType_10a53b70_ArrayB unk_90;
    UnkType_10a53b70_ArrayC unk_9c;
    UnkType_10a53b70_ArrayD unk_a8;
    UnkType_10a53b70_ArrayE unk_b4;
    UnkType_10a53b70_ArrayF unk_c0;
    UnkType_10a53b70_ArrayA unk_cc;
    UnkType_10a53b70_ArrayG unk_d8;
    UnkType_10a53b70_ArrayG unk_e4;
    unsigned char unk_f0[0x164 - 0xf0];
    UnkType_10a53b70_ArrayH unk_164;

    virtual ~UnkType_10a53b70();
};

// UnkType_10a53b70::~UnkType_10a53b70
UnkType_10a53b70::~UnkType_10a53b70()
{
    Unk_10cd7a30();
}
