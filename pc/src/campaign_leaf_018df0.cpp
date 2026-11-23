// campaign_leaf_018df0.cpp -- free function at VA 0x10918df0: serialises the pointer array its
// second argument refers to (data at 0x00, count at 0x04, capacity at 0x08) through the archive its
// first argument refers to: virtual slot 5 (vtable offset 0x14) with the byte sizes of the count
// and the capacity; when the archive's value at 0x18 is set, reads a count through the free
// function at VA 0x10cd80b0, empties the array to it with the method at VA 0x10917720, adds that
// many 4-byte elements with the method at VA 0x109176d0 and reads each through virtual slot 6
// (vtable offset 0x18); otherwise writes the count and each element the same way. Returns the
// archive. The class, member and function names are invented; the offsets, the slots, the size and
// the addresses are the binary's.

class UnkType_10918df0_Object;

class UnkType_10918df0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Size, int MaxSize);
    virtual UnkType_10918df0_Archive& VirtualSlot6(UnkType_10918df0_Object*& Value);

    unsigned char unk_04[0x14];
    int unk_18;
};

class UnkType_10918df0
{
public:
    void Unk_10917720(int Slack);
    int Unk_109176d0(int Count, int ElementSize);

    UnkType_10918df0_Object** unk_00;
    int unk_04;
    int unk_08;
};

void Unk_10cd80b0(UnkType_10918df0_Archive& Archive, int& Count);

// Unk_10918df0
UnkType_10918df0_Archive& Unk_10918df0(UnkType_10918df0_Archive& Archive, UnkType_10918df0& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * 4, Array.unk_08 * 4);
    if ( Archive.unk_18 )
    {
        int Count;
        Unk_10cd80b0(Archive, Count);
        Array.Unk_10917720(Count);
        Array.Unk_109176d0(Count, 4);
        for ( int i = 0; i < Count; i++ )
        {
            Archive.VirtualSlot6(Array.unk_00[i]);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Archive.VirtualSlot6(Array.unk_00[i]);
        }
    }
    return Archive;
}
