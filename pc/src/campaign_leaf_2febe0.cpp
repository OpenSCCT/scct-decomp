// campaign_leaf_2febe0.cpp -- a member function at VA 0x10bfebe0 that calls the member at VA
// 0x109a4320 and then stores 1 in the int at 0x2c4. The class, method and member names are
// invented; the offsets and addresses are the binary's.

class UnkType_10bfebe0
{
public:
    void Unk_109a4320();
    void Unk_10bfebe0();

private:
    unsigned char unk_000[0x2c4];
    int unk_2c4;
};

// UnkType_10bfebe0::Unk_10bfebe0
void UnkType_10bfebe0::Unk_10bfebe0()
{
    Unk_109a4320();
    unk_2c4 = 1;
}
