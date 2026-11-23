// campaign_leaf_60d630.cpp -- thiscall method at VA 0x10f0d630: calls the method at VA 0x10f08970
// with the addresses of five locals; when that returns true, passes them to virtual slot 4 (vtable
// offset 0x10) of the object at 0x14 and returns true, otherwise returns false. Before the call
// Third is zero-filled. The class, method and member names are invented; the offsets and addresses
// are the binary's.

extern "C" void* __cdecl memset(void* Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)

class UnkType_10f0d630_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(int First, int Second, char* Third, int Fourth, int Fifth);
};

class UnkType_10f0d630
{
public:
    bool Unk_10f0d630();
    bool Unk_10f08970(int* First, int* Second, char* Third, int* Fourth, int* Fifth);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0d630_Target* unk_14;
};

// UnkType_10f0d630::Unk_10f0d630
bool UnkType_10f0d630::Unk_10f0d630()
{
    int First;
    int Second;
    char Third[0x81];
    int Fourth;
    int Fifth;

    memset(Third, 0, sizeof(Third));

    if ( Unk_10f08970(&First, &Second, Third, &Fourth, &Fifth) )
    {
        unk_14->VirtualSlot4(First, Second, Third, Fourth, Fifth);
        return true;
    }
    return false;
}
