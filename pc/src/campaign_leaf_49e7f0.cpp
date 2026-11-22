// campaign_leaf_49e7f0.cpp -- thiscall at VA 0x10d9e7f0: passes the address of its unsigned char
// argument, a count of 1 and a size of 1 to the method at VA 0x10d9e290 on the same object,
// and returns the object. All names are invented.

class UnkType_10d9e7f0
{
public:
    void Unk_10d9e290(const void* Data, int Count, int Size);
    UnkType_10d9e7f0& Unk_10d9e7f0(unsigned char Value);
};

// UnkType_10d9e7f0::Unk_10d9e7f0
UnkType_10d9e7f0& UnkType_10d9e7f0::Unk_10d9e7f0(unsigned char Value)
{
    Unk_10d9e290(&Value, 1, 1);
    return *this;
}
