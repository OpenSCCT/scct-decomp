// campaign_leaf_222070.cpp -- a member function at VA 0x10b22070: it returns false when the
// pointer at 0x04 is null; otherwise it looks up an object (the entry the object at 0x04 gives for
// the byte at 0x0c with the member at VA 0x10a0e220, then the member at VA 0x10a45b50 of that
// entry's object at 0x64) and returns false when there is none or its pointer at 0x400 is null.
// It returns true when that object's member at VA 0x10b21990 returns non-zero and the int at 0x2c
// of the object its pointer at 0x400 refers to is set, and false otherwise. The class, method and
// member names are invented; the offsets and addresses are the binary's.

class UnkType_10b22070_State
{
public:
    unsigned char unk_00[0x2c];
    int unk_2c;
};

class UnkType_10b22070_Target
{
public:
    int Unk_10b21990();

    unsigned char unk_000[0x400];
    UnkType_10b22070_State* unk_400;
};

class UnkType_10b22070_Lookup
{
public:
    UnkType_10b22070_Target* Unk_10a45b50();
};

class UnkType_10b22070_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b22070_Lookup* unk_64;
};

class UnkType_10b22070_Table
{
public:
    UnkType_10b22070_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b22070
{
public:
    bool Unk_10b22070();

private:
    int unk_00;
    UnkType_10b22070_Table* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

// UnkType_10b22070::Unk_10b22070
bool UnkType_10b22070::Unk_10b22070()
{
    if ( !unk_04 )
    {
        return false;
    }
    UnkType_10b22070_Target* Target = unk_04->Unk_10a0e220(unk_0c)->unk_64->Unk_10a45b50();
    if ( !Target || !Target->unk_400 )
    {
        return false;
    }
    return Target->Unk_10b21990() && Target->unk_400->unk_2c;
}
