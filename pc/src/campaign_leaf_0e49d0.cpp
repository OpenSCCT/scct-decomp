// campaign_leaf_0e49d0.cpp -- free function at VA 0x109e49d0 taking an archive and a dynamic array
// of 8-byte elements (data pointer at 0x00, count at 0x04, capacity at 0x08): calls virtual slot 5
// of the archive with the byte sizes of the count and the capacity; when the word at 0x18 of the
// archive is set, reads a count through the function at VA 0x10cd80b0, passes it to the method at
// VA 0x109e0050, and reads that many elements, each placed by the allocation function at VA
// 0x109da640; otherwise writes the count and every element. Each element passes the fields at 0x04
// and 0x05 to virtual slot 1. Returns the archive. guess: an instance of the engine's operator<<
// for a TArray. The class, member and function names are invented; the offsets, the slots and the
// addresses are the binary's.

class UnkType_109e49d0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Length);
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Count, int Max);

    unsigned char unk_04[0x18 - 0x04];
    int unk_18;
};

struct UnkType_109e49d0_Element
{
    unsigned char unk_00[0x04];
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06[0x08 - 0x06];
};

// operator<<
inline UnkType_109e49d0_Archive& operator<<(UnkType_109e49d0_Archive& Archive,
                                        UnkType_109e49d0_Element& Element)
{
    Archive.VirtualSlot1(&Element.unk_04, sizeof(Element.unk_04));
    Archive.VirtualSlot1(&Element.unk_05, sizeof(Element.unk_05));
    return Archive;
}

class UnkType_109e49d0
{
public:
    void Unk_109e0050(int Slack);

    UnkType_109e49d0_Element* unk_00;
    int unk_04;
    int unk_08;
};

UnkType_109e49d0_Archive& Unk_10cd80b0(UnkType_109e49d0_Archive& Archive, int& Value);
void* operator new(unsigned int Size, UnkType_109e49d0& Array);

// Unk_109e49d0
UnkType_109e49d0_Archive& Unk_109e49d0(UnkType_109e49d0_Archive& Archive, UnkType_109e49d0& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_109e49d0_Element),
                         Array.unk_08 * sizeof(UnkType_109e49d0_Element));
    if ( Archive.unk_18 )
    {
        int NewNum;
        Unk_10cd80b0(Archive, NewNum);
        Array.Unk_109e0050(NewNum);
        for ( int i = 0; i < NewNum; i++ )
        {
            Archive << *new(Array) UnkType_109e49d0_Element;
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Archive << Array.unk_00[i];
        }
    }
    return Archive;
}
