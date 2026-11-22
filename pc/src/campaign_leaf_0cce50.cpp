// campaign_leaf_0cce50.cpp -- one function at file offset 0xcce50, preferred VA 0x109cce50. It
// copies from its argument into its object the word at offset 0x28, the two lowest bit fields of
// the word at offset 0x2c, the word at 0x30, the byte at 0x34, the word at 0x38, the byte at 0x3c
// and the lowest bit field of the word at offset 0x40. The class, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_109cce50
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

    void Unk_109cce50(const UnkType_109cce50& Other);
};

// UnkType_109cce50::Unk_109cce50
void UnkType_109cce50::Unk_109cce50(const UnkType_109cce50& Other)
{
    unk_28 = Other.unk_28;
    unk_2c_0 = Other.unk_2c_0;
    unk_2c_1 = Other.unk_2c_1;
    unk_30 = Other.unk_30;
    unk_34 = Other.unk_34;
    unk_38 = Other.unk_38;
    unk_3c = Other.unk_3c;
    unk_40_0 = Other.unk_40_0;
}
