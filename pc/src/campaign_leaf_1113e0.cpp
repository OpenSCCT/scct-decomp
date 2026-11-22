// campaign_leaf_1113e0.cpp -- returns 1 when the dword at offset 0x50 of this is nonzero. File
// offset 0x1113e0, VA 0x10a113e0. The class and method names are invented; the offsets are the
// binary's.

class UnkType_10a113e0
{
public:
    int TestUnk50Set();

private:
    unsigned char unk_00[0x50];     // not read by this function
    int unk_50;
};

// UnkType_10a113e0::TestUnk50Set
int UnkType_10a113e0::TestUnk50Set()
{
    return unk_50 != 0;
}
