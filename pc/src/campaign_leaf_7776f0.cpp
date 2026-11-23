// campaign_leaf_7776f0.cpp -- one function at file offset 0x7776f0, preferred VA 0x110776f0. It
// allocates a 0xe0-byte object through the allocator at VA 0x1105ee10 and constructs it with the
// constructor at VA 0x11075790, stores the third argument at 0x4 and a 0x68-byte block from the
// stdcall function at VA 0x1103c830 at 0x88; it returns -1 when any of that fails or when the
// object's sixth virtual method rejects the second argument (deleting the object through its
// virtual destructor), and otherwise stores the object through the first argument and returns 0.
// The class and function names are invented; the offsets and the addresses are the binary's.

void* __stdcall Unk_1103c830(int Size);

class UnkType_110776f0
{
public:
    static void* operator new(unsigned int Size);

    UnkType_110776f0();

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
    virtual ~UnkType_110776f0();

    int unk_4;
    unsigned char unk_8[0x88 - 0x8];
    void* unk_88;
    unsigned char unk_8c[0xe0 - 0x8c];
};

// Unk_110776f0
int Unk_110776f0(UnkType_110776f0** Object, int Value, int Extra)
{
    UnkType_110776f0* Created;

    Created = new UnkType_110776f0;
    if ( Created == 0 )
    {
        return -1;
    }
    Created->unk_4 = Extra;
    Created->unk_88 = Unk_1103c830(0x68);
    if ( Created->unk_88 == 0 )
    {
        delete Created;
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
