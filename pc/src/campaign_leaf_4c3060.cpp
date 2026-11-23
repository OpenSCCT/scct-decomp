// campaign_leaf_4c3060.cpp -- one function at file offset 0x4c3060, preferred VA 0x10dc3060.
// The virtual destructor passes the object held by the first node of the list at offset 0x18 to
// the method at 0x10dc2f80 until the list is empty; the inline destructor of the list then calls
// its method at 0x10dc28b0 and frees its head node. The base destructor at 0x10dadea0 runs last.
// The class, function, method and member names are invented; the offset and the bytes are the
// binary's.

void* Unk_10d8b460(void* Block, int Kind);
void Unk_10d8b550(void* Block);

struct UnkType_10dc3060_Node
{
    UnkType_10dc3060_Node* unk_0;
    UnkType_10dc3060_Node* unk_4;
    void* unk_8;
};

class UnkType_10dc28b0
{
public:
    int unk_0;
    UnkType_10dc3060_Node* unk_4;
    int unk_8;

    ~UnkType_10dc28b0()
    {
        Unk_10dc28b0();
        Unk_10d8b550(Unk_10d8b460(unk_4, 7));
        unk_4 = 0;
    }

    void Unk_10dc28b0();
};

class UnkType_10dc3060_Base
{
public:
    unsigned char unk_4[0x14];

    virtual ~UnkType_10dc3060_Base();
};

class UnkType_10dc3060 : public UnkType_10dc3060_Base
{
public:
    UnkType_10dc28b0 unk_18;

    virtual ~UnkType_10dc3060();

    void Unk_10dc2f80(void* Item);
};

// UnkType_10dc3060::~UnkType_10dc3060
UnkType_10dc3060::~UnkType_10dc3060()
{
    while ( unk_18.unk_8 != 0 )
    {
        Unk_10dc2f80(unk_18.unk_4->unk_0->unk_8);
    }
}
