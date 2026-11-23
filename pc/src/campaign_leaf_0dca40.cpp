// campaign_leaf_0dca40.cpp -- free function at VA 0x109dca40 taking an archive and a dynamic array
// of 0x9c-byte elements (data pointer at 0x00, count at 0x04): calls virtual slot 5 of the archive
// with the byte size of the count twice; when the word at 0x18 of the archive is set, reads a count
// through the function at VA 0x10cd80b0, passes 0 to the method at VA 0x109d7800, and that many
// times appends one element (count plus one, then the method at VA 0x10ccb3c0 with the element
// size) and passes it to the function at VA 0x109ca160; otherwise writes the count through VA
// 0x10cd80b0 and passes every element to VA 0x109ca160. Returns the archive. The class, member and
// function names are invented; the offsets, the slot and the addresses are the binary's.

class UnkType_109dca40_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Count, int Max);

    unsigned char unk_04[0x18 - 0x04];
    int unk_18;
};

struct UnkType_109dca40_Element
{
    unsigned char unk_00[0x9c];
};

class UnkType_109dca40
{
public:
    void Unk_109d7800(int Slack);
    void Unk_10ccb3c0(int ElementSize);

    int Add()
    {
        int Index = unk_04;
        unk_04 += 1;
        Unk_10ccb3c0(sizeof(UnkType_109dca40_Element));
        return Index;
    }

    UnkType_109dca40_Element* unk_00;
    int unk_04;
};

UnkType_109dca40_Archive& Unk_10cd80b0(UnkType_109dca40_Archive& Archive, int& Value);
UnkType_109dca40_Archive& Unk_109ca160(UnkType_109dca40_Archive& Archive,
                                       UnkType_109dca40_Element& Element);

// Unk_109dca40
UnkType_109dca40_Archive& Unk_109dca40(UnkType_109dca40_Archive& Archive, UnkType_109dca40& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_109dca40_Element),
                         Array.unk_04 * sizeof(UnkType_109dca40_Element));
    if ( Archive.unk_18 )
    {
        int NewNum;
        Unk_10cd80b0(Archive, NewNum);
        Array.Unk_109d7800(0);
        for ( int i = 0; i < NewNum; i++ )
        {
            Unk_109ca160(Archive, Array.unk_00[Array.Add()]);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Unk_109ca160(Archive, Array.unk_00[i]);
        }
    }
    return Archive;
}
