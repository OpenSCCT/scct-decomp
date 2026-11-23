// campaign_leaf_08fdb0.cpp -- method at VA 0x1098fdb0: calls the method at VA 0x1098fd40, clears
// the byte at 0x2f4 and, when the value at 0x308 is set, sets the bytes at 0x22d and 0x22f. The
// class, member and method names are invented; the offsets and the address are the binary's.

class UnkType_1098fdb0
{
public:
    void Unk_1098fdb0();
    void Unk_1098fd40();

private:
    unsigned char unk_000[0x22d];
    bool unk_22d;
    unsigned char unk_22e;
    bool unk_22f;
    unsigned char unk_230[0x2f4 - 0x230];
    bool unk_2f4;
    unsigned char unk_2f5[0x308 - 0x2f5];
    int unk_308;
};

// UnkType_1098fdb0::Unk_1098fdb0
void UnkType_1098fdb0::Unk_1098fdb0()
{
    Unk_1098fd40();
    unk_2f4 = false;
    if ( unk_308 )
    {
        unk_22d = true;
        unk_22f = true;
    }
}
