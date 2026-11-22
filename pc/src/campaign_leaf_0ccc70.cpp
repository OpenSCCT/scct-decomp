// campaign_leaf_0ccc70.cpp -- one function at file offset 0xccc70, preferred VA 0x109ccc70. It
// copies the word at offset 0x28 and the two lowest bit fields of the word at offset 0x2c from its
// argument into its object. The class, method and member names are invented; the offset and the
// bytes are the binary's.

class UnkType_109ccc70
{
public:
    unsigned char unk_0[0x28];
    int unk_28;
    unsigned int unk_2c_0 : 1;
    unsigned int unk_2c_1 : 1;

    void Unk_109ccc70(const UnkType_109ccc70& Other);
};

// UnkType_109ccc70::Unk_109ccc70
void UnkType_109ccc70::Unk_109ccc70(const UnkType_109ccc70& Other)
{
    unk_28 = Other.unk_28;
    unk_2c_0 = Other.unk_2c_0;
    unk_2c_1 = Other.unk_2c_1;
}
