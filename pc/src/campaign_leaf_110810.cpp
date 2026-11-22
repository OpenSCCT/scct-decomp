// campaign_leaf_110810.cpp -- returns 1 when the byte at offset 0x8c of this is nonzero. File
// offset 0x110810, VA 0x10a10810. The class and method names are invented; the offset is the
// binary's.

class UnkType_10a10810
{
public:
    int TestUnk8CSet();

private:
    unsigned char unk_00[0x8c];     // not read by this function
    unsigned char unk_8c;
};

// UnkType_10a10810::TestUnk8CSet
int UnkType_10a10810::TestUnk8CSet()
{
    return unk_8c != 0;
}
