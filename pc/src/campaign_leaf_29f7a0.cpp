// campaign_leaf_29f7a0.cpp -- method at VA 0x10b9f7a0 taking three words by address: stores in them
// the three at 0xaac when bit 0 of the word at 0xaa8 is set, otherwise what the method at VA
// 0x10b9f670 returns for bit 0 of the word at 0x790; then sets bit 0 of the word at 0xa3c. The
// class, member and method names are invented; the offsets and the address are the binary's.

class UnkType_10b9f7a0_Vector
{
public:
    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_10b9f7a0
{
public:
    void Unk_10b9f7a0(UnkType_10b9f7a0_Vector& Out);
    UnkType_10b9f7a0_Vector Unk_10b9f670(int Flag);

private:
    unsigned char unk_00[0x790];
    int unk_790;
    unsigned char unk_794[0xa3c - 0x794];
    int unk_a3c;
    unsigned char unk_a40[0xaa8 - 0xa40];
    int unk_aa8;
    UnkType_10b9f7a0_Vector unk_aac;
};

// UnkType_10b9f7a0::Unk_10b9f7a0
void UnkType_10b9f7a0::Unk_10b9f7a0(UnkType_10b9f7a0_Vector& Out)
{
    if ( unk_aa8 & 1 )
    {
        Out = unk_aac;
    }
    else
    {
        Out = Unk_10b9f670(unk_790 & 1);
    }
    unk_a3c |= 1;
}
