// campaign_leaf_1a5380.cpp -- clears the dword at offset 0x200 of this and returns this. File
// offset 0x1a5380, VA 0x10aa5380. The class and method names are invented; the offsets are the
// binary's.

class UnkType_10aa5380
{
public:
    UnkType_10aa5380 *UnkMethod_10aa5380();

private:
    unsigned char unk_00[0x200];    // not read by this function
    int unk_200;
};

// UnkType_10aa5380::UnkMethod_10aa5380
UnkType_10aa5380 *UnkType_10aa5380::UnkMethod_10aa5380()
{
    unk_200 = 0;
    return this;
}
