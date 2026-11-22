// campaign_leaf_1e1490.cpp -- method at VA 0x10ae1490: calls the free function at VA 0x10ae0d50
// with its argument and the address of the member at 0x04. The class, member and function names are
// invented; the offsets and the addresses are the binary's.

class UnkType_10ae1490_04
{
public:
    int unk_00;
};

void Unk_10ae0d50(int Value, UnkType_10ae1490_04* Member);

class UnkType_10ae1490
{
public:
    void Unk_10ae1490(int Value);

private:
    int unk_00;
    UnkType_10ae1490_04 unk_04;
};

// UnkType_10ae1490::Unk_10ae1490
void UnkType_10ae1490::Unk_10ae1490(int Value)
{
    Unk_10ae0d50(Value, &unk_04);
}
