// campaign_leaf_0cc3b0.cpp -- one function at file offset 0xcc3b0, preferred VA 0x109cc3b0. It
// sets the eighteen words of this object at the offsets from 0 to 0x4c, except 8 and 0xc, to zero
// and returns this object. The class and method names are invented; the offset and the bytes are
// the binary's.

class UnkType_109cc3b0
{
public:
    UnkType_109cc3b0 *UnkClear();

private:
    int unk_00;
    int unk_04;
    unsigned char unk_08[0x8];      // not touched by this function
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
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4c;
};

// UnkType_109cc3b0::UnkClear
UnkType_109cc3b0 *UnkType_109cc3b0::UnkClear()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_1c = 0;
    unk_18 = 0;
    unk_14 = 0;
    unk_10 = 0;
    unk_2c = 0;
    unk_28 = 0;
    unk_24 = 0;
    unk_20 = 0;
    unk_3c = 0;
    unk_38 = 0;
    unk_34 = 0;
    unk_30 = 0;
    unk_4c = 0;
    unk_48 = 0;
    unk_44 = 0;
    unk_40 = 0;
    return this;
}
