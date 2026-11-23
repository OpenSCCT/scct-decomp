// campaign_leaf_73bc40.cpp -- one function at file offset 0x73bc40, preferred VA 0x1103bc40. It
// stores 0x11 in the byte at 0x15 and the result of the method at VA 0x1103bc60 in the word at
// 0x18 of the record at 0x4, and returns the word at 0x0. The class, method and member names are
// invented; the offset and the callee's address are the binary's.

struct UnkType_1103bc40_Record
{
    unsigned char unk_0[0x15];
    unsigned char unk_15;
    unsigned char unk_16[0x18 - 0x16];
    int unk_18;
};

class UnkType_1103bc40
{
public:
    int Unk_1103bc40();
    int Unk_1103bc60();

    int unk_0;
    UnkType_1103bc40_Record* unk_4;
};

// UnkType_1103bc40::Unk_1103bc40
int UnkType_1103bc40::Unk_1103bc40()
{
    UnkType_1103bc40_Record* Record;
    int Value;

    Value = Unk_1103bc60();
    Record = unk_4;
    Record->unk_15 = 0x11;
    Record->unk_18 = Value;
    return unk_0;
}
