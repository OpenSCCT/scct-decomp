// campaign_leaf_0951f0.cpp -- virtual destructor at VA 0x109951f0 (vtable at VA 0x110c81b0): calls
// the method at VA 0x10cd7a30, then destroys the dynamic array at 0x518 (method at VA 0x10991db0,
// element size 4), the dynamic array at 0x50c (method at VA 0x10991f60, element size 156), the
// dynamic array at 0x4f8 (method at VA 0x10936600, element size 4), the dynamic array at 0x4e8
// (method at VA 0x10929cd0, element size 8), the dynamic array at 0x4dc (method at VA 0x10929cd0,
// element size 8), the dynamic array at 0x4d0 (method at VA 0x10929cd0, element size 8), the
// dynamic array at 0x4c4 (method at VA 0x10929cd0, element size 8), the dynamic array at 0x39c
// (method at VA 0x10929170, element size 4), the dynamic array at 0x390 (method at VA 0x10929b20,
// element size 4); each array is passed 0 and its count, then its data is freed through virtual
// slot 2 of the allocator global at VA 0x111c88a0; it ends in the outermost base destructor at VA
// 0x1092ad20. The class, member and method names are invented; the offsets and the addresses are
// the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109951f0_Array1
{
public:
    ~UnkType_109951f0_Array1()
    {
        Unk_10991db0(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10991db0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109951f0_Array2
{
public:
    ~UnkType_109951f0_Array2()
    {
        Unk_10991f60(0, unk_04, 156);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10991f60(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109951f0_Array3
{
public:
    ~UnkType_109951f0_Array3()
    {
        Unk_10936600(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10936600(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109951f0_Array4
{
public:
    ~UnkType_109951f0_Array4()
    {
        Unk_10929cd0(0, unk_04, 8);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929cd0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109951f0_Array5
{
public:
    ~UnkType_109951f0_Array5()
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

class UnkType_109951f0_Array6
{
public:
    ~UnkType_109951f0_Array6()
    {
        Unk_10929b20(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929b20(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109951f0_Base
{
public:
    virtual ~UnkType_109951f0_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x390 - 0x04];
};

class UnkType_109951f0 : public UnkType_109951f0_Base
{
public:
    virtual ~UnkType_109951f0();

private:
    UnkType_109951f0_Array6 unk_390;
    UnkType_109951f0_Array5 unk_39c;
    unsigned char unk_3a8[0x4c4 - 0x3a8];
    UnkType_109951f0_Array4 unk_4c4;
    UnkType_109951f0_Array4 unk_4d0;
    UnkType_109951f0_Array4 unk_4dc;
    UnkType_109951f0_Array4 unk_4e8;
    unsigned char unk_4f4[0x4f8 - 0x4f4];
    UnkType_109951f0_Array3 unk_4f8;
    unsigned char unk_504[0x50c - 0x504];
    UnkType_109951f0_Array2 unk_50c;
    UnkType_109951f0_Array1 unk_518;
};

// UnkType_109951f0::~UnkType_109951f0
UnkType_109951f0::~UnkType_109951f0()
{
    Unk_10cd7a30();
}
