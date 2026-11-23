// campaign_leaf_1431c0.cpp -- one function at file offset 0x1431c0, preferred VA 0x10a431c0.
// A destructor of a class three levels above the object base: each level installs its virtual
// tables at offsets 0 and 0x28 and calls the base's method at VA 0x10cd7a30. The most derived
// level destroys its member at offset 0x184 (destructor at VA 0x10a064f0), the middle level its
// strings at offsets 0xe0 and 0xd4 (destructor at VA 0x1090ba70), and the last runs the base
// destructor at VA 0x10cdc460.
// The class and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a431c0_Object
{
public:
    virtual ~UnkType_10a431c0_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a431c0_Interface
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10a431c0_Base : public UnkType_10a431c0_Object, public UnkType_10a431c0_Interface
{
public:
    unsigned char unk_2c[0xd4 - 0x2c];

    virtual ~UnkType_10a431c0_Base()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a431c0_String
{
public:
    void* unk_0;
    int unk_4;
    int unk_8;

    ~UnkType_10a431c0_String();
};

class UnkType_10a431c0_Middle : public UnkType_10a431c0_Base
{
public:
    UnkType_10a431c0_String unk_d4;
    UnkType_10a431c0_String unk_e0;
    unsigned char unk_ec[0x184 - 0xec];

    virtual ~UnkType_10a431c0_Middle()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a431c0_Member
{
public:
    int unk_0;

    ~UnkType_10a431c0_Member();
};

class UnkType_10a431c0 : public UnkType_10a431c0_Middle
{
public:
    UnkType_10a431c0_Member unk_184;

    virtual ~UnkType_10a431c0();
};

// UnkType_10a431c0::~UnkType_10a431c0
UnkType_10a431c0::~UnkType_10a431c0()
{
    Unk_10cd7a30();
}
