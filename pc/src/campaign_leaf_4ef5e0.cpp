// campaign_leaf_4ef5e0.cpp -- method at VA 0x10def5e0: reads eight bits from the byte buffer at
// 0x04 at byte 0x08, bit 0x0c, into its argument and advances one byte; sets the flag at 0x00
// instead when that would pass the bit limit at 0x10. The class, method and member names are
// invented; the offsets and the address are the binary's.

class UnkType_10def5e0_Buffer
{
public:
    unsigned char& Unk_10dce1a0(int Index);
};

class UnkType_10def5e0
{
public:
    void Unk_10def5e0(unsigned char* Out);

    bool unk_00;
    UnkType_10def5e0_Buffer* unk_04;
    unsigned int unk_08;
    unsigned int unk_0c;
    unsigned int unk_10;
};

// UnkType_10def5e0::Unk_10def5e0
void UnkType_10def5e0::Unk_10def5e0(unsigned char* Out)
{
    if ( unk_08 * 8 + unk_0c + 8 > unk_10 )
    {
        unk_00 = true;
        return;
    }
    unsigned char Remaining = 8 - (unsigned char)unk_0c;
    unsigned char High = unk_04->Unk_10dce1a0(unk_08) << (unsigned char)( 8 - Remaining );
    *Out = ( unk_04->Unk_10dce1a0(unk_08 + 1) >> Remaining ) | High;
    unk_08++;
}
