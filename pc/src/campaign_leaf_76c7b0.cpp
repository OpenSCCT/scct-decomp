// campaign_leaf_76c7b0.cpp -- one function at file offset 0x76c7b0, preferred VA 0x1106c7b0. A
// destructor: it installs the vtable at VA 0x11176b00, calls the method at VA 0x1106c700 and then
// runs the base destructor at VA 0x1105eee0. The class and method names are invented; the offset
// and the addresses are the binary's.

class UnkType_1105eee0
{
public:
    virtual ~UnkType_1105eee0();
};

class UnkType_1106c7b0 : public UnkType_1105eee0
{
public:
    virtual ~UnkType_1106c7b0();
    void Unk_1106c700();
};

// UnkType_1106c7b0::~UnkType_1106c7b0
UnkType_1106c7b0::~UnkType_1106c7b0()
{
    Unk_1106c700();
}
