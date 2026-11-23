// campaign_leaf_60dc30.cpp -- thiscall method at VA 0x10f0dc30: calls the method at VA 0x10f09950
// with the addresses of five locals; when that returns true, passes them to virtual slot 16 (vtable
// offset 0x40) of the object at 0x14 and returns true, otherwise returns false. Before the call
// Fourth and Fifth are zero-filled. The class, method and member names are invented; the
// offsets and addresses are the binary's.

struct UnkType_10f0dc30_Third
{
    unsigned char unk_00[0x10];
};

extern "C" void* __cdecl memset(void* Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)

class UnkType_10f0dc30_Target
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
    virtual void VirtualSlot16(int First, int Second, UnkType_10f0dc30_Third* Third, char* Fourth,
                               char* Fifth);
};

class UnkType_10f0dc30
{
public:
    bool Unk_10f0dc30();
    bool Unk_10f09950(int* First, int* Second, UnkType_10f0dc30_Third* Third, char* Fourth,
                      char* Fifth);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0dc30_Target* unk_14;
};

// UnkType_10f0dc30::Unk_10f0dc30
bool UnkType_10f0dc30::Unk_10f0dc30()
{
    int First;
    int Second;
    UnkType_10f0dc30_Third Third;
    char Fourth[0x81];
    char Fifth[0x81];

    memset(Fourth, 0, sizeof(Fourth));
    memset(Fifth, 0, sizeof(Fifth));

    if ( Unk_10f09950(&First, &Second, &Third, Fourth, Fifth) )
    {
        unk_14->VirtualSlot16(First, Second, &Third, Fourth, Fifth);
        return true;
    }
    return false;
}
