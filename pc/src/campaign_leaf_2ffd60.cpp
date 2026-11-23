// campaign_leaf_2ffd60.cpp -- method at VA 0x10bffd60 taking an object and a value: takes the
// object its argument's method at VA 0x10a037c0 returns, makes a function-local static name
// L"s_CoopRplBtmInit" on first use (through the name constructor at VA 0x10cd4790 with 2), and when
// that object is set and the name its method at VA 0x10cee180 returns equals this one, stores this
// object at 0x284 of the argument, copies the object's three words at 0x94c to the argument's at
// 0x684, passes the word at 0x2ec of the object's owner at 0x284 to the method at VA 0x1099e460 of
// the object's member at 0x400, and passes the argument and the value to this object's method at VA
// 0x1099f3f0. The class, member and method names are invented; the offsets, the string and the
// addresses are the binary's.

class UnkType_10bffd60_Name
{
public:
    UnkType_10bffd60_Name(const unsigned short* Text, int FindType);

    int operator==(const UnkType_10bffd60_Name& Other) const
    {
        return unk_00 == Other.unk_00;
    }

private:
    int unk_00;
};

class UnkType_10bffd60_Vector
{
public:
    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_10bffd60_400
{
public:
    void Unk_1099e460(int Value);
};

class UnkType_10bffd60;

class UnkType_10bffd60_Pawn
{
public:
    UnkType_10bffd60_Pawn* Unk_10a037c0();
    UnkType_10bffd60_Name Unk_10cee180();

    unsigned char unk_00[0x284];
    UnkType_10bffd60* unk_284;
    unsigned char unk_288[0x400 - 0x288];
    UnkType_10bffd60_400* unk_400;
    unsigned char unk_404[0x684 - 0x404];
    UnkType_10bffd60_Vector unk_684;
    unsigned char unk_690[0x94c - 0x690];
    UnkType_10bffd60_Vector unk_94c;
};

class UnkType_10bffd60
{
public:
    void Unk_10bffd60(UnkType_10bffd60_Pawn* Pawn, int Value);
    void Unk_1099f3f0(UnkType_10bffd60_Pawn* Pawn, int Value);

    unsigned char unk_00[0x2ec];
    int unk_2ec;
};

// UnkType_10bffd60::Unk_10bffd60
void UnkType_10bffd60::Unk_10bffd60(UnkType_10bffd60_Pawn* Pawn, int Value)
{
    UnkType_10bffd60_Pawn* Other = Pawn->Unk_10a037c0();
    static UnkType_10bffd60_Name CoopRplBtmInit(L"s_CoopRplBtmInit", 2);
    if ( Other && Other->Unk_10cee180() == CoopRplBtmInit )
    {
        Pawn->unk_284 = this;
        Pawn->unk_684 = Other->unk_94c;
        Other->unk_400->Unk_1099e460(Other->unk_284->unk_2ec);
        Unk_1099f3f0(Pawn, Value);
    }
}
