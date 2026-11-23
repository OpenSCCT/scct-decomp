// campaign_leaf_0c4320.cpp -- virtual destructor at VA 0x109c4320 (vtable at VA 0x110ce298): calls
// the method at VA 0x10cd7a30, then destroys the dynamic array at 0x19c (method at VA 0x10907710,
// element size 2), the dynamic array at 0x170 (method at VA 0x10907710, element size 2), the
// dynamic array at 0x144 (method at VA 0x10907710, element size 2), the dynamic array at 0x10c
// (method at VA 0x109bf190, element size 28), the 0x3c-byte member at 0xd0 (destructor at VA
// 0x109bfea0), the 0x18-byte member at 0xb8 (destructor at VA 0x109c0f70), the two-word dynamic
// array at 0xa8 (method at VA 0x10ccb3f0, element size 4), the two-word dynamic array at 0xa0
// (method at VA 0x10ccb3f0, element size 12), the dynamic array at 0x94 (method at VA 0x109c0020),
// the two-word dynamic array at 0x8c (method at VA 0x109bffa0), the two-word dynamic array at 0x84
// (method at VA 0x10ccb3f0, element size 1), the dynamic array at 0x78 (method at VA 0x10929170,
// element size 4), the dynamic array at 0x6c (method at VA 0x10929170, element size 4), the dynamic
// array at 0x60 (method at VA 0x109bf310, element size 28), the dynamic array at 0x54 (method at VA
// 0x109bf310, element size 28); then the inline destructor of base class 1 (vtable at VA
// 0x110c0b98) calls it; each array is passed 0 and its count, then its data is freed through
// virtual slot 2 of the allocator global at VA 0x111c88a0; it ends in the outermost base destructor
// at VA 0x10cdc460. The class, member and method names are invented; the offsets and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109c4320_Array1
{
public:
    ~UnkType_109c4320_Array1()
    {
        Unk_10907710(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10907710(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c4320_Array2
{
public:
    ~UnkType_109c4320_Array2()
    {
        Unk_109bf190(0, unk_04, 28);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109bf190(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c4320_Object3
{
public:
    ~UnkType_109c4320_Object3();

private:
    unsigned char unk_00[0x3c];
};

class UnkType_109c4320_Object4
{
public:
    virtual ~UnkType_109c4320_Object4();

private:
    unsigned char unk_04[0x18 - 0x04];
};

class UnkType_109c4320_Array5
{
public:
    ~UnkType_109c4320_Array5()
    {
        Unk_10ccb3f0(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = 0;
    }

    void Unk_10ccb3f0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
};

class UnkType_109c4320_Array6
{
public:
    ~UnkType_109c4320_Array6()
    {
        Unk_10ccb3f0(0, unk_04, 12);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = 0;
    }

    void Unk_10ccb3f0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
};

class UnkType_109c4320_Array7
{
public:
    ~UnkType_109c4320_Array7()
    {
        Unk_109c0020(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109c0020(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c4320_Array8
{
public:
    ~UnkType_109c4320_Array8()
    {
        Unk_109bffa0(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = 0;
    }

    void Unk_109bffa0(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
};

class UnkType_109c4320_Array9
{
public:
    ~UnkType_109c4320_Array9()
    {
        Unk_10ccb3f0(0, unk_04, 1);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = 0;
    }

    void Unk_10ccb3f0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
};

class UnkType_109c4320_Array10
{
public:
    ~UnkType_109c4320_Array10()
    {
        Unk_10929170(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929170(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c4320_Array11
{
public:
    ~UnkType_109c4320_Array11()
    {
        Unk_109bf310(0, unk_04, 28);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109bf310(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c4320_Base
{
public:
    virtual ~UnkType_109c4320_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x54 - 0x04];
};

class UnkType_109c4320_Level1 : public UnkType_109c4320_Base
{
public:
    virtual ~UnkType_109c4320_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109c4320 : public UnkType_109c4320_Level1
{
public:
    virtual ~UnkType_109c4320();

private:
    UnkType_109c4320_Array11 unk_54;
    UnkType_109c4320_Array11 unk_60;
    UnkType_109c4320_Array10 unk_6c;
    UnkType_109c4320_Array10 unk_78;
    UnkType_109c4320_Array9 unk_84;
    UnkType_109c4320_Array8 unk_8c;
    UnkType_109c4320_Array7 unk_94;
    UnkType_109c4320_Array6 unk_a0;
    UnkType_109c4320_Array5 unk_a8;
    unsigned char unk_b0[0xb8 - 0xb0];
    UnkType_109c4320_Object4 unk_b8;
    UnkType_109c4320_Object3 unk_d0;
    UnkType_109c4320_Array2 unk_10c;
    unsigned char unk_118[0x144 - 0x118];
    UnkType_109c4320_Array1 unk_144;
    unsigned char unk_150[0x170 - 0x150];
    UnkType_109c4320_Array1 unk_170;
    unsigned char unk_17c[0x19c - 0x17c];
    UnkType_109c4320_Array1 unk_19c;
};

// UnkType_109c4320::~UnkType_109c4320
UnkType_109c4320::~UnkType_109c4320()
{
    Unk_10cd7a30();
}
