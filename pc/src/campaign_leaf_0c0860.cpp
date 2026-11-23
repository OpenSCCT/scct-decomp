// campaign_leaf_0c0860.cpp -- free function at VA 0x109c0860 taking an archive and a dynamic array
// of 0x1c-byte elements (data pointer at 0x00, count at 0x04, capacity at 0x08): calls virtual slot
// 5 of the archive with the byte sizes of the count and the capacity; when the word at 0x18 of the
// archive is set, reads a count through the function at VA 0x10cd80b0, passes it to the method at
// VA 0x109bf7c0, and reads that many elements, each placed by the allocation function at VA
// 0x109beed0 and passed to the function at VA 0x109b6b70; otherwise writes the count through VA
// 0x10cd80b0 and passes every element to VA 0x109b6b70. Returns the archive. guess: an instance of
// the engine's operator<< for a TArray. The class, member and function names are invented; the
// offsets, the slot and the addresses are the binary's.

class UnkType_109c0860_Archive
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

class UnkType_109c0860_Element
{
public:
    UnkType_109c0860_Element();

private:
    unsigned char unk_00[0x1c];
};

class UnkType_109c0860
{
public:
    void Unk_109bf7c0(int Slack);

    UnkType_109c0860_Element* unk_00;
    int unk_04;
    int unk_08;
};

UnkType_109c0860_Archive& Unk_10cd80b0(UnkType_109c0860_Archive& Archive, int& Value);
UnkType_109c0860_Archive& Unk_109b6b70(UnkType_109c0860_Archive& Archive,
                                       UnkType_109c0860_Element& Element);
void* operator new(unsigned int Size, UnkType_109c0860& Array);

// Unk_109c0860
UnkType_109c0860_Archive& Unk_109c0860(UnkType_109c0860_Archive& Archive, UnkType_109c0860& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_109c0860_Element),
                         Array.unk_08 * sizeof(UnkType_109c0860_Element));
    if ( Archive.unk_18 )
    {
        int NewNum;
        Unk_10cd80b0(Archive, NewNum);
        Array.Unk_109bf7c0(NewNum);
        for ( int i = 0; i < NewNum; i++ )
        {
            Unk_109b6b70(Archive, *new(Array) UnkType_109c0860_Element);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Unk_109b6b70(Archive, Array.unk_00[i]);
        }
    }
    return Archive;
}
