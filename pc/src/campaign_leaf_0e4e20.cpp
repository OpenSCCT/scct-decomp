// campaign_leaf_0e4e20.cpp -- destructor at VA 0x109e4e20: destroys the dynamic array at 0x3c
// (method at VA 0x109d9520, element size 0x10), the dynamic array at 0x30 (method at VA 0x109d9520,
// element size 0x10), the dynamic array at 0x1c (method at VA 0x109d9440, element size 0x10), the
// dynamic array at 0x4 (method at VA 0x10919a00, element size 4); each array is passed 0 and its
// count, then its data is freed through virtual slot 2 of the allocator global at VA 0x111c88a0.
// The class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109e4e20_Array1
{
public:
    ~UnkType_109e4e20_Array1()
    {
        Unk_10919a00(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10919a00(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109e4e20_Array2
{
public:
    ~UnkType_109e4e20_Array2()
    {
        Unk_109d9440(0, unk_04, 0x10);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109d9440(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109e4e20_Array3
{
public:
    ~UnkType_109e4e20_Array3()
    {
        Unk_109d9520(0, unk_04, 0x10);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109d9520(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109e4e20
{
public:
    ~UnkType_109e4e20();

private:
    unsigned char unk_00[0x04];
    UnkType_109e4e20_Array1 unk_04;
    unsigned char unk_10[0x1c - 0x10];
    UnkType_109e4e20_Array2 unk_1c;
    unsigned char unk_28[0x30 - 0x28];
    UnkType_109e4e20_Array3 unk_30;
    UnkType_109e4e20_Array3 unk_3c;
};

// UnkType_109e4e20::~UnkType_109e4e20
UnkType_109e4e20::~UnkType_109e4e20()
{
}
