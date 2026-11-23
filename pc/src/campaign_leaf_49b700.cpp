// campaign_leaf_49b700.cpp -- destructor at VA 0x10d9b700. It deletes the object at 0x34 through
// its virtual destructor, calls 0x10dc1a10, then destroys its members: the part at 0x8c
// (0x10d9d0c0), the list at 0x20 (whose buffer goes back to the allocator with tag 7), the part
// at 0xc (0x10d98ee0) and the lock at 0x8, before the base destructor at 0x10da4690. The class
// and member names are invented.

void* Unk_10d8b460();
void Unk_10d8b550(void* Heap, void* Block, int Tag);
void Unk_10dc1a10();

// guess: the inline that returns a block to the allocator at 0x10d8b460 with tag 7
inline void FreeBlock(void* Block)
{
    Unk_10d8b550(Unk_10d8b460(), Block, 7);
}

class UnkType_10d9b700_Lock
{
public:
    ~UnkType_10d9b700_Lock();

private:
    int unk_0;
};

class UnkType_10d9b700_Items
{
public:
    ~UnkType_10d9b700_Items()
    {
        Unk_10d7eb20();
        FreeBlock(unk_4);
        unk_4 = 0;
    }

    void Unk_10d7eb20();

private:
    int unk_0;
    void* unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_10d9b700_List
{
private:
    UnkType_10d9b700_Lock unk_0;
    UnkType_10d9b700_Items unk_4;
};

class UnkType_10d9b700_PartC
{
public:
    ~UnkType_10d9b700_PartC();

private:
    unsigned char unk_0[0x14];
};

class UnkType_10d9b700_Part8c
{
public:
    ~UnkType_10d9b700_Part8c();

private:
    int unk_0;
};

class UnkType_10d9b700_Owned
{
public:
    virtual ~UnkType_10d9b700_Owned();
};

class UnkType_10d9b700_Base
{
public:
    virtual ~UnkType_10d9b700_Base();

private:
    int unk_4;
};

class UnkType_10d9b700 : public UnkType_10d9b700_Base
{
public:
    ~UnkType_10d9b700();

private:
    UnkType_10d9b700_Lock unk_8;
    UnkType_10d9b700_PartC unk_c;
    UnkType_10d9b700_List unk_20;
    UnkType_10d9b700_Owned* unk_34;
    unsigned char unk_38[0x54];
    UnkType_10d9b700_Part8c unk_8c;
};

// UnkType_10d9b700::~UnkType_10d9b700
UnkType_10d9b700::~UnkType_10d9b700()
{
    if ( unk_34 != 0 )
    {
        delete unk_34;
    }
    unk_34 = 0;
    Unk_10dc1a10();
}
