// campaign_leaf_4db940.cpp -- one function at file offset 0x4db940, preferred VA 0x10ddb940.
// The constructor installs the vtable at 0x11146518, builds the member at offset 4, whose inline
// constructor stores the result of its method at 0x10ddb5a0 at its offset 4 and clears its offset
// 8, and clears the int at offset 0x14. The class, method and member names are invented; the
// offset and the bytes are the binary's.

class UnkType_10ddb5a0
{
public:
    int unk_0;
    int unk_4;
    int unk_8;

    UnkType_10ddb5a0()
    {
        unk_4 = Unk_10ddb5a0();
        unk_8 = 0;
    }

    int Unk_10ddb5a0();
};

class UnkType_10ddb940
{
public:
    UnkType_10ddb5a0 unk_4;
    int unk_10;
    int unk_14;

    UnkType_10ddb940();

    virtual void VirtualSlot0();
};

// UnkType_10ddb940::UnkType_10ddb940
UnkType_10ddb940::UnkType_10ddb940()
{
    unk_14 = 0;
}
