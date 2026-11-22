// campaign_leaf_1ed810.cpp -- clears the fields at offsets 0x28 to 0x40 of this and the byte at
// offset 0x44, in the order the binary stores them. File offset 0x1ed810, VA 0x10aed810. The class
// and method names are invented; the offsets are the binary's. The field types are guesses.

class UnkType_10aed810
{
public:
    void UnkMethod_10aed810();

private:
    unsigned char unk_00[0x28];     // not read by this function
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    unsigned char unk_44;
};

// UnkType_10aed810::UnkMethod_10aed810
void UnkType_10aed810::UnkMethod_10aed810()
{
    unk_30 = 0;
    unk_2c = 0;
    unk_38 = 0;
    unk_34 = 0;
    unk_28 = 0;
    unk_3c = 0;
    unk_44 = 0;
    unk_40 = 0;
}
