// campaign_leaf_47abd0.cpp -- destructor at VA 0x10d7abd0. It deletes the arrays of polymorphic
// objects at 0x10 and 0x14; the inline destructor of its base class then restores the base
// vtable. The class and member names are invented.

class UnkType_10d7abd0_Element
{
public:
    virtual ~UnkType_10d7abd0_Element();
};

class UnkType_10d7abd0_Base
{
public:
    virtual ~UnkType_10d7abd0_Base() {}
};

class UnkType_10d7abd0 : public UnkType_10d7abd0_Base
{
public:
    virtual ~UnkType_10d7abd0();

private:
    unsigned char unk_4[0xc];
    UnkType_10d7abd0_Element* unk_10;
    UnkType_10d7abd0_Element* unk_14;
};

// UnkType_10d7abd0::~UnkType_10d7abd0
UnkType_10d7abd0::~UnkType_10d7abd0()
{
    delete[] unk_10;
    delete[] unk_14;
}
