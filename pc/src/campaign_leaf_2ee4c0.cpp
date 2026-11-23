// campaign_leaf_2ee4c0.cpp -- destructor at VA 0x10bee4c0 of a class with a vtable (VA 0x110c8a38):
// calls the method at VA 0x10cd7a30 and destroys the string at 0x2b8 (destructor at VA 0x1090ba70);
// then its parent class's inline destructor stores that class's vtable (VA 0x110c87a0) and calls
// the same method, and the root class destructor at VA 0x1092ad20 runs. The class, member and
// method names are invented; the offsets and the addresses are the binary's.

class UnkType_10bee4c0_Root
{
public:
    virtual ~UnkType_10bee4c0_Root();

    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2b8 - 0x04];
};

class UnkType_10bee4c0_Parent : public UnkType_10bee4c0_Root
{
public:
    virtual ~UnkType_10bee4c0_Parent()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10bee4c0_String
{
public:
    ~UnkType_10bee4c0_String();

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bee4c0 : public UnkType_10bee4c0_Parent
{
public:
    virtual ~UnkType_10bee4c0();

private:
    UnkType_10bee4c0_String unk_2b8;
};

// UnkType_10bee4c0::~UnkType_10bee4c0
UnkType_10bee4c0::~UnkType_10bee4c0()
{
    Unk_10cd7a30();
}
