// campaign_leaf_0dccb0.cpp -- free function at VA 0x109dccb0 taking an archive and an array of
// 6-byte elements (data pointer at 0x00, count at 0x04): calls virtual slot 5 of the archive with
// twice the byte size, passes the count to the function at VA 0x10cd80b0, reallocates the array
// through the method at VA 0x10ccb3c0 when the word at 0x18 of the archive is set, writes or reads
// the data through virtual slot 1 and returns the archive. guess: the engine's operator<< for a
// TArray. The class, member and function names are invented; the offsets, the slots and the
// addresses are the binary's.

class UnkType_109dccb0_Archive
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

struct UnkType_109dccb0_Element
{
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
};

class UnkType_109dccb0
{
public:
    void Unk_10ccb3c0(int ElementSize);

    UnkType_109dccb0_Element* unk_00;
    int unk_04;
};

UnkType_109dccb0_Archive& Unk_10cd80b0(UnkType_109dccb0_Archive& Archive, int& Value);

// Unk_109dccb0
UnkType_109dccb0_Archive& Unk_109dccb0(UnkType_109dccb0_Archive& Archive, UnkType_109dccb0& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_109dccb0_Element),
                         Array.unk_04 * sizeof(UnkType_109dccb0_Element));
    Unk_10cd80b0(Archive, Array.unk_04);
    if ( Archive.unk_18 )
    {
        Array.Unk_10ccb3c0(sizeof(UnkType_109dccb0_Element));
    }
    Archive.VirtualSlot1(Array.unk_00, Array.unk_04 * sizeof(UnkType_109dccb0_Element));
    return Archive;
}
