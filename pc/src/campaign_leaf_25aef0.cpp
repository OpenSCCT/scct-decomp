// campaign_leaf_25aef0.cpp -- a member function at VA 0x10b5aef0: for each of the objects the
// pointers at 0x44, 0x50, 0x4c and 0x48 refer to, in that order, when bit 1 of the object's byte at
// 0x4c differs from its byte at 0x50, it passes the bit to the object's virtual slot 7 and passes
// the object to its own virtual slot 3. The class, method and member names are invented; the
// offsets and slots are the binary's.

class UnkType_10b5aef0_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7(bool Value);

    unsigned char unk_04[0x4c - 0x04];
    unsigned char unk_4c : 1;
    unsigned char unk_4c_1 : 1;
    unsigned char unk_4d[0x50 - 0x4d];
    bool unk_50;
};

class UnkType_10b5aef0
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3(UnkType_10b5aef0_Item* Item);

    // guess: brings an item up to date (an inline helper; name invented)
    void Update(UnkType_10b5aef0_Item* Item)
    {
        bool Value = Item->unk_4c_1;
        if ( Value != Item->unk_50 )
        {
            Item->VirtualSlot7(Value);
            VirtualSlot3(Item);
        }
    }

    void Unk_10b5aef0();

private:
    unsigned char unk_04[0x44 - 0x04];
    UnkType_10b5aef0_Item* unk_44;
    UnkType_10b5aef0_Item* unk_48;
    UnkType_10b5aef0_Item* unk_4c;
    UnkType_10b5aef0_Item* unk_50;
};

// UnkType_10b5aef0::Unk_10b5aef0
void UnkType_10b5aef0::Unk_10b5aef0()
{
    Update(unk_44);
    Update(unk_50);
    Update(unk_4c);
    Update(unk_48);
}
