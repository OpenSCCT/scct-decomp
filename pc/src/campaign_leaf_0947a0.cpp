// campaign_leaf_0947a0.cpp -- virtual destructor at VA 0x109947a0 (vtable at VA 0x110c5730): calls
// the method at VA 0x10cd7a30; then the inline destructor of base class 1 (vtable at VA 0x110c51a8)
// calls the same method; it ends in the outermost base destructor at VA 0x1092ad20. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

class UnkType_109947a0_Base
{
public:
    virtual ~UnkType_109947a0_Base();
    void Unk_10cd7a30();
};

class UnkType_109947a0_Level1 : public UnkType_109947a0_Base
{
public:
    virtual ~UnkType_109947a0_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109947a0 : public UnkType_109947a0_Level1
{
public:
    virtual ~UnkType_109947a0();
};

// UnkType_109947a0::~UnkType_109947a0
UnkType_109947a0::~UnkType_109947a0()
{
    Unk_10cd7a30();
}
