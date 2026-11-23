// campaign_leaf_4cd730.cpp -- one function at file offset 0x4cd730, preferred VA 0x10dcd730.
// The constructor installs the vtable at 0x11144448 and builds the member at offset 4, whose
// inline constructor stores the result of its method at 0x10dcd270 at its offset 4 and clears its
// offset 8. The class, method and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_10dcd270
{
public:
    int unk_0;
    int unk_4;
    int unk_8;

    UnkType_10dcd270()
    {
        unk_4 = Unk_10dcd270();
        unk_8 = 0;
    }

    int Unk_10dcd270();
};

class UnkType_10dcd730
{
public:
    UnkType_10dcd270 unk_4;

    UnkType_10dcd730();

    virtual void VirtualSlot0();
};

// UnkType_10dcd730::UnkType_10dcd730
UnkType_10dcd730::UnkType_10dcd730()
{
}
