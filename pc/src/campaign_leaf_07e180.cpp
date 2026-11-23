// campaign_leaf_07e180.cpp -- destructor at VA 0x1097e180 of a class whose vtable is at VA
// 0x110c16b0: calls the method at VA 0x10cd7a30; destroys the member at 0x38, an array of 8-byte
// elements with a hash table (frees the table at 0x0c of it and clears it and the value at 0x10,
// then removes the elements with the method at VA 0x1097d830), and the array member at 0x2c
// (removes its elements with the method at VA 0x1097de20), freeing each array's data through
// virtual slot 2 of the allocator the global at VA 0x111c88a0 points to and clearing it; then runs
// the base destructor at VA 0x10cdc460. The class, member and method names are invented; the
// offsets, the size and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1097de20_07e180
{
public:
    ~UnkType_1097de20_07e180()
    {
        Unk_1097de20(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1097de20(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1097d830_07e180
{
public:
    ~UnkType_1097d830_07e180()
    {
        Unk_1097d830(0, unk_04, 8);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1097d830(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1097d830_07e180_Map : public UnkType_1097d830_07e180
{
public:
    ~UnkType_1097d830_07e180_Map()
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

class UnkType_1097e180_Base
{
public:
    virtual ~UnkType_1097e180_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x28];
};

class UnkType_1097e180 : public UnkType_1097e180_Base
{
public:
    virtual ~UnkType_1097e180();

private:
    UnkType_1097de20_07e180 unk_2c;
    UnkType_1097d830_07e180_Map unk_38;
};

// UnkType_1097e180::~UnkType_1097e180
UnkType_1097e180::~UnkType_1097e180()
{
    Unk_10cd7a30();
}
