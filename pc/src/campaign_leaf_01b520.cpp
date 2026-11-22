// campaign_leaf_01b520.cpp -- one function at file offset 0x1b520, preferred VA 0x1091b520. It sets
// the eleven words from offset 0 to offset 0x28 of this object to zero and returns this object. The
// class and method names are invented; the offset and the bytes are the binary's.

class UnkType_1091b520
{
public:
    UnkType_1091b520 *UnkClear();

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
};

// UnkType_1091b520::UnkClear
UnkType_1091b520 *UnkType_1091b520::UnkClear()
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
    unk_28 = 0;
    return this;
}
