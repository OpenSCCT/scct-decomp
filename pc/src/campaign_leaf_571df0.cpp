// campaign_leaf_571df0.cpp -- one function at file offset 0x571df0, preferred VA 0x10e71df0.
// It multiplies by Scale the float at offset 4 of Target and the first three floats of each of
// the three 16-byte rows at offset 0x20, column by column. The function, structure and member
// names are invented; the offset and the bytes are the binary's.

struct UnkType_10e71df0
{
    float unk_0;
    float unk_4;
    float unk_8[6];
    float unk_20[3][4];
};

// Unk_10e71df0
void Unk_10e71df0(float Scale, UnkType_10e71df0* Target)
{
    Target->unk_4 *= Scale;
    Target->unk_20[0][0] *= Scale;
    Target->unk_20[1][0] *= Scale;
    Target->unk_20[2][0] *= Scale;
    Target->unk_20[0][1] *= Scale;
    Target->unk_20[1][1] *= Scale;
    Target->unk_20[2][1] *= Scale;
    Target->unk_20[0][2] *= Scale;
    Target->unk_20[1][2] *= Scale;
    Target->unk_20[2][2] *= Scale;
}
