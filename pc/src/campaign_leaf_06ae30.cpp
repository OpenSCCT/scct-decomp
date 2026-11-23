// campaign_leaf_06ae30.cpp -- destructor at VA 0x1096ae30 of a class whose vtable is at VA
// 0x110bfb38: calls the method at VA 0x10cd7a30, then runs the destructors of the base classes
// whose vtables are at VA 0x110bf700, 0x110bf2a8, each of which calls that method again, before the
// base destructor at VA 0x10cdc460. The class and method names are invented; the addresses are the
// binary's.

class UnkType_1096ae30_Base
{
public:
    virtual ~UnkType_1096ae30_Base();
    void Unk_10cd7a30();
};

class UnkType_110bf2a8 : public UnkType_1096ae30_Base
{
public:
    virtual ~UnkType_110bf2a8()
    {
        Unk_10cd7a30();
    }
};

class UnkType_110bf700 : public UnkType_110bf2a8
{
public:
    virtual ~UnkType_110bf700()
    {
        Unk_10cd7a30();
    }
};

class UnkType_1096ae30 : public UnkType_110bf700
{
public:
    virtual ~UnkType_1096ae30();
};

// UnkType_1096ae30::~UnkType_1096ae30
UnkType_1096ae30::~UnkType_1096ae30()
{
    Unk_10cd7a30();
}
