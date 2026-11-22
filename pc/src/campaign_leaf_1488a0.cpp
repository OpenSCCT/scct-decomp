// campaign_leaf_1488a0.cpp -- stores the four arguments, as floats, at offsets 0x40 to 0x4c of
// this, and clears the dwords at offsets 0x50 and 0x54. File offset 0x1488a0, VA 0x10a488a0. The
// class and method names are invented; the offsets are the binary's.

class UnkType_10a488a0
{
public:
    void UnkMethod_10a488a0(int Value0, int Value1, int Value2, int Value3);

private:
    unsigned char unk_00[0x40];     // not read by this function
    float unk_40;
    float unk_44;
    float unk_48;
    float unk_4c;
    int unk_50;
    int unk_54;
};

// UnkType_10a488a0::UnkMethod_10a488a0
void UnkType_10a488a0::UnkMethod_10a488a0(int Value0, int Value1, int Value2, int Value3)
{
    unk_40 = Value0;
    unk_44 = Value1;
    unk_48 = Value2;
    unk_4c = Value3;
    unk_50 = 0;
    unk_54 = 0;
}
