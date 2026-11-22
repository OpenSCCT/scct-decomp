// campaign_leaf_148a30.cpp -- stores its two arguments at offsets 0x40 and 0x44 of this. File
// offset 0x148a30, VA 0x10a48a30. The class and method names are invented; the offsets are the
// binary's, and the argument types are guesses.

class UnkType_10a48a30
{
public:
    void SetUnk40And44(int Value0, int Value1);

private:
    unsigned char unk_00[0x40];     // not read by this function
    int unk_40;
    int unk_44;
};

// UnkType_10a48a30::SetUnk40And44
void UnkType_10a48a30::SetUnk40And44(int Value0, int Value1)
{
    unk_40 = Value0;
    unk_44 = Value1;
}
