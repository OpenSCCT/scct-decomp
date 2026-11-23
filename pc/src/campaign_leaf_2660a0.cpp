// campaign_leaf_2660a0.cpp -- a member function at VA 0x10b660a0: when the byte at 0x18 is set, it
// calls virtual slot 14 of the objects the pointers at 0x04 to 0x10 refer to and clears the byte;
// then it deletes the objects the pointers at 0x04 to 0x14 refer to through their virtual
// destructors and clears the pointers. guess: releases the parts. The class, method and member
// names are invented; the offsets, addresses and slot are the binary's.

class UnkType_10b660a0_Part
{
public:
    virtual ~UnkType_10b660a0_Part();
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
};

class UnkType_10b660a0
{
public:
    void Unk_10b660a0();

private:
    int unk_00;
    UnkType_10b660a0_Part* unk_04;
    UnkType_10b660a0_Part* unk_08;
    UnkType_10b660a0_Part* unk_0c;
    UnkType_10b660a0_Part* unk_10;
    UnkType_10b660a0_Part* unk_14;
    bool unk_18;
};

// UnkType_10b660a0::Unk_10b660a0
void UnkType_10b660a0::Unk_10b660a0()
{
    if ( unk_18 )
    {
        unk_04->VirtualSlot14();
        unk_08->VirtualSlot14();
        unk_0c->VirtualSlot14();
        unk_10->VirtualSlot14();
        unk_18 = false;
    }
    delete unk_04;
    delete unk_08;
    delete unk_0c;
    delete unk_10;
    delete unk_14;
    unk_04 = 0;
    unk_08 = 0;
    unk_0c = 0;
    unk_10 = 0;
    unk_14 = 0;
}
