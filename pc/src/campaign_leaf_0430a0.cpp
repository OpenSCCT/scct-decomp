// campaign_leaf_0430a0.cpp -- method at VA 0x109430a0: returns 1 when the method at VA 0x10cd72b0
// returns nonzero for the member at 0x438, bit 8 of the value at 0x410 is set, bit 2 of the byte at
// 0x814 is clear and bit 0 of the byte at 0xbfc is clear; otherwise 0. The class, member and method
// names are invented; the offsets, the bits and the address are the binary's.

class UnkType_109430a0_438
{
public:
    int unk_00;
};

class UnkType_109430a0
{
public:
    int Unk_109430a0();
    int Unk_10cd72b0(UnkType_109430a0_438* Value);

private:
    unsigned char unk_000[0x410];
    unsigned int unk_410;
    unsigned char unk_414[0x438 - 0x414];
    UnkType_109430a0_438 unk_438;
    unsigned char unk_43c[0x814 - 0x43c];
    unsigned char unk_814;
    unsigned char unk_815[0xbfc - 0x815];
    unsigned char unk_bfc;
};

// UnkType_109430a0::Unk_109430a0
int UnkType_109430a0::Unk_109430a0()
{
    if ( Unk_10cd72b0(&unk_438) && (unk_410 & 0x100) && !(unk_814 & 4) && !(unk_bfc & 1) )
    {
        return 1;
    }
    return 0;
}
