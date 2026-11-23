// campaign_leaf_19e700.cpp -- one function at file offset 0x19e700, preferred VA 0x10a9e700.
// A destructor: it installs its class's virtual table, destroys the members at offsets 0x19d4,
// 0x1550, 0x13f8, 0xaf0, 0x2f4 and 0x48 with the destructors at VA 0x10aff980, 0x10aff930,
// 0x10aff4b0, 0x10aff440, 0x10afeae0 and 0x10d9d570, then runs the base destructor at VA
// 0x10df4ca0.
// The class and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a9e700_Base
{
public:
    virtual ~UnkType_10a9e700_Base();

    unsigned char unk_4[0x48 - 0x4];
};

class UnkType_10a9e700_M48
{
public:
    unsigned char unk_0[0x2ac];

    ~UnkType_10a9e700_M48();
};

class UnkType_10a9e700_M2f4
{
public:
    unsigned char unk_0[0x7fc];

    ~UnkType_10a9e700_M2f4();
};

class UnkType_10a9e700_Maf0
{
public:
    unsigned char unk_0[0x908];

    ~UnkType_10a9e700_Maf0();
};

class UnkType_10a9e700_M13f8
{
public:
    unsigned char unk_0[0x158];

    ~UnkType_10a9e700_M13f8();
};

class UnkType_10a9e700_M1550
{
public:
    unsigned char unk_0[0x484];

    ~UnkType_10a9e700_M1550();
};

class UnkType_10a9e700_M19d4
{
public:
    unsigned char unk_0[0x4];

    ~UnkType_10a9e700_M19d4();
};

class UnkType_10a9e700 : public UnkType_10a9e700_Base
{
public:
    UnkType_10a9e700_M48 unk_48;
    UnkType_10a9e700_M2f4 unk_2f4;
    UnkType_10a9e700_Maf0 unk_af0;
    UnkType_10a9e700_M13f8 unk_13f8;
    UnkType_10a9e700_M1550 unk_1550;
    UnkType_10a9e700_M19d4 unk_19d4;
    virtual ~UnkType_10a9e700();
};

// UnkType_10a9e700::~UnkType_10a9e700
UnkType_10a9e700::~UnkType_10a9e700()
{
}
