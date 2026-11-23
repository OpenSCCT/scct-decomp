// campaign_leaf_612630.cpp -- thiscall method at VA 0x10f12630: calls the method at VA 0x10f11610
// with the constant 0x4e, then returns whether the method at VA 0x10f11670, called with 0x4e and
// its own two arguments, returns true. The class, method and parameter names are invented; the
// addresses and the constant are the binary's.

class UnkType_10f12630
{
public:
    bool Unk_10f12630(unsigned char* First, int Second);
    void Unk_10f11610(int Code);
    bool Unk_10f11670(int Code, unsigned char* First, int Second);
};

// UnkType_10f12630::Unk_10f12630
bool UnkType_10f12630::Unk_10f12630(unsigned char* First, int Second)
{
    Unk_10f11610(0x4e);
    return Unk_10f11670(0x4e, First, Second) ? true : false;
}
