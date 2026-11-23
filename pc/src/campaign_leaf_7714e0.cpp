// campaign_leaf_7714e0.cpp -- one function at file offset 0x7714e0, preferred VA 0x110714e0. It
// allocates a 0x30-byte object through the allocator at VA 0x1105ee10 and constructs it in line
// (base constructor at VA 0x1105ee30, vtable at VA 0x11177138, words 0x20 to 0x2c zeroed); it
// returns -1 when that fails or when the object's sixth virtual method rejects the second argument
// (deleting the object through its virtual destructor), and otherwise stores the object through
// the first argument and returns 0. The class and function names are invented; the offsets and
// the addresses are the binary's.

class UnkType_110714e0_Base
{
public:
    UnkType_110714e0_Base();

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
    virtual ~UnkType_110714e0_Base();

    unsigned char unk_4[0x20 - 0x4];
};

class UnkType_110714e0 : public UnkType_110714e0_Base
{
public:
    static void* operator new(unsigned int Size);

    UnkType_110714e0()
    {
        unk_20 = 0;
        unk_24 = 0;
        unk_28 = 0;
        unk_2c = 0;
    }

    virtual ~UnkType_110714e0();

    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
};

// Unk_110714e0
int Unk_110714e0(UnkType_110714e0** Object, int Value)
{
    UnkType_110714e0* Created;

    Created = new UnkType_110714e0;
    if ( Created == 0 )
    {
        return -1;
    }
    if ( Created->VirtualSlot5(Value) == 0 )
    {
        delete Created;
        return -1;
    }
    *Object = Created;
    return 0;
}
