// campaign_leaf_55f970.cpp -- thiscall method at VA 0x10e5f970: passes its argument to the method at
// VA 0x10e6d000, then to the method at VA 0x10e5f450, both on the same object. The class and method
// names are invented.

class UnkType_10e5f970
{
public:
    void Unk_10e6d000(int Value);
    void Unk_10e5f450(int Value);
    void Unk_10e5f970(int Value);
};

// UnkType_10e5f970::Unk_10e5f970
void UnkType_10e5f970::Unk_10e5f970(int Value)
{
    Unk_10e6d000(Value);
    Unk_10e5f450(Value);
}
