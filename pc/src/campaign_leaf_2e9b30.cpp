// campaign_leaf_2e9b30.cpp -- one function at file offset 0x2e9b30, preferred VA 0x10be9b30. It
// walks the chain of objects linked through offset 0xa8, starting at its argument, and returns 1
// when one of them has bit 4 set in the flags at offset 0x2c, else 0. It does not read its this
// pointer. The class, method and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_10be9b30
{
public:
    unsigned char unk_0[0x2c];
    int unk_2c;
    unsigned char unk_30[0xa8 - 0x30];
    UnkType_10be9b30* unk_a8;

    int Unk_10be9b30(UnkType_10be9b30* First);
};

// UnkType_10be9b30::Unk_10be9b30
int UnkType_10be9b30::Unk_10be9b30(UnkType_10be9b30* First)
{
    for ( UnkType_10be9b30* Link = First; Link; Link = Link->unk_a8 )
    {
        if ( Link->unk_2c & 4 )
        {
            return 1;
        }
    }
    return 0;
}
