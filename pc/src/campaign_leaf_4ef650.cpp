// campaign_leaf_4ef650.cpp -- method at VA 0x10def650: reads one bit (most significant first) from
// the byte buffer at 0x04 at byte 0x08, bit 0x0c, into its argument and advances the position; sets
// the flag at 0x00 instead when that would pass the bit limit at 0x10. The class, method and member
// names are invented; the offsets and the address are the binary's.

class UnkType_10def650_Buffer
{
public:
    unsigned char& Unk_10dce1a0(int Index);
};

class UnkType_10def650
{
public:
    void Unk_10def650(bool* Out);

    bool unk_00;
    UnkType_10def650_Buffer* unk_04;
    unsigned int unk_08;
    unsigned int unk_0c;
    unsigned int unk_10;
};

// UnkType_10def650::Unk_10def650
void UnkType_10def650::Unk_10def650(bool* Out)
{
    if ( unk_08 * 8 + unk_0c + 1 > unk_10 )
    {
        unk_00 = true;
        return;
    }
    unsigned char Mask = 1 << ( 7 - unk_0c );
    *Out = ( unk_04->Unk_10dce1a0(unk_08) & Mask ) == Mask;
    if ( ++unk_0c == 8 )
    {
        unk_0c = 0;
        unk_08++;
    }
}
