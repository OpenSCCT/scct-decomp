// campaign_leaf_700850.cpp -- one function at file offset 0x700850, preferred VA 0x11000850. It
// calls the method at VA 0x10e0f570 with its argument and then stores the word at 0xc at 0x4 of
// the argument. The class, method and member names are invented; the offset and the callee's
// address are the binary's.

struct UnkType_11000850_Record
{
    int unk_0;
    int unk_4;
};

class UnkType_11000850
{
public:
    void Unk_11000850(UnkType_11000850_Record* Record);
    void Unk_10e0f570(UnkType_11000850_Record* Record);

    unsigned char unk_0[0xc];
    int unk_c;
};

// UnkType_11000850::Unk_11000850
void UnkType_11000850::Unk_11000850(UnkType_11000850_Record* Record)
{
    Unk_10e0f570(Record);
    Record->unk_4 = unk_c;
}
