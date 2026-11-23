// campaign_leaf_075c30.cpp -- method at VA 0x10975c30: unless bit 5 of the value at 0x98 of the
// object at 0x0c is set, calls virtual slot 0 of the member at 0x10 of that object's object at
// 0xbc; returns the value at 0x1c of the object at 0xbc. The class, member and method names are
// invented; the offsets and the constant are the binary's.

class UnkType_10975c30_10
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10975c30_bc
{
public:
    unsigned char unk_00[0x10];
    UnkType_10975c30_10 unk_10;
    unsigned char unk_14[0x1c - 0x14];
    int unk_1c;
};

class UnkType_10975c30_0c
{
public:
    unsigned char unk_00[0x98];
    unsigned int unk_98;
    unsigned char unk_9c[0xbc - 0x9c];
    UnkType_10975c30_bc* unk_bc;
};

class UnkType_10975c30
{
public:
    int Unk_10975c30();

private:
    unsigned char unk_00[0x0c];
    UnkType_10975c30_0c* unk_0c;
};

// UnkType_10975c30::Unk_10975c30
int UnkType_10975c30::Unk_10975c30()
{
    if ( !(unk_0c->unk_98 & 0x20) )
    {
        UnkType_10975c30_bc* Object = unk_0c->unk_bc;
        Object->unk_10.VirtualSlot0();
    }
    return unk_0c->unk_bc->unk_1c;
}
