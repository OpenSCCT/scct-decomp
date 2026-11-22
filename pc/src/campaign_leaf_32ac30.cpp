// campaign_leaf_32ac30.cpp -- one function at file offset 0x32ac30, preferred VA 0x10c2ac30. It
// stores its argument at offset 0x28 when that word is zero, clears the words at offsets 0x78 and
// 0x74, sets bit 0x1 of the flags at offset 0xac and clears bit 0x1 of the flags at offset 0xd4.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10c2ac30
{
public:
    unsigned char unk_0[0x28];
    int unk_28;
    unsigned char unk_2c[0x74 - 0x2c];
    int unk_74;
    int unk_78;
    unsigned char unk_7c[0xac - 0x7c];
    int unk_ac;
    unsigned char unk_b0[0xd4 - 0xb0];
    int unk_d4;

    void Unk_10c2ac30(int Value);
};

// UnkType_10c2ac30::Unk_10c2ac30
void UnkType_10c2ac30::Unk_10c2ac30(int Value)
{
    if ( unk_28 == 0 )
    {
        unk_28 = Value;
    }
    unk_78 = 0;
    unk_74 = 0;
    unk_ac |= 1;
    unk_d4 &= ~1;
}
