// campaign_leaf_4f7a80.cpp -- method at VA 0x10df7a80: when virtual slot 1 of its argument returns
// 5 and the pointer selected by the index from the function at VA 0x10d98f30 (the global at VA
// 0x1131b3bc for index zero, else an entry of the array at VA 0x1131b3b8) is this object, it clears
// that pointer. The class and method names are invented; the slot, the value and the addresses are
// the binary's.

#include "campaign_global_1131b3b8.h"
#include "campaign_global_1131b3bc.h"

class UnkType_10df7a80_Arg
{
public:
    virtual void VirtualSlot0();
    virtual int VirtualSlot1();
};

int Unk_10d98f30();

class UnkType_10df7a80
{
public:
    void Unk_10df7a80(UnkType_10df7a80_Arg* Arg);
};

// UnkType_10df7a80::Unk_10df7a80
void UnkType_10df7a80::Unk_10df7a80(UnkType_10df7a80_Arg* Arg)
{
    if ( Arg->VirtualSlot1() == 5 )
    {
        int Index = Unk_10d98f30();
        void** Slot = Index == 0 ? &GUnk_1131b3bc : &GUnk_1131b3b8[Index];
        if ( this == *Slot )
        {
            Index = Unk_10d98f30();
            if ( Index == 0 )
            {
                GUnk_1131b3bc = 0;
            }
            else
            {
                GUnk_1131b3b8[Index] = 0;
            }
        }
    }
}
