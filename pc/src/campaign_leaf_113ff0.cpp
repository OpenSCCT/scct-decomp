// campaign_leaf_113ff0.cpp -- stores its two arguments at offsets 0x88 and 0x8c of this. File
// offset 0x113ff0, VA 0x10a13ff0. The class and method names are invented; the offsets are the
// binary's, and the argument types are guesses.

class UnkType_10a13ff0
{
public:
    void SetUnk88And8C(int Value0, int Value1);

private:
    unsigned char unk_00[0x88];     // not read by this function
    int unk_88;
    int unk_8c;
};

// UnkType_10a13ff0::SetUnk88And8C
void UnkType_10a13ff0::SetUnk88And8C(int Value0, int Value1)
{
    unk_88 = Value0;
    unk_8c = Value1;
}
