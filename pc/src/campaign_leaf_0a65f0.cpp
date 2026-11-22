// campaign_leaf_0a65f0.cpp -- one function at file offset 0xa65f0, preferred VA 0x109a65f0. It
// returns the array at offset 0x344 when its argument is nonzero or when one of its four words is
// nonzero, and 0 otherwise. The class and method names are invented; the offset and the bytes are
// the binary's.

class UnkType_109a65f0
{
public:
    int *UnkFindNonZero(unsigned char Flag);

private:
    unsigned char unk_00[0x344];    // not read by this function
    int unk_344[4];
};

// UnkType_109a65f0::UnkFindNonZero
int *UnkType_109a65f0::UnkFindNonZero(unsigned char Flag)
{
    if ( Flag != 0 )
    {
        return unk_344;
    }
    for ( int i = 0; i < 4; ++i )
    {
        if ( unk_344[i] != 0 )
        {
            return unk_344;
        }
    }
    return 0;
}
