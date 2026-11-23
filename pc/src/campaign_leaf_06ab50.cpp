// campaign_leaf_06ab50.cpp -- destructor at VA 0x1096ab50 of a class whose vtable is at VA
// 0x110bf700: calls the method at VA 0x10cd7a30, then runs the destructor of the base class whose
// vtable is at VA 0x110bf2a8, each of which calls that method again, before the base destructor at
// VA 0x10cdc460. The class and method names are invented; the addresses are the binary's.

class UnkType_1096ab50_Base
{
public:
    virtual ~UnkType_1096ab50_Base();
    void Unk_10cd7a30();
};

class UnkType_110bf2a8 : public UnkType_1096ab50_Base
{
public:
    virtual ~UnkType_110bf2a8()
    {
        Unk_10cd7a30();
    }
};

class UnkType_1096ab50 : public UnkType_110bf2a8
{
public:
    virtual ~UnkType_1096ab50();
};

// UnkType_1096ab50::~UnkType_1096ab50
UnkType_1096ab50::~UnkType_1096ab50()
{
    Unk_10cd7a30();
}
