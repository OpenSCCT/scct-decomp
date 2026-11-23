// campaign_leaf_0697e0.cpp -- free function at VA 0x109697e0: serialises the four bytes of the
// value its second argument refers to, in the order 2, 1, 0, 3, one byte each through virtual slot
// 1 of the archive its first argument refers to; returns the archive. The class, member and
// function names are invented; the offsets and the slot are the binary's.

class UnkType_109697e0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
};

class UnkType_109697e0_Color
{
public:
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
};

// Unk_109697e0
UnkType_109697e0_Archive& Unk_109697e0(UnkType_109697e0_Archive& Archive,
                                       UnkType_109697e0_Color& Value)
{
    Archive.VirtualSlot1(&Value.unk_02, 1);
    Archive.VirtualSlot1(&Value.unk_01, 1);
    Archive.VirtualSlot1(&Value.unk_00, 1);
    Archive.VirtualSlot1(&Value.unk_03, 1);
    return Archive;
}
