// campaign_leaf_331a90.cpp -- one function at file offset 0x331a90, preferred VA 0x10c31a90. It
// calls the method at 0x10c316c0, then fills the last 0x78-byte element of the array at 0x38
// (count at 0x3c): kind 6 in the byte at 0x1, the word First refers to at 0x70, Second at 0x68,
// Third to Sixth at 0x58 to 0x64, and Seventh in bit 1 of the word at 0x74. The class, method,
// structure, member and parameter names are invented; the offsets, the constants and the bytes
// are the binary's.

struct UnkType_10c31a90_Entry
{
    unsigned char unk_0;
    unsigned char unk_1;
    unsigned char unk_2[0x56];
    int unk_58;
    int unk_5c;
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6c;
    int unk_70;
    unsigned int bUnk_74_0 : 1;
    unsigned int bUnk_74_1 : 1;
};

class UnkType_10c31a90
{
public:
    void Unk_10c316c0();
    void Unk_10c31a90(const int& First, int Second, int Third, int Fourth, int Fifth, int Sixth,
                      int Seventh);

    unsigned char unk_0[0x38];
    UnkType_10c31a90_Entry* unk_38;
    int unk_3c;
};

// UnkType_10c31a90::Unk_10c31a90
void UnkType_10c31a90::Unk_10c31a90(const int& First, int Second, int Third, int Fourth,
                                    int Fifth, int Sixth, int Seventh)
{
    UnkType_10c31a90_Entry* Entry;

    Unk_10c316c0();
    Entry = &unk_38[unk_3c - 1];
    Entry->unk_1 = 6;
    Entry->unk_70 = First;
    Entry->unk_68 = Second;
    Entry->unk_58 = Third;
    Entry->unk_5c = Fourth;
    Entry->unk_60 = Fifth;
    Entry->unk_64 = Sixth;
    Entry->bUnk_74_1 = Seventh;
}
