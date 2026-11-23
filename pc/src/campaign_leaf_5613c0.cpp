// campaign_leaf_5613c0.cpp -- thiscall method at VA 0x10e613c0: passes its argument to the method
// at VA 0x10e6d000, then to the method at VA 0x10e61190, both on the same object. The class and
// method names are invented.

class UnkType_10e613c0
{
public:
    void Unk_10e6d000(int Value);
    void Unk_10e61190(int Value);
    void Unk_10e613c0(int Value);
};

// UnkType_10e613c0::Unk_10e613c0
void UnkType_10e613c0::Unk_10e613c0(int Value)
{
    Unk_10e6d000(Value);
    Unk_10e61190(Value);
}
