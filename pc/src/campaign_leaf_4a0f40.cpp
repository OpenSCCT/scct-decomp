// campaign_leaf_4a0f40.cpp -- one function at file offset 0x4a0f40, preferred VA 0x10da0f40.
// It passes its four arguments and 0 to the virtual method in slot 5 of the object at offset 0x20.
// The class, method, member and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_10da0f40_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int First, int Second, int Third, int Fourth, int Fifth);
};

class UnkType_10da0f40
{
public:
    unsigned char unk_0[0x20];
    UnkType_10da0f40_Item* unk_20;

    void Unk_10da0f40(int First, int Second, int Third, int Fourth);
};

// UnkType_10da0f40::Unk_10da0f40
void UnkType_10da0f40::Unk_10da0f40(int First, int Second, int Third, int Fourth)
{
    unk_20->VirtualSlot5(First, Second, Third, Fourth, 0);
}
