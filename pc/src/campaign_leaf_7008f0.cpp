// campaign_leaf_7008f0.cpp -- one function at file offset 0x7008f0, preferred VA 0x110008f0. It
// fills the record it is given: the base class's method at VA 0x10e0f570 writes its first word,
// and it then copies the words at 0xc and 0x10 into the record's words at 0x4 and 0x8. The class,
// method and member names are invented; the offsets and the callee's address are the binary's.

struct UnkType_110008f0_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_110008f0_Base
{
public:
    void Unk_10e0f570(UnkType_110008f0_Record* Record);

    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_110008f0 : public UnkType_110008f0_Base
{
public:
    void Unk_110008f0(UnkType_110008f0_Record* Record);

    int unk_c;
    int unk_10;
};

// UnkType_110008f0::Unk_110008f0
void UnkType_110008f0::Unk_110008f0(UnkType_110008f0_Record* Record)
{
    Unk_10e0f570(Record);
    Record->unk_4 = unk_c;
    Record->unk_8 = unk_10;
}
