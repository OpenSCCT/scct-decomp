// campaign_leaf_49dd10.cpp -- thiscall at VA 0x10d9dd10: calls the method at VA 0x10d9d700 on the
// same object with its argument, 1 and 1, and returns the object. All names are invented.

class UnkType_10d9dd10
{
public:
    void Unk_10d9d700(int Value, int Count, int Size);
    UnkType_10d9dd10& Unk_10d9dd10(int Value);
};

// UnkType_10d9dd10::Unk_10d9dd10
UnkType_10d9dd10& UnkType_10d9dd10::Unk_10d9dd10(int Value)
{
    Unk_10d9d700(Value, 1, 1);
    return *this;
}
