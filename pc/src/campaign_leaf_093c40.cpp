// campaign_leaf_093c40.cpp -- destructor of the class at VA 0x10993c40: installs its vtable (VA
// 0x110c4470), calls the method at VA 0x10cd7a30, then runs the base class destructor at VA
// 0x1092ad20. The class and method names are invented; the addresses are the binary's.

class UnkType_10993c40_1092ad20
{
public:
    virtual ~UnkType_10993c40_1092ad20();
};

class UnkType_10993c40 : public UnkType_10993c40_1092ad20
{
public:
    ~UnkType_10993c40();
    void Unk_10cd7a30();
};

// UnkType_10993c40::~UnkType_10993c40
UnkType_10993c40::~UnkType_10993c40()
{
    Unk_10cd7a30();
}
