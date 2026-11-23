// campaign_leaf_29d4a0.cpp -- method at VA 0x10b9d4a0 taking a pawn, a flag and a value: makes two
// function-local static names on first use (L"s_Grab" and L"s_GrabTargeting", through the name
// constructor at VA 0x10cd4790 with 2); returns 0 unless the pawn is set, bit 5 of its word at 0x2c
// is set, its controller at 0x2b4 is set and the name the controller's method at VA 0x10cee180
// returns is one of the two. With the flag set it also returns 0 when the controller's object at
// 0x60c is unset or has bit 31 of its word at 0x748 set. A nonzero value below 122 must exceed 3,
// and the float at 0x264 of that object must exceed the float at 0x2c8 of the object reached
// through 0x78 and 0x5d0 of this one, or it returns 0; a nonzero value then sets bit 31 of that
// word when the object is set. It returns 1 otherwise. The class, member and method names are
// invented; the offsets, the strings and the addresses are the binary's.

class UnkType_10b9d4a0_Name
{
public:
    UnkType_10b9d4a0_Name(const unsigned short* Text, int FindType);

    int operator==(const UnkType_10b9d4a0_Name& Other) const
    {
        return unk_00 == Other.unk_00;
    }

private:
    int unk_00;
};

class UnkType_10b9d4a0_60c
{
public:
    unsigned char unk_00[0x264];
    float unk_264;
    unsigned char unk_268[0x748 - 0x268];
    unsigned int unk_748;
};

class UnkType_10b9d4a0_Controller
{
public:
    UnkType_10b9d4a0_Name Unk_10cee180();

    unsigned char unk_00[0x60c];
    UnkType_10b9d4a0_60c* unk_60c;
};

class UnkType_10b9d4a0_Pawn
{
public:
    unsigned char unk_00[0x2c];
    int unk_2c;
    unsigned char unk_30[0x2b4 - 0x30];
    UnkType_10b9d4a0_Controller* unk_2b4;
};

class UnkType_10b9d4a0_5d0
{
public:
    unsigned char unk_00[0x2c8];
    float unk_2c8;
};

class UnkType_10b9d4a0_78
{
public:
    unsigned char unk_00[0x5d0];
    UnkType_10b9d4a0_5d0* unk_5d0;
};

class UnkType_10b9d4a0
{
public:
    int Unk_10b9d4a0(UnkType_10b9d4a0_Pawn* Pawn, int Check, int Value);

private:
    unsigned char unk_00[0x78];
    UnkType_10b9d4a0_78* unk_78;
};

// UnkType_10b9d4a0::Unk_10b9d4a0
int UnkType_10b9d4a0::Unk_10b9d4a0(UnkType_10b9d4a0_Pawn* Pawn, int Check, int Value)
{
    static UnkType_10b9d4a0_Name Grab(L"s_Grab", 2);
    static UnkType_10b9d4a0_Name GrabTargeting(L"s_GrabTargeting", 2);
    int Result = 0;
    if ( Pawn && ( Pawn->unk_2c & 0x20 ) )
    {
        UnkType_10b9d4a0_Controller* Controller = Pawn->unk_2b4;
        if ( Controller
            && ( Controller->Unk_10cee180() == Grab
                 || Controller->Unk_10cee180() == GrabTargeting ) )
        {
            if ( !Check
                || ( Controller->unk_60c && !( Controller->unk_60c->unk_748 & 0x80000000 ) ) )
            {
                if ( !Value )
                {
                    Result = 1;
                }
                else if ( Value >= 0x7a
                          || ( Value > 3 && Controller->unk_60c
                               && Controller->unk_60c->unk_264 > unk_78->unk_5d0->unk_2c8 ) )
                {
                    if ( Controller->unk_60c )
                    {
                        Controller->unk_60c->unk_748 |= 0x80000000;
                    }
                    Result = 1;
                }
            }
        }
    }
    return Result;
}
