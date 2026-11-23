// campaign_leaf_0ea230.cpp -- free function at VA 0x109ea230 taking an archive and a dynamic array
// of 0x1c-byte elements (data pointer at 0x00, count at 0x04, capacity at 0x08): calls virtual slot
// 5 of the archive with the byte sizes of the count and the capacity; when the word at 0x18 of the
// archive is set, reads a count through the function at VA 0x10cd80b0, passes it to the method at
// VA 0x109e2f10, and reads that many elements, each placed by the allocation function at VA
// 0x109df090 and passed to the function at VA 0x109cd820; otherwise writes the count through VA
// 0x10cd80b0 and passes every element to VA 0x109cd820. Returns the archive. guess: an instance of
// the engine's operator<< for a TArray. The class, member and function names are invented; the
// offsets, the slot and the addresses are the binary's.

class UnkType_109ea230_Archive
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

struct UnkType_109ea230_Element
{
    unsigned char unk_00[0x1c];
};

class UnkType_109ea230
{
public:
    void Unk_109e2f10(int Slack);

    UnkType_109ea230_Element* unk_00;
    int unk_04;
    int unk_08;
};

UnkType_109ea230_Archive& Unk_10cd80b0(UnkType_109ea230_Archive& Archive, int& Value);
UnkType_109ea230_Archive& Unk_109cd820(UnkType_109ea230_Archive& Archive,
                                       UnkType_109ea230_Element& Element);
void* operator new(unsigned int Size, UnkType_109ea230& Array);

// Unk_109ea230
UnkType_109ea230_Archive& Unk_109ea230(UnkType_109ea230_Archive& Archive, UnkType_109ea230& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_109ea230_Element),
                         Array.unk_08 * sizeof(UnkType_109ea230_Element));
    if ( Archive.unk_18 )
    {
        int NewNum;
        Unk_10cd80b0(Archive, NewNum);
        Array.Unk_109e2f10(NewNum);
        for ( int i = 0; i < NewNum; i++ )
        {
            Unk_109cd820(Archive, *new(Array) UnkType_109ea230_Element);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Unk_109cd820(Archive, Array.unk_00[i]);
        }
    }
    return Archive;
}
