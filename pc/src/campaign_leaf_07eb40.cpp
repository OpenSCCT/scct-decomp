// campaign_leaf_07eb40.cpp -- free function at VA 0x1097eb40: serialises the object its second
// argument refers to: the values at 0x00, 0x04 and 0x08 through the free function at VA 0x10cd80b0,
// each through the archive the previous call returns, and then the eight bytes at 0x0c through
// virtual slot 1 (vtable offset 0x04) of the last archive, which it returns. The class, member and
// function names are invented; the offsets, the size and the address are the binary's.

class UnkType_1097eb40_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
};

UnkType_1097eb40_Archive& Unk_10cd80b0(UnkType_1097eb40_Archive& Archive, int& Value);

class UnkType_1097eb40
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0c[8];
};

// Unk_1097eb40
UnkType_1097eb40_Archive& Unk_1097eb40(UnkType_1097eb40_Archive& Archive, UnkType_1097eb40& Value)
{
    UnkType_1097eb40_Archive& Out =
        Unk_10cd80b0(Unk_10cd80b0(Unk_10cd80b0(Archive, Value.unk_00), Value.unk_04), Value.unk_08);
    Out.VirtualSlot1(Value.unk_0c, 8);
    return Out;
}
