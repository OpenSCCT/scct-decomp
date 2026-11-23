// campaign_leaf_11bc20.cpp -- one function at file offset 0x11bc20, preferred VA 0x10a1bc20.
// It passes its own pointer to its argument's method at VA 0x1096f1e0, then calls virtual slot 29
// with the argument on each non-null object of the pointers at offsets 0x48, 0x50, 0x5c and 0x58.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a1bc20;

class UnkType_10a1bc20_Visitor
{
public:
    void Unk_1096f1e0(UnkType_10a1bc20*& Value);
};

class UnkType_10a1bc20_Child
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
    virtual void VirtualSlot29(UnkType_10a1bc20_Visitor& Arg);
};

class UnkType_10a1bc20
{
public:
    unsigned char unk_0[0x48];
    UnkType_10a1bc20_Child* unk_48;
    unsigned char unk_4c[0x50 - 0x4c];
    UnkType_10a1bc20_Child* unk_50;
    unsigned char unk_54[0x58 - 0x54];
    UnkType_10a1bc20_Child* unk_58;
    UnkType_10a1bc20_Child* unk_5c;

    void Unk_10a1bc20(UnkType_10a1bc20_Visitor& Arg);
};

// UnkType_10a1bc20::Unk_10a1bc20
void UnkType_10a1bc20::Unk_10a1bc20(UnkType_10a1bc20_Visitor& Arg)
{
    UnkType_10a1bc20* Self = this;
    Arg.Unk_1096f1e0(Self);
    UnkType_10a1bc20_Child* Children[4] = { unk_48, unk_50, unk_5c, unk_58 };
    for ( unsigned int i = 0; i < 4; i++ )
    {
        if ( Children[i] )
        {
            Children[i]->VirtualSlot29(Arg);
        }
    }
}
