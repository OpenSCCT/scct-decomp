// campaign_leaf_113e60.cpp -- stores its two arguments at offsets 0x54 and 0x58 of this. File
// offset 0x113e60, VA 0x10a13e60. The class and method names are invented; the offsets are the
// binary's, and the argument types are guesses.

class UnkType_10a13e60
{
public:
    void SetUnk54And58(int Value0, int Value1);

private:
    unsigned char unk_00[0x54];     // not read by this function
    int unk_54;
    int unk_58;
};

// UnkType_10a13e60::SetUnk54And58
void UnkType_10a13e60::SetUnk54And58(int Value0, int Value1)
{
    unk_54 = Value0;
    unk_58 = Value1;
}
