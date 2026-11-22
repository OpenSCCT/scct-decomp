// campaign_leaf_36b410.cpp -- a member function at VA 0x10c6b410 that calls the member at VA
// 0x1099db70 and stores in the int at 0x2cc the result of the free function at VA 0x10c6b350, given
// the pointer at 0x6c. The class, method and member names are invented; the offsets and addresses
// are the binary's.

int Unk_10c6b350(void* Item);

class UnkType_10c6b410
{
public:
    void Unk_1099db70();
    void Unk_10c6b410();

private:
    unsigned char unk_000[0x6c];
    void* unk_06c;
    unsigned char unk_070[0x2cc - 0x70];
    int unk_2cc;
};

// UnkType_10c6b410::Unk_10c6b410
void UnkType_10c6b410::Unk_10c6b410()
{
    Unk_1099db70();
    unk_2cc = Unk_10c6b350(unk_06c);
}
