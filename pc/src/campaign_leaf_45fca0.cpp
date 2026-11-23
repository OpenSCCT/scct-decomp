// campaign_leaf_45fca0.cpp -- method at VA 0x10d5fca0: calls the method at VA 0x10d5f5f0 with the
// float at 0x8c less one, at least the integer at 0x84. The class, member and method names are
// invented; the offsets and the address are the binary's.

class UnkType_10d5fca0
{
public:
    void Unk_10d5f5f0(float Value);
    void Unk_10d5fca0();

private:
    char unk_0[0x84];
    int unk_84;
    int unk_88;
    float unk_8c;
};

// UnkType_10d5fca0::Unk_10d5fca0
void UnkType_10d5fca0::Unk_10d5fca0()
{
    float Value = unk_8c - 1.0f;
    float Limit = (float)unk_84;

    Unk_10d5f5f0(Value > Limit ? Value : Limit);
}
