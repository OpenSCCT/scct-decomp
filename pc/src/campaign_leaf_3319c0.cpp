// campaign_leaf_3319c0.cpp -- one function at file offset 0x3319c0, preferred VA 0x10c319c0. It
// calls the method at 0x10c316c0, then fills the last 0x78-byte element of the array at 0x38
// (count at 0x3c): kind 4 in the byte at 0x1, First and Second in the 12-byte blocks at 0x24 and
// 0x30, and Third and Fourth in bits 1 and 2 of the word at 0x74. The class, method, structure,
// member, local and parameter names are invented; the offsets, the constants and the bytes are
// the binary's.

struct UnkType_10c319c0_Vector
{
    float unk_0;
    float unk_4;
    float unk_8;
};

struct UnkType_10c319c0_Entry
{
    unsigned char unk_0;
    unsigned char unk_1;
    unsigned char unk_2[0x22];
    UnkType_10c319c0_Vector unk_24;
    UnkType_10c319c0_Vector unk_30;
    unsigned char unk_3c[0x38];
    unsigned int bUnk_74_0 : 1;
    unsigned int bUnk_74_1 : 1;
    unsigned int bUnk_74_2 : 1;
};

class UnkType_10c319c0
{
public:
    void Unk_10c316c0();
    void Unk_10c319c0(const UnkType_10c319c0_Vector& First, const UnkType_10c319c0_Vector& Second,
                      int Third, int Fourth);

    unsigned char unk_0[0x38];
    UnkType_10c319c0_Entry* unk_38;
    int unk_3c;
};

// UnkType_10c319c0::Unk_10c319c0
void UnkType_10c319c0::Unk_10c319c0(const UnkType_10c319c0_Vector& First,
                                    const UnkType_10c319c0_Vector& Second, int Third, int Fourth)
{
    UnkType_10c319c0_Entry* Entry;

    Unk_10c316c0();
    Entry = &unk_38[unk_3c - 1];
    Entry->unk_1 = 4;
    Entry->unk_24 = First;
    Entry->unk_30 = Second;
    Entry->bUnk_74_1 = Third;
    Entry->bUnk_74_2 = Fourth;
}
