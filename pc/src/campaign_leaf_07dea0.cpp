// campaign_leaf_07dea0.cpp -- free function at VA 0x1097dea0: serialises the array of 16-byte
// elements its second argument refers to (data at 0x00, count at 0x04, capacity at 0x08) through
// the archive its first argument refers to; each element is a pointer at 0x00, serialised through
// virtual slot 6 (vtable offset 0x18), and an array at 0x04 (cleared by an inline constructor),
// serialised through the free function at VA 0x1097d990 on the archive that slot returns. First
// virtual slot 5 (vtable offset 0x14) gets the byte sizes of the count and the capacity; when the
// archive's value at 0x18 is set, a count is read through the free function at VA 0x10cd80b0, the
// array emptied to it with the method at VA 0x1097dd50 and each new element added with the
// allocation function at VA 0x1097d660; otherwise the count and each element are written the same
// way. Returns the archive. The class, member and function names are invented; the offsets, the
// slots, the size and the addresses are the binary's.

class UnkType_1097dea0_Object;

class UnkType_1097d990_07dea0
{
public:
    UnkType_1097d990_07dea0()
    : unk_00(0)
    , unk_04(0)
    , unk_08(0)
    {
    }

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1097d660_07dea0
{
public:
    UnkType_1097dea0_Object* unk_00;
    UnkType_1097d990_07dea0 unk_04;
};

class UnkType_1097dea0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Size, int MaxSize);
    virtual UnkType_1097dea0_Archive& VirtualSlot6(UnkType_1097dea0_Object*& Value);

    unsigned char unk_04[0x14];
    int unk_18;
};

class UnkType_1097dea0
{
public:
    void Unk_1097dd50(int Slack);

    UnkType_1097d660_07dea0* unk_00;
    int unk_04;
    int unk_08;
};

void* operator new(unsigned int Size, UnkType_1097dea0& Array);
void Unk_10cd80b0(UnkType_1097dea0_Archive& Archive, int& Count);
UnkType_1097dea0_Archive& Unk_1097d990(UnkType_1097dea0_Archive& Archive,
                                       UnkType_1097d990_07dea0& Value);

// Unk_1097dea0
UnkType_1097dea0_Archive& Unk_1097dea0(UnkType_1097dea0_Archive& Archive, UnkType_1097dea0& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_1097d660_07dea0),
                         Array.unk_08 * sizeof(UnkType_1097d660_07dea0));
    if ( Archive.unk_18 )
    {
        int Count;
        Unk_10cd80b0(Archive, Count);
        Array.Unk_1097dd50(Count);
        for ( int i = 0; i < Count; i++ )
        {
            UnkType_1097d660_07dea0* Item = new(Array) UnkType_1097d660_07dea0;
            Unk_1097d990(Archive.VirtualSlot6(Item->unk_00), Item->unk_04);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            UnkType_1097d660_07dea0& Item = Array.unk_00[i];
            Unk_1097d990(Archive.VirtualSlot6(Item.unk_00), Item.unk_04);
        }
    }
    return Archive;
}
