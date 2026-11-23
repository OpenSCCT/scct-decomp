// campaign_leaf_74c8a0.cpp -- one function at file offset 0x74c8a0, preferred VA 0x1104c8a0. For a
// record whose word at 0x4 is clear it asks the method at VA 0x11059e50 of the object returned by
// the function at VA 0x11056900 about the record's word at 0x10 and the second argument, returning
// 1 when that succeeds and otherwise passing the word at 0xc to the method at VA 0x1104be90; any
// record not handled that way goes to the method at VA 0x1104c570, and the result is 0. The type,
// method and parameter names are invented; the offsets and the addresses are the binary's.

class UnkType_1104c8a0_Manager
{
public:
    int Unk_11059e50(int Value, int Arg);
};

UnkType_1104c8a0_Manager* Unk_11056900();

struct UnkType_1104c8a0_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
};

class UnkType_1104c8a0
{
public:
    void Unk_1104be90(int Value);
    void Unk_1104c570(UnkType_1104c8a0_Record* Record);
    int Unk_1104c8a0(UnkType_1104c8a0_Record* Record, int Arg);
};

// UnkType_1104c8a0::Unk_1104c8a0
int UnkType_1104c8a0::Unk_1104c8a0(UnkType_1104c8a0_Record* Record, int Arg)
{
    if ( Record != 0 )
    {
        if ( Record->unk_4 == 0 )
        {
            if ( Unk_11056900()->Unk_11059e50(Record->unk_10, Arg) == 0 )
            {
                Unk_1104be90(Record->unk_c);
            }
            else
            {
                return 1;
            }
        }
        Unk_1104c570(Record);
    }
    return 0;
}
