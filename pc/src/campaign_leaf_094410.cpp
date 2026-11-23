// campaign_leaf_094410.cpp -- virtual destructor at VA 0x10994410 (vtable at VA 0x110c49c8): calls
// the method at VA 0x10cd7a30; then the inline destructor of base class 1 (vtable at VA 0x110c4728)
// calls the same method, then destroys the member at 0x34c (destructor at VA 0x1090ba70); then the
// inline destructor of base class 2 (vtable at VA 0x110c4470) calls the same method; it ends in the
// outermost base destructor at VA 0x1092ad20. The class, member and method names are invented; the
// offsets and the addresses are the binary's.

class UnkType_10994410_Member
{
public:
    ~UnkType_10994410_Member();

private:
    unsigned char unk_00[0x0c];
};

class UnkType_10994410_Base
{
public:
    virtual ~UnkType_10994410_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x34c - 0x04];
};

class UnkType_10994410_Level2 : public UnkType_10994410_Base
{
public:
    virtual ~UnkType_10994410_Level2()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10994410_Level1 : public UnkType_10994410_Level2
{
public:
    virtual ~UnkType_10994410_Level1()
    {
        Unk_10cd7a30();
    }

private:
    UnkType_10994410_Member unk_34c;
};

class UnkType_10994410 : public UnkType_10994410_Level1
{
public:
    virtual ~UnkType_10994410();
};

// UnkType_10994410::~UnkType_10994410
UnkType_10994410::~UnkType_10994410()
{
    Unk_10cd7a30();
}
