// campaign_leaf_6edbf0.cpp -- destructor at VA 0x10fedbf0 of a class whose vtable is at VA 0x1116fc80: decrements
// the 16-bit reference count at 0x06 of the object at 0x08 and deletes that object through its
// virtual destructor when the count reaches zero; the base class (vtable at VA 0x110c1d60) has an
// empty destructor. The class and member names are invented; the offsets and addresses are the
// binary's.

class UnkType_110c1d60_6edbf0
{
public:
    virtual ~UnkType_110c1d60_6edbf0()
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

class UnkType_10fedbf0 : public UnkType_110c1d60_6edbf0
{
public:
    virtual ~UnkType_10fedbf0();

private:
    UnkType_110c1d60_6edbf0* unk_8;
};

// UnkType_10fedbf0::~UnkType_10fedbf0
UnkType_10fedbf0::~UnkType_10fedbf0()
{
    unk_8->Release();
}
