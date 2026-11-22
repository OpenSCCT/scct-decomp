// campaign_leaf_1ac4b0.cpp -- clears the dwords at offsets 0x00 to 0x24 of this, except the
// dwords at 0x28, 0x2c and 0x30, which it sets to -1, in the order the binary stores them, and
// returns this. File offset 0x1ac4b0, VA 0x10aac4b0. The class and method names are invented; the
// offsets are the binary's. The field types and the meanings are guesses.

class UnkType_10aac4b0
{
public:
    UnkType_10aac4b0 *UnkMethod_10aac4b0();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
};

// UnkType_10aac4b0::UnkMethod_10aac4b0
UnkType_10aac4b0 *UnkType_10aac4b0::UnkMethod_10aac4b0()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0c = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_34 = 0;
    unk_1c = 0;
    unk_18 = 0;
    unk_24 = 0;
    unk_20 = 0;
    unk_30 = -1;
    unk_2c = -1;
    unk_28 = -1;
    return this;
}
