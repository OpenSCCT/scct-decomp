// campaign_leaf_3480b0.cpp -- one function at file offset 0x3480b0, preferred VA 0x10c480b0. It
// calls the method at 0x10995870 with 0, stores Third at 0x42c, Second at 0x284 and First at
// 0x430, registers this object in First's slot at 0x45c (or at 0x460 when the byte at 0x2f8 of
// Second is set) when that slot is empty, and calls the method at 0x10c47ea0. The class, method,
// member and parameter names are invented; the offsets and the bytes are the binary's.

class UnkType_10c480b0;

class UnkType_10c480b0_First
{
public:
    unsigned char unk_0[0x45c];
    UnkType_10c480b0* unk_45c;
    UnkType_10c480b0* unk_460;
};

class UnkType_10c480b0_Second
{
public:
    unsigned char unk_0[0x2f8];
    unsigned char unk_2f8;
};

class UnkType_10c480b0
{
public:
    void Unk_10995870(int Value);
    void Unk_10c47ea0();
    void Unk_10c480b0(UnkType_10c480b0_First* First, UnkType_10c480b0_Second* Second, int Third);

    unsigned char unk_0[0x284];
    UnkType_10c480b0_Second* unk_284;
    unsigned char unk_288[0x1a4];
    int unk_42c;
    UnkType_10c480b0_First* unk_430;
};

// UnkType_10c480b0::Unk_10c480b0
void UnkType_10c480b0::Unk_10c480b0(UnkType_10c480b0_First* First,
                                    UnkType_10c480b0_Second* Second, int Third)
{
    Unk_10995870(0);
    unk_42c = Third;
    unk_284 = Second;
    unk_430 = First;
    if ( !Second->unk_2f8 )
    {
        if ( First->unk_45c == 0 )
        {
            First->unk_45c = this;
        }
    }
    else
    {
        if ( First->unk_460 == 0 )
        {
            First->unk_460 = this;
        }
    }
    Unk_10c47ea0();
}
