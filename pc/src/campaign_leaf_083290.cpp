// campaign_leaf_083290.cpp -- free function at VA 0x10983290: serialises the pointer array its
// second argument refers to (data at 0x00, count at 0x04, capacity at 0x08) through the archive its
// first argument refers to: virtual slot 5 (vtable offset 0x14) with the byte sizes of the count
// and the capacity; when the archive's value at 0x18 is set, reads a count through the free
// function at VA 0x10cd80b0, empties the array to it with the method at VA 0x10982030 and reads
// each new element (added with the allocation function at VA 0x109512e0) through virtual slot 6
// (vtable offset 0x18); otherwise writes the count and each element the same way. Returns the
// archive. The class, member and function names are invented; the offsets, the slots and the
// addresses are the binary's.

class UnkType_10983290_Object;

class UnkType_10983290_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Size, int MaxSize);
    virtual UnkType_10983290_Archive& VirtualSlot6(UnkType_10983290_Object*& Value);

    unsigned char unk_04[0x14];
    int unk_18;
};

class UnkType_10983290
{
public:
    void Unk_10982030(int Slack);

    UnkType_10983290_Object** unk_00;
    int unk_04;
    int unk_08;
};

void* operator new(unsigned int Size, UnkType_10983290& Array);
void Unk_10cd80b0(UnkType_10983290_Archive& Archive, int& Count);

// Unk_10983290
UnkType_10983290_Archive& Unk_10983290(UnkType_10983290_Archive& Archive, UnkType_10983290& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * 4, Array.unk_08 * 4);
    if ( Archive.unk_18 )
    {
        int Count;
        Unk_10cd80b0(Archive, Count);
        Array.Unk_10982030(Count);
        for ( int i = 0; i < Count; i++ )
        {
            Archive.VirtualSlot6(*new(Array) UnkType_10983290_Object*);
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
