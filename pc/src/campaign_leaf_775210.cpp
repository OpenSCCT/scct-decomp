// campaign_leaf_775210.cpp -- one function at file offset 0x775210, preferred VA 0x11075210. It
// allocates a 0x34-byte object through the allocator at VA 0x1105ee10 and constructs it (the base
// constructor at VA 0x1106f8b0, the vtable at VA 0x11177500, the words from 0x24 to 0x30 cleared
// and the function at VA 0x11074fb0 stored at 0x20), and stores the third argument at 0x4. It
// returns -1 when that fails or when the object's sixth virtual method rejects the second argument
// (deleting the object through its virtual destructor), and otherwise stores the object through
// the first argument and returns 0. The class and function names are invented; the offsets and
// the addresses are the binary's.

void Unk_11074fb0(void* Object);

class UnkType_11075210_Base
{
public:
    static void* operator new(unsigned int Size);

    UnkType_11075210_Base();

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
    virtual ~UnkType_11075210_Base();

    int unk_4;
    unsigned char unk_8[0x20 - 0x8];
    void (*unk_20)(void* Object);
};

class UnkType_11075210 : public UnkType_11075210_Base
{
public:
    UnkType_11075210()
    {
        unk_24 = 0;
        unk_30 = 0;
        unk_28 = 0;
        unk_2c = 0;
        unk_20 = Unk_11074fb0;
    }

    virtual int VirtualSlot5(int Value);
    virtual ~UnkType_11075210();

    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
};

// Unk_11075210
int Unk_11075210(UnkType_11075210** Object, int Value, int Extra)
{
    UnkType_11075210* Created;

    Created = new UnkType_11075210;
    if ( Created == 0 )
    {
        return -1;
    }
    Created->unk_4 = Extra;
    if ( Created->VirtualSlot5(Value) == 0 )
    {
        delete Created;
        return -1;
    }
    *Object = Created;
    return 0;
}
