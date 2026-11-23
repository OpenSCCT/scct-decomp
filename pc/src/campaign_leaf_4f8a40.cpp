// campaign_leaf_4f8a40.cpp -- method at VA 0x10df8a40: when the member at 0x08 of its first
// argument matches one of the names L"MaxRTT" or L"MinBandwidth" or L"StepFrequency" (method at VA
// 0x10d7d020), formats the matching member (0x04 for MaxRTT, 0xb0 for MinBandwidth, 0x204 for
// StepFrequency) with L"%d" into its second argument (function at VA 0x10d7d200) and returns true;
// otherwise returns false. The class, method and member names are invented; the strings, the
// offsets and the addresses are the binary's.

class UnkType_10df8a40_Name
{
public:
    UnkType_10df8a40_Name(const unsigned short* Text);
    ~UnkType_10df8a40_Name();

    int unk_00;
};

class UnkType_10df8a40_Key
{
public:
    bool Unk_10d7d020(const UnkType_10df8a40_Name& Name);
};

class UnkType_10df8a40_Arg
{
public:
    unsigned char unk_00[0x08];
    UnkType_10df8a40_Key unk_08;
};

int Unk_10d7d200(unsigned short* Out, const unsigned short* Format, ...);

class UnkType_10df8a40
{
public:
    bool Unk_10df8a40(UnkType_10df8a40_Arg* Arg, unsigned short* Out);

    unsigned char unk_00[0x04];
    unsigned short unk_04;
    unsigned char unk_06[0xb0 - 0x06];
    int unk_b0;
    unsigned char unk_b4[0x204 - 0xb4];
    unsigned short unk_204;
};

// UnkType_10df8a40::Unk_10df8a40
bool UnkType_10df8a40::Unk_10df8a40(UnkType_10df8a40_Arg* Arg, unsigned short* Out)
{
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10df8a40_Name(L"MaxRTT")) )
    {
        Unk_10d7d200(Out, L"%d", unk_04);
        return true;
    }
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10df8a40_Name(L"MinBandwidth")) )
    {
        Unk_10d7d200(Out, L"%d", unk_b0);
        return true;
    }
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10df8a40_Name(L"StepFrequency")) )
    {
        Unk_10d7d200(Out, L"%d", unk_204);
        return true;
    }
    return false;
}
