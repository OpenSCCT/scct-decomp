// campaign_leaf_768c90.cpp -- one function at file offset 0x768c90, preferred VA 0x11068c90. It
// allocates a 0x30-byte object through the allocator at VA 0x1105ee10 and constructs it (the base
// constructor at VA 0x1105ee30, the vtable at VA 0x11176730, the words from 0x24 to 0x2c cleared
// and the function at VA 0x11068580 stored at 0x20). It returns -1 when that fails or
// when the object's sixth virtual method rejects the second argument (deleting the object through
// its virtual destructor); otherwise it stores the fourth argument at 0x24 and the word at 0x4 of
// the third at 0x2c, stores the object through the first argument and returns 0. The class and
// function names are invented; the offsets and the addresses are the binary's.

void Unk_11068580(void* Object);

struct UnkType_11068c90_Record
{
    int unk_0;
    int unk_4;
};

class UnkType_11068c90_Base
{
public:
    static void* operator new(unsigned int Size);

    UnkType_11068c90_Base();

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
    virtual ~UnkType_11068c90_Base();

    int unk_4;
    int unk_8;
    unsigned char unk_c[0x20 - 0xc];
    void (*unk_20)(void* Object);
};

class UnkType_11068c90 : public UnkType_11068c90_Base
{
public:
    UnkType_11068c90()
    {
        unk_24 = 0;
        unk_2c = 0;
        unk_28 = 0;
        unk_20 = Unk_11068580;
    }

    virtual int VirtualSlot5(int Value);
    virtual ~UnkType_11068c90();

    int unk_24;
    int unk_28;
    int unk_2c;
};

// Unk_11068c90
int Unk_11068c90(UnkType_11068c90** Object, int Value, UnkType_11068c90_Record* Record, int Extra)
{
    UnkType_11068c90* Created;

    Created = new UnkType_11068c90;
    if ( Created == 0 )
    {
        return -1;
    }
    if ( Created->VirtualSlot5(Value) == 0 )
    {
        delete Created;
        return -1;
    }
    Created->unk_24 = Extra;
    Created->unk_2c = Record->unk_4;
    *Object = Created;
    return 0;
}
