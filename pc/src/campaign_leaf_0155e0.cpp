// campaign_leaf_0155e0.cpp -- method at VA 0x109155e0: deletes each object in the pointer array at
// 0x34 (count at 0x38) that exists through its virtual destructor (slot 4), then passes 0 to the
// method at VA 0x10915620 of the array. The class, member and method names are invented; the
// offsets, the slot and the address are the binary's.

class UnkType_109155e0_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual ~UnkType_109155e0_Item();
};

class UnkType_10915620_0155e0
{
public:
    void Unk_10915620(int Slack);

    UnkType_109155e0_Item** unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109155e0
{
public:
    void Unk_109155e0();

private:
    unsigned char unk_00[0x34];
    UnkType_10915620_0155e0 unk_34;
};

// UnkType_109155e0::Unk_109155e0
void UnkType_109155e0::Unk_109155e0()
{
    for ( int i = 0; i < unk_34.unk_04; i++ )
    {
        delete unk_34.unk_00[i];
    }
    unk_34.Unk_10915620(0);
}
