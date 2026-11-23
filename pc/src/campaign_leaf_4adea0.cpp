// campaign_leaf_4adea0.cpp -- one function at file offset 0x4adea0, preferred VA 0x10dadea0.
// The virtual destructor clears the int at offset 0x14 when it is set, destroys the member at
// offset 8 with the destructor at 0x10d7cf40 and runs the base destructor at 0x10da4690. The class
// and member names are invented; the offset and the bytes are the binary's.

class UnkType_10dadea0_Base
{
public:
    int unk_4;

    virtual ~UnkType_10dadea0_Base();
};

class UnkType_10dadea0_Member
{
public:
    unsigned char unk_0[0xc];

    ~UnkType_10dadea0_Member();
};

class UnkType_10dadea0 : public UnkType_10dadea0_Base
{
public:
    UnkType_10dadea0_Member unk_8;
    int unk_14;

    virtual ~UnkType_10dadea0();
};

// UnkType_10dadea0::~UnkType_10dadea0
UnkType_10dadea0::~UnkType_10dadea0()
{
    if ( unk_14 != 0 )
    {
        unk_14 = 0;
    }
}
