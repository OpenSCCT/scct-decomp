// campaign_leaf_4c13b0.cpp -- one function at file offset 0x4c13b0, preferred VA 0x10dc13b0.
// The virtual destructor destroys the member at offset 0x24 (destructor at 0x10ddd4f0) and the
// member at offset 0x10 (destructor at 0x10d7cf40) and then runs the base destructor at 0x10da4690.
// The class and member names are invented; the offset and the bytes are the binary's.

class UnkType_10dc13b0_Base
{
public:
    unsigned char unk_4[0xc];

    virtual ~UnkType_10dc13b0_Base();
};

class UnkType_10dc13b0_Member
{
public:
    unsigned char unk_0[0x14];

    ~UnkType_10dc13b0_Member();
};

class UnkType_10dc13b0_Member2
{
public:
    int unk_0;

    ~UnkType_10dc13b0_Member2();
};

class UnkType_10dc13b0 : public UnkType_10dc13b0_Base
{
public:
    UnkType_10dc13b0_Member unk_10;
    UnkType_10dc13b0_Member2 unk_24;

    virtual ~UnkType_10dc13b0();
};

// UnkType_10dc13b0::~UnkType_10dc13b0
UnkType_10dc13b0::~UnkType_10dc13b0()
{
}
