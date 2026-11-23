// campaign_leaf_091550.cpp -- method at VA 0x10991550 taking one argument: stores it at 0x394 and
// passes it to the function at VA 0x10990c40; when that returns an object, calls virtual slot 4
// with the result of the method at VA 0x10cd92d0 (called with the global at VA 0x111fa058 and three
// zeros), then converts the integers at 0x8c and 0x90 of the object to the floats at 0x3d0 and
// 0x3d4. The class, member and method names are invented; the offsets, the slot and the addresses
// are the binary's.

#include "campaign_global_111fa058.h"

class UnkType_10991550_Info
{
public:
    unsigned char unk_00[0x8c];
    int unk_8c;
    int unk_90;
};

UnkType_10991550_Info* Unk_10990c40(int Key);

class UnkType_10991550
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(int Value);

    void Unk_10991550(int Key);
    int Unk_10cd92d0(int Name, int Arg1, int Arg2, int Arg3);

private:
    unsigned char unk_04[0x394 - 0x04];
    int unk_394;
    unsigned char unk_398[0x3d0 - 0x398];
    float unk_3d0;
    float unk_3d4;
};

// UnkType_10991550::Unk_10991550
void UnkType_10991550::Unk_10991550(int Key)
{
    unk_394 = Key;
    UnkType_10991550_Info* Info = Unk_10990c40(Key);
    if ( Info )
    {
        VirtualSlot4(Unk_10cd92d0(GUnk_111fa058, 0, 0, 0));
        unk_3d0 = Info->unk_8c;
        unk_3d4 = Info->unk_90;
    }
}
