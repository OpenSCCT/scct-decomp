// campaign_leaf_73bc40.cpp -- thiscall method at VA 0x1103bc40: stores 0x11 in the byte at 0x15 and
// the result of the method at VA 0x1103bc60 at 0x18 of the object at 0x04, then returns the member
// at 0x00. The class and method names are invented.

struct UnkType_1103bc40_04
{
    int unk_00[5];
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char unk_16;
    unsigned char unk_17;
    int unk_18;
};

class UnkType_1103bc40
{
public:
    int Unk_1103bc60();
    int Unk_1103bc40();

private:
    int unk_00;
    UnkType_1103bc40_04* unk_04;
};

// UnkType_1103bc40::Unk_1103bc40
int UnkType_1103bc40::Unk_1103bc40()
{
    int Value = Unk_1103bc60();
    UnkType_1103bc40_04* Object = unk_04;
    Object->unk_15 = 0x11;
    Object->unk_18 = Value;
    return unk_00;
}
