// campaign_leaf_14b530.cpp -- sets the dword at offset 0x15c of this to -1 and the dword at offset
// 0x160 to 0. File offset 0x14b530, VA 0x10a4b530. The class and method names are invented; the
// offsets are the binary's.

class UnkType_10a4b530
{
public:
    void ResetUnk15CAnd160();

private:
    unsigned char unk_00[0x15c];    // not read by this function
    int unk_15c;
    int unk_160;
};

// UnkType_10a4b530::ResetUnk15CAnd160
void UnkType_10a4b530::ResetUnk15CAnd160()
{
    unk_15c = -1;
    unk_160 = 0;
}
