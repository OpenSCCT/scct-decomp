// campaign_leaf_0cd020.cpp -- virtual destructor at VA 0x109cd020 (vtable at VA 0x110cf500): calls
// the method at VA 0x10cd7a30; then the inline destructor of base class 1 (vtable at VA 0x110c0b98)
// calls the same method; it ends in the outermost base destructor at VA 0x10cdc460. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

class UnkType_109cd020_Base
{
public:
    virtual ~UnkType_109cd020_Base();
    void Unk_10cd7a30();
};

class UnkType_109cd020_Level1 : public UnkType_109cd020_Base
{
public:
    virtual ~UnkType_109cd020_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109cd020 : public UnkType_109cd020_Level1
{
public:
    virtual ~UnkType_109cd020();
};

// UnkType_109cd020::~UnkType_109cd020
UnkType_109cd020::~UnkType_109cd020()
{
    Unk_10cd7a30();
}
