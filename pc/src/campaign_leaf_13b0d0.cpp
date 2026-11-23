// campaign_leaf_13b0d0.cpp -- one function at file offset 0x13b0d0, preferred VA 0x10a3b0d0.
// A constructor: it runs the object base constructor at VA 0x10cd7930, installs the virtual
// tables at offsets 0 and 0x28, clears the strings at offsets 0xd4 and 0xe0 and five members,
// and sets the member at 0xf4 to one. Its class is the middle level destroyed by the destructor
// at VA 0x10a431c0.
// The class and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a3b0d0_Object
{
public:
    UnkType_10a3b0d0_Object();
    virtual ~UnkType_10a3b0d0_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a3b0d0_Interface
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10a3b0d0_Base : public UnkType_10a3b0d0_Object, public UnkType_10a3b0d0_Interface
{
public:
    unsigned char unk_2c[0xa4 - 0x2c];

    virtual ~UnkType_10a3b0d0_Base()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a3b0d0_String
{
public:
    void* unk_0;
    int unk_4;
    int unk_8;

    UnkType_10a3b0d0_String()
        : unk_0(0), unk_4(0), unk_8(0)
    {
    }
    ~UnkType_10a3b0d0_String();
};

class UnkType_10a3b0d0 : public UnkType_10a3b0d0_Base
{
public:
    int unk_a4;
    int unk_a8;
    unsigned char unk_ac[0xb8 - 0xac];
    int unk_b8;
    int unk_bc;
    int unk_c0;
    unsigned char unk_c4[0xd4 - 0xc4];
    UnkType_10a3b0d0_String unk_d4;
    UnkType_10a3b0d0_String unk_e0;
    unsigned char unk_ec[0xf4 - 0xec];
    int unk_f4;

    UnkType_10a3b0d0();
    virtual ~UnkType_10a3b0d0();
};

// UnkType_10a3b0d0::UnkType_10a3b0d0
UnkType_10a3b0d0::UnkType_10a3b0d0()
{
    unk_a8 = 0;
    unk_b8 = 0;
    unk_a4 = 0;
    unk_c0 = 0;
    unk_bc = 0;
    unk_f4 = 1;
}
