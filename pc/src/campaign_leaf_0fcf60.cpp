// campaign_leaf_0fcf60.cpp -- free function at VA 0x109fcf60 taking an archive and a dynamic array
// of 0x48-byte elements (data pointer at 0x00, count at 0x04, capacity at 0x08): calls virtual slot
// 5 of the archive with the byte sizes of the count and the capacity; when the word at 0x18 of the
// archive is set, reads a count through the function at VA 0x10cd80b0, passes it to the method at
// VA 0x109f2d40, and reads that many elements, each placed by the allocation function at VA
// 0x109df2c0 and passed to the function at VA 0x109f1990; otherwise writes the count through VA
// 0x10cd80b0 and passes every element to VA 0x109f1990. Returns the archive. guess: an instance of
// the engine's operator<< for a TArray. The class, member and function names are invented; the
// offsets, the slot and the addresses are the binary's.

class UnkType_109fcf60_Archive
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

class UnkType_109fcf60_Element
{
public:
    UnkType_109fcf60_Element();

private:
    unsigned char unk_00[0x48];
};

class UnkType_109fcf60
{
public:
    void Unk_109f2d40(int Slack);

    UnkType_109fcf60_Element* unk_00;
    int unk_04;
    int unk_08;
};

UnkType_109fcf60_Archive& Unk_10cd80b0(UnkType_109fcf60_Archive& Archive, int& Value);
UnkType_109fcf60_Archive& Unk_109f1990(UnkType_109fcf60_Archive& Archive,
                                       UnkType_109fcf60_Element& Element);
void* operator new(unsigned int Size, UnkType_109fcf60& Array);

// Unk_109fcf60
UnkType_109fcf60_Archive& Unk_109fcf60(UnkType_109fcf60_Archive& Archive, UnkType_109fcf60& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_109fcf60_Element),
                         Array.unk_08 * sizeof(UnkType_109fcf60_Element));
    if ( Archive.unk_18 )
    {
        int NewNum;
        Unk_10cd80b0(Archive, NewNum);
        Array.Unk_109f2d40(NewNum);
        for ( int i = 0; i < NewNum; i++ )
        {
            Unk_109f1990(Archive, *new(Array) UnkType_109fcf60_Element);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Unk_109f1990(Archive, Array.unk_00[i]);
        }
    }
    return Archive;
}
