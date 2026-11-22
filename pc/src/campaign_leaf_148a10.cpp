// campaign_leaf_148a10.cpp -- stores its two arguments at offsets 0x50 and 0x54 of this. File
// offset 0x148a10, VA 0x10a48a10. The class and method names are invented; the offsets are the
// binary's, and the argument types are guesses.

class UnkType_10a48a10
{
public:
    void SetUnk50And54(int Value0, int Value1);

private:
    unsigned char unk_00[0x50];     // not read by this function
    int unk_50;
    int unk_54;
};

// UnkType_10a48a10::SetUnk50And54
void UnkType_10a48a10::SetUnk50And54(int Value0, int Value1)
{
    unk_50 = Value0;
    unk_54 = Value1;
}
