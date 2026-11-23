// campaign_leaf_01a0d0.cpp -- method at VA 0x1091a0d0: passes the archive its argument refers to to
// virtual slot 7 (vtable offset 0x1c) of each object in the pointer array at 0x34 (count at 0x38),
// then passes the member at 0x40 to virtual slot 6 of the archive and the member at 0x70 to virtual
// slot 7 of the archive that returns. The class, member and method names are invented; the offsets
// and the slots are the binary's.

class UnkType_1091a0d0_6
{
public:
    int unk_00;
};

class UnkType_1091a0d0_7
{
public:
    int unk_00;
};

class UnkType_1091a0d0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual UnkType_1091a0d0_Archive& VirtualSlot6(UnkType_1091a0d0_6& Value);
    virtual UnkType_1091a0d0_Archive& VirtualSlot7(UnkType_1091a0d0_7& Value);
};

class UnkType_1091a0d0_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7(UnkType_1091a0d0_Archive& Archive);
};

class UnkType_1091a0d0
{
public:
    void Unk_1091a0d0(UnkType_1091a0d0_Archive& Archive);

private:
    unsigned char unk_00[0x34];
    UnkType_1091a0d0_Item** unk_34;
    int unk_38;
    int unk_3c;
    UnkType_1091a0d0_6 unk_40;
    unsigned char unk_44[0x70 - 0x44];
    UnkType_1091a0d0_7 unk_70;
};

// UnkType_1091a0d0::Unk_1091a0d0
void UnkType_1091a0d0::Unk_1091a0d0(UnkType_1091a0d0_Archive& Archive)
{
    for ( int i = 0; i < unk_38; i++ )
    {
        unk_34[i]->VirtualSlot7(Archive);
    }
    Archive.VirtualSlot6(unk_40).VirtualSlot7(unk_70);
}
