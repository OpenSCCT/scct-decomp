// campaign_leaf_5113a0.cpp -- one function at file offset 0x5113a0, preferred VA 0x10e113a0. It
// copies the words at 0x0-0x8 and 0x10-0x20 of its argument to 0x30-0x38 and 0x40-0x50, leaving
// the word between each range alone. The class, method, structure and member names are
// invented; the offsets and the bytes are the binary's.

struct UnkSource
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
};

class UnkType_10e113a0
{
public:
    void Unk_10e113a0(const UnkSource& Source);

    unsigned char unk_0[0x30];
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4c;
    int unk_50;
};

// UnkType_10e113a0::Unk_10e113a0
void UnkType_10e113a0::Unk_10e113a0(const UnkSource& Source)
{
    unk_30 = Source.unk_0;
    unk_34 = Source.unk_4;
    unk_38 = Source.unk_8;
    unk_40 = Source.unk_10;
    unk_44 = Source.unk_14;
    unk_48 = Source.unk_18;
    unk_4c = Source.unk_1c;
    unk_50 = Source.unk_20;
}
