// campaign_leaf_4b17d0.cpp -- one function at file offset 0x4b17d0, preferred VA 0x10db17d0.
// The virtual destructor destroys the member at offset 0x10 (destructor at 0x10d8edb0) and then
// runs the base destructor at 0x10dae3c0. The class and member names are invented; the offset and
// the bytes are the binary's.

class UnkType_10db17d0_Base
{
public:
    unsigned char unk_4[0xc];

    virtual ~UnkType_10db17d0_Base();
};

class UnkType_10db17d0_Member
{
public:
    int unk_0;

    ~UnkType_10db17d0_Member();
};

class UnkType_10db17d0 : public UnkType_10db17d0_Base
{
public:
    UnkType_10db17d0_Member unk_10;

    virtual ~UnkType_10db17d0();
};

// UnkType_10db17d0::~UnkType_10db17d0
UnkType_10db17d0::~UnkType_10db17d0()
{
}
