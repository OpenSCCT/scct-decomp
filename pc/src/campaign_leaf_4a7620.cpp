// campaign_leaf_4a7620.cpp -- one function at file offset 0x4a7620, preferred VA 0x10da7620.
// The virtual destructor destroys the member at offset 0x2c (destructor at 0x10dd6770) and the
// member at offset 8 (destructor at 0x10da7330) and then runs the base destructor at 0x10dd6b70.
// The class and member names are invented; the offset and the bytes are the binary's.

class UnkType_10da7620_Base
{
public:
    int unk_4;

    virtual ~UnkType_10da7620_Base();
};

class UnkType_10da7620_Member
{
public:
    unsigned char unk_0[0x24];

    ~UnkType_10da7620_Member();
};

class UnkType_10da7620_Member2
{
public:
    int unk_0;

    ~UnkType_10da7620_Member2();
};

class UnkType_10da7620 : public UnkType_10da7620_Base
{
public:
    UnkType_10da7620_Member unk_8;
    UnkType_10da7620_Member2 unk_2c;

    virtual ~UnkType_10da7620();
};

// UnkType_10da7620::~UnkType_10da7620
UnkType_10da7620::~UnkType_10da7620()
{
}
