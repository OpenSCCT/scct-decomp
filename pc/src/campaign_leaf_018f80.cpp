// campaign_leaf_018f80.cpp -- method at VA 0x10918f80: deletes each object in the pointer array at
// 0x28 (count at 0x2c) that exists through its virtual destructor (slot 1), empties the array
// (count and capacity 0, data reallocated through virtual slot 1 of the allocator the global at VA
// 0x111c88a0 points to, tagged "FArray"), clears the value at 0x24 and calls virtual slot 10
// (vtable offset 0x28); then, when the object at 0x0c is set and is not the one virtual slot 57
// (offset 0xe4) of the object at 0x08 returns, passes its argument to that object's virtual slot 12
// (offset 0x30). The class, member and method names are invented; the offsets, the tag and the
// slots are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10918f80_Item
{
public:
    virtual void VirtualSlot0();
    virtual ~UnkType_10918f80_Item();
};

class UnkType_111c88a0_018f80
{
public:
    void Empty()
    {
        unk_04 = 0;
        unk_08 = 0;
        unk_00 = static_cast<UnkType_10918f80_Item**>(GUnk_111c88a0->Realloc(unk_00, 0,
                                                                                L"FArray"));
    }

    UnkType_10918f80_Item** unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10918f80_0c
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12(int Value);
};

class UnkType_10918f80_08
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
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
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual UnkType_10918f80_0c* VirtualSlot57();
};

class UnkType_10918f80
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();

    void Unk_10918f80(int Value);

private:
    int unk_04;
    UnkType_10918f80_08* unk_08;
    UnkType_10918f80_0c* unk_0c;
    unsigned char unk_10[0x24 - 0x10];
    int unk_24;
    UnkType_111c88a0_018f80 unk_28;
};

// UnkType_10918f80::Unk_10918f80
void UnkType_10918f80::Unk_10918f80(int Value)
{
    for ( int i = 0; i < unk_28.unk_04; i++ )
    {
        delete unk_28.unk_00[i];
    }
    unk_28.Empty();
    unk_24 = 0;
    VirtualSlot10();
    if ( unk_0c && unk_0c != unk_08->VirtualSlot57() )
    {
        unk_0c->VirtualSlot12(Value);
    }
}
