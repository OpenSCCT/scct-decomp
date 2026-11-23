// campaign_leaf_0e0d90.cpp -- free function at VA 0x109e0d90 taking an archive and an object:
// passes the member at 0x00 to the function at VA 0x109dcc00 and the member at 0x08 to the function
// at VA 0x109dccb0, then for the byte array at 0x10 (count at 0x14) calls virtual slot 5 of the
// archive those return with twice the count, passes the count to the function at VA 0x10cd80b0,
// reallocates the array through the method at VA 0x10ccb3c0 when the word at 0x18 of the archive is
// set, writes or reads the data through virtual slot 1 and returns the archive. The class, member
// and function names are invented; the offsets, the slots and the addresses are the binary's.

class UnkType_109e0d90_Archive
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

struct UnkType_109e0d90_First
{
    int unk_00;
    int unk_04;
};

struct UnkType_109e0d90_Second
{
    void* unk_00;
    int unk_04;
};

class UnkType_109e0d90_Bytes
{
public:
    void Unk_10ccb3c0(int ElementSize);

    unsigned char* unk_00;
    int unk_04;
};

struct UnkType_109e0d90
{
    UnkType_109e0d90_First unk_00;
    UnkType_109e0d90_Second unk_08;
    UnkType_109e0d90_Bytes unk_10;
};

UnkType_109e0d90_Archive& Unk_10cd80b0(UnkType_109e0d90_Archive& Archive, int& Value);
UnkType_109e0d90_Archive& Unk_109dcc00(UnkType_109e0d90_Archive& Archive,
                                       UnkType_109e0d90_First& Value);
UnkType_109e0d90_Archive& Unk_109dccb0(UnkType_109e0d90_Archive& Archive,
                                       UnkType_109e0d90_Second& Value);

// Unk_109e0d90
UnkType_109e0d90_Archive& Unk_109e0d90(UnkType_109e0d90_Archive& Archive, UnkType_109e0d90& Object)
{
    UnkType_109e0d90_Bytes& Bytes = Object.unk_10;
    UnkType_109e0d90_Archive& Result =
        Unk_109dccb0(Unk_109dcc00(Archive, Object.unk_00), Object.unk_08);
    Result.VirtualSlot5(Bytes.unk_04, Bytes.unk_04);
    Unk_10cd80b0(Result, Bytes.unk_04);
    if ( Result.unk_18 )
    {
        Bytes.Unk_10ccb3c0(1);
    }
    Result.VirtualSlot1(Bytes.unk_00, Bytes.unk_04);
    return Result;
}
