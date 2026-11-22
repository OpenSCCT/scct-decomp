// campaign_leaf_47d1c0.cpp -- thiscall at VA 0x10d7d1c0: calls the free function at VA 0x10d7cde0
// with its argument and the dword at offset 0. All names are invented.

void Unk_10d7cde0(int Value, int Member);

class UnkType_10d7d1c0
{
public:
    void Unk_10d7d1c0(int Value);

private:
    int unk_00;
};

// UnkType_10d7d1c0::Unk_10d7d1c0
void UnkType_10d7d1c0::Unk_10d7d1c0(int Value)
{
    Unk_10d7cde0(Value, unk_00);
}
