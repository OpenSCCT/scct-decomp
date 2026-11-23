// campaign_leaf_4bd4e0.cpp -- one function at file offset 0x4bd4e0, preferred VA 0x10dbd4e0.
// The virtual destructor destroys the member at offset 0x20 (destructor at 0x10d8edb0) and then
// runs the base destructor at 0x10dd38e0. The class and member names are invented; the offset and
// the bytes are the binary's.

class UnkType_10dbd4e0_Base
{
public:
    unsigned char unk_4[0x1c];

    virtual ~UnkType_10dbd4e0_Base();
};

class UnkType_10dbd4e0_Member
{
public:
    int unk_0;

    ~UnkType_10dbd4e0_Member();
};

class UnkType_10dbd4e0 : public UnkType_10dbd4e0_Base
{
public:
    UnkType_10dbd4e0_Member unk_20;

    virtual ~UnkType_10dbd4e0();
};

// UnkType_10dbd4e0::~UnkType_10dbd4e0
UnkType_10dbd4e0::~UnkType_10dbd4e0()
{
}
