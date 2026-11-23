// campaign_leaf_5a0980.cpp -- thiscall method at VA 0x10ea0980: passes its argument to the method
// at VA 0x10ea43d0, then to the method at VA 0x10ea0600, both on the same object. The class and
// method names are invented.

class UnkType_10ea0980
{
public:
    void Unk_10ea43d0(int Value);
    void Unk_10ea0600(int Value);
    void Unk_10ea0980(int Value);
};

// UnkType_10ea0980::Unk_10ea0980
void UnkType_10ea0980::Unk_10ea0980(int Value)
{
    Unk_10ea43d0(Value);
    Unk_10ea0600(Value);
}
