// campaign_leaf_084430.cpp -- free function at VA 0x10984430: serialises the array of 0x2c-byte
// elements its second argument refers to (data at 0x00, count at 0x04, capacity at 0x08) through
// the archive its first argument refers to: virtual slot 5 (vtable offset 0x14) with the byte sizes
// of the count and the capacity; when the archive's value at 0x18 is set, reads a count through the
// free function at VA 0x10cd80b0, empties the array to it with the method at VA 0x109837e0 and
// reads each new element (added with the allocation function at VA 0x10981050 and built by the
// constructor at VA 0x10aa6d50) through the free function at VA 0x10aa73c0; otherwise writes the
// count and each element the same way. Returns the archive. The class, member and function names
// are invented; the offsets, the slot, the size and the addresses are the binary's.

class UnkType_10aa6d50
{
public:
    UnkType_10aa6d50();

private:
    unsigned char unk_00[0x2c];
};

class UnkType_10984430_Archive
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

class UnkType_10984430
{
public:
    void Unk_109837e0(int Slack);

    UnkType_10aa6d50* unk_00;
    int unk_04;
    int unk_08;
};

void* operator new(unsigned int Size, UnkType_10984430& Array);
void Unk_10cd80b0(UnkType_10984430_Archive& Archive, int& Count);
UnkType_10984430_Archive& Unk_10aa73c0(UnkType_10984430_Archive& Archive, UnkType_10aa6d50& Value);

// Unk_10984430
UnkType_10984430_Archive& Unk_10984430(UnkType_10984430_Archive& Archive, UnkType_10984430& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_10aa6d50),
                         Array.unk_08 * sizeof(UnkType_10aa6d50));
    if ( Archive.unk_18 )
    {
        int Count;
        Unk_10cd80b0(Archive, Count);
        Array.Unk_109837e0(Count);
        for ( int i = 0; i < Count; i++ )
        {
            Unk_10aa73c0(Archive, *new(Array) UnkType_10aa6d50);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Unk_10aa73c0(Archive, Array.unk_00[i]);
        }
    }
    return Archive;
}
