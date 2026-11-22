// campaign_leaf_08d230.cpp -- one function at file offset 0x8d230, preferred VA 0x1098d230. It
// sets the words at offsets 0, 4, 8, 0x28, 0x2c, 0x30, 0x34, 0x38 and 0x3c of this object to zero
// and returns this object. The class and method names are invented; the offset and the bytes are
// the binary's.

class UnkType_1098d230
{
public:
    UnkType_1098d230 *UnkClear();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0c[0x1c];     // not touched by this function
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
};

// UnkType_1098d230::UnkClear
UnkType_1098d230 *UnkType_1098d230::UnkClear()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_28 = 0;
    unk_2c = 0;
    unk_30 = 0;
    unk_34 = 0;
    unk_38 = 0;
    unk_3c = 0;
    return this;
}
