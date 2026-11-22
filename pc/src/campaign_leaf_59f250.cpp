// campaign_leaf_59f250.cpp -- thiscall method at VA 0x10e9f250: passes its argument to the method at
// VA 0x10ea3ff0, then to the method at VA 0x10e9ed70, both on the same object. The class and method
// names are invented.

class UnkType_10e9f250
{
public:
    void Unk_10ea3ff0(int Value);
    void Unk_10e9ed70(int Value);
    void Unk_10e9f250(int Value);
};

// UnkType_10e9f250::Unk_10e9f250
void UnkType_10e9f250::Unk_10e9f250(int Value)
{
    Unk_10ea3ff0(Value);
    Unk_10e9ed70(Value);
}
