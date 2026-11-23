// campaign_leaf_0671a0.cpp -- destructor at VA 0x109671a0 of a class whose vtable is at VA
// 0x110bec68: passes this object to virtual slot 18 (vtable offset 0x48) of the object at 0x04, if
// any; then destroys the byte array member at 0x0c (elements removed with the method at VA
// 0x10966210, data freed through virtual slot 2 of the allocator the global at VA 0x111c88a0 points
// to). The class, member and method names are invented; the offsets, the slot and the addresses are
// the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109671a0;

class UnkType_109671a0_Owner
{
public:
    virtual void Malloc();
    virtual void Realloc();
    virtual void Free();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18(UnkType_109671a0* Object);
};

class UnkType_10966210_0671a0
{
public:
    ~UnkType_10966210_0671a0()
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

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109671a0
{
public:
    virtual ~UnkType_109671a0();

private:
    UnkType_109671a0_Owner* unk_04;
    int unk_08;
    UnkType_10966210_0671a0 unk_0c;
};

// UnkType_109671a0::~UnkType_109671a0
UnkType_109671a0::~UnkType_109671a0()
{
    if ( unk_04 )
    {
        unk_04->VirtualSlot18(this);
    }
}
