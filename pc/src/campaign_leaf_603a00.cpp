// campaign_leaf_603a00.cpp -- thiscall method at VA 0x10f03a00: dispatches on the low 16 bits of
// its argument: 0x401, 0x402, 0x501 and 0x601 return the result of the methods at VA 0x10f1a690,
// 0x10f1a6f0, 0x10f1b430 and 0x10f1cf50; any other value is passed to the method at VA 0x10f02720
// and false is returned. guess: a message handler. The class and method names are invented.

class UnkType_10f03a00
{
public:
    void Unk_10f02720(int Id);
    bool Unk_10f1a690();
    bool Unk_10f1a6f0();
    bool Unk_10f1b430();
    bool Unk_10f1cf50();
    bool Unk_10f03a00(int Message);
};

// UnkType_10f03a00::Unk_10f03a00
bool UnkType_10f03a00::Unk_10f03a00(int Message)
{
    int Id = Message & 0xffff;

    switch ( Id )
    {
    case 0x401:
        return Unk_10f1a690();
    case 0x402:
        return Unk_10f1a6f0();
    case 0x501:
        return Unk_10f1b430();
    case 0x601:
        return Unk_10f1cf50();
    }
    Unk_10f02720(Id);
    return false;
}
