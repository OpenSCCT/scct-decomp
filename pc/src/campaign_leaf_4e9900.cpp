// campaign_leaf_4e9900.cpp -- method at VA 0x10de9900: when the member at 0x08 of its first
// argument matches the name L"m_uiFirst" or L"m_uiLast" (method at VA 0x10d7d020), formats the word
// at 0x00 or 0x04 with L"%d" into its second argument (function at VA 0x10d7d200) and returns true;
// otherwise returns false. The class, method and member names are invented; the strings and
// addresses are the binary's.

class UnkType_10de9900_Name
{
public:
    UnkType_10de9900_Name(const unsigned short* Text);
    ~UnkType_10de9900_Name();

    int unk_00;
};

class UnkType_10de9900_Key
{
public:
    bool Unk_10d7d020(const UnkType_10de9900_Name& Name);
};

class UnkType_10de9900_Arg
{
public:
    unsigned char unk_00[0x08];
    UnkType_10de9900_Key unk_08;
};

int Unk_10d7d200(unsigned short* Out, const unsigned short* Format, ...);

class UnkType_10de9900
{
public:
    bool Unk_10de9900(UnkType_10de9900_Arg* Arg, unsigned short* Out);

    unsigned int unk_00;
    unsigned int unk_04;
};

// UnkType_10de9900::Unk_10de9900
bool UnkType_10de9900::Unk_10de9900(UnkType_10de9900_Arg* Arg, unsigned short* Out)
{
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10de9900_Name(L"m_uiFirst")) )
    {
        Unk_10d7d200(Out, L"%d", unk_00);
        return true;
    }
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10de9900_Name(L"m_uiLast")) )
    {
        Unk_10d7d200(Out, L"%d", unk_04);
        return true;
    }
    return false;
}
