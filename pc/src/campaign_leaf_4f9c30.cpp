// campaign_leaf_4f9c30.cpp -- method at VA 0x10df9c30: compares the member at 0x08 of its first
// argument with the names L"SimulationChecksum" and L"UserChecksum0" to L"UserChecksum2" (method at
// VA 0x10d7d020), then L"UserChecksum3" and L"UserChecksum4" (method at VA 0x10a9c7b0), stopping at
// the first match; it formats none of them and always returns false. The class, method and member
// names are invented; the strings and addresses are the binary's.

class UnkType_10df9c30_Name
{
public:
    UnkType_10df9c30_Name(const unsigned short* Text);
    ~UnkType_10df9c30_Name();

    int unk_00;
};

class UnkType_10df9c30_Key
{
public:
    bool Unk_10d7d020(const UnkType_10df9c30_Name& Name);
    bool Unk_10a9c7b0(const unsigned short* Name);
};

class UnkType_10df9c30_Arg
{
public:
    unsigned char unk_00[0x08];
    UnkType_10df9c30_Key unk_08;
};

class UnkType_10df9c30
{
public:
    bool Unk_10df9c30(UnkType_10df9c30_Arg* Arg, unsigned short* Out);
};

// UnkType_10df9c30::Unk_10df9c30
bool UnkType_10df9c30::Unk_10df9c30(UnkType_10df9c30_Arg* Arg, unsigned short* Out)
{
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10df9c30_Name(L"SimulationChecksum")) )
    {
        return false;
    }
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10df9c30_Name(L"UserChecksum0")) )
    {
        return false;
    }
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10df9c30_Name(L"UserChecksum1")) )
    {
        return false;
    }
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10df9c30_Name(L"UserChecksum2")) )
    {
        return false;
    }
    if ( Arg->unk_08.Unk_10a9c7b0(L"UserChecksum3") )
    {
        return false;
    }
    if ( Arg->unk_08.Unk_10a9c7b0(L"UserChecksum4") )
    {
        return false;
    }
    return false;
}
