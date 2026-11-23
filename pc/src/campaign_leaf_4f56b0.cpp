// campaign_leaf_4f56b0.cpp -- method at VA 0x10df56b0: when the member at 0x08 of its first
// argument matches the name L"m_uiRNGSeed" or L"m_uiSimulationID" (method at VA 0x10d7d020),
// formats the word at 0x00 or the sixteen-bit value at 0x04 with L"%d" into its second argument
// (function at VA 0x10d7d200) and returns true; otherwise returns false. The class, method and
// member names are invented; the strings and addresses are the binary's.

class UnkType_10df56b0_Name
{
public:
    UnkType_10df56b0_Name(const unsigned short* Text);
    ~UnkType_10df56b0_Name();

    int unk_00;
};

class UnkType_10df56b0_Key
{
public:
    bool Unk_10d7d020(const UnkType_10df56b0_Name& Name);
};

class UnkType_10df56b0_Arg
{
public:
    unsigned char unk_00[0x08];
    UnkType_10df56b0_Key unk_08;
};

int Unk_10d7d200(unsigned short* Out, const unsigned short* Format, ...);

class UnkType_10df56b0
{
public:
    bool Unk_10df56b0(UnkType_10df56b0_Arg* Arg, unsigned short* Out);

    unsigned int unk_00;
    unsigned short unk_04;
};

// UnkType_10df56b0::Unk_10df56b0
bool UnkType_10df56b0::Unk_10df56b0(UnkType_10df56b0_Arg* Arg, unsigned short* Out)
{
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10df56b0_Name(L"m_uiRNGSeed")) )
    {
        Unk_10d7d200(Out, L"%d", unk_00);
        return true;
    }
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10df56b0_Name(L"m_uiSimulationID")) )
    {
        Unk_10d7d200(Out, L"%d", unk_04);
        return true;
    }
    return false;
}
