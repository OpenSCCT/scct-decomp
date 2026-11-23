// campaign_leaf_764ae0.cpp -- one function at file offset 0x764ae0, preferred VA 0x11064ae0. It
// calls the third virtual method of the object at 0x50 and the method at VA 0x1105eef0 on the
// object at 0x48, each only when its pointer is set. The class, method and member names are
// invented; the offsets and the callee's address are the binary's.

class UnkType_11064ae0_First
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
};

class UnkType_11064ae0_Second
{
public:
    void Unk_1105eef0();
};

class UnkType_11064ae0
{
public:
    void Unk_11064ae0();

    unsigned char unk_0[0x48];
    UnkType_11064ae0_Second* unk_48;
    int unk_4c;
    UnkType_11064ae0_First* unk_50;
};

// UnkType_11064ae0::Unk_11064ae0
void UnkType_11064ae0::Unk_11064ae0()
{
    if ( unk_50 != 0 )
    {
        unk_50->VirtualSlot2();
    }
    if ( unk_48 != 0 )
    {
        unk_48->Unk_1105eef0();
    }
}
