// campaign_leaf_75d440.cpp -- one function at file offset 0x75d440, preferred VA 0x1105d440. When
// the word at 0x100 of the record is 1 it passes the record's words at 0x4 and 0x8 to the function
// pointer at 0x14 of the table at 0x18 and returns its result; otherwise it returns 0xffff0000.
// The class, method and member names are invented; the offsets are the binary's.

struct UnkType_1105d440_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
    unsigned char unk_c[0x100 - 0xc];
    int unk_100;
};

struct UnkType_1105d440_Table
{
    unsigned char unk_0[0x14];
    int (*unk_14)(int First, int Second);
};

class UnkType_1105d440
{
public:
    int Unk_1105d440(UnkType_1105d440_Record* Record);

    unsigned char unk_0[0x18];
    UnkType_1105d440_Table* unk_18;
};

// UnkType_1105d440::Unk_1105d440
int UnkType_1105d440::Unk_1105d440(UnkType_1105d440_Record* Record)
{
    if ( Record->unk_100 == 1 )
    {
        return unk_18->unk_14(Record->unk_4, Record->unk_8);
    }
    return 0xffff0000;
}
