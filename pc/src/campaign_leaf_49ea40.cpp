// campaign_leaf_49ea40.cpp -- thiscall at VA 0x10d9ea40: passes the address of its eight-byte
// argument and 1 to the method at VA 0x10d9e6e0 on the same object, and returns the object. All
// names are invented.

class UnkType_10d9ea40
{
public:
    void Unk_10d9e6e0(const __int64* Data, int Count);
    UnkType_10d9ea40& Unk_10d9ea40(__int64 Value);
};

// UnkType_10d9ea40::Unk_10d9ea40
UnkType_10d9ea40& UnkType_10d9ea40::Unk_10d9ea40(__int64 Value)
{
    Unk_10d9e6e0(&Value, 1);
    return *this;
}
