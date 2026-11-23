// campaign_leaf_4bbbd0.cpp -- one function at file offset 0x4bbbd0, preferred VA 0x10dbbbd0.
// The virtual destructor destroys the member at offset 0x20 (destructor at 0x10d8edb0) and then
// runs the base destructor at 0x10dd38e0. The class and member names are invented; the offset and
// the bytes are the binary's.

class UnkType_10dbbbd0_Base
{
public:
    unsigned char unk_4[0x1c];

    virtual ~UnkType_10dbbbd0_Base();
};

class UnkType_10dbbbd0_Member
{
public:
    int unk_0;

    ~UnkType_10dbbbd0_Member();
};

class UnkType_10dbbbd0 : public UnkType_10dbbbd0_Base
{
public:
    UnkType_10dbbbd0_Member unk_20;

    virtual ~UnkType_10dbbbd0();
};

// UnkType_10dbbbd0::~UnkType_10dbbbd0
UnkType_10dbbbd0::~UnkType_10dbbbd0()
{
}
