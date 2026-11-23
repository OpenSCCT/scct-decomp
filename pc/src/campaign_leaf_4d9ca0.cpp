// campaign_leaf_4d9ca0.cpp -- one function at file offset 0x4d9ca0, preferred VA 0x10dd9ca0.
// The destructor calls the method at 0x10d9b4a0; the empty inline destructor of the base, whose
// vtable is at 0x111437bc, then installs the base vtable. The class and method names are invented;
// the offset and the bytes are the binary's.

class UnkType_111437bc
{
public:
    virtual ~UnkType_111437bc()
    {
    }
};

class UnkType_10dd9ca0 : public UnkType_111437bc
{
public:
    virtual ~UnkType_10dd9ca0();

    void Unk_10d9b4a0();
};

// UnkType_10dd9ca0::~UnkType_10dd9ca0
UnkType_10dd9ca0::~UnkType_10dd9ca0()
{
    Unk_10d9b4a0();
}
