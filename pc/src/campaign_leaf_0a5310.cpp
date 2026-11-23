// campaign_leaf_0a5310.cpp -- virtual destructor at VA 0x109a5310 (vtable at VA 0x110cb9b8): calls
// the method at VA 0x10cd7a30; then the inline destructor of base class 1 (vtable at VA 0x110bf398)
// calls the same method; then the inline destructor of base class 2 (vtable at VA 0x110bf2a8) calls
// the same method; it ends in the outermost base destructor at VA 0x10cdc460. The class, member and
// method names are invented; the offsets and the addresses are the binary's.

class UnkType_109a5310_Base
{
public:
    virtual ~UnkType_109a5310_Base();
    void Unk_10cd7a30();
};

class UnkType_109a5310_Level2 : public UnkType_109a5310_Base
{
public:
    virtual ~UnkType_109a5310_Level2()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109a5310_Level1 : public UnkType_109a5310_Level2
{
public:
    virtual ~UnkType_109a5310_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109a5310 : public UnkType_109a5310_Level1
{
public:
    virtual ~UnkType_109a5310();
};

// UnkType_109a5310::~UnkType_109a5310
UnkType_109a5310::~UnkType_109a5310()
{
    Unk_10cd7a30();
}
