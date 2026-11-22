// campaign_leaf_09db20.cpp -- one function at file offset 0x9db20, preferred VA 0x1099db20. It
// returns 0 when bit 14 of the word at offset 0x284 is set; otherwise it returns the word at
// offset 0x29c. The class and method names are invented; the offset and the bytes are the
// binary's.

class UnkType_1099db20
{
public:
    int UnkValue() const;

private:
    unsigned char unk_00[0x284];    // not read by this function
    int unk_284;
    unsigned char unk_288[0x14];    // not read by this function
    int unk_29c;
};

// UnkType_1099db20::UnkValue
int UnkType_1099db20::UnkValue() const
{
    if ( ( unk_284 & 0x4000 ) != 0 )
    {
        return 0;
    }
    return unk_29c;
}
