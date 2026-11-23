// campaign_leaf_2fd480.cpp -- destructor at VA 0x10bfd480 of a class with a vtable (VA 0x110f15c0):
// calls the method at VA 0x10cd7a30, then destroys the string at 0x410 (destructor at VA
// 0x1090ba70), and runs the base class destructor at VA 0x10bee4f0. The class, member and method
// names are invented; the offsets and the addresses are the binary's.

class UnkType_10bfd480_Base
{
public:
    virtual ~UnkType_10bfd480_Base();

    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x410 - 0x04];
};

class UnkType_10bfd480_String
{
public:
    ~UnkType_10bfd480_String();

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bfd480 : public UnkType_10bfd480_Base
{
public:
    virtual ~UnkType_10bfd480();

private:
    UnkType_10bfd480_String unk_410;
};

// UnkType_10bfd480::~UnkType_10bfd480
UnkType_10bfd480::~UnkType_10bfd480()
{
    Unk_10cd7a30();
}
