// campaign_leaf_006950.cpp -- one function at file offset 0x6950, preferred VA 0x10906950. It
// returns 1 when both of two words of this object are nonzero, and 0 otherwise. The class and
// method names are invented; the offset and the bytes are the binary's.

class UnkType_10906950
{
public:
    int UnkBothNonZero();

private:
    unsigned char unk_00[0xa4];     // not read by this function
    int unk_a4;                     // tested against zero
    int unk_a8;                     // tested against zero
};

// UnkType_10906950::UnkBothNonZero
int UnkType_10906950::UnkBothNonZero()
{
    if ( unk_a8 != 0 && unk_a4 != 0 )
    {
        return 1;
    }
    return 0;
}
