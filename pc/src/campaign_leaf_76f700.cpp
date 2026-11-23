// campaign_leaf_76f700.cpp -- one function at file offset 0x76f700, preferred VA 0x1106f700. It
// allocates a 0x48-byte object through the allocator at VA 0x1105ee10 and constructs it (the base
// constructor at VA 0x11064ff0, the vtable at VA 0x11176e40, the words at 0x24 and 0x40 cleared and
// the function at VA 0x1106f500 stored at 0x20), and stores the third argument at 0x4. It returns
// -1 when that fails or when the object's nineteenth virtual method rejects the second and third
// arguments (deleting the object through its virtual destructor), and otherwise stores the object
// through the first argument and returns 0. The class and function names are invented; the
// offsets and the addresses are the binary's.

void Unk_1106f500(void* Object);

class UnkType_1106f700_Base
{
public:
    static void* operator new(unsigned int Size);

    UnkType_1106f700_Base();

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
    virtual ~UnkType_1106f700_Base();
    virtual void VirtualSlot17();
    virtual int VirtualSlot18(int Value, int Extra);

    int unk_4;
    unsigned char unk_8[0x20 - 0x8];
    void (*unk_20)(void* Object);
    int unk_24;
};

class UnkType_1106f700 : public UnkType_1106f700_Base
{
public:
    UnkType_1106f700()
    {
        unk_24 = 0;
        unk_20 = Unk_1106f500;
        unk_40 = 0;
    }

    virtual ~UnkType_1106f700();
    virtual int VirtualSlot18(int Value, int Extra);

    unsigned char unk_28[0x40 - 0x28];
    int unk_40;
    int unk_44;
};

// Unk_1106f700
int Unk_1106f700(UnkType_1106f700** Object, int Value, int Extra)
{
    UnkType_1106f700* Created;

    Created = new UnkType_1106f700;
    if ( Created == 0 )
    {
        return -1;
    }
    Created->unk_4 = Extra;
    if ( Created->VirtualSlot18(Value, Extra) == 0 )
    {
        delete Created;
        return -1;
    }
    *Object = Created;
    return 0;
}
