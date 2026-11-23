// campaign_leaf_0c6510.cpp -- virtual destructor at VA 0x109c6510 (vtable at VA 0x110cec48): calls
// the method at VA 0x10cd7a30, destroys the dynamic array at 0x48 (method at VA 0x10977960 with 0,
// its count and the element size 4) and the dynamic array at 0x28 (method at VA 0x109c61c0 with 0
// and its count), each then freeing its data through virtual slot 2 of the allocator global at VA
// 0x111c88a0, and ends in the base class destructor at VA 0x10cdc460. The class, member and method
// names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109c6510_Base
{
public:
    virtual ~UnkType_109c6510_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x28 - 0x04];
};

class UnkType_109c6510_List
{
public:
    ~UnkType_109c6510_List()
    {
        Unk_109c61c0(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109c61c0(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c6510_Array
{
public:
    ~UnkType_109c6510_Array()
    {
        Unk_10977960(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10977960(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c6510 : public UnkType_109c6510_Base
{
public:
    virtual ~UnkType_109c6510();

private:
    UnkType_109c6510_List unk_28;
    unsigned char unk_34[0x48 - 0x34];
    UnkType_109c6510_Array unk_48;
};

// UnkType_109c6510::~UnkType_109c6510
UnkType_109c6510::~UnkType_109c6510()
{
    Unk_10cd7a30();
}
