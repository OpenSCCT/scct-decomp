// campaign_leaf_6eedf0.cpp -- destructor at VA 0x10feedf0 of a class whose vtable is at VA 0x1116fdd8:
// decrements the 16-bit reference counts at 0x06 of the objects at 0x08 and 0x0c and deletes each
// through its virtual destructor when its count reaches zero; the base class (vtable at VA
// 0x110c1d60) has an empty destructor. The class and member names are invented; the offsets and
// addresses are the binary's.

class UnkType_110c1d60_6eedf0
{
public:
    virtual ~UnkType_110c1d60_6eedf0()
    {
    }

    // guess: drops one reference and deletes the object when none remain.
    void Release()
    {
        if ( --unk_6 == 0 )
        {
            delete this;
        }
    }

    unsigned short unk_4;
    unsigned short unk_6;
};

class UnkType_10feedf0 : public UnkType_110c1d60_6eedf0
{
public:
    virtual ~UnkType_10feedf0();

private:
    UnkType_110c1d60_6eedf0* unk_8;
    UnkType_110c1d60_6eedf0* unk_c;
};

// UnkType_10feedf0::~UnkType_10feedf0
UnkType_10feedf0::~UnkType_10feedf0()
{
    unk_8->Release();
    unk_c->Release();
}
