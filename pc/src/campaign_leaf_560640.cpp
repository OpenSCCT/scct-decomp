// campaign_leaf_560640.cpp -- thiscall method at VA 0x10e60640: passes its argument to the method at
// VA 0x10e6d000, then to the method at VA 0x10e60050, both on the same object. The class and method
// names are invented.

class UnkType_10e60640
{
public:
    void Unk_10e6d000(int Value);
    void Unk_10e60050(int Value);
    void Unk_10e60640(int Value);
};

// UnkType_10e60640::Unk_10e60640
void UnkType_10e60640::Unk_10e60640(int Value)
{
    Unk_10e6d000(Value);
    Unk_10e60050(Value);
}
