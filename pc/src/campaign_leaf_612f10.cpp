// campaign_leaf_612f10.cpp -- thiscall method at VA 0x10f12f10: calls the method at VA 0x10f11610
// with the constant 0x51, then returns whether the method at VA 0x10f11670, called with 0x51 and
// its own two arguments, returns true. The class, method and parameter names are invented; the
// addresses and the constant are the binary's.

class UnkType_10f12f10
{
public:
    bool Unk_10f12f10(unsigned char* First, int Second);
    void Unk_10f11610(int Code);
    bool Unk_10f11670(int Code, unsigned char* First, int Second);
};

// UnkType_10f12f10::Unk_10f12f10
bool UnkType_10f12f10::Unk_10f12f10(unsigned char* First, int Second)
{
    Unk_10f11610(0x51);
    return Unk_10f11670(0x51, First, Second) ? true : false;
}
