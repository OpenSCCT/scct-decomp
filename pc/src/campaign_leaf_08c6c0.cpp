// campaign_leaf_08c6c0.cpp -- free function at VA 0x1098c6c0: serialises the object its second
// argument refers to: the member at 0x00 through the free function at VA 0x1098c110, the member at
// 0x04 through the free function at VA 0x10cce480 on the archive that returns, and the value at
// 0x10 (four bytes, through virtual slot 1) on the archive that one returns, which it returns. The
// class, member and function names are invented; the offsets, the size, the slot and the addresses
// are the binary's.

class UnkType_1098c6c0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
};

class UnkType_1098c6c0_00
{
public:
    int unk_00;
};

class UnkType_1098c6c0_04
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
};

UnkType_1098c6c0_Archive& Unk_1098c110(UnkType_1098c6c0_Archive& Archive,
                                       UnkType_1098c6c0_00& Value);
UnkType_1098c6c0_Archive& Unk_10cce480(UnkType_1098c6c0_Archive& Archive,
                                       UnkType_1098c6c0_04& Value);

class UnkType_1098c6c0
{
public:
    UnkType_1098c6c0_00 unk_00;
    UnkType_1098c6c0_04 unk_04;
    int unk_10;
};

// Unk_1098c6c0
UnkType_1098c6c0_Archive& Unk_1098c6c0(UnkType_1098c6c0_Archive& Archive, UnkType_1098c6c0& Value)
{
    UnkType_1098c6c0_Archive& Out = Unk_10cce480(Unk_1098c110(Archive, Value.unk_00), Value.unk_04);
    Out.VirtualSlot1(&Value.unk_10, 4);
    return Out;
}
