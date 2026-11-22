// campaign_leaf_182060.cpp -- clears bit 0x00400000 of the dword at offset 0x2c of this and sets
// the float at offset 0x260 to -1.0. The argument is not read. File offset 0x182060, VA 0x10a82060.
// The class and method names are invented; the offsets are the binary's.

class UnkType_10a82060
{
public:
    void ClearUnk2CBit22AndSetUnk260(int);

private:
    unsigned char unk_00[0x2c];     // not read by this function
    unsigned int unk_2c;
    unsigned char unk_30[0x230];    // not read by this function
    float unk_260;
};

// UnkType_10a82060::ClearUnk2CBit22AndSetUnk260
void UnkType_10a82060::ClearUnk2CBit22AndSetUnk260(int)
{
    unk_2c &= 0xffbfffff;
    unk_260 = -1.0f;
}
