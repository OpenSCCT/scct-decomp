// campaign_leaf_38a9c0.cpp -- one function at file offset 0x38a9c0, preferred VA 0x10c8a9c0. It
// calls its own virtual slot 32; then, when the interface at 0x4d3c is set, calls the method at
// 0x10c8a2e0 and releases that interface (stdcall slot 2) if it is still set; it also releases
// the interface at 0x4d40. Released pointers are cleared. The class, method and member names are
// invented; the offsets, the slots and the bytes are the binary's.

class UnkType_10c8a9c0_Interface
{
public:
    virtual long __stdcall VirtualSlot0();
    virtual unsigned long __stdcall VirtualSlot1();
    virtual unsigned long __stdcall VirtualSlot2();
};

class UnkType_10c8a9c0
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
    void Unk_10c8a2e0();
    void Unk_10c8a9c0();

    unsigned char unk_4[0x4d38];
    UnkType_10c8a9c0_Interface* unk_4d3c;
    UnkType_10c8a9c0_Interface* unk_4d40;
};

// UnkType_10c8a9c0::Unk_10c8a9c0
void UnkType_10c8a9c0::Unk_10c8a9c0()
{
    VirtualSlot32();
    if ( unk_4d3c != 0 )
    {
        Unk_10c8a2e0();
        if ( unk_4d3c != 0 )
        {
            unk_4d3c->VirtualSlot2();
            unk_4d3c = 0;
        }
    }
    if ( unk_4d40 != 0 )
    {
        unk_4d40->VirtualSlot2();
        unk_4d40 = 0;
    }
}
