// campaign_leaf_073f10.cpp -- free function at VA 0x10973f10: serialises the array of 0x1c-byte
// elements (each with a member at 0x10 that an inline constructor clears) its second argument
// refers to (data at 0x00, count at 0x04, capacity at 0x08) through the archive its first argument
// refers to: virtual slot 5 (vtable offset 0x14) with the byte sizes of the count and the capacity;
// when the archive's value at 0x18 is set, reads a count through the free function at VA
// 0x10cd80b0, empties the array to it with the method at VA 0x10973dd0 and reads each new element
// (added with the allocation function at VA 0x10973960) through the free function at VA 0x10973c40;
// otherwise writes the count and each element the same way. Returns the archive. The class, member
// and function names are invented; the offsets, the slot, the size and the addresses are the
// binary's.

class UnkType_1090ba70_073f10
{
public:
    UnkType_1090ba70_073f10()
    : unk_00(0)
    , unk_04(0)
    , unk_08(0)
    {
    }

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10973c40
{
public:
    unsigned char unk_00[0x10];
    UnkType_1090ba70_073f10 unk_10;
};

class UnkType_10973f10_Archive
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

class UnkType_10973f10
{
public:
    void Unk_10973dd0(int Slack);

    UnkType_10973c40* unk_00;
    int unk_04;
    int unk_08;
};

void* operator new(unsigned int Size, UnkType_10973f10& Array);
void Unk_10cd80b0(UnkType_10973f10_Archive& Archive, int& Count);
UnkType_10973f10_Archive& Unk_10973c40(UnkType_10973f10_Archive& Archive, UnkType_10973c40& Value);

// Unk_10973f10
UnkType_10973f10_Archive& Unk_10973f10(UnkType_10973f10_Archive& Archive, UnkType_10973f10& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_10973c40),
                         Array.unk_08 * sizeof(UnkType_10973c40));
    if ( Archive.unk_18 )
    {
        int Count;
        Unk_10cd80b0(Archive, Count);
        Array.Unk_10973dd0(Count);
        for ( int i = 0; i < Count; i++ )
        {
            Unk_10973c40(Archive, *new(Array) UnkType_10973c40);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Unk_10973c40(Archive, Array.unk_00[i]);
        }
    }
    return Archive;
}
