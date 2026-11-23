// campaign_leaf_45fc50.cpp -- method at VA 0x10d5fc50: calls the method at VA 0x10d5f5f0 with the
// float at 0x8c plus one, limited to the integer at 0x88. The class, member and method names are
// invented; the offsets and the address are the binary's.

class UnkType_10d5fc50
{
public:
    void Unk_10d5f5f0(float Value);
    void Unk_10d5fc50();

private:
    char unk_0[0x88];
    int unk_88;
    float unk_8c;
};

// UnkType_10d5fc50::Unk_10d5fc50
void UnkType_10d5fc50::Unk_10d5fc50()
{
    float Value = unk_8c + 1.0f;
    float Limit = (float)unk_88;

    Unk_10d5f5f0(Value < Limit ? Value : Limit);
}
