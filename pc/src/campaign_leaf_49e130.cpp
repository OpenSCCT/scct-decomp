// campaign_leaf_49e130.cpp -- thiscall at VA 0x10d9e130: calls the method at VA 0x10d9db40 on the
// same object with its argument and 1, and returns the object. All names are invented.

class UnkType_10d9e130
{
public:
    void Unk_10d9db40(int Value, int Count);
    UnkType_10d9e130& Unk_10d9e130(int Value);
};

// UnkType_10d9e130::Unk_10d9e130
UnkType_10d9e130& UnkType_10d9e130::Unk_10d9e130(int Value)
{
    Unk_10d9db40(Value, 1);
    return *this;
}
