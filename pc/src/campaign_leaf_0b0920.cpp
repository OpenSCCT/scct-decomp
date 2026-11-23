// campaign_leaf_0b0920.cpp -- method at VA 0x109b0920 taking one argument: sets bit 2 of the flags
// at 0x28; when the object at 0x2b4 is set and either has no object at 0x0c or that object has bit
// 0x1000000 of its 64-bit flags at 0x20 set, hands the argument on to the method at VA 0x1098e5c0
// of the object at 0x2b4; otherwise, unless the object at 0x0c exists with that bit clear, calls
// virtual slot 4 with the result of the method at VA 0x10cd92d0 (called with the global at VA
// 0x111f9fa0, 0, a one-word record holding the argument, and 0). The class, member and method names
// are invented; the offsets, the slot and the addresses are the binary's.

#include "campaign_global_111f9fa0.h"

class UnkType_109b0920_Class
{
public:
    unsigned char unk_00[0x20];
    unsigned __int64 unk_20;
};

class UnkType_109b0920_Other
{
public:
    void Unk_1098e5c0(int Value);

    unsigned char unk_00[0x0c];
    UnkType_109b0920_Class* unk_0c;
};

struct UnkType_109b0920_Parms
{
    int unk_00;
};

class UnkType_109b0920
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(int Value);

    void Unk_109b0920(int Value);
    int Unk_10cd92d0(int Name, int Arg1, void* Parms, int Arg3);

private:
    unsigned char unk_04[0x0c - 0x04];
    UnkType_109b0920_Class* unk_0c;
    unsigned char unk_10[0x28 - 0x10];
    unsigned int unk_28;
    unsigned char unk_2c[0x2b4 - 0x2c];
    UnkType_109b0920_Other* unk_2b4;
};

// UnkType_109b0920::Unk_109b0920
void UnkType_109b0920::Unk_109b0920(int Value)
{
    unk_28 |= 2;
    if ( unk_2b4 && (!unk_2b4->unk_0c || (unk_2b4->unk_0c->unk_20 & 0x1000000)) )
    {
        unk_2b4->Unk_1098e5c0(Value);
        return;
    }
    if ( !unk_0c || (unk_0c->unk_20 & 0x1000000) )
    {
        UnkType_109b0920_Parms Parms;
        Parms.unk_00 = Value;
        VirtualSlot4(Unk_10cd92d0(GUnk_111f9fa0, 0, &Parms, 0));
    }
}
