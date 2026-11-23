// campaign_leaf_4f9390.cpp -- method at VA 0x10df9390: when the member at 0x08 of its first
// argument matches the name L"m_uiSimulationID" (method at VA 0x10d7d020), formats the word at 0x00
// with L"%d" into its second argument (function at VA 0x10d7d200) and returns true; otherwise
// returns false. The class, method and member names are invented; the strings and addresses are the
// binary's.

class UnkType_10df9390_Name
{
public:
    UnkType_10df9390_Name(const unsigned short* Text);
    ~UnkType_10df9390_Name();

    int unk_00;
};

class UnkType_10df9390_Key
{
public:
    bool Unk_10d7d020(const UnkType_10df9390_Name& Name);
};

class UnkType_10df9390_Arg
{
public:
    unsigned char unk_00[0x08];
    UnkType_10df9390_Key unk_08;
};

int Unk_10d7d200(unsigned short* Out, const unsigned short* Format, ...);

class UnkType_10df9390
{
public:
    bool Unk_10df9390(UnkType_10df9390_Arg* Arg, unsigned short* Out);

    unsigned short unk_00;
};

// UnkType_10df9390::Unk_10df9390
bool UnkType_10df9390::Unk_10df9390(UnkType_10df9390_Arg* Arg, unsigned short* Out)
{
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10df9390_Name(L"m_uiSimulationID")) )
    {
        Unk_10d7d200(Out, L"%d", unk_00);
        return true;
    }
    return false;
}
