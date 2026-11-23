// campaign_leaf_55f2f0.cpp -- thiscall method at VA 0x10e5f2f0: passes its argument to the method
// at VA 0x10e60640, then to the method at VA 0x10e5e7d0, both on the same object. The class and
// method names are invented.

class UnkType_10e5f2f0
{
public:
    void Unk_10e60640(int Value);
    void Unk_10e5e7d0(int Value);
    void Unk_10e5f2f0(int Value);
};

// UnkType_10e5f2f0::Unk_10e5f2f0
void UnkType_10e5f2f0::Unk_10e5f2f0(int Value)
{
    Unk_10e60640(Value);
    Unk_10e5e7d0(Value);
}
