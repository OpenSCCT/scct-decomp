// campaign_leaf_355f00.cpp -- a member function at VA 0x10c55f00 that calls the member at VA
// 0x10bee290 and stores in the int at 0x3fc the result of the free function at VA 0x10bfe700, given
// the pointer at 0x6c. The class, method and member names are invented; the offsets and addresses
// are the binary's.

int Unk_10bfe700(void* Item);

class UnkType_10c55f00
{
public:
    void Unk_10bee290();
    void Unk_10c55f00();

private:
    unsigned char unk_000[0x6c];
    void* unk_06c;
    unsigned char unk_070[0x3fc - 0x70];
    int unk_3fc;
};

// UnkType_10c55f00::Unk_10c55f00
void UnkType_10c55f00::Unk_10c55f00()
{
    Unk_10bee290();
    unk_3fc = Unk_10bfe700(unk_06c);
}
