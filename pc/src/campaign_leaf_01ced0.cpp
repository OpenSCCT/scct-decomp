// campaign_leaf_01ced0.cpp -- method at VA 0x1091ced0: passes the archive its argument refers to to
// virtual slot 7 (vtable offset 0x1c) of each object in the pointer array at 0x34 (count at 0x38),
// then passes the member at 0x50 to virtual slot 6 of the archive, the member at 0x60 to its
// virtual slot 7 and the member at 0x64 to virtual slot 6 of the archive that returns. The class,
// member and method names are invented; the offsets and the slots are the binary's.

class UnkType_1091ced0_6
{
public:
    int unk_00;
};

class UnkType_1091ced0_7
{
public:
    int unk_00;
};

class UnkType_1091ced0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual UnkType_1091ced0_Archive& VirtualSlot6(UnkType_1091ced0_6& Value);
    virtual UnkType_1091ced0_Archive& VirtualSlot7(UnkType_1091ced0_7& Value);
};

class UnkType_1091ced0_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7(UnkType_1091ced0_Archive& Archive);
};

class UnkType_1091ced0
{
public:
    void Unk_1091ced0(UnkType_1091ced0_Archive& Archive);

private:
    unsigned char unk_00[0x34];
    UnkType_1091ced0_Item** unk_34;
    int unk_38;
    int unk_3c;
    unsigned char unk_40[0x50 - 0x40];
    UnkType_1091ced0_6 unk_50;
    unsigned char unk_54[0x60 - 0x54];
    UnkType_1091ced0_7 unk_60;
    UnkType_1091ced0_6 unk_64;
};

// UnkType_1091ced0::Unk_1091ced0
void UnkType_1091ced0::Unk_1091ced0(UnkType_1091ced0_Archive& Archive)
{
    for ( int i = 0; i < unk_38; i++ )
    {
        unk_34[i]->VirtualSlot7(Archive);
    }
    Archive.VirtualSlot6(unk_50);
    Archive.VirtualSlot7(unk_60).VirtualSlot6(unk_64);
}
