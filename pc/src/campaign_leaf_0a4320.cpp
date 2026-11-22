// campaign_leaf_0a4320.cpp -- method at VA 0x109a4320: calls the method at VA 0x1099db70, then
// copies the value at 0x2d8 to 0x2e4. The class, member and method names are invented; the offsets
// and the address are the binary's.

class UnkType_109a4320
{
public:
    void Unk_109a4320();
    void Unk_1099db70();

private:
    unsigned char unk_000[0x2d8];
    int unk_2d8;
    int unk_2dc;
    int unk_2e0;
    int unk_2e4;
};

// UnkType_109a4320::Unk_109a4320
void UnkType_109a4320::Unk_109a4320()
{
    Unk_1099db70();
    unk_2e4 = unk_2d8;
}
