// campaign_leaf_14b510.cpp -- stores its two arguments at offsets 0x15c and 0x160 of this. File
// offset 0x14b510, VA 0x10a4b510. The class and method names are invented; the offsets are the
// binary's, and the argument types are guesses.

class UnkType_10a4b510
{
public:
    void SetUnk15CAnd160(int Value0, int Value1);

private:
    unsigned char unk_00[0x15c];    // not read by this function
    int unk_15c;
    int unk_160;
};

// UnkType_10a4b510::SetUnk15CAnd160
void UnkType_10a4b510::SetUnk15CAnd160(int Value0, int Value1)
{
    unk_15c = Value0;
    unk_160 = Value1;
}
