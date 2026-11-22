// campaign_leaf_113080.cpp -- returns 1 when the dword at offset 0x4c of this is nonzero. File
// offset 0x113080, VA 0x10a13080. The class and method names are invented; the offsets are the
// binary's.

class UnkType_10a13080
{
public:
    int TestUnk4CSet();

private:
    unsigned char unk_00[0x4c];     // not read by this function
    int unk_4c;
};

// UnkType_10a13080::TestUnk4CSet
int UnkType_10a13080::TestUnk4CSet()
{
    return unk_4c != 0;
}
