// campaign_leaf_148a50.cpp -- stores its two arguments at offsets 0x48 and 0x4c of this. File
// offset 0x148a50, VA 0x10a48a50. The class and method names are invented; the offsets are the
// binary's, and the argument types are guesses.

class UnkType_10a48a50
{
public:
    void SetUnk48And4C(int Value0, int Value1);

private:
    unsigned char unk_00[0x48];     // not read by this function
    int unk_48;
    int unk_4c;
};

// UnkType_10a48a50::SetUnk48And4C
void UnkType_10a48a50::SetUnk48And4C(int Value0, int Value1)
{
    unk_48 = Value0;
    unk_4c = Value1;
}
