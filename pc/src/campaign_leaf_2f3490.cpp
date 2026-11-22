// campaign_leaf_2f3490.cpp -- a member function at VA 0x10bf3490: when the pointer at 0x420 is not
// null it calls virtual slot 9 of its object; it then clears the pointer. The class, method and
// member names are invented; the offsets and the slot are the binary's.

class UnkType_10bf3490_Item
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
};

class UnkType_10bf3490
{
public:
    void Unk_10bf3490();

private:
    unsigned char unk_000[0x420];
    UnkType_10bf3490_Item* unk_420;
};

// UnkType_10bf3490::Unk_10bf3490
void UnkType_10bf3490::Unk_10bf3490()
{
    if ( unk_420 )
    {
        unk_420->VirtualSlot9();
    }
    unk_420 = 0;
}
