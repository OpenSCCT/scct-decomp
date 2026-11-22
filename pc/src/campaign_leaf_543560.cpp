// campaign_leaf_543560.cpp -- one function at file offset 0x543560, preferred VA 0x10e43560. It
// sets Result to 1 when any of the three floats of Value exceeds Limit, otherwise to 0. It has no
// this pointer. The function, structure, member and parameter names are invented; the bytes are
// the binary's.

struct UnkVector
{
    float unk_0;
    float unk_4;
    float unk_8;
};

// Unk_10e43560
void Unk_10e43560(const UnkVector& Value, const float& Limit, int& Result)
{
    Result = Value.unk_0 > Limit || Value.unk_4 > Limit || Value.unk_8 > Limit;
}
