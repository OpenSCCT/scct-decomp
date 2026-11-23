// campaign_leaf_6fe0a0.cpp -- destructor at VA 0x10ffe0a0 of a class whose vtable is at VA 0x111704c0:
// decrements the 16-bit reference count at 0x06 of the object at 0x0c and deletes it through its
// virtual destructor when the count reaches zero. The inlined base destructor (vtable at VA
// 0x110c1d64) then clears the top bit of the 16-bit value at 0x04, when set, and calls the method
// at VA 0x10dfc240 with 0; the root class (vtable at VA 0x110c1d60) has an empty destructor. The
// class, method and member names are invented; the offsets and addresses are the binary's.

class UnkType_110c1d60_6fe0a0
{
public:
    virtual ~UnkType_110c1d60_6fe0a0()
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

class UnkType_10ffe0a0_Base : public UnkType_110c1d60_6fe0a0
{
public:
    virtual ~UnkType_10ffe0a0_Base()
    {
        if ( unk_4 & 0x8000 )
        {
            unk_4 &= 0x7fff;
            Unk_10dfc240(0);
        }
    }

    void Unk_10dfc240(int Value);
};

class UnkType_10ffe0a0 : public UnkType_10ffe0a0_Base
{
public:
    virtual ~UnkType_10ffe0a0();

private:
    int unk_8;
    UnkType_110c1d60_6fe0a0* unk_c;
};

// UnkType_10ffe0a0::~UnkType_10ffe0a0
UnkType_10ffe0a0::~UnkType_10ffe0a0()
{
    unk_c->Release();
}
