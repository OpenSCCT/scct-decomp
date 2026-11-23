// campaign_leaf_0e0e20.cpp -- destructor at VA 0x109e0e20: destroys the two-word dynamic array at
// 0x10 (method at VA 0x10ccb3f0, element size 1), the two-word dynamic array at 0x8 (method at VA
// 0x10ccb3f0, element size 6), the two-word dynamic array at 0x0 (method at VA 0x10ccb3f0, element
// size 8); each array is passed 0 and its count, then its data is freed through virtual slot 2 of
// the allocator global at VA 0x111c88a0. The class, member and method names are invented; the
// offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109e0e20_Array1
{
public:
    ~UnkType_109e0e20_Array1()
    {
        Unk_10ccb3f0(0, unk_04, 8);
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

class UnkType_109e0e20_Array2
{
public:
    ~UnkType_109e0e20_Array2()
    {
        Unk_10ccb3f0(0, unk_04, 6);
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

class UnkType_109e0e20_Array3
{
public:
    ~UnkType_109e0e20_Array3()
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

class UnkType_109e0e20
{
public:
    ~UnkType_109e0e20();

private:
    UnkType_109e0e20_Array1 unk_00;
    UnkType_109e0e20_Array2 unk_08;
    UnkType_109e0e20_Array3 unk_10;
};

// UnkType_109e0e20::~UnkType_109e0e20
UnkType_109e0e20::~UnkType_109e0e20()
{
}
