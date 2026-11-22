// campaign_leaf_40cb20.cpp -- thiscall at VA 0x10d0cb20: calls the method at VA 0x1090ec40 on the
// same object, then deletes the object at offset 0x80 through its virtual destructor. All names
// are invented.

class UnkType_10d0cb20_Obj
{
public:
    virtual void VirtualSlot0();
    virtual ~UnkType_10d0cb20_Obj();
};

class UnkType_10d0cb20
{
public:
    void Unk_1090ec40();
    void Unk_10d0cb20();

private:
    unsigned char unk_00[0x80];
    UnkType_10d0cb20_Obj* unk_80;
};

// UnkType_10d0cb20::Unk_10d0cb20
void UnkType_10d0cb20::Unk_10d0cb20()
{
    Unk_1090ec40();
    delete unk_80;
}
