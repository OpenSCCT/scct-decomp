// campaign_leaf_4b90c0.cpp -- one function at file offset 0x4b90c0, preferred VA 0x10db90c0.
// The virtual destructor destroys the members at offsets 0x2c and 0x20 (destructor at 0x10d8edb0)
// and then runs the base destructor at 0x10dd38e0. The class and member names are invented; the
// offset and the bytes are the binary's.

class UnkType_10db90c0_Base
{
public:
    unsigned char unk_4[0x1c];

    virtual ~UnkType_10db90c0_Base();
};

class UnkType_10db90c0_Member
{
public:
    unsigned char unk_0[0xc];

    ~UnkType_10db90c0_Member();
};

class UnkType_10db90c0 : public UnkType_10db90c0_Base
{
public:
    UnkType_10db90c0_Member unk_20;
    UnkType_10db90c0_Member unk_2c;

    virtual ~UnkType_10db90c0();
};

// UnkType_10db90c0::~UnkType_10db90c0
UnkType_10db90c0::~UnkType_10db90c0()
{
}
