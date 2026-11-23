// campaign_leaf_067ed0.cpp -- destructor at VA 0x10967ed0 of a class whose vtable is at VA
// 0x110beeb8: calls the method at VA 0x10cd7a30, then runs the destructor of the base class whose
// vtable is at VA 0x110bee58, each of which calls that method again, before the base destructor at
// VA 0x10cdc460. The class and method names are invented; the addresses are the binary's.

class UnkType_10967ed0_Base
{
public:
    virtual ~UnkType_10967ed0_Base();
    void Unk_10cd7a30();
};

class UnkType_110bee58 : public UnkType_10967ed0_Base
{
public:
    virtual ~UnkType_110bee58()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10967ed0 : public UnkType_110bee58
{
public:
    virtual ~UnkType_10967ed0();
};

// UnkType_10967ed0::~UnkType_10967ed0
UnkType_10967ed0::~UnkType_10967ed0()
{
    Unk_10cd7a30();
}
