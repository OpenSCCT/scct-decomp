// campaign_leaf_49cd60.cpp -- constructor at VA 0x10d9cd60: runs the base constructor at
// VA 0x10dcd730 and clears the dwords at offsets 0x14 and 0x18. All names are invented.

class UnkType_10d9cd60_Base
{
public:
    UnkType_10d9cd60_Base();

private:
    unsigned char unk_00[0x14];
};

class UnkType_10d9cd60 : public UnkType_10d9cd60_Base
{
public:
    UnkType_10d9cd60();

private:
    int unk_14;
    int unk_18;
};

// UnkType_10d9cd60::UnkType_10d9cd60
UnkType_10d9cd60::UnkType_10d9cd60()
{
    unk_14 = 0;
    unk_18 = 0;
}
