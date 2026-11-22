// campaign_leaf_59d1d0.cpp -- thiscall method at VA 0x10e9d1d0: passes its argument to the method at
// VA 0x10ea35f0, then to the method at VA 0x10e9cc40, both on the same object. The class and method
// names are invented.

class UnkType_10e9d1d0
{
public:
    void Unk_10ea35f0(int Value);
    void Unk_10e9cc40(int Value);
    void Unk_10e9d1d0(int Value);
};

// UnkType_10e9d1d0::Unk_10e9d1d0
void UnkType_10e9d1d0::Unk_10e9d1d0(int Value)
{
    Unk_10ea35f0(Value);
    Unk_10e9cc40(Value);
}
