// campaign_leaf_07cf20.cpp -- free function at VA 0x1097cf20: serialises the four floats of the
// 16-byte value its second argument refers to, four bytes each through virtual slot 1 of the
// archive its first argument refers to; returns the archive. The class, member and function names
// are invented; the offsets, the sizes and the slot are the binary's.

class UnkType_1097cf20_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
};

class UnkType_1097cf20_Value
{
public:
    float X;
    float Y;
    float Z;
    float W;
};

// Unk_1097cf20
UnkType_1097cf20_Archive& Unk_1097cf20(UnkType_1097cf20_Archive& Archive, UnkType_1097cf20_Value& Value)
{
    Archive.VirtualSlot1(&Value.X, 4);
    Archive.VirtualSlot1(&Value.Y, 4);
    Archive.VirtualSlot1(&Value.Z, 4);
    Archive.VirtualSlot1(&Value.W, 4);
    return Archive;
}
