// campaign_leaf_0bfcb0.cpp -- free function at VA 0x109bfcb0 taking an archive and an object: for
// the array of 16-bit values at 0x00 (count at 0x04) calls virtual slot 5 of the archive with twice
// the byte size, passes the count to the function at VA 0x10cd80b0, reallocates the array through
// the method at VA 0x10ccb3c0 when the word at 0x18 of the archive is set and writes or reads the
// data through virtual slot 1; then returns the function at VA 0x109724f0 called with the archive
// and the member at 0x08. The class, member and function names are invented; the offsets, the slots
// and the addresses are the binary's.

class UnkType_109bfcb0_Archive
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

class UnkType_109bfcb0_Array
{
public:
    void Unk_10ccb3c0(int ElementSize);

    unsigned short* unk_00;
    int unk_04;
};

struct UnkType_109bfcb0
{
    UnkType_109bfcb0_Array unk_00;
    int unk_08;
};

UnkType_109bfcb0_Archive& Unk_10cd80b0(UnkType_109bfcb0_Archive& Archive, int& Value);
UnkType_109bfcb0_Archive& Unk_109724f0(UnkType_109bfcb0_Archive& Archive, int& Value);

// Unk_109bfcb0
UnkType_109bfcb0_Archive& Unk_109bfcb0(UnkType_109bfcb0_Archive& Archive, UnkType_109bfcb0& Object)
{
    Archive.VirtualSlot5(Object.unk_00.unk_04 * sizeof(unsigned short),
                         Object.unk_00.unk_04 * sizeof(unsigned short));
    Unk_10cd80b0(Archive, Object.unk_00.unk_04);
    if ( Archive.unk_18 )
    {
        Object.unk_00.Unk_10ccb3c0(sizeof(unsigned short));
    }
    Archive.VirtualSlot1(Object.unk_00.unk_00, Object.unk_00.unk_04 * sizeof(unsigned short));
    return Unk_109724f0(Archive, Object.unk_08);
}
