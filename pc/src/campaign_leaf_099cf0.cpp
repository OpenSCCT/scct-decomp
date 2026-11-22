// campaign_leaf_099cf0.cpp -- one function at file offset 0x99cf0, preferred VA 0x10999cf0. It
// returns 1 unless bit 2 of the word at offset 0x3d8 is set and bit 1 is not, in which case it
// returns 0. The class and method names are invented; the offset and the bytes are the binary's.

class UnkType_10999cf0
{
public:
    int UnkFlagTest() const;

private:
    unsigned char unk_00[0x3d8];    // not read by this function
    int unk_3d8;
};

// UnkType_10999cf0::UnkFlagTest
int UnkType_10999cf0::UnkFlagTest() const
{
    int Result = 0;
    if ( ( unk_3d8 & 2 ) != 0 )
    {
        Result = 1;
    }
    else if ( ( unk_3d8 & 4 ) == 0 )
    {
        Result = 1;
    }
    return Result;
}
