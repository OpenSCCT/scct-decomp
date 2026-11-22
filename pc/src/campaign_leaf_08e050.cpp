// campaign_leaf_08e050.cpp -- one function at file offset 0x8e050, preferred VA 0x1098e050. Unless
// its object has bit 0x20 and its argument bit 0x40000 set in the flags at offset 0x2c, it returns
// 1 when the argument is in the chain of objects linked through offset 0xa8 starting at this one;
// otherwise 0. The class, method and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_1098e050
{
public:
    unsigned char unk_0[0x2c];
    int unk_2c;
    unsigned char unk_30[0xa8 - 0x30];
    UnkType_1098e050* unk_a8;

    int Unk_1098e050(UnkType_1098e050* Other);
};

// UnkType_1098e050::Unk_1098e050
int UnkType_1098e050::Unk_1098e050(UnkType_1098e050* Other)
{
    if ( ( unk_2c & 0x20 ) && ( Other->unk_2c & 0x40000 ) )
    {
        return 0;
    }
    for ( UnkType_1098e050* Link = this; Link; Link = Link->unk_a8 )
    {
        if ( Link == Other )
        {
            return 1;
        }
    }
    return 0;
}
