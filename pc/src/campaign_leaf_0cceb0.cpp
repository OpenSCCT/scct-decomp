// campaign_leaf_0cceb0.cpp -- one function at file offset 0xcceb0, preferred VA 0x109cceb0. It
// copies from its object into its argument the word at offset 0x28, the two lowest bit fields of
// the word at offset 0x2c, the word at 0x30, the byte at 0x34, the word at 0x38, the byte at 0x3c
// and the lowest bit field of the word at offset 0x40. The class, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_109cceb0
{
public:
    unsigned char unk_0[0x28];
    int unk_28;
    unsigned int unk_2c_0 : 1;
    unsigned int unk_2c_1 : 1;
    int unk_30;
    unsigned char unk_34;
    unsigned char unk_35[3];
    int unk_38;
    unsigned char unk_3c;
    unsigned char unk_3d[3];
    unsigned int unk_40_0 : 1;

    void Unk_109cceb0(UnkType_109cceb0& Other) const;
};

// UnkType_109cceb0::Unk_109cceb0
void UnkType_109cceb0::Unk_109cceb0(UnkType_109cceb0& Other) const
{
    Other.unk_28 = unk_28;
    Other.unk_2c_0 = unk_2c_0;
    Other.unk_2c_1 = unk_2c_1;
    Other.unk_30 = unk_30;
    Other.unk_34 = unk_34;
    Other.unk_38 = unk_38;
    Other.unk_3c = unk_3c;
    Other.unk_40_0 = unk_40_0;
}
