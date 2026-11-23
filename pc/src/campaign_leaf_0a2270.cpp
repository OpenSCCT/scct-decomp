// campaign_leaf_0a2270.cpp -- virtual destructor at VA 0x109a2270 (vtable at VA 0x110c1d64): when
// bit 0x8000 of the 16-bit word at 0x04 is set, clears it and calls the method at VA 0x10dfc240
// with 0; then runs the empty inline destructor of its base class (vtable at VA 0x110c1d60). The
// class, member and method names are invented; the offsets and the addresses are the binary's.

class UnkType_109a2270_Base
{
public:
    virtual ~UnkType_109a2270_Base()
    {
    }
};

class UnkType_109a2270 : public UnkType_109a2270_Base
{
public:
    virtual ~UnkType_109a2270();
    void Unk_10dfc240(int Value);

private:
    unsigned short unk_04;
};

// UnkType_109a2270::~UnkType_109a2270
UnkType_109a2270::~UnkType_109a2270()
{
    if ( unk_04 & 0x8000 )
    {
        unk_04 &= 0x7fff;
        Unk_10dfc240(0);
    }
}
