// campaign_leaf_3401a0.cpp -- one function at file offset 0x3401a0, preferred VA 0x10c401a0. A
// destructor: it installs the vtable at 0x110fede0, calls the method at 0x10cd7a30 and destroys
// the members at 0x94, 0x88, 0x7c, 0x70 and 0x64 (destructor at 0x1090ba70); it then runs the
// intermediate base destructor inline (vtable at 0x110fed70, the method at 0x10cd7a30 again, the
// members at 0x50 and 0x3c) and ends in the base destructor at 0x10cdc460. The class, method and
// member names are invented; the offsets and the bytes are the binary's.

class UnkType_10c401a0_Base
{
public:
    virtual ~UnkType_10c401a0_Base();
    void Unk_10cd7a30();

    unsigned char unk_4[0x38];
};

class UnkType_1090ba70
{
public:
    ~UnkType_1090ba70();

    unsigned char unk_0[0xc];
};

class UnkType_10c401a0_Middle : public UnkType_10c401a0_Base
{
public:
    virtual ~UnkType_10c401a0_Middle()
    {
        Unk_10cd7a30();
    }

    UnkType_1090ba70 unk_3c;
    unsigned char unk_48[0x8];
    UnkType_1090ba70 unk_50;
    unsigned char unk_5c[0x8];
};

class UnkType_10c401a0 : public UnkType_10c401a0_Middle
{
public:
    virtual ~UnkType_10c401a0();

    UnkType_1090ba70 unk_64;
    UnkType_1090ba70 unk_70;
    UnkType_1090ba70 unk_7c;
    UnkType_1090ba70 unk_88;
    UnkType_1090ba70 unk_94;
};

// UnkType_10c401a0::~UnkType_10c401a0
UnkType_10c401a0::~UnkType_10c401a0()
{
    Unk_10cd7a30();
}
