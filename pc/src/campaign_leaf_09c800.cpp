// campaign_leaf_09c800.cpp -- destructor at VA 0x1099c800: destroys the dynamic array at 0x18
// (method at VA 0x10919a00, element size 4), the dynamic array at 0xc (method at VA 0x10929a90,
// element size 4), the dynamic array at 0x0 (method at VA 0x1099a6b0, element size 0x24); each
// array is passed 0 and its count, then its data is freed through virtual slot 2 of the allocator
// global at VA 0x111c88a0. The class, member and method names are invented; the offsets and the
// addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1099c800_Array1
{
public:
    ~UnkType_1099c800_Array1()
    {
        Unk_1099a6b0(0, unk_04, 0x24);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1099a6b0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1099c800_Array2
{
public:
    ~UnkType_1099c800_Array2()
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

class UnkType_1099c800_Array3
{
public:
    ~UnkType_1099c800_Array3()
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

class UnkType_1099c800
{
public:
    ~UnkType_1099c800();

private:
    UnkType_1099c800_Array1 unk_00;
    UnkType_1099c800_Array2 unk_0c;
    UnkType_1099c800_Array3 unk_18;
    unsigned char unk_24[0x2c - 0x24];
};

// UnkType_1099c800::~UnkType_1099c800
UnkType_1099c800::~UnkType_1099c800()
{
}
