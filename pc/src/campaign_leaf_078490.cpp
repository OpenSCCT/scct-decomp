// campaign_leaf_078490.cpp -- free function at VA 0x10978490: serialises the pointer array its
// second argument refers to (data at 0x00, count at 0x04, capacity at 0x08) through the archive its
// first argument refers to: virtual slot 5 (vtable offset 0x14) with the byte sizes of the count
// and the capacity; when the archive's value at 0x18 is set, reads a count through the free
// function at VA 0x10cd80b0, empties the array to it with the method at VA 0x109673e0 and reads
// each new element (added with the allocation function at VA 0x109672d0) through the free function
// at VA 0x10975010; otherwise writes the count and each element the same way. Returns the archive.
// The class, member and function names are invented; the offsets, the slot and the addresses are
// the binary's.

class UnkType_10978490_Object;

class UnkType_10978490_Archive
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

class UnkType_10978490
{
public:
    void Unk_109673e0(int Slack);

    UnkType_10978490_Object** unk_00;
    int unk_04;
    int unk_08;
};

void* operator new(unsigned int Size, UnkType_10978490& Array);
void Unk_10cd80b0(UnkType_10978490_Archive& Archive, int& Count);
UnkType_10978490_Archive& Unk_10975010(UnkType_10978490_Archive& Archive,
                                       UnkType_10978490_Object*& Value);

// Unk_10978490
UnkType_10978490_Archive& Unk_10978490(UnkType_10978490_Archive& Archive, UnkType_10978490& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * 4, Array.unk_08 * 4);
    if ( Archive.unk_18 )
    {
        int Count;
        Unk_10cd80b0(Archive, Count);
        Array.Unk_109673e0(Count);
        for ( int i = 0; i < Count; i++ )
        {
            Unk_10975010(Archive, *new(Array) UnkType_10978490_Object*);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Unk_10975010(Archive, Array.unk_00[i]);
        }
    }
    return Archive;
}
