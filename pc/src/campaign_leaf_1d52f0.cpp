// campaign_leaf_1d52f0.cpp -- returns the number of dwords in the range that the pointer at offset
// 0x08 of this refers to, or zero when the pointer or its begin pointer is null. File offset
// 0x1d52f0, VA 0x10ad52f0. The class and method names are invented; the offsets are the binary's.

class UnkType_10ad52f0Range
{
public:
    unsigned char unk_00[0x04];     // not read by this function
    int *unk_04;
    int *unk_08;
};

class UnkType_10ad52f0
{
public:
    int UnkMethod_10ad52f0();

private:
    unsigned char unk_00[0x08];     // not read by this function
    UnkType_10ad52f0Range *unk_08;
};

// UnkType_10ad52f0::UnkMethod_10ad52f0
int UnkType_10ad52f0::UnkMethod_10ad52f0()
{
    UnkType_10ad52f0Range *range = unk_08;
    if (range == 0 || range->unk_04 == 0)
        return 0;
    return range->unk_08 - range->unk_04;
}
