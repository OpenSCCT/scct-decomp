// campaign_leaf_4cd970.cpp -- one function at file offset 0x4cd970, preferred VA 0x10dcd970.
// The destructor destroys the members at offsets 0x4c and 0x14 (destructor at 0x10ddd4f0) and the
// member at offset 0x10 (destructor at 0x10d8b2e0); the empty inline destructor of the base, whose
// vtable is at 0x11144480, then installs the base vtable. The class and member names are invented;
// the offset and the bytes are the binary's.

class UnkType_11144480
{
public:
    unsigned char unk_4[0xc];

    virtual ~UnkType_11144480()
    {
    }
};

class UnkType_10dcd970_Member
{
public:
    int unk_0;

    ~UnkType_10dcd970_Member();
};

class UnkType_10dcd970_Member2
{
public:
    unsigned char unk_0[0x38];

    ~UnkType_10dcd970_Member2();
};

class UnkType_10dcd970 : public UnkType_11144480
{
public:
    UnkType_10dcd970_Member unk_10;
    UnkType_10dcd970_Member2 unk_14;
    UnkType_10dcd970_Member2 unk_4c;

    virtual ~UnkType_10dcd970();
};

// UnkType_10dcd970::~UnkType_10dcd970
UnkType_10dcd970::~UnkType_10dcd970()
{
}
