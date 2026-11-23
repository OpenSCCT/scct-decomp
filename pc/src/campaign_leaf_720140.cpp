// campaign_leaf_720140.cpp -- one function at file offset 0x720140, preferred VA 0x11020140. It
// calls the second virtual method of the embedded objects at 0x30, 0x40 and 0x24 and returns
// true. The class, method and member names are invented; the offsets are the binary's.

class UnkType_11020140_Member
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();

    int unk_4;
    int unk_8;
};

class UnkType_11020140
{
public:
    bool Unk_11020140();

    unsigned char unk_0[0x24];
    UnkType_11020140_Member unk_24;
    UnkType_11020140_Member unk_30;
    unsigned char unk_3c[0x40 - 0x3c];
    UnkType_11020140_Member unk_40;
};

// UnkType_11020140::Unk_11020140
bool UnkType_11020140::Unk_11020140()
{
    unk_30.VirtualSlot1();
    unk_40.VirtualSlot1();
    unk_24.VirtualSlot1();
    return true;
}
