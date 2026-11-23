// campaign_leaf_073c40.cpp -- free function at VA 0x10973c40: serialises the four floats at the
// start of the value its second argument refers to, four bytes each through virtual slot 1 of the
// archive its first argument refers to, then the member at 0x10 through the free function at VA
// 0x10969150; returns the archive. The class, member and function names are invented; the offsets,
// the sizes, the slot and the address are the binary's.

class UnkType_10973c40_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
};

class UnkType_10973c40_10
{
public:
    float unk_00;
    float unk_04;
    float unk_08;
};

UnkType_10973c40_Archive& Unk_10969150(UnkType_10973c40_Archive& Archive,
                                       UnkType_10973c40_10& Value);

class UnkType_10973c40_Value
{
public:
    float unk_00;
    float unk_04;
    float unk_08;
    float unk_0c;
    UnkType_10973c40_10 unk_10;
};

// Unk_10973c40
UnkType_10973c40_Archive& Unk_10973c40(UnkType_10973c40_Archive& Archive,
                                       UnkType_10973c40_Value& Value)
{
    Archive.VirtualSlot1(&Value.unk_00, 4);
    Archive.VirtualSlot1(&Value.unk_04, 4);
    Archive.VirtualSlot1(&Value.unk_08, 4);
    Archive.VirtualSlot1(&Value.unk_0c, 4);
    Unk_10969150(Archive, Value.unk_10);
    return Archive;
}
