// campaign_leaf_3459c0.cpp -- one function at file offset 0x3459c0, preferred VA 0x10c459c0. It
// calls the method at 0x10995870 with 0, stores Third at 0x400, Second at 0x284 and First at
// 0x3fc, copies bit 0 of Second's word at 0x2f8 into bit 0 of the word at 0x428, registers this
// object in First's slot at 0x448 (or at 0x44c when that one is taken), and calls the method at
// 0x10c45810. The class, method, member and parameter names are invented; the offsets and the
// bytes are the binary's.

class UnkType_10c459c0;

class UnkType_10c459c0_First
{
public:
    unsigned char unk_0[0x448];
    UnkType_10c459c0* unk_448;
    UnkType_10c459c0* unk_44c;
};

class UnkType_10c459c0_Second
{
public:
    unsigned char unk_0[0x2f8];
    unsigned int bUnk_2f8_0 : 1;
};

class UnkType_10c459c0
{
public:
    void Unk_10995870(int Value);
    void Unk_10c45810();
    void Unk_10c459c0(UnkType_10c459c0_First* First, UnkType_10c459c0_Second* Second, int Third);

    unsigned char unk_0[0x284];
    UnkType_10c459c0_Second* unk_284;
    unsigned char unk_288[0x174];
    UnkType_10c459c0_First* unk_3fc;
    int unk_400;
    unsigned char unk_404[0x24];
    unsigned int bUnk_428_0 : 1;
};

// UnkType_10c459c0::Unk_10c459c0
void UnkType_10c459c0::Unk_10c459c0(UnkType_10c459c0_First* First,
                                    UnkType_10c459c0_Second* Second, int Third)
{
    Unk_10995870(0);
    unk_400 = Third;
    unk_284 = Second;
    unk_3fc = First;
    bUnk_428_0 = Second->bUnk_2f8_0;
    if ( First->unk_448 == 0 )
    {
        First->unk_448 = this;
    }
    else
    {
        First->unk_44c = this;
    }
    Unk_10c45810();
}
