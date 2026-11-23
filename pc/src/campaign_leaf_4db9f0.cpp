// campaign_leaf_4db9f0.cpp -- one function at file offset 0x4db9f0, preferred VA 0x10ddb9f0.
// The destructor calls the method at 0x10ddacc0 and then the base destructor at 0x10ddac90. The
// class names are invented; the offset and the bytes are the binary's.

class UnkType_10ddb9f0_Base
{
public:
    virtual ~UnkType_10ddb9f0_Base();
};

class UnkType_10ddb9f0 : public UnkType_10ddb9f0_Base
{
public:
    virtual ~UnkType_10ddb9f0();

    void Unk_10ddacc0();
};

// UnkType_10ddb9f0::~UnkType_10ddb9f0
UnkType_10ddb9f0::~UnkType_10ddb9f0()
{
    Unk_10ddacc0();
}
