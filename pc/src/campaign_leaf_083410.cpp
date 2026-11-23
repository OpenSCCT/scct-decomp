// campaign_leaf_083410.cpp -- free function at VA 0x10983410: serialises the array of 0x18-byte
// elements its second argument refers to (data at 0x00, count at 0x04, capacity at 0x08) through
// the archive its first argument refers to: virtual slot 5 (vtable offset 0x14) with the byte sizes
// of the count and the capacity; when the archive's value at 0x18 is set, reads a count through the
// free function at VA 0x10cd80b0, empties the array to it with the method at VA 0x10982140 and
// reads each new element (added with the allocation function at VA 0x10980f10) through the free
// function at VA 0x10982590; otherwise writes the count and each element the same way. Returns the
// archive. The class, member and function names are invented; the offsets, the slot, the size and
// the addresses are the binary's.

class UnkType_10982590_083410_04
{
public:
    UnkType_10982590_083410_04()
    : unk_00(0)
    , unk_04(0)
    {
    }

private:
    void* unk_00;
    int unk_04;
};

class UnkType_10982590_083410
{
public:
    void* unk_00;
    UnkType_10982590_083410_04 unk_04;
    int unk_0c;
    int unk_10;
    int unk_14;
};

class UnkType_10983410_Archive
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

class UnkType_10983410
{
public:
    void Unk_10982140(int Slack);

    UnkType_10982590_083410* unk_00;
    int unk_04;
    int unk_08;
};

void* operator new(unsigned int Size, UnkType_10983410& Array);
void Unk_10cd80b0(UnkType_10983410_Archive& Archive, int& Count);
UnkType_10983410_Archive& Unk_10982590(UnkType_10983410_Archive& Archive,
                                       UnkType_10982590_083410& Value);

// Unk_10983410
UnkType_10983410_Archive& Unk_10983410(UnkType_10983410_Archive& Archive, UnkType_10983410& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_10982590_083410),
                         Array.unk_08 * sizeof(UnkType_10982590_083410));
    if ( Archive.unk_18 )
    {
        int Count;
        Unk_10cd80b0(Archive, Count);
        Array.Unk_10982140(Count);
        for ( int i = 0; i < Count; i++ )
        {
            Unk_10982590(Archive, *new(Array) UnkType_10982590_083410);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Unk_10982590(Archive, Array.unk_00[i]);
        }
    }
    return Archive;
}
