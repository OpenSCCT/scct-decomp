// campaign_leaf_763360.cpp -- one function at file offset 0x763360, preferred VA 0x11063360. It
// calls the fourth virtual method of the object at 0x74 and the method at VA 0x1105ef00 on the
// object at 0x78, each only when its pointer is set. The class, method and member names are
// invented; the offsets and the callee's address are the binary's.

class UnkType_11063360_First
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
};

class UnkType_11063360_Second
{
public:
    void Unk_1105ef00();
};

class UnkType_11063360
{
public:
    void Unk_11063360();

    unsigned char unk_0[0x74];
    UnkType_11063360_First* unk_74;
    UnkType_11063360_Second* unk_78;
};

// UnkType_11063360::Unk_11063360
void UnkType_11063360::Unk_11063360()
{
    if ( unk_74 != 0 )
    {
        unk_74->VirtualSlot3();
    }
    if ( unk_78 != 0 )
    {
        unk_78->Unk_1105ef00();
    }
}
