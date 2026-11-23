// campaign_leaf_768d40.cpp -- one function at file offset 0x768d40, preferred VA 0x11068d40. It
// allocates a 0x5c-byte object through the allocator at VA 0x1105ee10 and constructs it with the
// constructor at VA 0x11068610; it returns -1 when that fails or when the object's sixth virtual
// method rejects the second argument (deleting the object through its virtual destructor). It
// otherwise stores the fourth argument at 0x24 and the word at 0x4 of the third at 0x38, stores
// the object through the first argument and returns 0. The class and function names are invented;
// the offsets and the addresses are the binary's.

struct UnkType_11068d40_Record
{
    int unk_0;
    int unk_4;
};

class UnkType_11068d40
{
public:
    static void* operator new(unsigned int Size);

    UnkType_11068d40();

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
    virtual ~UnkType_11068d40();

    unsigned char unk_4[0x24 - 0x4];
    int unk_24;
    unsigned char unk_28[0x38 - 0x28];
    int unk_38;
    unsigned char unk_3c[0x5c - 0x3c];
};

// Unk_11068d40
int Unk_11068d40(UnkType_11068d40** Object, int Value, UnkType_11068d40_Record* Record, int Extra)
{
    UnkType_11068d40* Created;

    Created = new UnkType_11068d40;
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
    Created->unk_38 = Record->unk_4;
    *Object = Created;
    return 0;
}
