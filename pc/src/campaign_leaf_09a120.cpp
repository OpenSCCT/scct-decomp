// campaign_leaf_09a120.cpp -- one function at file offset 0x9a120, preferred VA 0x1099a120. It
// returns 1 when a word of the int array at offset 0x3c0 equals its argument, for one of the first
// count words (the count at 0x3c4), and 0 otherwise. The class and method names are invented; the
// offset and the bytes are the binary's.

class UnkType_1099a120
{
public:
    int UnkContains(int Value) const;

private:
    unsigned char unk_00[0x3c0];    // not read by this function
    int *unk_3c0;
    int unk_3c4;
};

// UnkType_1099a120::UnkContains
int UnkType_1099a120::UnkContains(int Value) const
{
    for ( int i = 0; i < unk_3c4; ++i )
    {
        if ( unk_3c0[i] == Value )
        {
            return 1;
        }
    }
    return 0;
}
