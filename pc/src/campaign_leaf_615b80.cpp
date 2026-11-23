// campaign_leaf_615b80.cpp -- thiscall method at VA 0x10f15b80: calls the method at VA 0x10f14470
// with the constant 0x62, then returns whether the method at VA 0x10f144d0, called with 0x62 and
// its own two arguments, returns true. The class, method and parameter names are invented; the
// addresses and the constant are the binary's.

class UnkType_10f15b80
{
public:
    bool Unk_10f15b80(unsigned char* First, int Second);
    void Unk_10f14470(int Code);
    bool Unk_10f144d0(int Code, unsigned char* First, int Second);
};

// UnkType_10f15b80::Unk_10f15b80
bool UnkType_10f15b80::Unk_10f15b80(unsigned char* First, int Second)
{
    Unk_10f14470(0x62);
    return Unk_10f144d0(0x62, First, Second) ? true : false;
}
