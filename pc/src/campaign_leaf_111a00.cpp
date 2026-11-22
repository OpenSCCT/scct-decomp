// campaign_leaf_111a00.cpp -- returns 1 when the dword at offset 0x54 of this is nonzero. File
// offset 0x111a00, VA 0x10a11a00. The class and method names are invented; the offsets are the
// binary's.

class UnkType_10a11a00
{
public:
    int TestUnk54Set();

private:
    unsigned char unk_00[0x54];     // not read by this function
    int unk_54;
};

// UnkType_10a11a00::TestUnk54Set
int UnkType_10a11a00::TestUnk54Set()
{
    return unk_54 != 0;
}
