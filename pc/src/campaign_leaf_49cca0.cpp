// campaign_leaf_49cca0.cpp -- thiscall at VA 0x10d9cca0: passes its by-value argument by
// reference to the method at VA 0x10d9cbd0 of the member at offset 0xa4. All names are invented.

class UnkType_10d9cbd0
{
public:
    void Unk_10d9cbd0(const int& Value);
};

class UnkType_10d9cca0
{
public:
    void Unk_10d9cca0(int Value);

private:
    unsigned char unk_00[0xa4];
    UnkType_10d9cbd0 unk_a4;
};

// UnkType_10d9cca0::Unk_10d9cca0
void UnkType_10d9cca0::Unk_10d9cca0(int Value)
{
    unk_a4.Unk_10d9cbd0(Value);
}
