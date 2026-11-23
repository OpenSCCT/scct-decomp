// campaign_leaf_4f4480.cpp -- method at VA 0x10df4480: when the member at 0x08 of its second
// argument matches the name L"m_dsSyncObjectInfo" (method at VA 0x10d7d020), returns the method at
// VA 0x10df9390 of the first argument's member at 0x44 called with the last two arguments;
// otherwise returns the method at VA 0x10da0850 called with all four. The class, method and member
// names are invented; the string and addresses are the binary's.

class UnkType_10df4480_Name
{
public:
    UnkType_10df4480_Name(const unsigned short* Text);
    ~UnkType_10df4480_Name();

    int unk_00;
};

class UnkType_10df4480_Key
{
public:
    bool Unk_10d7d020(const UnkType_10df4480_Name& Name);
};

class UnkType_10df4480_Arg
{
public:
    unsigned char unk_00[0x08];
    UnkType_10df4480_Key unk_08;
};

class UnkType_10df4480_Info
{
public:
    bool Unk_10df9390(int Arg, int Out);
};

class UnkType_10df4480_Owner
{
public:
    unsigned char unk_00[0x44];
    UnkType_10df4480_Info unk_44;
};

class UnkType_10df4480
{
public:
    bool Unk_10df4480(UnkType_10df4480_Owner* Owner, UnkType_10df4480_Arg* Arg, int Arg2, int Out);
    bool Unk_10da0850(UnkType_10df4480_Owner* Owner, UnkType_10df4480_Arg* Arg, int Arg2, int Out);
};

// UnkType_10df4480::Unk_10df4480
bool UnkType_10df4480::Unk_10df4480(UnkType_10df4480_Owner* Owner, UnkType_10df4480_Arg* Arg,
                                    int Arg2, int Out)
{
    if ( Arg->unk_08.Unk_10d7d020(UnkType_10df4480_Name(L"m_dsSyncObjectInfo")) )
    {
        return Owner->unk_44.Unk_10df9390(Arg2, Out);
    }
    return Unk_10da0850(Owner, Arg, Arg2, Out);
}
