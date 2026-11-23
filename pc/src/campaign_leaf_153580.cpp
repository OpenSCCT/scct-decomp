// campaign_leaf_153580.cpp -- one function at file offset 0x153580, preferred VA 0x10a53580.
// guess: when both indices are valid entries of the array at offset 0x90 (72-byte entries) and
// at least one of the two entries lacks its first flag, passes the pair and the third argument to
// the method at VA 0x10a52ae0 of its list at offset 0x9c.
// The class, member, parameter and callee names are invented; the offset and the bytes are the
// binary's.

class UnkType_10a53580_Entry
{
public:
    unsigned char unk_0_0 : 1;
    unsigned char unk_1[0x48 - 0x1];
};

class UnkType_10a53580_Link
{
public:
    int First;
    int Second;
    int Value;
};

class UnkType_10a53580_List
{
public:
    void Unk_10a52ae0(const UnkType_10a53580_Link& Link);
};

class UnkType_10a53580
{
public:
    unsigned char unk_0[0x90];
    UnkType_10a53580_Entry* unk_90;
    int unk_94;
    unsigned char unk_98[0x9c - 0x98];
    UnkType_10a53580_List unk_9c;

    void Unk_10a53580(int First, int Second, int Value);
};

// UnkType_10a53580::Unk_10a53580
void UnkType_10a53580::Unk_10a53580(int First, int Second, int Value)
{
    if ( First >= 0 && First < unk_94 && Second >= 0 && Second < unk_94 )
    {
        if ( !unk_90[First].unk_0_0 || !unk_90[Second].unk_0_0 )
        {
            UnkType_10a53580_Link Link;
            Link.First = First;
            Link.Second = Second;
            Link.Value = Value;
            unk_9c.Unk_10a52ae0(Link);
        }
    }
}
