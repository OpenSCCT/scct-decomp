// campaign_leaf_0a76d0.cpp -- virtual destructor at VA 0x109a76d0 (vtable at VA 0x110cc0a8): calls
// the method at VA 0x10cd7a30, then destroys the dynamic array at 0x304 (method at VA 0x109a7150,
// element size 8), the dynamic array at 0x2f8 (method at VA 0x10929260, element size 12), the
// dynamic array at 0x2ec (method at VA 0x109a7030, element size 16), the dynamic array at 0x2e0
// (method at VA 0x109a70c0, element size 24), the dynamic array at 0x2d4 (method at VA 0x109a7030,
// element size 16), the dynamic array at 0x2c8 (method at VA 0x109a6fa0, element size 16), the
// dynamic array at 0x2bc (method at VA 0x10929a90, element size 4); each array is passed 0 and its
// count, then its data is freed through virtual slot 2 of the allocator global at VA 0x111c88a0; it
// ends in the outermost base destructor at VA 0x1092ad20. The class, member and method names are
// invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109a76d0_Array1
{
public:
    ~UnkType_109a76d0_Array1()
    {
        Unk_109a7150(0, unk_04, 8);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109a7150(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109a76d0_Array2
{
public:
    ~UnkType_109a76d0_Array2()
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

class UnkType_109a76d0_Array3
{
public:
    ~UnkType_109a76d0_Array3()
    {
        Unk_109a7030(0, unk_04, 16);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109a7030(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109a76d0_Array4
{
public:
    ~UnkType_109a76d0_Array4()
    {
        Unk_109a70c0(0, unk_04, 24);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109a70c0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109a76d0_Array5
{
public:
    ~UnkType_109a76d0_Array5()
    {
        Unk_109a6fa0(0, unk_04, 16);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109a6fa0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109a76d0_Array6
{
public:
    ~UnkType_109a76d0_Array6()
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

class UnkType_109a76d0_Base
{
public:
    virtual ~UnkType_109a76d0_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2bc - 0x04];
};

class UnkType_109a76d0 : public UnkType_109a76d0_Base
{
public:
    virtual ~UnkType_109a76d0();

private:
    UnkType_109a76d0_Array6 unk_2bc;
    UnkType_109a76d0_Array5 unk_2c8;
    UnkType_109a76d0_Array3 unk_2d4;
    UnkType_109a76d0_Array4 unk_2e0;
    UnkType_109a76d0_Array3 unk_2ec;
    UnkType_109a76d0_Array2 unk_2f8;
    UnkType_109a76d0_Array1 unk_304;
};

// UnkType_109a76d0::~UnkType_109a76d0
UnkType_109a76d0::~UnkType_109a76d0()
{
    Unk_10cd7a30();
}
