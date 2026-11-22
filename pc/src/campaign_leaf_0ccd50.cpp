// campaign_leaf_0ccd50.cpp -- one function at file offset 0xccd50, preferred VA 0x109ccd50. It
// copies from its argument into its object the word at offset 0x28, the two lowest bit fields of
// the word at offset 0x2c, the word at offset 0x30 and the lowest bit field of the word at offset
// 0x34. The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_109ccd50
{
public:
    unsigned char unk_0[0x28];
    int unk_28;
    unsigned int unk_2c_0 : 1;
    unsigned int unk_2c_1 : 1;
    int unk_30;
    unsigned int unk_34_0 : 1;

    void Unk_109ccd50(const UnkType_109ccd50& Other);
};

// UnkType_109ccd50::Unk_109ccd50
void UnkType_109ccd50::Unk_109ccd50(const UnkType_109ccd50& Other)
{
    unk_28 = Other.unk_28;
    unk_2c_0 = Other.unk_2c_0;
    unk_2c_1 = Other.unk_2c_1;
    unk_30 = Other.unk_30;
    unk_34_0 = Other.unk_34_0;
}
