// campaign_leaf_078890.cpp -- free function at VA 0x10978890: serialises the object its second
// argument refers to into the object its first argument refers to: the member at 0x10 through the
// free function at VA 0x109781c0, then the values at 0x04 and 0x08 (four bytes each) and the bytes
// at 0x0c and 0x0d through virtual slot 1 (vtable offset 0x04); returns the first argument. The
// class, member and function names are invented; the offsets, the sizes and the address are the
// binary's.

class UnkType_10978890_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
};

class UnkType_10978890_10
{
public:
    int unk_00;
};

UnkType_10978890_Archive& Unk_109781c0(UnkType_10978890_Archive& Archive,
                                       UnkType_10978890_10& Value);

class UnkType_10978890
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0c;
    unsigned char unk_0d;
    unsigned char unk_0e[2];
    UnkType_10978890_10 unk_10;
};

// Unk_10978890
UnkType_10978890_Archive& Unk_10978890(UnkType_10978890_Archive& Archive, UnkType_10978890& Value)
{
    Unk_109781c0(Archive, Value.unk_10);
    Archive.VirtualSlot1(&Value.unk_04, 4);
    Archive.VirtualSlot1(&Value.unk_08, 4);
    Archive.VirtualSlot1(&Value.unk_0c, 1);
    Archive.VirtualSlot1(&Value.unk_0d, 1);
    return Archive;
}
