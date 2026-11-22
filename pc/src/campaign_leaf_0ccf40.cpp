// campaign_leaf_0ccf40.cpp -- one function at file offset 0xccf40, preferred VA 0x109ccf40. It
// returns 1 when the word at offset 0xa8 is nonzero and the word at offset 0xa4 is zero, and 0
// otherwise. The class and method names are invented; the offset and the bytes are the binary's.

class UnkType_109ccf40
{
public:
    int UnkFlagPair() const;

private:
    unsigned char unk_00[0xa4];     // not read by this function
    int unk_a4;
    int unk_a8;
};

// UnkType_109ccf40::UnkFlagPair
int UnkType_109ccf40::UnkFlagPair() const
{
    if ( unk_a8 != 0 && unk_a4 == 0 )
    {
        return 1;
    }
    return 0;
}
