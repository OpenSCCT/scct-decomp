// campaign_leaf_08fd40.cpp -- method at VA 0x1098fd40: calls the method at VA 0x10cd79f0; calls the
// method at VA 0x10cdb590 with two zeros when bit 5 (0x20) of the value at 0x284 of the object at
// 0x24 is set; sets bit 0 of the value at 0x1c of the object at 0x190 and of the object at 0x54 of
// that one, where they exist; and when bit 15 (0x8000) of the value at 0x28 is set, clears it and
// sets bits 12 and 13 (0x3000) of the value at 0x30. The class, member and method names are
// invented; the offsets, the bits and the addresses are the binary's.

class UnkType_1098fd40_24
{
public:
    unsigned char unk_000[0x284];
    unsigned int unk_284;
};

class UnkType_1098fd40_190
{
public:
    unsigned char unk_00[0x1c];
    unsigned int unk_1c;
    unsigned char unk_20[0x54 - 0x20];
    UnkType_1098fd40_190* unk_54;
};

class UnkType_1098fd40
{
public:
    void Unk_1098fd40();
    void Unk_10cd79f0();
    void Unk_10cdb590(int Arg0, int Arg1);

private:
    unsigned char unk_000[0x24];
    UnkType_1098fd40_24* unk_024;
    unsigned int unk_028;
    int unk_02c;
    unsigned int unk_030;
    unsigned char unk_034[0x190 - 0x34];
    UnkType_1098fd40_190* unk_190;
};

// UnkType_1098fd40::Unk_1098fd40
void UnkType_1098fd40::Unk_1098fd40()
{
    Unk_10cd79f0();
    if ( unk_024->unk_284 & 0x20 )
    {
        Unk_10cdb590(0, 0);
    }
    if ( unk_190 )
    {
        unk_190->unk_1c |= 1;
    }
    if ( unk_190 )
    {
        UnkType_1098fd40_190* Next = unk_190->unk_54;
        if ( Next )
        {
            Next->unk_1c |= 1;
        }
    }
    if ( unk_028 & 0x8000 )
    {
        unk_030 |= 0x3000;
        unk_028 &= ~0x8000;
    }
}
