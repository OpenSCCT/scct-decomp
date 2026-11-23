// campaign_leaf_37d670.cpp -- one function at file offset 0x37d670, preferred VA 0x10c7d670. It
// passes Ar to the method at 0x10c7d160; when the word at 0x54 is above 15 it passes the word at
// 0x268 to virtual slot 6 of Ar and writes the four-byte words at 0x26c and 0x270 through virtual
// slot 1 of the archive that returns. It then copies the word at 0x370 of the object at 0x58 to
// 0x264. The class, method, member and parameter names are invented; the offsets, the slots and
// the bytes are the binary's.

class UnkType_10c7d670_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual UnkType_10c7d670_Archive& VirtualSlot6(int& Value);
};

class UnkType_10c7d670_Owner
{
public:
    unsigned char unk_0[0x370];
    int unk_370;
};

class UnkType_10c7d670
{
public:
    void Unk_10c7d160(UnkType_10c7d670_Archive& Ar);
    void Unk_10c7d670(UnkType_10c7d670_Archive& Ar);

    unsigned char unk_0[0x54];
    int unk_54;
    UnkType_10c7d670_Owner* unk_58;
    unsigned char unk_5c[0x208];
    int unk_264;
    int unk_268;
    int unk_26c;
    int unk_270;
};

// UnkType_10c7d670::Unk_10c7d670
void UnkType_10c7d670::Unk_10c7d670(UnkType_10c7d670_Archive& Ar)
{
    Unk_10c7d160(Ar);
    if ( unk_54 > 15 )
    {
        UnkType_10c7d670_Archive& Inner = Ar.VirtualSlot6(unk_268);

        Inner.VirtualSlot1(&unk_26c, 4);
        Inner.VirtualSlot1(&unk_270, 4);
    }
    unk_264 = unk_58->unk_370;
}
