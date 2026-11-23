// campaign_leaf_3a4d80.cpp -- method at VA 0x10ca4d80: gathers the bytes at 0x86, 0xb7 and 0xcf
// of Source into three values and returns the blend, truncated, of the value the index at 0x160
// selects and the one the index at 0x164 selects, weighted by the float at 0x168. The class,
// member, method and local names are invented; the offsets are the binary's.

class UnkType_10ca4d80_Source
{
public:
    char unk_0[0x86];
    unsigned char unk_86;
    char unk_87[0xb7 - 0x87];
    unsigned char unk_b7;
    char unk_b8[0xcf - 0xb8];
    unsigned char unk_cf;
};

class UnkType_10ca4d80
{
public:
    int Unk_10ca4d80(UnkType_10ca4d80_Source* Source);

private:
    char unk_0[0x160];
    int unk_160;
    int unk_164;
    float unk_168;
};

// UnkType_10ca4d80::Unk_10ca4d80
int UnkType_10ca4d80::Unk_10ca4d80(UnkType_10ca4d80_Source* Source)
{
    float Alpha = unk_168;
    unsigned char Values[3];

    Values[0] = Source->unk_86;
    Values[1] = Source->unk_b7;
    Values[2] = Source->unk_cf;
    return (int)( Values[unk_160] * ( 1.0f - Alpha ) + Values[unk_164] * Alpha );
}
