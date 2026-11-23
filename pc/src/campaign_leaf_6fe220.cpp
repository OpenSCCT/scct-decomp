// campaign_leaf_6fe220.cpp -- constructor at VA 0x10ffe220: runs the base constructor at VA
// 0x10ffe2d0, then clears three groups of four values at 0x10-0x3c, last member of each group
// first. The class and member names are invented; the offsets and addresses are the binary's.

class UnkType_10ffe220_Base
{
public:
    UnkType_10ffe220_Base();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

class UnkType_10ffe220 : public UnkType_10ffe220_Base
{
public:
    UnkType_10ffe220();

private:
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
};

// UnkType_10ffe220::UnkType_10ffe220
UnkType_10ffe220::UnkType_10ffe220()
{
    unk_10 = unk_14 = unk_18 = unk_1c = 0;
    unk_20 = unk_24 = unk_28 = unk_2c = 0;
    unk_30 = unk_34 = unk_38 = unk_3c = 0;
}
