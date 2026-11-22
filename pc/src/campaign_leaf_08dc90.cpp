// campaign_leaf_08dc90.cpp -- one function at file offset 0x8dc90, preferred VA 0x1098dc90. It
// returns the array at offset 0x328 when its argument is nonzero or when one of its four words is
// nonzero, and 0 otherwise. The class and method names are invented; the offset and the bytes are
// the binary's.

class UnkType_1098dc90
{
public:
    int *UnkFindNonZero(unsigned char Flag);

private:
    unsigned char unk_00[0x328];    // not read by this function
    int unk_328[4];
};

// UnkType_1098dc90::UnkFindNonZero
int *UnkType_1098dc90::UnkFindNonZero(unsigned char Flag)
{
    if ( Flag != 0 )
    {
        return unk_328;
    }
    for ( int i = 0; i < 4; ++i )
    {
        if ( unk_328[i] != 0 )
        {
            return unk_328;
        }
    }
    return 0;
}
