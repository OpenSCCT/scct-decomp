// campaign_leaf_36de80.cpp -- a member function at VA 0x10c6de80 that calls the member at VA
// 0x10a93130 and then passes the byte at 0x2b4 to the member at VA 0x10c6dcd0. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10c6de80
{
public:
    void Unk_10a93130();
    void Unk_10c6dcd0(int Value);
    void Unk_10c6de80();

private:
    unsigned char unk_000[0x2b4];
    unsigned char unk_2b4;
};

// UnkType_10c6de80::Unk_10c6de80
void UnkType_10c6de80::Unk_10c6de80()
{
    Unk_10a93130();
    Unk_10c6dcd0(unk_2b4);
}
