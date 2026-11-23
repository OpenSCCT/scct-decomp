// campaign_leaf_562ba0.cpp -- thiscall method at VA 0x10e62ba0: passes its argument to the method
// at VA 0x10e6d000, then to the method at VA 0x10e628d0, both on the same object. The class and
// method names are invented.

class UnkType_10e62ba0
{
public:
    void Unk_10e6d000(int Value);
    void Unk_10e628d0(int Value);
    void Unk_10e62ba0(int Value);
};

// UnkType_10e62ba0::Unk_10e62ba0
void UnkType_10e62ba0::Unk_10e62ba0(int Value)
{
    Unk_10e6d000(Value);
    Unk_10e628d0(Value);
}
