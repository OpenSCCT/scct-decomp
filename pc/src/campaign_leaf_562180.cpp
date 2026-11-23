// campaign_leaf_562180.cpp -- thiscall method at VA 0x10e62180: passes its argument to the method
// at VA 0x10e6d000, then to the method at VA 0x10e61d10, both on the same object. The class and
// method names are invented.

class UnkType_10e62180
{
public:
    void Unk_10e6d000(int Value);
    void Unk_10e61d10(int Value);
    void Unk_10e62180(int Value);
};

// UnkType_10e62180::Unk_10e62180
void UnkType_10e62180::Unk_10e62180(int Value)
{
    Unk_10e6d000(Value);
    Unk_10e61d10(Value);
}
