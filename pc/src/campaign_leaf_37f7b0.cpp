// campaign_leaf_37f7b0.cpp -- a member function at VA 0x10c7f7b0 that passes its two arguments to
// the member at VA 0x10c7f770 and, when the result is not null, calls virtual slot 5 of the object
// it points to. The class, method and parameter names are invented; the addresses and slot are the
// binary's.

class UnkType_10c7f7b0_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
};

class UnkType_10c7f7b0
{
public:
    UnkType_10c7f7b0_Item* Unk_10c7f770(int First, int Second);
    void Unk_10c7f7b0(int First, int Second);
};

// UnkType_10c7f7b0::Unk_10c7f7b0
void UnkType_10c7f7b0::Unk_10c7f7b0(int First, int Second)
{
    UnkType_10c7f7b0_Item* Item = Unk_10c7f770(First, Second);
    if ( Item )
    {
        Item->VirtualSlot5();
    }
}
