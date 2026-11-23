// campaign_leaf_55c7c0.cpp -- thiscall method at VA 0x10e5c7c0: passes its argument to the method
// at VA 0x10e62180, then to the method at VA 0x10e5c630, both on the same object. The class and
// method names are invented.

class UnkType_10e5c7c0
{
public:
    void Unk_10e62180(int Value);
    void Unk_10e5c630(int Value);
    void Unk_10e5c7c0(int Value);
};

// UnkType_10e5c7c0::Unk_10e5c7c0
void UnkType_10e5c7c0::Unk_10e5c7c0(int Value)
{
    Unk_10e62180(Value);
    Unk_10e5c630(Value);
}
