// campaign_leaf_74c9f0.cpp -- one function at file offset 0x74c9f0, preferred VA 0x1104c9f0. For a
// record whose word at 0x4 is clear it asks the method at VA 0x11059dd0 of the object returned by
// the function at VA 0x11056900 about the record's word at 0x10, passing it on to that object's
// method at VA 0x11059d50 when that succeeds, and passes the word at 0xc to the method at VA
// 0x1104be90; every record is then passed to the method at VA 0x1104c570. The type, method and
// parameter names are invented; the offsets and the addresses are the binary's.

class UnkType_1104c9f0_Manager
{
public:
    void Unk_11059d50(int Value);
    int Unk_11059dd0(int Value);
};

UnkType_1104c9f0_Manager* Unk_11056900();

struct UnkType_1104c9f0_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
};

class UnkType_1104c9f0
{
public:
    void Unk_1104be90(int Value);
    void Unk_1104c570(UnkType_1104c9f0_Record* Record);
    void Unk_1104c9f0(UnkType_1104c9f0_Record* Record);
};

// UnkType_1104c9f0::Unk_1104c9f0
void UnkType_1104c9f0::Unk_1104c9f0(UnkType_1104c9f0_Record* Record)
{
    if ( Record == 0 )
    {
        return;
    }
    if ( Record->unk_4 == 0 )
    {
        if ( Unk_11056900()->Unk_11059dd0(Record->unk_10) == 0 )
        {
            Unk_1104be90(Record->unk_c);
            Unk_1104c570(Record);
            return;
        }
        Unk_11056900()->Unk_11059d50(Record->unk_10);
        Unk_1104be90(Record->unk_c);
    }
    Unk_1104c570(Record);
}
