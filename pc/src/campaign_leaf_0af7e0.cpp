// campaign_leaf_0af7e0.cpp -- one function at file offset 0xaf7e0, preferred VA 0x109af7e0. It
// returns the array at offset 0x41c when its argument is nonzero or when one of its four words is
// nonzero, and 0 otherwise. The class and method names are invented; the offset and the bytes are
// the binary's.

class UnkType_109af7e0
{
public:
    int *UnkFindNonZero(unsigned char Flag);

private:
    unsigned char unk_00[0x41c];    // not read by this function
    int unk_41c[4];
};

// UnkType_109af7e0::UnkFindNonZero
int *UnkType_109af7e0::UnkFindNonZero(unsigned char Flag)
{
    if ( Flag != 0 )
    {
        return unk_41c;
    }
    for ( int i = 0; i < 4; ++i )
    {
        if ( unk_41c[i] != 0 )
        {
            return unk_41c;
        }
    }
    return 0;
}
