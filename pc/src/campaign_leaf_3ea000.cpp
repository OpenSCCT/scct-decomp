// campaign_leaf_3ea000.cpp -- one function at file offset 0x3ea000, preferred VA 0x10cea000. It
// serializes this object through Ar: the method at 0x10ce4280 first, then the halfword at 0x34
// and the word at 0x38 through Ar's virtual slot 1, and the words at 0x3c and 0x40 through its
// chained slot 7. When Ar's word at 0x18 is set it clears the halfword at 0x44 and the word at
// 0x4c. The class, method, member and parameter names are invented; the offsets, the slots and
// the bytes are the binary's.

class UnkType_10cea000_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual UnkType_10cea000_Archive& VirtualSlot7(int& Value);

    unsigned char unk_4[0x14];
    int unk_18;
};

class UnkType_10cea000
{
public:
    void Unk_10ce4280(UnkType_10cea000_Archive& Ar);
    void Unk_10cea000(UnkType_10cea000_Archive& Ar);

    unsigned char unk_0[0x34];
    short unk_34;
    short unk_36;
    int unk_38;
    int unk_3c;
    int unk_40;
    short unk_44;
    short unk_46;
    int unk_48;
    int unk_4c;
};

// UnkType_10cea000::Unk_10cea000
void UnkType_10cea000::Unk_10cea000(UnkType_10cea000_Archive& Ar)
{
    Unk_10ce4280(Ar);
    Ar.VirtualSlot1(&unk_34, 2);
    Ar.VirtualSlot1(&unk_38, 4);
    Ar.VirtualSlot7(unk_3c).VirtualSlot7(unk_40);
    if ( Ar.unk_18 != 0 )
    {
        unk_44 = 0;
        unk_4c = 0;
    }
}
