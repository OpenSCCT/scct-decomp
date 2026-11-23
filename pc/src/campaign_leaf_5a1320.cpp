// campaign_leaf_5a1320.cpp -- thiscall method at VA 0x10ea1320: passes its argument to the method
// at VA 0x10ea4500, then to the method at VA 0x10ea1210, both on the same object. The class and
// method names are invented.

class UnkType_10ea1320
{
public:
    void Unk_10ea4500(int Value);
    void Unk_10ea1210(int Value);
    void Unk_10ea1320(int Value);
};

// UnkType_10ea1320::Unk_10ea1320
void UnkType_10ea1320::Unk_10ea1320(int Value)
{
    Unk_10ea4500(Value);
    Unk_10ea1210(Value);
}
