// campaign_leaf_299090.cpp -- destructor at VA 0x10b99090 of a class with a vtable (VA 0x110e8140):
// calls the method at VA 0x10cd7a30; then the inline destructors of three ancestor classes each
// store their vtable (VA 0x110c49c8, VA 0x110c4728, VA 0x110c4470) and call the same method, the
// second of them also destroying the string at 0x34c (destructor at VA 0x1090ba70); the root class
// destructor at VA 0x1092ad20 runs last. The class, member and method names are invented; the
// offsets and the addresses are the binary's.

class UnkType_10b99090_Root
{
public:
    virtual ~UnkType_10b99090_Root();

    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x34c - 0x04];
};

class UnkType_10b99090_Third : public UnkType_10b99090_Root
{
public:
    virtual ~UnkType_10b99090_Third()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10b99090_String
{
public:
    ~UnkType_10b99090_String();

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b99090_Second : public UnkType_10b99090_Third
{
public:
    virtual ~UnkType_10b99090_Second()
    {
        Unk_10cd7a30();
    }

private:
    UnkType_10b99090_String unk_34c;
};

class UnkType_10b99090_First : public UnkType_10b99090_Second
{
public:
    virtual ~UnkType_10b99090_First()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10b99090 : public UnkType_10b99090_First
{
public:
    virtual ~UnkType_10b99090();
};

// UnkType_10b99090::~UnkType_10b99090
UnkType_10b99090::~UnkType_10b99090()
{
    Unk_10cd7a30();
}
