// campaign_leaf_06aff0.cpp -- method at VA 0x1096aff0: returns whether either of the floats at
// 0x54 and 0x58 is non-zero. The class, member and method names are invented; the offsets are the
// binary's.

class UnkType_1096aff0
{
public:
    int Unk_1096aff0();

private:
    char unk_0[0x54];
    float unk_54;
    float unk_58;
};

// UnkType_1096aff0::Unk_1096aff0
int UnkType_1096aff0::Unk_1096aff0()
{
    return unk_54 != 0.0f || unk_58 != 0.0f;
}
