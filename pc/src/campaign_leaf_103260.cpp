// campaign_leaf_103260.cpp -- clears the dwords at offsets 0x00 to 0x24 of this, except the one at
// 0x0c, and returns this. File offset 0x103260, VA 0x10a03260. The class and method names are
// invented; the offsets are the binary's.

class UnkType_10a03260
{
public:
    UnkType_10a03260 *UnkMethod_10a03260();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0c[4];        // not written by this function
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
};

// UnkType_10a03260::UnkMethod_10a03260
UnkType_10a03260 *UnkType_10a03260::UnkMethod_10a03260()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1c = 0;
    unk_20 = 0;
    unk_24 = 0;
    return this;
}
