// campaign_leaf_0f2bf0.cpp -- free function at VA 0x109f2bf0 taking an archive and a dynamic array
// of 0x18-byte elements (data pointer at 0x00, count at 0x04, capacity at 0x08): calls virtual slot
// 5 of the archive with the byte sizes of the count and the capacity; when the word at 0x18 of the
// archive is set, reads a count through the function at VA 0x10cd80b0, passes it to the method at
// VA 0x109eabd0, and reads that many elements, each placed by the allocation function at VA
// 0x109d87b0 and passed to the function at VA 0x109e0d90; otherwise writes the count through VA
// 0x10cd80b0 and passes every element to VA 0x109e0d90. Returns the archive. guess: an instance of
// the engine's operator<< for a TArray. The class, member and function names are invented; the
// offsets, the slot and the addresses are the binary's.

class UnkType_109f2bf0_Archive
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

struct UnkType_109f2bf0_Element
{
    UnkType_109f2bf0_Element() : unk_00(0), unk_04(0), unk_08(0), unk_0c(0), unk_10(0), unk_14(0)
    {
    }

    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
};

class UnkType_109f2bf0
{
public:
    void Unk_109eabd0(int Slack);

    UnkType_109f2bf0_Element* unk_00;
    int unk_04;
    int unk_08;
};

UnkType_109f2bf0_Archive& Unk_10cd80b0(UnkType_109f2bf0_Archive& Archive, int& Value);
UnkType_109f2bf0_Archive& Unk_109e0d90(UnkType_109f2bf0_Archive& Archive,
                                       UnkType_109f2bf0_Element& Element);
void* operator new(unsigned int Size, UnkType_109f2bf0& Array);

// Unk_109f2bf0
UnkType_109f2bf0_Archive& Unk_109f2bf0(UnkType_109f2bf0_Archive& Archive, UnkType_109f2bf0& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_109f2bf0_Element),
                         Array.unk_08 * sizeof(UnkType_109f2bf0_Element));
    if ( Archive.unk_18 )
    {
        int NewNum;
        Unk_10cd80b0(Archive, NewNum);
        Array.Unk_109eabd0(NewNum);
        for ( int i = 0; i < NewNum; i++ )
        {
            Unk_109e0d90(Archive, *new(Array) UnkType_109f2bf0_Element);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Unk_109e0d90(Archive, Array.unk_00[i]);
        }
    }
    return Archive;
}
