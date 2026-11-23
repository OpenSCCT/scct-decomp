// campaign_leaf_07b710.cpp -- destructor at VA 0x1097b710 of a class whose vtable is at VA
// 0x110c1204: destroys the array member at 0x2c (removes its elements with the method at VA
// 0x1090d050), the member at 0x10, an array of 12-byte elements with a hash table (frees the table
// at 0x0c of it and clears it and the value at 0x10, then removes the elements with the method at
// VA 0x10977840), and the array member at 0x04 (removes its elements with the method at VA
// 0x1097aef0), freeing each array's data through virtual slot 2 of the allocator the global at VA
// 0x111c88a0 points to and clearing it. The class, member and method names are invented; the
// offsets, the size and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1090d050_07b710
{
public:
    ~UnkType_1090d050_07b710()
    {
        Unk_1090d050(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1090d050(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1097aef0_07b710
{
public:
    ~UnkType_1097aef0_07b710()
    {
        Unk_1097aef0(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1097aef0(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10977840_07b710
{
public:
    ~UnkType_10977840_07b710()
    {
        Unk_10977840(0, unk_04, 12);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10977840(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10977840_07b710_Map : public UnkType_10977840_07b710
{
public:
    ~UnkType_10977840_07b710_Map()
    {
        if ( unk_0c )
        {
            GUnk_111c88a0->Free(unk_0c);
        }
        unk_0c = 0;
        unk_10 = 0;
    }

private:
    int* unk_0c;
    int unk_10;
};

class UnkType_1097b710
{
public:
    virtual ~UnkType_1097b710();

private:
    UnkType_1097aef0_07b710 unk_04;
    UnkType_10977840_07b710_Map unk_10;
    int unk_24;
    int unk_28;
    UnkType_1090d050_07b710 unk_2c;
};

// UnkType_1097b710::~UnkType_1097b710
UnkType_1097b710::~UnkType_1097b710()
{
}
