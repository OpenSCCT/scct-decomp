// campaign_leaf_06a430.cpp -- method at VA 0x1096a430 taking six arguments: sets the value its
// third argument points to to 1 when bit 1 of the value at 0x58 is set, and when bit 0 is set sets
// the value its fourth argument points to to 1 and copies the byte at 0x5c to the byte its fifth
// argument points to; then returns virtual slot 27 (vtable offset 0x6c) of the object at 0x48
// called with all six arguments, or 0 when there is none. The class, member and method names are
// invented; the offsets, the bits and the slot are the binary's.

class UnkType_1096a430_48
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
    virtual int VirtualSlot27(int Arg0, int Arg1, int* Arg2, int* Arg3, unsigned char* Arg4,
                              int Arg5);
};

class UnkType_1096a430
{
public:
    int Unk_1096a430(int Arg0, int Arg1, int* Arg2, int* Arg3, unsigned char* Arg4, int Arg5);

private:
    unsigned char unk_00[0x48];
    UnkType_1096a430_48* unk_48;
    unsigned char unk_4c[0x58 - 0x4c];
    unsigned char unk_58;
    unsigned char unk_59[3];
    unsigned char unk_5c;
};

// UnkType_1096a430::Unk_1096a430
int UnkType_1096a430::Unk_1096a430(int Arg0, int Arg1, int* Arg2, int* Arg3, unsigned char* Arg4,
                                   int Arg5)
{
    if ( unk_58 & 2 )
    {
        *Arg2 = 1;
    }
    if ( unk_58 & 1 )
    {
        *Arg3 = 1;
        *Arg4 = unk_5c;
    }
    if ( unk_48 )
    {
        return unk_48->VirtualSlot27(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5);
    }
    return 0;
}
