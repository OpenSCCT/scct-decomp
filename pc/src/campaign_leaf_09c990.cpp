// campaign_leaf_09c990.cpp -- virtual destructor at VA 0x1099c990 (vtable at VA 0x110c95a0): calls
// the method at VA 0x10cd7a30, then destroys the dynamic array at 0x3cc (method at VA 0x1099a860,
// element size 4), the dynamic array at 0x3c0 (method at VA 0x10936600, element size 4), the
// dynamic array at 0x3b4 (method at VA 0x10929170, element size 4), the dynamic array at 0x3a8
// (method at VA 0x10929a90, element size 4), the dynamic array at 0x39c (method at VA 0x10929a90,
// element size 4), the 4 0x2c-byte objects at 0x2ec, last first (destructor at VA 0x1099c800), the
// dynamic array at 0x2d0 (method at VA 0x1099a7d0, element size 4), the dynamic array at 0x2c4
// (method at VA 0x1099a740, element size 4), the dynamic array at 0x2b4 (method at VA 0x10936600,
// element size 4); each array is passed 0 and its count, then its data is freed through virtual
// slot 2 of the allocator global at VA 0x111c88a0; it ends in the outermost base destructor at VA
// 0x1092ad20. The class, member and method names are invented; the offsets and the addresses are
// the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1099c990_Array1
{
public:
    ~UnkType_1099c990_Array1()
    {
        Unk_1099a860(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1099a860(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1099c990_Array2
{
public:
    ~UnkType_1099c990_Array2()
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

class UnkType_1099c990_Array3
{
public:
    ~UnkType_1099c990_Array3()
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

class UnkType_1099c990_Array4
{
public:
    ~UnkType_1099c990_Array4()
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

class UnkType_1099c990_Object5
{
public:
    ~UnkType_1099c990_Object5();

private:
    unsigned char unk_00[0x2c];
};

class UnkType_1099c990_Array6
{
public:
    ~UnkType_1099c990_Array6()
    {
        Unk_1099a7d0(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1099a7d0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1099c990_Array7
{
public:
    ~UnkType_1099c990_Array7()
    {
        Unk_1099a740(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1099a740(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1099c990_Base
{
public:
    virtual ~UnkType_1099c990_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2b4 - 0x04];
};

class UnkType_1099c990 : public UnkType_1099c990_Base
{
public:
    virtual ~UnkType_1099c990();

private:
    UnkType_1099c990_Array2 unk_2b4;
    unsigned char unk_2c0[0x2c4 - 0x2c0];
    UnkType_1099c990_Array7 unk_2c4;
    UnkType_1099c990_Array6 unk_2d0;
    unsigned char unk_2dc[0x2ec - 0x2dc];
    UnkType_1099c990_Object5 unk_2ec[4];
    UnkType_1099c990_Array4 unk_39c;
    UnkType_1099c990_Array4 unk_3a8;
    UnkType_1099c990_Array3 unk_3b4;
    UnkType_1099c990_Array2 unk_3c0;
    UnkType_1099c990_Array1 unk_3cc;
};

// UnkType_1099c990::~UnkType_1099c990
UnkType_1099c990::~UnkType_1099c990()
{
    Unk_10cd7a30();
}
