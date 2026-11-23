// campaign_leaf_4b8750.cpp -- one function at file offset 0x4b8750, preferred VA 0x10db8750.
// When the short at offset 0x5c is set it passes the object to the virtual method in slot 2 of
// what the function at 0x10da5460 returns; then it calls the method at 0x10d8ed80 of the member at
// offset 0x64 and the method at 0x10dc1290 of the object at offset 0x90. The class, function,
// method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10db8750;

class UnkType_10db8750_Owner
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(UnkType_10db8750* Item);
};

UnkType_10db8750_Owner* Unk_10da5460();

class UnkType_10db8750_Member
{
public:
    void Unk_10d8ed80();
};

class UnkType_10db8750_Callee
{
public:
    void Unk_10dc1290();
};

class UnkType_10db8750
{
public:
    unsigned char unk_0[0x5c];
    short unk_5c;
    unsigned char unk_5e[6];
    UnkType_10db8750_Member unk_64;
    unsigned char unk_65[0x2b];
    UnkType_10db8750_Callee* unk_90;

    void Unk_10db8750();
};

// UnkType_10db8750::Unk_10db8750
void UnkType_10db8750::Unk_10db8750()
{
    if ( unk_5c != 0 )
    {
        Unk_10da5460()->VirtualSlot2(this);
    }
    unk_64.Unk_10d8ed80();
    unk_90->Unk_10dc1290();
}
