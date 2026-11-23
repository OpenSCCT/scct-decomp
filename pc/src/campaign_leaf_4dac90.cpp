// campaign_leaf_4dac90.cpp -- one function at file offset 0x4dac90, preferred VA 0x10ddac90.
// The virtual destructor destroys the member at offset 0x30 (destructor at 0x10dcd690) and the
// member at offset 8 (destructor at 0x10dadea0) and then runs the base destructor at 0x10de9b80.
// The class and member names are invented; the offset and the bytes are the binary's.

class UnkType_10ddac90_Base
{
public:
    int unk_4;

    virtual ~UnkType_10ddac90_Base();
};

class UnkType_10ddac90_Member
{
public:
    unsigned char unk_0[0x28];

    ~UnkType_10ddac90_Member();
};

class UnkType_10ddac90_Member2
{
public:
    int unk_0;

    ~UnkType_10ddac90_Member2();
};

class UnkType_10ddac90 : public UnkType_10ddac90_Base
{
public:
    UnkType_10ddac90_Member unk_8;
    UnkType_10ddac90_Member2 unk_30;

    virtual ~UnkType_10ddac90();
};

// UnkType_10ddac90::~UnkType_10ddac90
UnkType_10ddac90::~UnkType_10ddac90()
{
}
