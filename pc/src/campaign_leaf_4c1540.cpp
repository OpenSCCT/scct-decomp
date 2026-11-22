// campaign_leaf_4c1540.cpp -- thiscall at VA 0x10dc1540: stores the address of the function at
// VA 0x10dc1520 at offset 8 and its argument at offset 0x0c. All names are invented.

void Unk_10dc1520();

class UnkType_10dc1540
{
public:
    void Unk_10dc1540(int Value);

private:
    int unk_00;
    int unk_04;
    void (*unk_08)();
    int unk_0c;
};

// UnkType_10dc1540::Unk_10dc1540
void UnkType_10dc1540::Unk_10dc1540(int Value)
{
    unk_08 = Unk_10dc1520;
    unk_0c = Value;
}
