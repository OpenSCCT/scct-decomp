// campaign_leaf_193890.cpp -- one function at file offset 0x193890, preferred VA 0x10a93890. It
// returns 1 when bit 0x2000000 of the flags at offset 0x30 is set and the word at offset 0x188 is
// nonzero, with either bit 0x80 or 0x40000 set in the flags at offset 0x2c or the byte at offset
// 0x4c equal to 10; otherwise 0. The class, method and member names are invented; the offset and
// the bytes are the binary's.

class UnkType_10a93890
{
public:
    unsigned char unk_0[0x2c];
    int unk_2c;
    int unk_30;
    unsigned char unk_34[0x4c - 0x34];
    unsigned char unk_4c;
    unsigned char unk_4d[0x188 - 0x4d];
    int unk_188;

    int Unk_10a93890();
};

// UnkType_10a93890::Unk_10a93890
int UnkType_10a93890::Unk_10a93890()
{
    if ( unk_30 & 0x2000000 )
    {
        if ( unk_188 && ( ( unk_2c & 0x80 ) || ( unk_2c & 0x40000 ) ) )
        {
            return 1;
        }
        if ( unk_4c == 10 && unk_188 )
        {
            return 1;
        }
    }
    return 0;
}
