// campaign_leaf_5a00f0.cpp -- thiscall method at VA 0x10ea00f0: passes its argument to the method at
// VA 0x10ea42a0, then to the method at VA 0x10e9fca0, both on the same object. The class and method
// names are invented.

class UnkType_10ea00f0
{
public:
    void Unk_10ea42a0(int Value);
    void Unk_10e9fca0(int Value);
    void Unk_10ea00f0(int Value);
};

// UnkType_10ea00f0::Unk_10ea00f0
void UnkType_10ea00f0::Unk_10ea00f0(int Value)
{
    Unk_10ea42a0(Value);
    Unk_10e9fca0(Value);
}
