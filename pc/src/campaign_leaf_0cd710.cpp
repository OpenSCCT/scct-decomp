// campaign_leaf_0cd710.cpp -- virtual destructor at VA 0x109cd710 (vtable at VA 0x110cf6c8): calls
// the method at VA 0x10cd7a30; then the inline destructor of base class 1 (vtable at VA 0x110cf588)
// calls it; then the inline destructor of base class 2 (vtable at VA 0x110c0b98) calls it; it ends
// in the outermost base destructor at VA 0x10cdc460. The class, member and method names are
// invented; the offsets and the addresses are the binary's.

class UnkType_109cd710_Base
{
public:
    virtual ~UnkType_109cd710_Base();
    void Unk_10cd7a30();
};

class UnkType_109cd710_Level2 : public UnkType_109cd710_Base
{
public:
    virtual ~UnkType_109cd710_Level2()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109cd710_Level1 : public UnkType_109cd710_Level2
{
public:
    virtual ~UnkType_109cd710_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109cd710 : public UnkType_109cd710_Level1
{
public:
    virtual ~UnkType_109cd710();
};

// UnkType_109cd710::~UnkType_109cd710
UnkType_109cd710::~UnkType_109cd710()
{
    Unk_10cd7a30();
}
