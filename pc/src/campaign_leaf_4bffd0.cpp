// campaign_leaf_4bffd0.cpp -- one function at file offset 0x4bffd0, preferred VA 0x10dbffd0.
// The virtual destructor frees the block at offset 8, if any, with the function at 0x10d87b90 and
// then destroys the member at offset 4 with the destructor at 0x10d7cf40. The class, function and
// member names are invented; the offset and the bytes are the binary's.

void Unk_10d87b90(void* Block);

class UnkType_10dbffd0_Member
{
public:
    int unk_0;

    ~UnkType_10dbffd0_Member();
};

class UnkType_10dbffd0
{
public:
    UnkType_10dbffd0_Member unk_4;
    void* unk_8;

    virtual ~UnkType_10dbffd0();
};

// UnkType_10dbffd0::~UnkType_10dbffd0
UnkType_10dbffd0::~UnkType_10dbffd0()
{
    if ( unk_8 != 0 )
    {
        Unk_10d87b90(unk_8);
    }
}
