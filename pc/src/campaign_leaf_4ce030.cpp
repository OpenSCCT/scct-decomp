// campaign_leaf_4ce030.cpp -- one function at file offset 0x4ce030, preferred VA 0x10dce030.
// The virtual destructor passes the result of the function at 0x10d8b460, called with the pointer
// at offset 8 and 1, to the function at 0x10d8b550 and then runs the base destructor at
// 0x10da4690. The class, function and member names are invented; the offset and the bytes are the
// binary's.

void* Unk_10d8b460(void* Block, int Kind);
void Unk_10d8b550(void* Block);

class UnkType_10dce030_Base
{
public:
    int unk_4;

    virtual ~UnkType_10dce030_Base();
};

class UnkType_10dce030 : public UnkType_10dce030_Base
{
public:
    void* unk_8;

    virtual ~UnkType_10dce030();
};

// UnkType_10dce030::~UnkType_10dce030
UnkType_10dce030::~UnkType_10dce030()
{
    Unk_10d8b550(Unk_10d8b460(unk_8, 1));
}
