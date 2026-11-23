// campaign_leaf_76e490.cpp -- one function at file offset 0x76e490, preferred VA 0x1106e490. A
// destructor: it installs the vtable at VA 0x11176c38, passes the address of the pointer at 0x2c
// to the function at VA 0x110634d0 when that pointer is set, and runs the base destructor at VA
// 0x1105eee0. The class names are invented; the offsets and the addresses are the binary's.

void Unk_110634d0(void** Object);

class UnkType_1106e490_Base
{
public:
    virtual ~UnkType_1106e490_Base();

    unsigned char unk_4[0x2c - 0x4];
};

class UnkType_1106e490 : public UnkType_1106e490_Base
{
public:
    virtual ~UnkType_1106e490();

    void* unk_2c;
};

// UnkType_1106e490::~UnkType_1106e490
UnkType_1106e490::~UnkType_1106e490()
{
    if ( unk_2c != 0 )
    {
        Unk_110634d0(&unk_2c);
    }
}
