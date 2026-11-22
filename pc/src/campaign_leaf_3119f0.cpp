// campaign_leaf_3119f0.cpp -- one function at file offset 0x3119f0, preferred VA 0x10c119f0. It
// walks the chain of objects that starts at offset 0x5e0 and is linked through offset 0x2d4, and
// sets bit 0x1 of the flags at offset 0x52c of each one whose flags at offset 0x2c0 lack bit 0x1
// and whose word at offset 0x518 equals its argument. The class, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_10c119f0_Link
{
public:
    unsigned char unk_0[0x2c0];
    int unk_2c0;
    unsigned char unk_2c4[0x2d4 - 0x2c4];
    UnkType_10c119f0_Link* unk_2d4;
    unsigned char unk_2d8[0x518 - 0x2d8];
    int unk_518;
    unsigned char unk_51c[0x52c - 0x51c];
    int unk_52c;
};

class UnkType_10c119f0
{
public:
    unsigned char unk_0[0x5e0];
    UnkType_10c119f0_Link* unk_5e0;

    void Unk_10c119f0(int Key);
};

// UnkType_10c119f0::Unk_10c119f0
void UnkType_10c119f0::Unk_10c119f0(int Key)
{
    for ( UnkType_10c119f0_Link* Link = unk_5e0; Link; Link = Link->unk_2d4 )
    {
        if ( !( Link->unk_2c0 & 1 ) && Link->unk_518 == Key )
        {
            Link->unk_52c |= 1;
        }
    }
}
