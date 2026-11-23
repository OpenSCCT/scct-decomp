// campaign_leaf_06a850.cpp -- destructor at VA 0x1096a850 of a class whose vtable is at VA
// 0x110bf398: calls the method at VA 0x10cd7a30, then runs the destructor of the base class whose
// vtable is at VA 0x110bf2a8, each of which calls that method again, before the base destructor at
// VA 0x10cdc460. The class and method names are invented; the addresses are the binary's.

class UnkType_1096a850_Base
{
public:
    virtual ~UnkType_1096a850_Base();
    void Unk_10cd7a30();
};

class UnkType_110bf2a8 : public UnkType_1096a850_Base
{
public:
    virtual ~UnkType_110bf2a8()
    {
        Unk_10cd7a30();
    }
};

class UnkType_1096a850 : public UnkType_110bf2a8
{
public:
    virtual ~UnkType_1096a850();
};

// UnkType_1096a850::~UnkType_1096a850
UnkType_1096a850::~UnkType_1096a850()
{
    Unk_10cd7a30();
}
