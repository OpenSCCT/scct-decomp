// campaign_leaf_08adc0.cpp -- destructor at VA 0x1098adc0 of a class whose vtable is at VA 0x110c1d90:
// deletes the object at 0x08 through its virtual destructor (slot 0) when it is set and clears
// the pointer, then runs the inline destructor of the base class whose vtable is at VA
// 0x110c1d60. The class and member names are invented; the offsets and the addresses are the
// binary's.

class UnkType_1098adc0_Object
{
public:
    virtual ~UnkType_1098adc0_Object();
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

class UnkType_1098adc0 : public UnkType_110c1d60
{
public:
    virtual ~UnkType_1098adc0();

private:
    UnkType_1098adc0_Object* unk_08;
};

// UnkType_1098adc0::~UnkType_1098adc0
UnkType_1098adc0::~UnkType_1098adc0()
{
    delete unk_08;
    unk_08 = 0;
}
