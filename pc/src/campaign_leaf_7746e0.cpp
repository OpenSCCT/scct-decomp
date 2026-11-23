// campaign_leaf_7746e0.cpp -- one function at file offset 0x7746e0, preferred VA 0x110746e0. It
// allocates a 0x318-byte object through the allocator at VA 0x1105ee10 and constructs it with the
// constructor at VA 0x110734d0; it returns -1 when that fails. It stores the third argument at
// 0x4 and returns -1 when the object's sixth virtual method rejects the second argument (deleting
// the object through its virtual destructor); otherwise it stores the object through the first
// argument, stores the result of the function at VA 0x1105a980 in the global at VA 0x1132eb50 and
// returns 0. The class and function names are invented; the offsets and the addresses are the
// binary's.

#include "campaign_global_1132eb50.h"

int Unk_1105a980();

class UnkType_110746e0
{
public:
    static void* operator new(unsigned int Size);

    UnkType_110746e0();

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
    virtual ~UnkType_110746e0();

    int unk_4;
    unsigned char unk_8[0x318 - 0x8];
};

// Unk_110746e0
int Unk_110746e0(UnkType_110746e0** Object, int Value, int Owner)
{
    UnkType_110746e0* Created;

    Created = new UnkType_110746e0;
    if ( Created == 0 )
    {
        return -1;
    }
    Created->unk_4 = Owner;
    if ( Created->VirtualSlot5(Value) == 0 )
    {
        delete Created;
        return -1;
    }
    *Object = Created;
    GUnk_1132eb50 = Unk_1105a980();
    return 0;
}
