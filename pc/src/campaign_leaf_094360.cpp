// campaign_leaf_094360.cpp -- virtual destructor at VA 0x10994360 (vtable at VA 0x110c4728): calls
// the method at VA 0x10cd7a30, then destroys the member at 0x34c (destructor at VA 0x1090ba70);
// then the inline destructor of base class 1 (vtable at VA 0x110c4470) calls the same method; it
// ends in the outermost base destructor at VA 0x1092ad20. The class, member and method names are
// invented; the offsets and the addresses are the binary's.

class UnkType_10994360_Member
{
public:
    ~UnkType_10994360_Member();

private:
    unsigned char unk_00[0x0c];
};

class UnkType_10994360_Base
{
public:
    virtual ~UnkType_10994360_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x34c - 0x04];
};

class UnkType_10994360_Level1 : public UnkType_10994360_Base
{
public:
    virtual ~UnkType_10994360_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10994360 : public UnkType_10994360_Level1
{
public:
    virtual ~UnkType_10994360();

private:
    UnkType_10994360_Member unk_34c;
};

// UnkType_10994360::~UnkType_10994360
UnkType_10994360::~UnkType_10994360()
{
    Unk_10cd7a30();
}
