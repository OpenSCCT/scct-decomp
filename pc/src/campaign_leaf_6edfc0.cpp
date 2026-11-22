// campaign_leaf_6edfc0.cpp -- thiscall method at VA 0x10fedfc0: passes the address of its 4-byte
// argument, the size 4 and the flag 1 to the method at VA 0x10fedc70 on the same object. The
// class, method and parameter names are invented.

class UnkType_10fedfc0
{
public:
    void Unk_10fedc70(void* Data, int Size, int Flag);
    void Unk_10fedfc0(int Value);
};

// UnkType_10fedfc0::Unk_10fedfc0
void UnkType_10fedfc0::Unk_10fedfc0(int Value)
{
    Unk_10fedc70(&Value, 4, 1);
}
