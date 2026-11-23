// campaign_leaf_0f2da0.cpp -- virtual destructor at VA 0x109f2da0 (vtable at VA 0x110cfac0): calls
// the method at VA 0x10cd7a30, then destroys the dynamic array at 0xf4 (method at VA 0x109dfc80,
// element size 8), the dynamic array at 0xe8 (method at VA 0x109dfbf0, element size 12), the
// dynamic array at 0xdc (method at VA 0x10907710, element size 2), the dynamic array at 0xd0
// (method at VA 0x109dfb60, element size 8), the dynamic array at 0xc4 (method at VA 0x10907710,
// element size 2), the dynamic array at 0xb8 (method at VA 0x10907710, element size 2), the dynamic
// array at 0x88 (method at VA 0x109dfad0, element size 40), the dynamic array at 0x7c (method at VA
// 0x10929a00, element size 4), the dynamic array at 0x70 (method at VA 0x10929a00, element size 4),
// the dynamic array at 0x64 (method at VA 0x109dfa40, element size 4); then the inline destructor
// of base class 1 (vtable at VA 0x110cf500) calls it; then the inline destructor of base class 2
// (vtable at VA 0x110c0b98) calls it; each array is passed 0 and its count, then its data is freed
// through virtual slot 2 of the allocator global at VA 0x111c88a0; it ends in the outermost base
// destructor at VA 0x10cdc460. The class, member and method names are invented; the offsets and the
// addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109f2da0_Array1
{
public:
    ~UnkType_109f2da0_Array1()
    {
        Unk_109dfc80(0, unk_04, 8);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109dfc80(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109f2da0_Array2
{
public:
    ~UnkType_109f2da0_Array2()
    {
        Unk_109dfbf0(0, unk_04, 12);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109dfbf0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109f2da0_Array3
{
public:
    ~UnkType_109f2da0_Array3()
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

class UnkType_109f2da0_Array4
{
public:
    ~UnkType_109f2da0_Array4()
    {
        Unk_109dfb60(0, unk_04, 8);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109dfb60(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109f2da0_Array5
{
public:
    ~UnkType_109f2da0_Array5()
    {
        Unk_109dfad0(0, unk_04, 40);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109dfad0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109f2da0_Array6
{
public:
    ~UnkType_109f2da0_Array6()
    {
        Unk_10929a00(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929a00(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109f2da0_Array7
{
public:
    ~UnkType_109f2da0_Array7()
    {
        Unk_109dfa40(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109dfa40(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109f2da0_Base
{
public:
    virtual ~UnkType_109f2da0_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x64 - 0x04];
};

class UnkType_109f2da0_Level2 : public UnkType_109f2da0_Base
{
public:
    virtual ~UnkType_109f2da0_Level2()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109f2da0_Level1 : public UnkType_109f2da0_Level2
{
public:
    virtual ~UnkType_109f2da0_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109f2da0 : public UnkType_109f2da0_Level1
{
public:
    virtual ~UnkType_109f2da0();

private:
    UnkType_109f2da0_Array7 unk_64;
    UnkType_109f2da0_Array6 unk_70;
    UnkType_109f2da0_Array6 unk_7c;
    UnkType_109f2da0_Array5 unk_88;
    unsigned char unk_94[0xb8 - 0x94];
    UnkType_109f2da0_Array3 unk_b8;
    UnkType_109f2da0_Array3 unk_c4;
    UnkType_109f2da0_Array4 unk_d0;
    UnkType_109f2da0_Array3 unk_dc;
    UnkType_109f2da0_Array2 unk_e8;
    UnkType_109f2da0_Array1 unk_f4;
};

// UnkType_109f2da0::~UnkType_109f2da0
UnkType_109f2da0::~UnkType_109f2da0()
{
    Unk_10cd7a30();
}
