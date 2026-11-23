// campaign_leaf_774f00.cpp -- one function at file offset 0x774f00, preferred VA 0x11074f00. It
// allocates a 0x74-byte object through the allocator at VA 0x1105ee10 and constructs it with the
// constructor at VA 0x11074830, and stores the third argument at 0x4. It returns -1 when that
// fails, or when the object's sixth virtual method rejects the second argument or its method at
// VA 0x11074890 fails (deleting the object through its virtual destructor); otherwise it stores
// the object through the first argument and returns 0. The class and function names are
// invented; the offsets and the addresses are the binary's.

class UnkType_11074f00
{
public:
    static void* operator new(unsigned int Size);

    UnkType_11074f00();

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
    virtual ~UnkType_11074f00();

    int Unk_11074890();

    int unk_4;
    unsigned char unk_8[0x74 - 0x8];
};

// Unk_11074f00
int Unk_11074f00(UnkType_11074f00** Object, int Value, int Extra)
{
    UnkType_11074f00* Created;

    Created = new UnkType_11074f00;
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
    if ( Created->Unk_11074890() == 0 )
    {
        delete Created;
        return -1;
    }
    *Object = Created;
    return 0;
}
