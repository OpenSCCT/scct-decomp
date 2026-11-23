// campaign_leaf_760a80.cpp -- one function at file offset 0x760a80, preferred VA 0x11060a80. A
// destructor: it installs the vtable at VA 0x1117614c and, when the object at 0x4 is set, deletes
// it through its virtual destructor and clears the pointer. The class names are invented; the
// offsets and the vtable's address are the binary's.

class UnkType_11060a80_Object
{
public:
    virtual ~UnkType_11060a80_Object();
};

class UnkType_11060a80
{
public:
    virtual ~UnkType_11060a80();

    UnkType_11060a80_Object* unk_4;
};

// UnkType_11060a80::~UnkType_11060a80
UnkType_11060a80::~UnkType_11060a80()
{
    if ( unk_4 != 0 )
    {
        delete unk_4;
        unk_4 = 0;
    }
}
