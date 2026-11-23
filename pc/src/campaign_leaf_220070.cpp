// campaign_leaf_220070.cpp -- a member function at VA 0x10b20070 taking three values: it passes
// what its base's member at VA 0x10a0e2a0 returns to its own member at VA 0x10b20010. When the
// pointer at 0x40 is set and that object's member at VA 0x10ad4790 returns non-zero, it clears the
// object's byte at 0x14 and returns 1 when the object's target (what the member at VA 0x10a45b50
// of the object at 0x64 of the entry its pointer at 0x04 gives for its byte at 0x0c with the member
// at VA 0x10a0e220 returns) has bit 17 of its int at 0x28 set and the object's int at 0xfe0 is set,
// or when the object's pointer at 0xe4 is set and its member at VA 0x10ad4ac0 returns non-zero for
// the values; otherwise it returns what its base's member at VA 0x10a0db60 returns for them. It
// returns 0 otherwise. The class, method, member and parameter names are invented; the offsets and
// addresses are the binary's.

class UnkType_10b20070_Target
{
public:
    unsigned char unk_00[0x28];
    int unk_28;
};

class UnkType_10b20070_Lookup
{
public:
    UnkType_10b20070_Target* Unk_10a45b50();
};

class UnkType_10b20070_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b20070_Lookup* unk_64;
};

class UnkType_10b20070_Table
{
public:
    UnkType_10b20070_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b20070_Menu
{
public:
    // guess: the current target (an inline accessor; name invented)
    UnkType_10b20070_Target* GetTarget()
    {
        return unk_004->Unk_10a0e220(unk_00c)->unk_64->Unk_10a45b50();
    }

    int Unk_10ad4790();
    int Unk_10ad4ac0(int First, int Second, int Third);

    int unk_000;
    UnkType_10b20070_Table* unk_004;
    int unk_008;
    unsigned char unk_00c;
    unsigned char unk_00d[0x14 - 0x0d];
    bool unk_014;
    unsigned char unk_015[0xe4 - 0x15];
    void* unk_0e4;
    unsigned char unk_0e8[0xfe0 - 0xe8];
    int unk_fe0;
};

class UnkType_10b20070_Base
{
public:
    int Unk_10a0db60(int First, int Second, int Third);
    int Unk_10a0e2a0();
};

class UnkType_10b20070 : public UnkType_10b20070_Base
{
public:
    void Unk_10b20010(int Value);
    int Unk_10b20070(int First, int Second, int Third);

private:
    unsigned char unk_00[0x40];
    UnkType_10b20070_Menu* unk_40;
};

// UnkType_10b20070::Unk_10b20070
int UnkType_10b20070::Unk_10b20070(int First, int Second, int Third)
{
    Unk_10b20010(Unk_10a0e2a0());
    UnkType_10b20070_Menu* Menu = unk_40;
    if ( Menu && Menu->Unk_10ad4790() )
    {
        Menu->unk_014 = false;
        if ( (Menu->GetTarget()->unk_28 & 0x20000) && Menu->unk_fe0 )
        {
            return 1;
        }
        if ( Menu->unk_0e4 && Menu->Unk_10ad4ac0(First, Second, Third) )
        {
            return 1;
        }
        return Unk_10a0db60(First, Second, Third);
    }
    return 0;
}
