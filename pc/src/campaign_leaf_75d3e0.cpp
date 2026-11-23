// campaign_leaf_75d3e0.cpp -- one function at file offset 0x75d3e0, preferred VA 0x1105d3e0. It
// sets the word at 0x104 of the record to 1 and, when the word at 0x100 is 1, passes the record's
// words at 0x4 and 0x8 to the function pointer at 0xc of the table at 0x18. The class, method and
// member names are invented; the offsets are the binary's.

struct UnkType_1105d3e0_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
    unsigned char unk_c[0x100 - 0xc];
    int unk_100;
    int unk_104;
};

struct UnkType_1105d3e0_Table
{
    unsigned char unk_0[0xc];
    void (*unk_c)(int First, int Second);
};

class UnkType_1105d3e0
{
public:
    void Unk_1105d3e0(UnkType_1105d3e0_Record* Record);

    unsigned char unk_0[0x18];
    UnkType_1105d3e0_Table* unk_18;
};

// UnkType_1105d3e0::Unk_1105d3e0
void UnkType_1105d3e0::Unk_1105d3e0(UnkType_1105d3e0_Record* Record)
{
    Record->unk_104 = 1;
    if ( Record->unk_100 == 1 )
    {
        unk_18->unk_c(Record->unk_4, Record->unk_8);
    }
}
