// campaign_leaf_082590.cpp -- free function at VA 0x10982590: serialises the object its second
// argument refers to: the pointer at 0x00 through virtual slot 6 (vtable offset 0x18) of the
// archive its first argument refers to, then, through the archive that returns, the byte array at
// 0x04 (data pointer at 0x04, count at 0x08: virtual slot 5 with the count twice, the count through
// the free function at VA 0x10cd80b0, the method at VA 0x10ccb3c0 with element size 1 when the
// archive's value at 0x18 is set, and virtual slot 1 with the data) and the values at 0x0c and
// 0x10; finally the value at 0x14 through the first archive, which it returns. The class, member
// and function names are invented; the offsets, the slots, the sizes and the addresses are the
// binary's.

class UnkType_10982590_Object;

class UnkType_10982590_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Size, int MaxSize);
    virtual UnkType_10982590_Archive& VirtualSlot6(UnkType_10982590_Object*& Value);

    unsigned char unk_04[0x14];
    int unk_18;
};

class UnkType_10982590_Bytes
{
public:
    void Unk_10ccb3c0(int ElementSize);

    unsigned char* unk_00;
    int unk_04;
};

void Unk_10cd80b0(UnkType_10982590_Archive& Archive, int& Count);

class UnkType_10982590
{
public:
    UnkType_10982590_Object* unk_00;
    UnkType_10982590_Bytes unk_04;
    int unk_0c;
    int unk_10;
    int unk_14;
};

// Unk_10982590
UnkType_10982590_Archive& Unk_10982590(UnkType_10982590_Archive& Archive, UnkType_10982590& Value)
{
    UnkType_10982590_Archive& Out = Archive.VirtualSlot6(Value.unk_00);
    Out.VirtualSlot5(Value.unk_04.unk_04, Value.unk_04.unk_04);
    Unk_10cd80b0(Out, Value.unk_04.unk_04);
    if ( Out.unk_18 )
    {
        Value.unk_04.Unk_10ccb3c0(1);
    }
    Out.VirtualSlot1(Value.unk_04.unk_00, Value.unk_04.unk_04);
    Out.VirtualSlot1(&Value.unk_0c, 4);
    Out.VirtualSlot1(&Value.unk_10, 4);
    Archive.VirtualSlot1(&Value.unk_14, 4);
    return Archive;
}
