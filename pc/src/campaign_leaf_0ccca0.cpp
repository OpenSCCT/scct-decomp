// campaign_leaf_0ccca0.cpp -- one function at file offset 0xccca0, preferred VA 0x109ccca0. It
// copies the word at offset 0x28 and the two lowest bit fields of the word at offset 0x2c from its
// object into its argument. The class, method and member names are invented; the offset and the
// bytes are the binary's.

class UnkType_109ccca0
{
public:
    unsigned char unk_0[0x28];
    int unk_28;
    unsigned int unk_2c_0 : 1;
    unsigned int unk_2c_1 : 1;

    void Unk_109ccca0(UnkType_109ccca0& Other) const;
};

// UnkType_109ccca0::Unk_109ccca0
void UnkType_109ccca0::Unk_109ccca0(UnkType_109ccca0& Other) const
{
    Other.unk_28 = unk_28;
    Other.unk_2c_0 = unk_2c_0;
    Other.unk_2c_1 = unk_2c_1;
}
