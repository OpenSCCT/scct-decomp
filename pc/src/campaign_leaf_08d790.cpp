// campaign_leaf_08d790.cpp -- method at VA 0x1098d790: passes its archive argument to the method at
// VA 0x10cd9030, then serialises the value at 0x34 (four bytes, through virtual slot 1), the
// 12-byte members at 0x38 and 0x44 and, when the archive's value at 0x0c is at least 70, the one at
// 0x50 (through the free function at VA 0x10983290), the member at 0x5c (through the free function
// at VA 0x1098d600), the value at 0x2c and, again from version 70, the value at 0x30. The class,
// member and method names are invented; the offsets, the constant, the slot and the addresses are
// the binary's.

class UnkType_1098d790_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);

    int unk_04;
    int unk_08;
    int unk_0c;
};

class UnkType_1098d790_Vector
{
public:
    float X;
    float Y;
    float Z;
};

class UnkType_1098d790_5c
{
public:
    int unk_00;
};

UnkType_1098d790_Archive& Unk_10983290(UnkType_1098d790_Archive& Archive,
                                       UnkType_1098d790_Vector& Value);
UnkType_1098d790_Archive& Unk_1098d600(UnkType_1098d790_Archive& Archive,
                                       UnkType_1098d790_5c& Value);

class UnkType_1098d790
{
public:
    void Unk_1098d790(UnkType_1098d790_Archive& Archive);
    void Unk_10cd9030(UnkType_1098d790_Archive& Archive);

private:
    unsigned char unk_00[0x2c];
    int unk_2c;
    int unk_30;
    int unk_34;
    UnkType_1098d790_Vector unk_38;
    UnkType_1098d790_Vector unk_44;
    UnkType_1098d790_Vector unk_50;
    UnkType_1098d790_5c unk_5c;
};

// UnkType_1098d790::Unk_1098d790
void UnkType_1098d790::Unk_1098d790(UnkType_1098d790_Archive& Archive)
{
    Unk_10cd9030(Archive);
    Archive.VirtualSlot1(&unk_34, 4);
    Unk_10983290(Unk_10983290(Archive, unk_38), unk_44);
    if ( Archive.unk_0c >= 70 )
    {
        Unk_10983290(Archive, unk_50);
    }
    Unk_1098d600(Archive, unk_5c);
    Archive.VirtualSlot1(&unk_2c, 4);
    if ( Archive.unk_0c >= 70 )
    {
        Archive.VirtualSlot1(&unk_30, 4);
    }
}
