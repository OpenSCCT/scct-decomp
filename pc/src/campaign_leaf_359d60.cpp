// campaign_leaf_359d60.cpp -- one function at file offset 0x359d60, preferred VA 0x10c59d60. It
// calls the method at 0x10c58e10, passes five zeros to virtual slot 37 of the object at 0x48 of the
// object at 0x38 of the object at 0x7c when that is set, and passes each of the objects at 0x578,
// 0x57c and 0x518 that is set with 0 to virtual slot 35 of the object at 0x7c. The class, method,
// member and local names are invented; the offsets, the slots and the bytes are the binary's.

class UnkType_10c59d60_Effect
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37(int First, int Second, int Third, int Fourth, int Fifth);
};

class UnkType_10c59d60_Mesh
{
public:
    unsigned char unk_0[0x48];
    UnkType_10c59d60_Effect* unk_48;
};

class UnkType_10c59d60_Owner
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35(void* Object, int Flags);

    unsigned char unk_4[0x34];
    UnkType_10c59d60_Mesh* unk_38;
};

class UnkType_10c59d60
{
public:
    void Unk_10c58e10();
    void Unk_10c59d60();

    unsigned char unk_0[0x7c];
    UnkType_10c59d60_Owner* unk_7c;
    unsigned char unk_80[0x498];
    void* unk_518;
    unsigned char unk_51c[0x5c];
    void* unk_578;
    void* unk_57c;
};

// UnkType_10c59d60::Unk_10c59d60
void UnkType_10c59d60::Unk_10c59d60()
{
    UnkType_10c59d60_Effect* Effect;

    Unk_10c58e10();
    Effect = unk_7c->unk_38->unk_48;
    if ( Effect != 0 )
    {
        Effect->VirtualSlot37(0, 0, 0, 0, 0);
    }
    if ( unk_578 != 0 )
    {
        unk_7c->VirtualSlot35(unk_578, 0);
    }
    if ( unk_57c != 0 )
    {
        unk_7c->VirtualSlot35(unk_57c, 0);
    }
    if ( unk_518 != 0 )
    {
        unk_7c->VirtualSlot35(unk_518, 0);
    }
}
