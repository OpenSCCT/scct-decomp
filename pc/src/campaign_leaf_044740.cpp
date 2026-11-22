// campaign_leaf_044740.cpp -- one function at file offset 0x44740, preferred VA 0x10944740. It sets
// the thirteen words of this object to zero, except the word at offset 0x28, which it sets to -1,
// and returns this object. The class and method names are invented; the offset and the bytes are
// the binary's.

class UnkType_10944740
{
public:
    UnkType_10944740 *UnkReset();

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
};

// UnkType_10944740::UnkReset
UnkType_10944740 *UnkType_10944740::UnkReset()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0c = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1c = 0;
    unk_20 = 0;
    unk_24 = 0;
    unk_28 = -1;
    unk_2c = 0;
    unk_30 = 0;
    return this;
}
