// campaign_leaf_2af510.cpp -- destructor at VA 0x10baf510 of a class with a vtable (VA 0x110e9d98):
// calls the method at VA 0x10cd7a30, destroys the dynamic array at 0x38 (its contents removed
// through the method at VA 0x10966210 with 1 as the element size, its data freed through virtual
// slot 2 of the allocator at VA 0x111c88a0, its three words cleared) and the member at 0x28
// (destructor at VA 0x1090ba70), then runs the base class destructor at VA 0x10cdc460. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10baf510_Base
{
public:
    virtual ~UnkType_10baf510_Base();

    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x28 - 0x04];
};

class UnkType_10baf510_28
{
public:
    ~UnkType_10baf510_28();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10baf510_38
{
public:
    ~UnkType_10baf510_38()
    {
        Unk_10966210(0, unk_04, 1);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10966210(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10baf510 : public UnkType_10baf510_Base
{
public:
    virtual ~UnkType_10baf510();

private:
    UnkType_10baf510_28 unk_28;
    int unk_34;
    UnkType_10baf510_38 unk_38;
};

// UnkType_10baf510::~UnkType_10baf510
UnkType_10baf510::~UnkType_10baf510()
{
    Unk_10cd7a30();
}
