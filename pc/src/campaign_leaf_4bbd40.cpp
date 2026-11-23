// campaign_leaf_4bbd40.cpp -- one function at file offset 0x4bbd40, preferred VA 0x10dbbd40.
// The destructor destroys the members at offsets 0x40, 0x2c and 0x18 (destructor at 0x10d9a410)
// and then the member at offset 4 (destructor at 0x10d98ee0). The class and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_10dbbd40_Member
{
public:
    unsigned char unk_0[0x14];

    ~UnkType_10dbbd40_Member();
};

class UnkType_10dbbd40_Member2
{
public:
    unsigned char unk_0[0x14];

    ~UnkType_10dbbd40_Member2();
};

class UnkType_10dbbd40
{
public:
    int unk_0;
    UnkType_10dbbd40_Member unk_4;
    UnkType_10dbbd40_Member2 unk_18;
    UnkType_10dbbd40_Member2 unk_2c;
    UnkType_10dbbd40_Member2 unk_40;

    ~UnkType_10dbbd40();
};

// UnkType_10dbbd40::~UnkType_10dbbd40
UnkType_10dbbd40::~UnkType_10dbbd40()
{
}
