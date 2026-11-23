// campaign_leaf_08a4d0.cpp -- destructor at VA 0x1098a4d0 of a class whose vtable is at VA
// 0x110c1d64: when bit 15 of the 16-bit value at 0x04 is set, clears it and passes 0 to the method
// at VA 0x10dfc240; then runs the inline destructor of the base class whose vtable is at VA
// 0x110c1d60. The class, member and method names are invented; the offsets, the constants and the
// addresses are the binary's.

class UnkType_110c1d60
{
public:
    virtual ~UnkType_110c1d60()
    {
    }

    void Unk_10dfc240(int Value);

protected:
    unsigned short unk_04;
};

class UnkType_1098a4d0 : public UnkType_110c1d60
{
public:
    virtual ~UnkType_1098a4d0();
};

// UnkType_1098a4d0::~UnkType_1098a4d0
UnkType_1098a4d0::~UnkType_1098a4d0()
{
    if ( unk_04 & 0x8000 )
    {
        unk_04 &= 0x7fff;
        Unk_10dfc240(0);
    }
}
