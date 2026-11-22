// campaign_leaf_341630.cpp -- a member function at VA 0x10c41630: when the pointer at 0x454 is not
// null it calls virtual slot 9 of its object; it then clears the pointer. The class, method and
// member names are invented; the offsets and the slot are the binary's.

class UnkType_10c41630_Item
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

class UnkType_10c41630
{
public:
    void Unk_10c41630();

private:
    unsigned char unk_000[0x454];
    UnkType_10c41630_Item* unk_454;
};

// UnkType_10c41630::Unk_10c41630
void UnkType_10c41630::Unk_10c41630()
{
    if ( unk_454 )
    {
        unk_454->VirtualSlot9();
    }
    unk_454 = 0;
}
