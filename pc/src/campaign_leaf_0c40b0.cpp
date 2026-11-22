// campaign_leaf_0c40b0.cpp -- one function at file offset 0xc40b0, preferred VA 0x109c40b0. It
// returns 1 when bit 22 of the word at offset 0x28 is set and bit 17 of the word at 0x2c is not,
// and 0 otherwise. The class and method names are invented; the offset and the bytes are the
// binary's.

class UnkType_109c40b0
{
public:
    int UnkFlagPair() const;

private:
    unsigned char unk_00[0x28];     // not read by this function
    int unk_28;
    int unk_2c;
};

// UnkType_109c40b0::UnkFlagPair
int UnkType_109c40b0::UnkFlagPair() const
{
    if ( ( unk_28 & 0x400000 ) != 0 && ( unk_2c & 0x20000 ) == 0 )
    {
        return 1;
    }
    return 0;
}
