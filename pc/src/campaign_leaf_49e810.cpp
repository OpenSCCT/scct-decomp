// campaign_leaf_49e810.cpp -- thiscall at VA 0x10d9e810: passes the address of its unsigned short
// argument, a count of 1 and a size of 2 to the method at VA 0x10d9e290 on the same object,
// and returns the object. All names are invented.

class UnkType_10d9e810
{
public:
    void Unk_10d9e290(const void* Data, int Count, int Size);
    UnkType_10d9e810& Unk_10d9e810(unsigned short Value);
};

// UnkType_10d9e810::Unk_10d9e810
UnkType_10d9e810& UnkType_10d9e810::Unk_10d9e810(unsigned short Value)
{
    Unk_10d9e290(&Value, 1, 2);
    return *this;
}
