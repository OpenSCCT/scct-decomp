// campaign_leaf_4da550.cpp -- one function at file offset 0x4da550, preferred VA 0x10dda550.
// The virtual destructor destroys the member at offset 0x20 (destructor at 0x10d9c6d0) and then
// the member at offset 8 (destructor at 0x10d8edb0). The class and member names are invented; the
// offset and the bytes are the binary's.

class UnkType_10dda550_Member
{
public:
    unsigned char unk_0[0x18];

    ~UnkType_10dda550_Member();
};

class UnkType_10dda550_Member2
{
public:
    int unk_0;

    ~UnkType_10dda550_Member2();
};

class UnkType_10dda550
{
public:
    int unk_4;
    UnkType_10dda550_Member unk_8;
    UnkType_10dda550_Member2 unk_20;

    virtual ~UnkType_10dda550();
};

// UnkType_10dda550::~UnkType_10dda550
UnkType_10dda550::~UnkType_10dda550()
{
}
