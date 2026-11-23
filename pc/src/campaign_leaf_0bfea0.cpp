// campaign_leaf_0bfea0.cpp -- virtual destructor at VA 0x109bfea0 (vtable at VA 0x110ce194): when
// the pointer at 0x04 is set, calls its virtual slot 18 (vtable offset 0x48) with this; then
// destroys the dynamic array at 0x0c (method at VA 0x109b8410 with 0, its count and the element
// size 0x4, then frees its data through virtual slot 2 of the allocator global at VA 0x111c88a0).
// The class, member and method names are invented; the offsets, the slots and the addresses are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109bfea0;

class UnkType_109bfea0_Owner
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
    virtual void VirtualSlot18(UnkType_109bfea0* Object);
};

class UnkType_109bfea0_Array
{
public:
    ~UnkType_109bfea0_Array()
    {
        Unk_109b8410(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109b8410(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109bfea0
{
public:
    virtual ~UnkType_109bfea0();

private:
    UnkType_109bfea0_Owner* unk_04;
    int unk_08;
    UnkType_109bfea0_Array unk_0c;
};

// UnkType_109bfea0::~UnkType_109bfea0
UnkType_109bfea0::~UnkType_109bfea0()
{
    if ( unk_04 )
    {
        unk_04->VirtualSlot18(this);
    }
}
