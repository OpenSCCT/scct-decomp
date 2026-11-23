// campaign_leaf_615b50.cpp -- thiscall method at VA 0x10f15b50: calls the method at VA 0x10f14470
// with the constant 0x01, then returns whether the method at VA 0x10f144d0, called with 0x01 and
// its own two arguments, returns true. The class, method and parameter names are invented; the
// addresses and the constant are the binary's.

class UnkType_10f15b50
{
public:
    bool Unk_10f15b50(unsigned char* First, int Second);
    void Unk_10f14470(int Code);
    bool Unk_10f144d0(int Code, unsigned char* First, int Second);
};

// UnkType_10f15b50::Unk_10f15b50
bool UnkType_10f15b50::Unk_10f15b50(unsigned char* First, int Second)
{
    Unk_10f14470(0x01);
    return Unk_10f144d0(0x01, First, Second) ? true : false;
}
