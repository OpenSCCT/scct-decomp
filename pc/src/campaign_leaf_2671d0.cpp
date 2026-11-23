// campaign_leaf_2671d0.cpp -- a member function at VA 0x10b671d0 taking two flags: when the
// pointer at 0x144 is set and the lookup through the object the pointer at 0x1c refers to (the
// entry its member at 0x04 gives for its byte at 0x0c with the member at VA 0x10a0e220, then the
// member at VA 0x10a45b50 of that entry's object at 0x64) gives non-zero, it calls the member at
// VA 0x10d308c0 of the object at 0x144 with 0 and 1 when the first flag is set, then passes that
// object's member at VA 0x10d30870 the second flag, and its member at VA 0x10d307f0 1 and 1 when
// the second flag is set, or the first flag and 1 when it is not. The class, method, member and
// parameter names are invented; the offsets and addresses are the binary's.

class UnkType_10b671d0_Lookup
{
public:
    int Unk_10a45b50();
};

class UnkType_10b671d0_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b671d0_Lookup* unk_64;
};

class UnkType_10b671d0_Table
{
public:
    UnkType_10b671d0_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b671d0_Item
{
public:
    int unk_00;
    UnkType_10b671d0_Table* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

class UnkType_10b671d0_Target
{
public:
    void Unk_10d307f0(bool First, int Second);
    void Unk_10d30870(bool Value);
    void Unk_10d308c0(int First, int Second);
};

class UnkType_10b671d0
{
public:
    void Unk_10b671d0(bool First, bool Second);

private:
    unsigned char unk_000[0x1c];
    UnkType_10b671d0_Item* unk_01c;
    unsigned char unk_020[0x144 - 0x20];
    UnkType_10b671d0_Target* unk_144;
};

// UnkType_10b671d0::Unk_10b671d0
void UnkType_10b671d0::Unk_10b671d0(bool First, bool Second)
{
    if ( unk_144 && unk_01c->unk_04->Unk_10a0e220(unk_01c->unk_0c)->unk_64->Unk_10a45b50() )
    {
        if ( First )
        {
            unk_144->Unk_10d308c0(0, 1);
        }
        if ( Second )
        {
            unk_144->Unk_10d30870(true);
            unk_144->Unk_10d307f0(true, 1);
        }
        else
        {
            unk_144->Unk_10d30870(false);
            unk_144->Unk_10d307f0(First, 1);
        }
    }
}
