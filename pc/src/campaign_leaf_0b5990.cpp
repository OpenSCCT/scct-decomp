// campaign_leaf_0b5990.cpp -- virtual destructor at VA 0x109b5990 (vtable at VA 0x110cde48): calls
// the method at VA 0x10cd7a30; then the inline destructor of base class 1 (vtable at VA 0x110cddd8)
// calls the same method; it ends in the outermost base destructor at VA 0x10cdc460. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

class UnkType_109b5990_Base
{
public:
    virtual ~UnkType_109b5990_Base();
    void Unk_10cd7a30();
};

class UnkType_109b5990_Level1 : public UnkType_109b5990_Base
{
public:
    virtual ~UnkType_109b5990_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109b5990 : public UnkType_109b5990_Level1
{
public:
    virtual ~UnkType_109b5990();
};

// UnkType_109b5990::~UnkType_109b5990
UnkType_109b5990::~UnkType_109b5990()
{
    Unk_10cd7a30();
}
