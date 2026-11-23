// campaign_leaf_60d5b0.cpp -- thiscall method at VA 0x10f0d5b0: calls the method at VA 0x10f08ba0
// with the addresses of five locals; when that returns true, passes them to virtual slot 5 (vtable
// offset 0x14) of the object at 0x14 and returns true, otherwise returns false. Before the call
// Third is zero-filled. The class, method and member names are invented; the offsets and addresses
// are the binary's.

extern "C" void* __cdecl memset(void* Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)

class UnkType_10f0d5b0_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int First, int Second, char* Third, int Fourth, int Fifth);
};

class UnkType_10f0d5b0
{
public:
    bool Unk_10f0d5b0();
    bool Unk_10f08ba0(int* First, int* Second, char* Third, int* Fourth, int* Fifth);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0d5b0_Target* unk_14;
};

// UnkType_10f0d5b0::Unk_10f0d5b0
bool UnkType_10f0d5b0::Unk_10f0d5b0()
{
    int First;
    int Second;
    char Third[0x81];
    int Fourth;
    int Fifth;

    memset(Third, 0, sizeof(Third));

    if ( Unk_10f08ba0(&First, &Second, Third, &Fourth, &Fifth) )
    {
        unk_14->VirtualSlot5(First, Second, Third, Fourth, Fifth);
        return true;
    }
    return false;
}
