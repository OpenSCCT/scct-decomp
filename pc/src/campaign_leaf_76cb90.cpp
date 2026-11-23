// campaign_leaf_76cb90.cpp -- one function at file offset 0x76cb90, preferred VA 0x1106cb90. It
// allocates a 0x38-byte object through the allocator at VA 0x1105ee10 and constructs it (the base
// constructor at VA 0x1105ee30, the words from 0x20 to 0x34 cleared, the vtable at VA
// 0x11176b00). It returns -1 when that fails or when the object's sixth virtual method or its
// method at VA 0x1106ca30 rejects the value (deleting the object through its virtual
// destructor); otherwise it stores the object through the first argument and returns 0. The
// class and function names are invented; the offsets and the addresses are the binary's.

class UnkType_1106cb90_Base
{
public:
    static void* operator new(unsigned int Size);

    UnkType_1106cb90_Base();

    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual int VirtualSlot5(int Value);
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
    virtual ~UnkType_1106cb90_Base();

    unsigned char unk_4[0x20 - 0x4];
};

class UnkType_1106cb90 : public UnkType_1106cb90_Base
{
public:
    UnkType_1106cb90()
    {
        unk_20 = 0;
        unk_24 = 0;
        unk_28 = 0;
        unk_2c = 0;
        unk_30 = 0;
        unk_34 = 0;
    }

    virtual int VirtualSlot5(int Value);
    virtual ~UnkType_1106cb90();

    int Unk_1106ca30(int Value);

    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
};

// Unk_1106cb90
int Unk_1106cb90(UnkType_1106cb90** Object, int Value)
{
    UnkType_1106cb90* Created;

    Created = new UnkType_1106cb90;
    if ( Created == 0 )
    {
        return -1;
    }
    if ( Created->VirtualSlot5(Value) == 0 )
    {
        delete Created;
        return -1;
    }
    if ( Created->Unk_1106ca30(Value) == 0 )
    {
        delete Created;
        return -1;
    }
    *Object = Created;
    return 0;
}
