// campaign_leaf_4ef240.cpp -- method at VA 0x10def240: writes one bit (most significant first) into
// the byte buffer at 0x04 at byte 0x08, bit 0x0c (setting the whole byte at bit 0), advances the
// position and counts the bit at 0x10. The class, method and member names are invented; the offsets
// and the address are the binary's.

class UnkType_10def240_Buffer
{
public:
    unsigned char& Unk_10dce1a0(int Index);
};

class UnkType_10def240
{
public:
    void Unk_10def240(bool Bit);

    bool unk_00;
    UnkType_10def240_Buffer* unk_04;
    unsigned int unk_08;
    unsigned int unk_0c;
    unsigned int unk_10;
};

// UnkType_10def240::Unk_10def240
void UnkType_10def240::Unk_10def240(bool Bit)
{
    if ( unk_0c == 0 )
    {
        unk_04->Unk_10dce1a0(unk_08) = Bit << 7;
    }
    else if ( Bit == 1 )
    {
        unk_04->Unk_10dce1a0(unk_08) =
            unk_04->Unk_10dce1a0(unk_08) | ( 1 << (unsigned char)( 7 - (unsigned char)unk_0c ) );
    }
    if ( ++unk_0c == 8 )
    {
        unk_0c = 0;
        unk_08++;
    }
    unk_10++;
}
