// campaign_leaf_0be7e0.cpp -- free function at VA 0x109be7e0 taking an archive and a dynamic array
// of 4-byte elements (data pointer at 0x00, count at 0x04): calls virtual slot 5 of the archive
// with the byte size of the count twice; when the word at 0x18 of the archive is set, reads a count
// through the function at VA 0x10cd80b0, passes 0 to the method at VA 0x109b7a30 and appends that
// many elements, each time raising the count and calling the method at VA 0x10ccb3c0 with the
// element size; otherwise writes the count through VA 0x10cd80b0. Every element is passed to
// virtual slot 6 (vtable offset 0x18) of the archive. Returns the archive. guess: an instance of
// the engine's operator<< for a TArray. The class, member and function names are invented; the
// offsets, the slots and the addresses are the binary's.

class UnkType_109be7e0_Object;

class UnkType_109be7e0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Count, int Max);
    virtual UnkType_109be7e0_Archive& VirtualSlot6(UnkType_109be7e0_Object*& Object);

    unsigned char unk_04[0x18 - 0x04];
    int unk_18;
};

class UnkType_109be7e0
{
public:
    void Unk_109b7a30(int Slack);
    void Unk_10ccb3c0(int ElementSize);

    int Add()
    {
        int Index = unk_04;
        unk_04++;
        Unk_10ccb3c0(sizeof(UnkType_109be7e0_Object*));
        return Index;
    }

    UnkType_109be7e0_Object** unk_00;
    int unk_04;
};

void Unk_10cd80b0(UnkType_109be7e0_Archive& Archive, int& Value);

// Unk_109be7e0
UnkType_109be7e0_Archive& Unk_109be7e0(UnkType_109be7e0_Archive& Archive, UnkType_109be7e0& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_109be7e0_Object*),
                         Array.unk_04 * sizeof(UnkType_109be7e0_Object*));
    if ( Archive.unk_18 )
    {
        int Count;
        Unk_10cd80b0(Archive, Count);
        Array.Unk_109b7a30(0);
        for ( int i = 0; i < Count; i++ )
        {
            Archive.VirtualSlot6(Array.unk_00[Array.Add()]);
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
