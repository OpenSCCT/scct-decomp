// campaign_leaf_764b00.cpp -- one function at file offset 0x764b00, preferred VA 0x11064b00. It
// calls the fourth virtual method of the object at 0x50 and the method at VA 0x1105ef00 on the
// object at 0x48, each only when its pointer is set. The class, method and member names are
// invented; the offsets and the callee's address are the binary's.

class UnkType_11064b00_First
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
};

class UnkType_11064b00_Second
{
public:
    void Unk_1105ef00();
};

class UnkType_11064b00
{
public:
    void Unk_11064b00();

    unsigned char unk_0[0x48];
    UnkType_11064b00_Second* unk_48;
    int unk_4c;
    UnkType_11064b00_First* unk_50;
};

// UnkType_11064b00::Unk_11064b00
void UnkType_11064b00::Unk_11064b00()
{
    if ( unk_50 != 0 )
    {
        unk_50->VirtualSlot3();
    }
    if ( unk_48 != 0 )
    {
        unk_48->Unk_1105ef00();
    }
}
