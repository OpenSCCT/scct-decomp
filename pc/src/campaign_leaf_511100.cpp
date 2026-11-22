// campaign_leaf_511100.cpp -- one function at file offset 0x511100, preferred VA 0x10e11100. It
// copies its six-word argument into the structure at 0x18. The class, method, structure and
// member names are invented; the offsets and the bytes are the binary's.

struct UnkType_10e11100_Six
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
};

class UnkType_10e11100
{
public:
    void Unk_10e11100(const UnkType_10e11100_Six& Value);

    unsigned char unk_0[0x18];
    UnkType_10e11100_Six unk_18;
};

// UnkType_10e11100::Unk_10e11100
void UnkType_10e11100::Unk_10e11100(const UnkType_10e11100_Six& Value)
{
    unk_18 = Value;
}
