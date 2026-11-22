// campaign_leaf_10da80.cpp -- clears the dword at offset 0x40 of this and returns 1. File offset
// 0x10da80, VA 0x10a0da80. The class and method names are invented; the offsets are the binary's.

class UnkType_10a0da80
{
public:
    int UnkMethod_10a0da80();

private:
    unsigned char unk_00[0x40];     // not read by this function
    int unk_40;
};

// UnkType_10a0da80::UnkMethod_10a0da80
int UnkType_10a0da80::UnkMethod_10a0da80()
{
    unk_40 = 0;
    return 1;
}
