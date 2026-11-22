// campaign_leaf_028ca0.cpp -- one function at file offset 0x28ca0, preferred VA 0x10928ca0. It
// returns 1 when the byte at offset 0x3f0 of this object is at least 4, and 0 otherwise. The class
// and method names are invented; the offset and the bytes are the binary's.

class UnkType_10928ca0
{
public:
    int UnkAtLeastFour();

private:
    unsigned char unk_00[0x3f0];    // not read by this function
    unsigned char unk_3f0;          // compared with 4, unsigned
};

// UnkType_10928ca0::UnkAtLeastFour
int UnkType_10928ca0::UnkAtLeastFour()
{
    if ( unk_3f0 >= 4 )
    {
        return 1;
    }
    return 0;
}
