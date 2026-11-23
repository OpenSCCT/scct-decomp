// campaign_leaf_068460.cpp -- method at VA 0x10968460: passes its archive argument to the method at
// VA 0x10cd9030 of its base class, then serialises the values at 0x28 and 0x2c (four bytes each,
// through virtual slot 1 of the archive) and those at 0x30 and 0x34 (four bytes each, through the
// archive method at VA 0x10967df0). The class, member and method names are invented; the offsets,
// the sizes, the slot and the addresses are the binary's.

class UnkType_10968460_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);

    void Unk_10967df0(void* Data, int Size);
};

class UnkType_10968460_Base
{
public:
    void Unk_10cd9030(UnkType_10968460_Archive& Archive);

private:
    unsigned char unk_00[0x28];
};

class UnkType_10968460 : public UnkType_10968460_Base
{
public:
    void Unk_10968460(UnkType_10968460_Archive& Archive);

private:
    int unk_28;
    int unk_2c;
    float unk_30;
    float unk_34;
};

// UnkType_10968460::Unk_10968460
void UnkType_10968460::Unk_10968460(UnkType_10968460_Archive& Archive)
{
    Unk_10cd9030(Archive);
    Archive.VirtualSlot1(&unk_28, 4);
    Archive.VirtualSlot1(&unk_2c, 4);
    Archive.Unk_10967df0(&unk_30, 4);
    Archive.Unk_10967df0(&unk_34, 4);
}
