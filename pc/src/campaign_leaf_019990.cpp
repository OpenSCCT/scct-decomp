// campaign_leaf_019990.cpp -- method at VA 0x10919990: passes the archive its argument refers to to
// virtual slot 7 (vtable offset 0x1c) of each object in the pointer array at 0x34 (count at 0x38),
// then passes the member at 0x40 to virtual slot 7 of the archive and the member at 0x44 to virtual
// slot 6 of the archive that returns. The class, member and method names are invented; the offsets
// and the slots are the binary's.

class UnkType_10919990_6
{
public:
    int unk_00;
};

class UnkType_10919990_7
{
public:
    int unk_00;
};

class UnkType_10919990_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual UnkType_10919990_Archive& VirtualSlot6(UnkType_10919990_6& Value);
    virtual UnkType_10919990_Archive& VirtualSlot7(UnkType_10919990_7& Value);
};

class UnkType_10919990_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7(UnkType_10919990_Archive& Archive);
};

class UnkType_10919990
{
public:
    void Unk_10919990(UnkType_10919990_Archive& Archive);

private:
    unsigned char unk_00[0x34];
    UnkType_10919990_Item** unk_34;
    int unk_38;
    int unk_3c;
    UnkType_10919990_7 unk_40;
    UnkType_10919990_6 unk_44;
};

// UnkType_10919990::Unk_10919990
void UnkType_10919990::Unk_10919990(UnkType_10919990_Archive& Archive)
{
    for ( int i = 0; i < unk_38; i++ )
    {
        unk_34[i]->VirtualSlot7(Archive);
    }
    Archive.VirtualSlot7(unk_40).VirtualSlot6(unk_44);
}
