// campaign_leaf_34bd70.cpp -- a member function at VA 0x10c4bd70 that calls the member at VA
// 0x10bf18b0 and then sets the byte at 0x180 to 1. The class, method and member names are
// invented; the offsets and addresses are the binary's.

class UnkType_10c4bd70
{
public:
    void Unk_10bf18b0();
    void Unk_10c4bd70();

private:
    unsigned char unk_000[0x180];
    unsigned char unk_180;
};

// UnkType_10c4bd70::Unk_10c4bd70
void UnkType_10c4bd70::Unk_10c4bd70()
{
    Unk_10bf18b0();
    unk_180 = 1;
}
