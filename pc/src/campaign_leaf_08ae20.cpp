// campaign_leaf_08ae20.cpp -- destructor at VA 0x1098ae20 of a class whose vtable is at VA 0x110c1dac:
// deletes the object at 0x08 through its virtual destructor (slot 0) when it is set and clears
// the pointer, then runs the inline destructor of the base class whose vtable is at VA
// 0x110c1d60. The class and member names are invented; the offsets and the addresses are the
// binary's.

class UnkType_1098ae20_Object
{
public:
    virtual ~UnkType_1098ae20_Object();
};

class UnkType_110c1d60
{
public:
    virtual ~UnkType_110c1d60()
    {
    }

private:
    int unk_04;
};

class UnkType_1098ae20 : public UnkType_110c1d60
{
public:
    virtual ~UnkType_1098ae20();

private:
    UnkType_1098ae20_Object* unk_08;
};

// UnkType_1098ae20::~UnkType_1098ae20
UnkType_1098ae20::~UnkType_1098ae20()
{
    delete unk_08;
    unk_08 = 0;
}
