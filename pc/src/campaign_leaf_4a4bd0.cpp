// campaign_leaf_4a4bd0.cpp -- one function at file offset 0x4a4bd0, preferred VA 0x10da4bd0.
// The virtual destructor destroys the member at offset 0x44 (destructor at 0x10dd52d0); the empty
// inline destructor of the middle class, whose vtable is at 0x1113e7d0, then installs that vtable
// and runs the base destructor at 0x10da2740. The class and member names are invented; the offset
// and the bytes are the binary's.

class UnkType_10da4bd0_Base
{
public:
    unsigned char unk_4[0x40];

    virtual ~UnkType_10da4bd0_Base();
};

class UnkType_1113e7d0 : public UnkType_10da4bd0_Base
{
public:
    virtual ~UnkType_1113e7d0()
    {
    }
};

class UnkType_10da4bd0_Member
{
public:
    int unk_0;

    ~UnkType_10da4bd0_Member();
};

class UnkType_10da4bd0 : public UnkType_1113e7d0
{
public:
    UnkType_10da4bd0_Member unk_44;

    virtual ~UnkType_10da4bd0();
};

// UnkType_10da4bd0::~UnkType_10da4bd0
UnkType_10da4bd0::~UnkType_10da4bd0()
{
}
