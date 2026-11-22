// campaign_leaf_3681f0.cpp -- a member function at VA 0x10c681f0 that stores in the int at 0x2f0
// the result of the free function at VA 0x10c44760, given the pointer at 0x6c, and then calls the
// member at VA 0x10c647d0. The class, method and member names are invented; the offsets and
// addresses are the binary's.

int Unk_10c44760(void* Item);

class UnkType_10c681f0
{
public:
    void Unk_10c647d0();
    void Unk_10c681f0();

private:
    unsigned char unk_000[0x6c];
    void* unk_06c;
    unsigned char unk_070[0x2f0 - 0x70];
    int unk_2f0;
};

// UnkType_10c681f0::Unk_10c681f0
void UnkType_10c681f0::Unk_10c681f0()
{
    unk_2f0 = Unk_10c44760(unk_06c);
    Unk_10c647d0();
}
