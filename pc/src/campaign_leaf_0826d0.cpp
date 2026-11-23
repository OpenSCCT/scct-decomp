// campaign_leaf_0826d0.cpp -- free function at VA 0x109826d0: serialises the array of 0x1c-byte
// elements its second argument refers to (data at 0x00, count at 0x04, capacity at 0x08) through
// the archive its first argument refers to: virtual slot 5 (vtable offset 0x14) with the byte sizes
// of the count and the capacity; when the archive's value at 0x18 is set, reads a count through the
// free function at VA 0x10cd80b0, empties the array to it with the method at VA 0x10981350 and
// reads each new element (added with the allocation function at VA 0x10980540) through the free
// function at VA 0x1097ed20; otherwise writes the count and each element the same way. Returns the
// archive. The class, member and function names are invented; the offsets, the slot, the size and
// the addresses are the binary's.

class UnkType_109826d0_Item
{
public:
    unsigned char unk_00[0x1c];
};

class UnkType_109826d0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Size, int MaxSize);

    unsigned char unk_04[0x14];
    int unk_18;
};

class UnkType_109826d0
{
public:
    void Unk_10981350(int Slack);

    UnkType_109826d0_Item* unk_00;
    int unk_04;
    int unk_08;
};

void* operator new(unsigned int Size, UnkType_109826d0& Array);
void Unk_10cd80b0(UnkType_109826d0_Archive& Archive, int& Count);
UnkType_109826d0_Archive& Unk_1097ed20(UnkType_109826d0_Archive& Archive,
                                       UnkType_109826d0_Item& Value);

// Unk_109826d0
UnkType_109826d0_Archive& Unk_109826d0(UnkType_109826d0_Archive& Archive, UnkType_109826d0& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_109826d0_Item),
                         Array.unk_08 * sizeof(UnkType_109826d0_Item));
    if ( Archive.unk_18 )
    {
        int Count;
        Unk_10cd80b0(Archive, Count);
        Array.Unk_10981350(Count);
        for ( int i = 0; i < Count; i++ )
        {
            Unk_1097ed20(Archive, *new(Array) UnkType_109826d0_Item);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Unk_1097ed20(Archive, Array.unk_00[i]);
        }
    }
    return Archive;
}
