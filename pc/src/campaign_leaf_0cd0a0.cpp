// campaign_leaf_0cd0a0.cpp -- virtual destructor at VA 0x109cd0a0 (vtable at VA 0x110cf588): calls
// the method at VA 0x10cd7a30, then runs the inline destructor of its base class (vtable at VA
// 0x110c0b98), which calls the same method, and ends in that class's base destructor at VA
// 0x10cdc460. The class and method names are invented; the addresses are the binary's.

class UnkType_109cd0a0_Base
{
public:
    virtual ~UnkType_109cd0a0_Base();
    void Unk_10cd7a30();
};

class UnkType_109cd0a0_Middle : public UnkType_109cd0a0_Base
{
public:
    virtual ~UnkType_109cd0a0_Middle()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109cd0a0 : public UnkType_109cd0a0_Middle
{
public:
    virtual ~UnkType_109cd0a0();
};

// UnkType_109cd0a0::~UnkType_109cd0a0
UnkType_109cd0a0::~UnkType_109cd0a0()
{
    Unk_10cd7a30();
}
