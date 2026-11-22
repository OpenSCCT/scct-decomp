// campaign_leaf_1cddd0.cpp -- clears the dword at offset 0xa4 of this and returns this. File offset
// 0x1cddd0, VA 0x10acddd0. The class and method names are invented; the offsets are the binary's.

class UnkType_10acddd0
{
public:
    UnkType_10acddd0 *UnkMethod_10acddd0();

private:
    unsigned char unk_00[0xa4];     // not read by this function
    int unk_a4;
};

// UnkType_10acddd0::UnkMethod_10acddd0
UnkType_10acddd0 *UnkType_10acddd0::UnkMethod_10acddd0()
{
    unk_a4 = 0;
    return this;
}
