// campaign_leaf_0a46c0.cpp -- one function at file offset 0xa46c0, preferred VA 0x109a46c0. It
// returns the array at offset 0x2c4 when its argument is nonzero or when one of its four words is
// nonzero, and 0 otherwise. The class and method names are invented; the offset and the bytes are
// the binary's.

class UnkType_109a46c0
{
public:
    int *UnkFindNonZero(unsigned char Flag);

private:
    unsigned char unk_00[0x2c4];    // not read by this function
    int unk_2c4[4];
};

// UnkType_109a46c0::UnkFindNonZero
int *UnkType_109a46c0::UnkFindNonZero(unsigned char Flag)
{
    if ( Flag != 0 )
    {
        return unk_2c4;
    }
    for ( int i = 0; i < 4; ++i )
    {
        if ( unk_2c4[i] != 0 )
        {
            return unk_2c4;
        }
    }
    return 0;
}
