// campaign_leaf_75d410.cpp -- one function at file offset 0x75d410, preferred VA 0x1105d410. It
// clears the word at 0x104 of the record and, when the word at 0x100 is 1, passes the record's
// words at 0x4 and 0x8 to the function pointer at 0x10 of the table at 0x18. The class, method and
// member names are invented; the offsets are the binary's.

struct UnkType_1105d410_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
    unsigned char unk_c[0x100 - 0xc];
    int unk_100;
    int unk_104;
};

struct UnkType_1105d410_Table
{
    unsigned char unk_0[0x10];
    void (*unk_10)(int First, int Second);
};

class UnkType_1105d410
{
public:
    void Unk_1105d410(UnkType_1105d410_Record* Record);

    unsigned char unk_0[0x18];
    UnkType_1105d410_Table* unk_18;
};

// UnkType_1105d410::Unk_1105d410
void UnkType_1105d410::Unk_1105d410(UnkType_1105d410_Record* Record)
{
    Record->unk_104 = 0;
    if ( Record->unk_100 == 1 )
    {
        unk_18->unk_10(Record->unk_4, Record->unk_8);
    }
}
