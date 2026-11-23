// campaign_leaf_55d680.cpp -- thiscall method at VA 0x10e5d680: passes its argument to the method
// at VA 0x10e6d000, then to the method at VA 0x10e5d280, both on the same object. The class and
// method names are invented.

class UnkType_10e5d680
{
public:
    void Unk_10e6d000(int Value);
    void Unk_10e5d280(int Value);
    void Unk_10e5d680(int Value);
};

// UnkType_10e5d680::Unk_10e5d680
void UnkType_10e5d680::Unk_10e5d680(int Value)
{
    Unk_10e6d000(Value);
    Unk_10e5d280(Value);
}
