// campaign_leaf_4d32d0.cpp -- one function at file offset 0x4d32d0, preferred VA 0x10dd32d0.
// The virtual destructor destroys the member at offset 0x44 (destructor at 0x10de99f0) and then
// runs the base destructor at 0x10da2740. The class and member names are invented; the offset and
// the bytes are the binary's.

class UnkType_10dd32d0_Base
{
public:
    unsigned char unk_4[0x40];

    virtual ~UnkType_10dd32d0_Base();
};

class UnkType_10dd32d0_Member
{
public:
    int unk_0;

    ~UnkType_10dd32d0_Member();
};

class UnkType_10dd32d0 : public UnkType_10dd32d0_Base
{
public:
    UnkType_10dd32d0_Member unk_44;

    virtual ~UnkType_10dd32d0();
};

// UnkType_10dd32d0::~UnkType_10dd32d0
UnkType_10dd32d0::~UnkType_10dd32d0()
{
}
