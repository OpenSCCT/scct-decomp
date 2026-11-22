// campaign_leaf_73a6b0.cpp -- one function at file offset 0x73a6b0, preferred VA 0x1103a6b0. A
// destructor with the same body as the one at 0x73a670: it installs the vtable at VA 0x111713a8,
// destroys the member at 0x44 (destructor at VA 0x1103b0d0) and runs the base destructor at VA
// 0x10da2740. The class names are invented; the offset and the addresses are the binary's.

class UnkType_10da2740
{
public:
    virtual ~UnkType_10da2740();

    unsigned char unk_4[0x44 - 0x4];
};

class UnkType_1103b0d0
{
public:
    ~UnkType_1103b0d0();
};

class UnkType_1103a6b0 : public UnkType_10da2740
{
public:
    virtual ~UnkType_1103a6b0();

    UnkType_1103b0d0 unk_44;
};

// UnkType_1103a6b0::~UnkType_1103a6b0
UnkType_1103a6b0::~UnkType_1103a6b0()
{
}
