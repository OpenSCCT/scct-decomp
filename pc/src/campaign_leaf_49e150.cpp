// campaign_leaf_49e150.cpp -- thiscall at VA 0x10d9e150: calls the method at VA 0x10d9dc10 on the
// same object with its argument and 1, and returns the object. All names are invented.

class UnkType_10d9e150
{
public:
    void Unk_10d9dc10(int Value, int Count);
    UnkType_10d9e150& Unk_10d9e150(int Value);
};

// UnkType_10d9e150::Unk_10d9e150
UnkType_10d9e150& UnkType_10d9e150::Unk_10d9e150(int Value)
{
    Unk_10d9dc10(Value, 1);
    return *this;
}
