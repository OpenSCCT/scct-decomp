// campaign_leaf_6084c0.cpp -- thiscall method at VA 0x10f084c0: calls the method at VA 0x10f049d0
// with the constant 0x15, then returns whether the method at VA 0x10f04a10, called with 0x15 and
// its own two arguments, returns true. The class, method and parameter names are invented; the
// addresses and the constant are the binary's.

class UnkType_10f084c0
{
public:
    bool Unk_10f084c0(unsigned char* First, int Second);
    void Unk_10f049d0(int Code);
    bool Unk_10f04a10(int Code, unsigned char* First, int Second);
};

// UnkType_10f084c0::Unk_10f084c0
bool UnkType_10f084c0::Unk_10f084c0(unsigned char* First, int Second)
{
    Unk_10f049d0(0x15);
    return Unk_10f04a10(0x15, First, Second) ? true : false;
}
