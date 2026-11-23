// campaign_leaf_4bf2c0.cpp -- one function at file offset 0x4bf2c0, preferred VA 0x10dbf2c0.
// The constructor installs the vtable at 0x11142944, builds the member at offset 4 with the
// constructor at 0x10d8b2d0, clears the ints at offsets 0x10, 0x14 and 0x18 and stores 2 at offset
// 8. The class and member names are invented; the offset and the bytes are the binary's.

class UnkType_10dbf2c0_Member
{
public:
    int unk_0;

    UnkType_10dbf2c0_Member();
};

class UnkType_10dbf2c0
{
public:
    UnkType_10dbf2c0_Member unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    int unk_18;

    UnkType_10dbf2c0();

    virtual void VirtualSlot0();
};

// UnkType_10dbf2c0::UnkType_10dbf2c0
UnkType_10dbf2c0::UnkType_10dbf2c0()
{
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_8 = 2;
}
