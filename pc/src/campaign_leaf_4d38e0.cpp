// campaign_leaf_4d38e0.cpp -- one function at file offset 0x4d38e0, preferred VA 0x10dd38e0.
// The virtual destructor destroys the member at offset 0x10 (destructor at 0x10d8edb0); the empty
// inline destructor of the base, whose vtable is at 0x1113e7bc, then installs the base vtable. The
// class and member names are invented; the offset and the bytes are the binary's.

class UnkType_1113e7bc
{
public:
    unsigned char unk_4[0xc];

    virtual ~UnkType_1113e7bc()
    {
    }
};

class UnkType_10dd38e0_Member
{
public:
    int unk_0;

    ~UnkType_10dd38e0_Member();
};

class UnkType_10dd38e0 : public UnkType_1113e7bc
{
public:
    UnkType_10dd38e0_Member unk_10;

    virtual ~UnkType_10dd38e0();
};

// UnkType_10dd38e0::~UnkType_10dd38e0
UnkType_10dd38e0::~UnkType_10dd38e0()
{
}
