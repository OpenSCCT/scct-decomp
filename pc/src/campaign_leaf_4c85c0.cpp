// campaign_leaf_4c85c0.cpp -- one function at file offset 0x4c85c0, preferred VA 0x10dc85c0.
// The virtual destructor deletes the object at offset 0x2c through its virtual destructor and then
// runs the base destructor at 0x10dc81d0. The class and member names are invented; the offset and
// the bytes are the binary's.

class UnkType_10dc85c0_Item
{
public:
    virtual ~UnkType_10dc85c0_Item();
};

class UnkType_10dc85c0_Base
{
public:
    unsigned char unk_4[0x28];

    virtual ~UnkType_10dc85c0_Base();
};

class UnkType_10dc85c0 : public UnkType_10dc85c0_Base
{
public:
    UnkType_10dc85c0_Item* unk_2c;

    virtual ~UnkType_10dc85c0();
};

// UnkType_10dc85c0::~UnkType_10dc85c0
UnkType_10dc85c0::~UnkType_10dc85c0()
{
    delete unk_2c;
}
