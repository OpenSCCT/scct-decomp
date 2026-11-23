// campaign_leaf_2b76f0.cpp -- destructor at VA 0x10bb76f0 of a class with a vtable (VA 0x110c5468):
// calls the method at VA 0x10cd7a30; then its parent class's inline destructor stores that class's
// vtable (VA 0x110c51a8) and calls the same method, and the root class destructor at VA 0x1092ad20
// runs. The class, member and method names are invented; the addresses are the binary's.

class UnkType_10bb76f0_Root
{
public:
    virtual ~UnkType_10bb76f0_Root();

    void Unk_10cd7a30();
};

class UnkType_10bb76f0_Parent : public UnkType_10bb76f0_Root
{
public:
    virtual ~UnkType_10bb76f0_Parent()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10bb76f0 : public UnkType_10bb76f0_Parent
{
public:
    virtual ~UnkType_10bb76f0();
};

// UnkType_10bb76f0::~UnkType_10bb76f0
UnkType_10bb76f0::~UnkType_10bb76f0()
{
    Unk_10cd7a30();
}
