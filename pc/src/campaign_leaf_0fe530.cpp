// campaign_leaf_0fe530.cpp -- free function at VA 0x109fe530 taking an archive and a dynamic array
// of 0x3c-byte elements (data pointer at 0x00, count at 0x04, capacity at 0x08): calls virtual slot
// 5 of the archive with the byte sizes of the count and the capacity; when the word at 0x18 of the
// archive is set, reads a count through the function at VA 0x10cd80b0, passes it to the method at
// VA 0x109fd0b0, and reads that many elements, each placed by the allocation function at VA
// 0x109df270 and passed to the function at VA 0x109f36f0; otherwise writes the count through VA
// 0x10cd80b0 and passes every element to VA 0x109f36f0. Returns the archive. guess: an instance of
// the engine's operator<< for a TArray. The class, member and function names are invented; the
// offsets, the slot and the addresses are the binary's.

class UnkType_109fe530_Archive
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

struct UnkType_109fe530_Element
{
    UnkType_109fe530_Element() : unk_18(0), unk_1c(0), unk_20(0), unk_2c(0), unk_30(0), unk_34(0),
                             unk_38(0)
    {
    }

    unsigned char unk_00[0x18];
    int unk_18;
    int unk_1c;
    int unk_20;
    unsigned char unk_24[0x2c - 0x24];
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
};

class UnkType_109fe530
{
public:
    void Unk_109fd0b0(int Slack);

    UnkType_109fe530_Element* unk_00;
    int unk_04;
    int unk_08;
};

UnkType_109fe530_Archive& Unk_10cd80b0(UnkType_109fe530_Archive& Archive, int& Value);
UnkType_109fe530_Archive& Unk_109f36f0(UnkType_109fe530_Archive& Archive,
                                       UnkType_109fe530_Element& Element);
void* operator new(unsigned int Size, UnkType_109fe530& Array);

// Unk_109fe530
UnkType_109fe530_Archive& Unk_109fe530(UnkType_109fe530_Archive& Archive, UnkType_109fe530& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_109fe530_Element),
                         Array.unk_08 * sizeof(UnkType_109fe530_Element));
    if ( Archive.unk_18 )
    {
        int NewNum;
        Unk_10cd80b0(Archive, NewNum);
        Array.Unk_109fd0b0(NewNum);
        for ( int i = 0; i < NewNum; i++ )
        {
            Unk_109f36f0(Archive, *new(Array) UnkType_109fe530_Element);
        }
    }
    else
    {
        Unk_10cd80b0(Archive, Array.unk_04);
        for ( int i = 0; i < Array.unk_04; i++ )
        {
            Unk_109f36f0(Archive, Array.unk_00[i]);
        }
    }
    return Archive;
}
