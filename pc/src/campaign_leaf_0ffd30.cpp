// campaign_leaf_0ffd30.cpp -- virtual destructor at VA 0x109ffd30 (vtable at VA 0x110cfc00): calls
// the method at VA 0x10cd7a30, then destroys the dynamic array at 0x2a8 (method at VA 0x10936690,
// element size 4), the dynamic array at 0x274 (method at VA 0x10966210, element size 1), the
// dynamic array at 0x268 (method at VA 0x10929a90, element size 4), the dynamic array at 0x25c
// (method at VA 0x109e0470, element size 72), the dynamic array at 0x250 (method at VA 0x109dff50,
// element size 8), the dynamic array at 0x244 (method at VA 0x109e03e0, element size 16), the
// dynamic array at 0x238 (method at VA 0x109e0350, element size 16), the dynamic array at 0x22c
// (method at VA 0x109e02c0, element size 4), the dynamic array at 0x220 (method at VA 0x109e02c0,
// element size 4), the dynamic array at 0x214 (method at VA 0x109e0230, element size 8), the
// dynamic array at 0x208 (method at VA 0x10929260, element size 12), the dynamic array at 0x1f4
// (method at VA 0x10929170, element size 4), the dynamic array at 0x194 (method at VA 0x10929260,
// element size 12), the dynamic array at 0x188 (method at VA 0x109e0110, element size 48), the
// dynamic array at 0x17c (method at VA 0x109e01a0, element size 32), the dynamic array at 0x168
// (method at VA 0x109e0110, element size 48), the two-word dynamic array at 0x120 (method at VA
// 0x109fd4a0), the dynamic array at 0xf8 (method at VA 0x10966210, element size 1), the dynamic
// array at 0xec (method at VA 0x10929260, element size 12), the dynamic array at 0xe0 (method at VA
// 0x10929260, element size 12), the dynamic array at 0xd4 (method at VA 0x109e0080, element size
// 16), the dynamic array at 0xc8 (method at VA 0x109e0080, element size 16), the two-word dynamic
// array at 0xb4 (method at VA 0x10ccb3f0, element size 96), the two-word dynamic array at 0xac
// (method at VA 0x10ccb3f0, element size 156), the two-word dynamic array at 0xa4 (method at VA
// 0x10ccb3f0, element size 156), the two-word dynamic array at 0x9c (method at VA 0x10ccb3f0,
// element size 60), the two-word dynamic array at 0x94 (method at VA 0x10ccb3f0, element size 128),
// the two-word dynamic array at 0x8c (method at VA 0x109f33e0), the two-word dynamic array at 0x80
// (method at VA 0x109eb8a0), the two-word dynamic array at 0x78 (method at VA 0x10ccb3f0, element
// size 4); then the inline destructor of base class 1 (vtable at VA 0x110cf6c8) calls it; then the
// inline destructor of base class 2 (vtable at VA 0x110cf588) calls it; then the inline destructor
// of base class 3 (vtable at VA 0x110c0b98) calls it; each array is passed 0 and its count, then
// its data is freed through virtual slot 2 of the allocator global at VA 0x111c88a0; it ends in the
// outermost base destructor at VA 0x10cdc460. The class, member and method names are invented; the
// offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109ffd30_Array1
{
public:
    ~UnkType_109ffd30_Array1()
    {
        Unk_10936690(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10936690(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array2
{
public:
    ~UnkType_109ffd30_Array2()
    {
        Unk_10966210(0, unk_04, 1);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10966210(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array3
{
public:
    ~UnkType_109ffd30_Array3()
    {
        Unk_10929a90(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929a90(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array4
{
public:
    ~UnkType_109ffd30_Array4()
    {
        Unk_109e0470(0, unk_04, 72);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109e0470(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array5
{
public:
    ~UnkType_109ffd30_Array5()
    {
        Unk_109dff50(0, unk_04, 8);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109dff50(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array6
{
public:
    ~UnkType_109ffd30_Array6()
    {
        Unk_109e03e0(0, unk_04, 16);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109e03e0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array7
{
public:
    ~UnkType_109ffd30_Array7()
    {
        Unk_109e0350(0, unk_04, 16);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109e0350(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array8
{
public:
    ~UnkType_109ffd30_Array8()
    {
        Unk_109e02c0(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109e02c0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array9
{
public:
    ~UnkType_109ffd30_Array9()
    {
        Unk_109e0230(0, unk_04, 8);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109e0230(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array10
{
public:
    ~UnkType_109ffd30_Array10()
    {
        Unk_10929260(0, unk_04, 12);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929260(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array11
{
public:
    ~UnkType_109ffd30_Array11()
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

class UnkType_109ffd30_Array12
{
public:
    ~UnkType_109ffd30_Array12()
    {
        Unk_109e0110(0, unk_04, 48);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109e0110(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array13
{
public:
    ~UnkType_109ffd30_Array13()
    {
        Unk_109e01a0(0, unk_04, 32);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109e01a0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array14
{
public:
    ~UnkType_109ffd30_Array14()
    {
        Unk_109fd4a0(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = 0;
    }

    void Unk_109fd4a0(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
};

class UnkType_109ffd30_Array15
{
public:
    ~UnkType_109ffd30_Array15()
    {
        Unk_109e0080(0, unk_04, 16);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109e0080(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ffd30_Array16
{
public:
    ~UnkType_109ffd30_Array16()
    {
        Unk_10ccb3f0(0, unk_04, 96);
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

class UnkType_109ffd30_Array17
{
public:
    ~UnkType_109ffd30_Array17()
    {
        Unk_10ccb3f0(0, unk_04, 156);
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

class UnkType_109ffd30_Array18
{
public:
    ~UnkType_109ffd30_Array18()
    {
        Unk_10ccb3f0(0, unk_04, 60);
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

class UnkType_109ffd30_Array19
{
public:
    ~UnkType_109ffd30_Array19()
    {
        Unk_10ccb3f0(0, unk_04, 128);
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

class UnkType_109ffd30_Array20
{
public:
    ~UnkType_109ffd30_Array20()
    {
        Unk_109f33e0(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = 0;
    }

    void Unk_109f33e0(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
};

class UnkType_109ffd30_Array21
{
public:
    ~UnkType_109ffd30_Array21()
    {
        Unk_109eb8a0(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = 0;
    }

    void Unk_109eb8a0(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
};

class UnkType_109ffd30_Array22
{
public:
    ~UnkType_109ffd30_Array22()
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

class UnkType_109ffd30_Base
{
public:
    virtual ~UnkType_109ffd30_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x78 - 0x04];
};

class UnkType_109ffd30_Level3 : public UnkType_109ffd30_Base
{
public:
    virtual ~UnkType_109ffd30_Level3()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109ffd30_Level2 : public UnkType_109ffd30_Level3
{
public:
    virtual ~UnkType_109ffd30_Level2()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109ffd30_Level1 : public UnkType_109ffd30_Level2
{
public:
    virtual ~UnkType_109ffd30_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109ffd30 : public UnkType_109ffd30_Level1
{
public:
    virtual ~UnkType_109ffd30();

private:
    UnkType_109ffd30_Array22 unk_78;
    UnkType_109ffd30_Array21 unk_80;
    unsigned char unk_88[0x8c - 0x88];
    UnkType_109ffd30_Array20 unk_8c;
    UnkType_109ffd30_Array19 unk_94;
    UnkType_109ffd30_Array18 unk_9c;
    UnkType_109ffd30_Array17 unk_a4;
    UnkType_109ffd30_Array17 unk_ac;
    UnkType_109ffd30_Array16 unk_b4;
    unsigned char unk_bc[0xc8 - 0xbc];
    UnkType_109ffd30_Array15 unk_c8;
    UnkType_109ffd30_Array15 unk_d4;
    UnkType_109ffd30_Array10 unk_e0;
    UnkType_109ffd30_Array10 unk_ec;
    UnkType_109ffd30_Array2 unk_f8;
    unsigned char unk_104[0x120 - 0x104];
    UnkType_109ffd30_Array14 unk_120;
    unsigned char unk_128[0x168 - 0x128];
    UnkType_109ffd30_Array12 unk_168;
    unsigned char unk_174[0x17c - 0x174];
    UnkType_109ffd30_Array13 unk_17c;
    UnkType_109ffd30_Array12 unk_188;
    UnkType_109ffd30_Array10 unk_194;
    unsigned char unk_1a0[0x1f4 - 0x1a0];
    UnkType_109ffd30_Array11 unk_1f4;
    unsigned char unk_200[0x208 - 0x200];
    UnkType_109ffd30_Array10 unk_208;
    UnkType_109ffd30_Array9 unk_214;
    UnkType_109ffd30_Array8 unk_220;
    UnkType_109ffd30_Array8 unk_22c;
    UnkType_109ffd30_Array7 unk_238;
    UnkType_109ffd30_Array6 unk_244;
    UnkType_109ffd30_Array5 unk_250;
    UnkType_109ffd30_Array4 unk_25c;
    UnkType_109ffd30_Array3 unk_268;
    UnkType_109ffd30_Array2 unk_274;
    unsigned char unk_280[0x2a8 - 0x280];
    UnkType_109ffd30_Array1 unk_2a8;
};

// UnkType_109ffd30::~UnkType_109ffd30
UnkType_109ffd30::~UnkType_109ffd30()
{
    Unk_10cd7a30();
}
