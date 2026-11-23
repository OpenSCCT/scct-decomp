// campaign_leaf_4ef1a0.cpp -- method at VA 0x10def1a0: writes a byte at the byte index at 0x08 and
// bit offset at 0x0c of the buffer at 0x04 (whose method at VA 0x10dce1a0 returns the address of a
// byte), splitting it over two bytes when the bit offset is not zero, then advances the byte index
// and adds eight to the bit count at 0x10. The class, method and member names are invented; the
// offsets and the address are the binary's.

class UnkType_10def1a0_Buffer
{
public:
    unsigned char* Unk_10dce1a0(int Index);
};

class UnkType_10def1a0
{
public:
    void Unk_10def1a0(unsigned char Value);

    int unk_00;
    UnkType_10def1a0_Buffer* unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
};

// UnkType_10def1a0::Unk_10def1a0
void UnkType_10def1a0::Unk_10def1a0(unsigned char Value)
{
    if ( unk_0c == 0 )
    {
        *unk_04->Unk_10dce1a0(unk_08) = Value;
    }
    else
    {
        unsigned char Shift = (unsigned char)( 8 - unk_0c );
        unsigned char Back = (unsigned char)( 8 - Shift );
        unsigned char High = (unsigned char)( Value >> Back );
        *unk_04->Unk_10dce1a0(unk_08) = *unk_04->Unk_10dce1a0(unk_08) | High;
        *unk_04->Unk_10dce1a0(unk_08 + 1) =
            (unsigned char)( (unsigned char)( (unsigned char)( High << Back ) ^ Value ) << Shift );
    }
    unk_08++;
    unk_10 += 8;
}
