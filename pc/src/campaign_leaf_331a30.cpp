// campaign_leaf_331a30.cpp -- one function at file offset 0x331a30, preferred VA 0x10c31a30. It
// calls the method at 0x10c316c0, then fills the last 0x78-byte element of the array at 0x38
// (count at 0x3c): kind 5 in the byte at 0x1, First and Second in the 12-byte blocks at 0x18 and
// 0x24, Third in the word at 0x5c and 0 in the word at 0x58. The class, method, structure, member
// and parameter names are invented; the offsets, the constants and the bytes are the binary's.

struct UnkType_10c31a30_Vector
{
    float unk_0;
    float unk_4;
    float unk_8;
};

struct UnkType_10c31a30_Entry
{
    unsigned char unk_0;
    unsigned char unk_1;
    unsigned char unk_2[0x16];
    UnkType_10c31a30_Vector unk_18;
    UnkType_10c31a30_Vector unk_24;
    unsigned char unk_30[0x28];
    int unk_58;
    int unk_5c;
    unsigned char unk_60[0x18];
};

class UnkType_10c31a30
{
public:
    void Unk_10c316c0();
    void Unk_10c31a30(const UnkType_10c31a30_Vector& First, const UnkType_10c31a30_Vector& Second,
                      int Third);

    unsigned char unk_0[0x38];
    UnkType_10c31a30_Entry* unk_38;
    int unk_3c;
};

// UnkType_10c31a30::Unk_10c31a30
void UnkType_10c31a30::Unk_10c31a30(const UnkType_10c31a30_Vector& First,
                                    const UnkType_10c31a30_Vector& Second, int Third)
{
    UnkType_10c31a30_Entry* Entry;

    Unk_10c316c0();
    Entry = &unk_38[unk_3c - 1];
    Entry->unk_1 = 5;
    Entry->unk_18 = First;
    Entry->unk_24 = Second;
    Entry->unk_5c = Third;
    Entry->unk_58 = 0;
}
