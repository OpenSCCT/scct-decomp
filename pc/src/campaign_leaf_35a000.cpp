// campaign_leaf_35a000.cpp -- a member function at VA 0x10c5a000 that returns, by value, the
// 12-byte result of the member at VA 0x1092e5f0 of the member at 0xf4 of the object the pointer at
// 0x57c refers to. The class, method and member names are invented; the offsets and addresses are
// the binary's.

struct UnkType_1092e5f0_Result
{
    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_1092e5f0
{
public:
    UnkType_1092e5f0_Result Unk_1092e5f0();
};

class UnkType_10c5a000_Item
{
public:
    unsigned char unk_00[0xf4];
    UnkType_1092e5f0 unk_f4;
};

class UnkType_10c5a000
{
public:
    UnkType_1092e5f0_Result Unk_10c5a000();

private:
    unsigned char unk_000[0x57c];
    UnkType_10c5a000_Item* unk_57c;
};

// UnkType_10c5a000::Unk_10c5a000
UnkType_1092e5f0_Result UnkType_10c5a000::Unk_10c5a000()
{
    return unk_57c->unk_f4.Unk_1092e5f0();
}
