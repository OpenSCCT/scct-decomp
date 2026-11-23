// campaign_leaf_069070.cpp -- method at VA 0x10969070: passes its archive argument to the method at
// VA 0x10cd9030, then serialises the value at 0x28 (four bytes, through virtual slot 1 of the
// archive) and the member at 0x2c (through the free function at VA 0x10968a30). The class, member
// and function names are invented; the offsets, the size, the slot and the addresses are the
// binary's.

class UnkType_10969070_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
};

class UnkType_10969070_2c
{
public:
    int unk_00;
};

UnkType_10969070_Archive& Unk_10968a30(UnkType_10969070_Archive& Archive,
                                       UnkType_10969070_2c& Value);

class UnkType_10969070
{
public:
    void Unk_10969070(UnkType_10969070_Archive& Archive);
    void Unk_10cd9030(UnkType_10969070_Archive& Archive);

private:
    unsigned char unk_00[0x28];
    int unk_28;
    UnkType_10969070_2c unk_2c;
};

// UnkType_10969070::Unk_10969070
void UnkType_10969070::Unk_10969070(UnkType_10969070_Archive& Archive)
{
    Unk_10cd9030(Archive);
    Archive.VirtualSlot1(&unk_28, 4);
    Unk_10968a30(Archive, unk_2c);
}
