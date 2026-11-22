// campaign_leaf_36a6a0.cpp -- a member function at VA 0x10c6a6a0: when the int at 0x2c8 is zero it
// stores there the result of the free function at VA 0x10c600b0, given the pointer at 0x6c. The
// class, method and member names are invented; the offsets and addresses are the binary's.

int Unk_10c600b0(void* Item);

class UnkType_10c6a6a0
{
public:
    void Unk_10c6a6a0();

private:
    unsigned char unk_000[0x6c];
    void* unk_06c;
    unsigned char unk_070[0x2c8 - 0x70];
    int unk_2c8;
};

// UnkType_10c6a6a0::Unk_10c6a6a0
void UnkType_10c6a6a0::Unk_10c6a6a0()
{
    if ( !unk_2c8 )
    {
        unk_2c8 = Unk_10c600b0(unk_06c);
    }
}
