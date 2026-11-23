// campaign_leaf_615a70.cpp -- thiscall method at VA 0x10f15a70: calls the method at VA 0x10f14470
// with the constant 0x66, then returns whether the method at VA 0x10f144d0, called with 0x66 and
// its own two arguments, returns true. The class, method and parameter names are invented; the
// addresses and the constant are the binary's.

class UnkType_10f15a70
{
public:
    bool Unk_10f15a70(unsigned char* First, int Second);
    void Unk_10f14470(int Code);
    bool Unk_10f144d0(int Code, unsigned char* First, int Second);
};

// UnkType_10f15a70::Unk_10f15a70
bool UnkType_10f15a70::Unk_10f15a70(unsigned char* First, int Second)
{
    Unk_10f14470(0x66);
    return Unk_10f144d0(0x66, First, Second) ? true : false;
}
