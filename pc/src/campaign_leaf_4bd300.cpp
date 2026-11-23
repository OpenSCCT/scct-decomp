// campaign_leaf_4bd300.cpp -- one function at file offset 0x4bd300, preferred VA 0x10dbd300.
// The constructor runs the base constructor at 0x10d98fa0 with 5, installs the vtable at
// 0x11142724, clears the ints at offsets 0x14 and 0x18 and sets the byte at offset 0x1c. The class
// and member names are invented; the offset and the bytes are the binary's.

class UnkType_10dbd300_Base
{
public:
    unsigned char unk_4[0x10];

    UnkType_10dbd300_Base(int Value);

    virtual void VirtualSlot0();
};

class UnkType_10dbd300 : public UnkType_10dbd300_Base
{
public:
    int unk_14;
    int unk_18;
    bool unk_1c;

    UnkType_10dbd300();

    virtual void VirtualSlot0();
};

// UnkType_10dbd300::UnkType_10dbd300
UnkType_10dbd300::UnkType_10dbd300()
    : UnkType_10dbd300_Base(5)
{
    unk_14 = 0;
    unk_18 = 0;
    unk_1c = true;
}
