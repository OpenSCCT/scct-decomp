// campaign_leaf_092330.cpp -- virtual destructor at VA 0x10992330 (vtable at VA 0x110c4118): calls
// the method at VA 0x10cd7a30, then destroys the members at 0x40, 0x34, 0x28 (destructor at VA
// 0x1090ba70); it ends in the outermost base destructor at VA 0x10cdc460. The class, member and
// method names are invented; the offsets and the addresses are the binary's.

class UnkType_10992330_Member
{
public:
    ~UnkType_10992330_Member();

private:
    unsigned char unk_00[0x0c];
};

class UnkType_10992330_Base
{
public:
    virtual ~UnkType_10992330_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x28 - 0x04];
};

class UnkType_10992330 : public UnkType_10992330_Base
{
public:
    virtual ~UnkType_10992330();

private:
    UnkType_10992330_Member unk_28;
    UnkType_10992330_Member unk_34;
    UnkType_10992330_Member unk_40;
};

// UnkType_10992330::~UnkType_10992330
UnkType_10992330::~UnkType_10992330()
{
    Unk_10cd7a30();
}
