// campaign_leaf_718c60.cpp -- one function at file offset 0x718c60, preferred VA 0x11018c60. It
// fills the record it is given: the base class's method at VA 0x10e6d2a0 writes its first word,
// and it then copies the words at 0x18 and 0x1c into the record's words at 0x4 and 0x8. The class,
// method and member names are invented; the offsets and the callee's address are the binary's.

struct UnkType_11018c60_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_11018c60_Base
{
public:
    void Unk_10e6d2a0(UnkType_11018c60_Record* Record);

    unsigned char unk_0[0x14];
    int unk_14;
};

class UnkType_11018c60 : public UnkType_11018c60_Base
{
public:
    void Unk_11018c60(UnkType_11018c60_Record* Record);

    int unk_18;
    int unk_1c;
};

// UnkType_11018c60::Unk_11018c60
void UnkType_11018c60::Unk_11018c60(UnkType_11018c60_Record* Record)
{
    Unk_10e6d2a0(Record);
    Record->unk_4 = unk_18;
    Record->unk_8 = unk_1c;
}
