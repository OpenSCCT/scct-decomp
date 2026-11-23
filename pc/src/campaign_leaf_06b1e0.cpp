// campaign_leaf_06b1e0.cpp -- destructor at VA 0x1096b1e0 of a class whose vtable is at VA
// 0x110c0158: calls the method at VA 0x10cd7a30, then runs the destructors of the base classes
// whose vtables are at VA 0x110bf398, 0x110bf2a8, each of which calls that method again, before the
// base destructor at VA 0x10cdc460. The class and method names are invented; the addresses are the
// binary's.

class UnkType_1096b1e0_Base
{
public:
    virtual ~UnkType_1096b1e0_Base();
    void Unk_10cd7a30();
};

class UnkType_110bf2a8 : public UnkType_1096b1e0_Base
{
public:
    virtual ~UnkType_110bf2a8()
    {
        Unk_10cd7a30();
    }
};

class UnkType_110bf398 : public UnkType_110bf2a8
{
public:
    virtual ~UnkType_110bf398()
    {
        Unk_10cd7a30();
    }
};

class UnkType_1096b1e0 : public UnkType_110bf398
{
public:
    virtual ~UnkType_1096b1e0();
};

// UnkType_1096b1e0::~UnkType_1096b1e0
UnkType_1096b1e0::~UnkType_1096b1e0()
{
    Unk_10cd7a30();
}
