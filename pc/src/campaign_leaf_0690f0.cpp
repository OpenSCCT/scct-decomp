// campaign_leaf_0690f0.cpp -- method at VA 0x109690f0: serialises the object into the archive its
// argument refers to: first through the base class method at VA 0x10cd9030, then the values at 0x28
// and 0x2c (four bytes each) through the archive's virtual slot 1 (vtable offset 0x04), the values
// at 0x30 and 0x34 through the archive method at VA 0x10967df0, and the member at 0x38 through the
// free function at VA 0x10969150. The class, member and method names are invented; the offsets, the
// sizes and the addresses are the binary's.

class UnkType_109690f0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);

    UnkType_109690f0_Archive& Unk_10967df0(void* Data, int Size);
};

class UnkType_109690f0_38
{
public:
    int unk_00;
};

UnkType_109690f0_Archive& Unk_10969150(UnkType_109690f0_Archive& Archive,
                                       UnkType_109690f0_38& Value);

class UnkType_109690f0_Base
{
public:
    void Unk_10cd9030(UnkType_109690f0_Archive& Archive);

private:
    unsigned char unk_00[0x28];
};

class UnkType_109690f0 : public UnkType_109690f0_Base
{
public:
    void Unk_109690f0(UnkType_109690f0_Archive& Archive);

private:
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    UnkType_109690f0_38 unk_38;
};

// UnkType_109690f0::Unk_109690f0
void UnkType_109690f0::Unk_109690f0(UnkType_109690f0_Archive& Archive)
{
    Unk_10cd9030(Archive);
    Archive.VirtualSlot1(&unk_28, 4);
    Archive.VirtualSlot1(&unk_2c, 4);
    Archive.Unk_10967df0(&unk_30, 4);
    Archive.Unk_10967df0(&unk_34, 4);
    Unk_10969150(Archive, unk_38);
}
