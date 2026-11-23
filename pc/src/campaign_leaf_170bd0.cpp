// campaign_leaf_170bd0.cpp -- one function at file offset 0x170bd0, preferred VA 0x10a70bd0.
// A destructor of a class two levels above its root class: each level installs its virtual table
// and calls the base's method at VA 0x10cd7a30. The most derived level destroys the array at offset
// 0x924 (its method at VA 0x10907710 removes every element), the array at offset 0x914 (its method
// at VA 0x109b8410 removes every element), the array at offset 0x908 (its method at VA 0x109b8410
// removes every element), the array at offset 0x8f8 (its method at VA 0x10a6f4d0 removes every
// element), the array at offset 0x88c (its method at VA 0x10a6f440 removes every element), the
// array at offset 0x86c (its method at VA 0x10929260 removes every element), the array at offset
// 0x860 (its method at VA 0x10a6f3b0 removes every element), the array at offset 0x854 (its method
// at VA 0x10a708e0 removes every element), the array at offset 0x844 (its method at VA 0x10a6f290
// removes every element), freeing each block through the allocator at VA 0x111c88a0, and the base
// destructor at VA 0x1092ad20 runs last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a70bd0_Root
{
public:
    virtual ~UnkType_10a70bd0_Root();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a70bd0_Base : public UnkType_10a70bd0_Root
{
public:
    unsigned char unk_28[0x844 - 0x28];

    virtual ~UnkType_10a70bd0_Base()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a70bd0_ArrayA
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10907710(int Index, int Count, int ElementSize);

    ~UnkType_10a70bd0_ArrayA()
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

class UnkType_10a70bd0_ArrayB
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10929260(int Index, int Count, int ElementSize);

    ~UnkType_10a70bd0_ArrayB()
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

class UnkType_10a70bd0_ArrayC
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_109b8410(int Index, int Count, int ElementSize);

    ~UnkType_10a70bd0_ArrayC()
    {
        Unk_109b8410(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a70bd0_ArrayD
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a6f290(int Index, int Count, int ElementSize);

    ~UnkType_10a70bd0_ArrayD()
    {
        Unk_10a6f290(0, ArrayNum, 80);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a70bd0_ArrayE
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a6f3b0(int Index, int Count, int ElementSize);

    ~UnkType_10a70bd0_ArrayE()
    {
        Unk_10a6f3b0(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a70bd0_ArrayF
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a6f440(int Index, int Count, int ElementSize);

    ~UnkType_10a70bd0_ArrayF()
    {
        Unk_10a6f440(0, ArrayNum, 24);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a70bd0_ArrayG
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a6f4d0(int Index, int Count, int ElementSize);

    ~UnkType_10a70bd0_ArrayG()
    {
        Unk_10a6f4d0(0, ArrayNum, 20);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a70bd0_ArrayH
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a708e0(int Index, int Count);

    ~UnkType_10a70bd0_ArrayH()
    {
        Unk_10a708e0(0, ArrayNum);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a70bd0 : public UnkType_10a70bd0_Base
{
public:
    UnkType_10a70bd0_ArrayD unk_844;
    unsigned char unk_850[0x854 - 0x850];
    UnkType_10a70bd0_ArrayH unk_854;
    UnkType_10a70bd0_ArrayE unk_860;
    UnkType_10a70bd0_ArrayB unk_86c;
    unsigned char unk_878[0x88c - 0x878];
    UnkType_10a70bd0_ArrayF unk_88c;
    unsigned char unk_898[0x8f8 - 0x898];
    UnkType_10a70bd0_ArrayG unk_8f8;
    unsigned char unk_904[0x908 - 0x904];
    UnkType_10a70bd0_ArrayC unk_908;
    UnkType_10a70bd0_ArrayC unk_914;
    unsigned char unk_920[0x924 - 0x920];
    UnkType_10a70bd0_ArrayA unk_924;

    virtual ~UnkType_10a70bd0();
};

// UnkType_10a70bd0::~UnkType_10a70bd0
UnkType_10a70bd0::~UnkType_10a70bd0()
{
    Unk_10cd7a30();
}
