// campaign_leaf_090b80.cpp -- method at VA 0x10990b80: when the global at VA 0x11232794 is set and
// the pointer at 0x78 is set, sets the global at VA 0x11232790 and bit 2 of the flags at 0x4a4 of
// the object at 0x78, calls virtual slot 4 with the result of the method at VA 0x10cd92d0 (called
// with the global at VA 0x111fa120 and three zeros), then clears the bit and the global again. The
// class, member and method names are invented; the offsets, the slot and the addresses are the
// binary's.

#include "campaign_global_11232790.h"
#include "campaign_global_11232794.h"
#include "campaign_global_111fa120.h"

class UnkType_10990b80_Other
{
public:
    unsigned char unk_00[0x4a4];
    unsigned int unk_4a4;
};

class UnkType_10990b80
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(int Value);

    void Unk_10990b80();
    int Unk_10cd92d0(int Name, int Arg1, int Arg2, int Arg3);

private:
    unsigned char unk_04[0x78 - 0x04];
    UnkType_10990b80_Other* unk_78;
};

// UnkType_10990b80::Unk_10990b80
void UnkType_10990b80::Unk_10990b80()
{
    if ( GUnk_11232794 && unk_78 )
    {
        GUnk_11232790 = 1;
        unk_78->unk_4a4 |= 2;
        VirtualSlot4(Unk_10cd92d0(GUnk_111fa120, 0, 0, 0));
        unk_78->unk_4a4 &= ~2;
        GUnk_11232790 = 0;
    }
}
