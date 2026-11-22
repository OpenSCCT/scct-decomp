// campaign_leaf_36a1f0.cpp -- a member function at VA 0x10c6a1f0 that calls the member at VA
// 0x10c647d0 and stores in the int at 0x300 the result of the free function at VA 0x10c6a190, given
// the pointer at 0x6c. The class, method and member names are invented; the offsets and addresses
// are the binary's.

int Unk_10c6a190(void* Item);

class UnkType_10c6a1f0
{
public:
    void Unk_10c647d0();
    void Unk_10c6a1f0();

private:
    unsigned char unk_000[0x6c];
    void* unk_06c;
    unsigned char unk_070[0x300 - 0x70];
    int unk_300;
};

// UnkType_10c6a1f0::Unk_10c6a1f0
void UnkType_10c6a1f0::Unk_10c6a1f0()
{
    Unk_10c647d0();
    unk_300 = Unk_10c6a190(unk_06c);
}
