// campaign_leaf_60e960.cpp -- thiscall method at VA 0x10f0e960: calls the method at VA 0x10f0bb60
// with the addresses of three locals; when that returns true, passes them to virtual slot 36
// (vtable offset 0x90) of the object at 0x14 and returns true, otherwise returns false. Before the
// call Third is zero-filled. The class, method and member names are invented; the offsets and
// addresses are the binary's.

extern "C" void* __cdecl memset(void* Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)

class UnkType_10f0e960_Target
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
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36(int First, int Second, char* Third);
};

class UnkType_10f0e960
{
public:
    bool Unk_10f0e960();
    bool Unk_10f0bb60(int* First, int* Second, char* Third);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0e960_Target* unk_14;
};

// UnkType_10f0e960::Unk_10f0e960
bool UnkType_10f0e960::Unk_10f0e960()
{
    int First;
    int Second;
    char Third[0x81];

    memset(Third, 0, sizeof(Third));

    if ( Unk_10f0bb60(&First, &Second, Third) )
    {
        unk_14->VirtualSlot36(First, Second, Third);
        return true;
    }
    return false;
}
