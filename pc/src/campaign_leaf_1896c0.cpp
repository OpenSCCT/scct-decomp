// campaign_leaf_1896c0.cpp -- returns this when bit 0x4000 of the dword at offset 0x28 of this is
// set, otherwise null. File offset 0x1896c0, VA 0x10a896c0. The class and method names are
// invented; the offsets are the binary's.

class UnkType_10a896c0
{
public:
    UnkType_10a896c0 *UnkMethod_10a896c0();

private:
    unsigned char unk_00[0x28];     // not read by this function
    int unk_28;
};

// UnkType_10a896c0::UnkMethod_10a896c0
UnkType_10a896c0 *UnkType_10a896c0::UnkMethod_10a896c0()
{
    return ( unk_28 & 0x4000 ) ? this : 0;
}
