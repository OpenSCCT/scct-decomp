// campaign_leaf_55acd0.cpp -- thiscall method at VA 0x10e5acd0: passes its argument to the method
// at VA 0x10e50530, then to the method at VA 0x10e5abc0, both on the same object. The class and
// method names are invented.

class UnkType_10e5acd0
{
public:
    void Unk_10e50530(int Value);
    void Unk_10e5abc0(int Value);
    void Unk_10e5acd0(int Value);
};

// UnkType_10e5acd0::Unk_10e5acd0
void UnkType_10e5acd0::Unk_10e5acd0(int Value)
{
    Unk_10e50530(Value);
    Unk_10e5abc0(Value);
}
