// campaign_leaf_1104a0.cpp -- one function at file offset 0x1104a0, preferred VA 0x10a104a0.
// It returns the result of virtual slot 26 of the first non-null object among the pointers at
// offsets 0x48, 0x50, 0x58, 0x64, 0x68 and 0x60, or 0 when all are null. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkType_10a104a0_Child
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
    virtual int VirtualSlot26();
};

class UnkType_10a104a0
{
public:
    unsigned char unk_0[0x48];
    UnkType_10a104a0_Child* unk_48;
    unsigned char unk_4c[0x50 - 0x4c];
    UnkType_10a104a0_Child* unk_50;
    unsigned char unk_54[0x58 - 0x54];
    UnkType_10a104a0_Child* unk_58;
    unsigned char unk_5c[0x60 - 0x5c];
    UnkType_10a104a0_Child* unk_60;
    UnkType_10a104a0_Child* unk_64;
    UnkType_10a104a0_Child* unk_68;

    int Unk_10a104a0();
};

// UnkType_10a104a0::Unk_10a104a0
int UnkType_10a104a0::Unk_10a104a0()
{
    UnkType_10a104a0_Child* Children[6] = { unk_48, unk_50, unk_58, unk_64, unk_68, unk_60 };
    for ( unsigned int i = 0; i < 6; i++ )
    {
        if ( Children[i] )
        {
            return Children[i]->VirtualSlot26();
        }
    }
    return 0;
}
