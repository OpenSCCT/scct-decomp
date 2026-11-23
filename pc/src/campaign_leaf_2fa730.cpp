// campaign_leaf_2fa730.cpp -- method at VA 0x10bfa730: calls the method at VA 0x10bf7fa0, then for
// each of the pointers at 0x53c, 0x544 and 0x560 that is set, passes it with 0 to virtual slot 35
// (vtable offset 0x8c) of the object at 0x7c. The class, member and method names are invented; the
// offsets, the slot and the address are the binary's.

class UnkType_10bfa730_7c
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
    virtual void VirtualSlot35(void* Object, int Flag);
};

class UnkType_10bfa730
{
public:
    void Unk_10bfa730();
    void Unk_10bf7fa0();

private:
    unsigned char unk_00[0x7c];
    UnkType_10bfa730_7c* unk_7c;
    unsigned char unk_80[0x53c - 0x80];
    void* unk_53c;
    unsigned char unk_540[0x544 - 0x540];
    void* unk_544;
    unsigned char unk_548[0x560 - 0x548];
    void* unk_560;
};

// UnkType_10bfa730::Unk_10bfa730
void UnkType_10bfa730::Unk_10bfa730()
{
    Unk_10bf7fa0();
    if ( unk_53c )
    {
        unk_7c->VirtualSlot35(unk_53c, 0);
    }
    if ( unk_544 )
    {
        unk_7c->VirtualSlot35(unk_544, 0);
    }
    if ( unk_560 )
    {
        unk_7c->VirtualSlot35(unk_560, 0);
    }
}
