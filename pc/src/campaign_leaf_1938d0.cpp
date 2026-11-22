// campaign_leaf_1938d0.cpp -- one function at file offset 0x1938d0, preferred VA 0x10a938d0. It
// walks the chain of objects linked through offset 0xa8, starting at its own object (which may be
// null), and returns 1 when one of them has a nonzero word at offset 0x188 and bit 0x80 or 0x40000
// set in the flags at offset 0x2c, else 0. The class, method and member names are invented; the
// offset and the bytes are the binary's.

class UnkType_10a938d0
{
public:
    unsigned char unk_0[0x2c];
    int unk_2c;
    unsigned char unk_30[0xa8 - 0x30];
    UnkType_10a938d0* unk_a8;
    unsigned char unk_ac[0x188 - 0xac];
    int unk_188;

    int Unk_10a938d0();
};

// UnkType_10a938d0::Unk_10a938d0
int UnkType_10a938d0::Unk_10a938d0()
{
    for ( UnkType_10a938d0* Link = this; Link; Link = Link->unk_a8 )
    {
        if ( Link->unk_188 && ( ( Link->unk_2c & 0x80 ) || ( Link->unk_2c & 0x40000 ) ) )
        {
            return 1;
        }
    }
    return 0;
}
