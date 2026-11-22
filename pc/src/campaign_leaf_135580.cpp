// campaign_leaf_135580.cpp -- returns 1 when the dword at offset 0xee4 of this is nonzero. File
// offset 0x135580, VA 0x10a35580. The class and method names are invented; the offsets are the
// binary's.

class UnkType_10a35580
{
public:
    int TestUnkEE4Set();

private:
    unsigned char unk_00[0xee4];    // not read by this function
    int unk_ee4;
};

// UnkType_10a35580::TestUnkEE4Set
int UnkType_10a35580::TestUnkEE4Set()
{
    return unk_ee4 != 0;
}
