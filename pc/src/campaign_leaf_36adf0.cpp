// campaign_leaf_36adf0.cpp -- a member function at VA 0x10c6adf0 that calls the member at VA
// 0x1099db70 and stores in the int at 0x2c8 the result of the free function at VA 0x10c3bd00, given
// the pointer at 0x6c. The class, method and member names are invented; the offsets and addresses
// are the binary's.

int Unk_10c3bd00(void* Item);

class UnkType_10c6adf0
{
public:
    void Unk_1099db70();
    void Unk_10c6adf0();

private:
    unsigned char unk_000[0x6c];
    void* unk_06c;
    unsigned char unk_070[0x2c8 - 0x70];
    int unk_2c8;
};

// UnkType_10c6adf0::Unk_10c6adf0
void UnkType_10c6adf0::Unk_10c6adf0()
{
    Unk_1099db70();
    unk_2c8 = Unk_10c3bd00(unk_06c);
}
