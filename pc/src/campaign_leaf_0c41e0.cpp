// campaign_leaf_0c41e0.cpp -- virtual destructor at VA 0x109c41e0 (vtable at VA 0x110ce640): calls
// the method at VA 0x10cd7a30; then the inline destructor of base class 1 (vtable at VA 0x110ce3a8)
// calls the same method; it ends in the outermost base destructor at VA 0x1092ad20. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

class UnkType_109c41e0_Base
{
public:
    virtual ~UnkType_109c41e0_Base();
    void Unk_10cd7a30();
};

class UnkType_109c41e0_Level1 : public UnkType_109c41e0_Base
{
public:
    virtual ~UnkType_109c41e0_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109c41e0 : public UnkType_109c41e0_Level1
{
public:
    virtual ~UnkType_109c41e0();
};

// UnkType_109c41e0::~UnkType_109c41e0
UnkType_109c41e0::~UnkType_109c41e0()
{
    Unk_10cd7a30();
}
