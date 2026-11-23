// campaign_leaf_139300.cpp -- one function at file offset 0x139300, preferred VA 0x10a39300.
// guess: while the global at VA 0x112327b4 is set and it holds an object at offset 0x30, clears
// that object's member at 0x394, has the object's level (member at 0x7c) handle the object's
// member at 0x2b4 and, unless its kind at 0x428 is 20 or 21, the object itself (virtual slot 35,
// with true), and forgets the object. It then runs its base's method at VA 0x10cd8ea0.
// The class, member and callee names are invented; the offset and the bytes are the binary's.

#include "campaign_global_112327b4.h"

class UnkType_10a39300_Actor;

class UnkType_10a39300_Level
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
    virtual void VirtualSlot35(UnkType_10a39300_Actor* Actor, int bFlag);
};

class UnkType_10a39300_Actor
{
public:
    unsigned char unk_0[0x7c];
    UnkType_10a39300_Level* unk_7c;
    unsigned char unk_80[0x2b4 - 0x80];
    UnkType_10a39300_Actor* unk_2b4;
    unsigned char unk_2b8[0x394 - 0x2b8];
    int unk_394;
    unsigned char unk_398[0x428 - 0x398];
    int unk_428;
};

class UnkType_10a39300_Base
{
public:
    void Unk_10cd8ea0();
};

class UnkType_10a39300 : public UnkType_10a39300_Base
{
public:
    unsigned char unk_0[0x30];
    UnkType_10a39300_Actor* unk_30;

    void Unk_10a39300();
};

// UnkType_10a39300::Unk_10a39300
void UnkType_10a39300::Unk_10a39300()
{
    if ( GUnk_112327b4 && unk_30 )
    {
        UnkType_10a39300_Level* Level = unk_30->unk_7c;
        unk_30->unk_394 = 0;
        if ( unk_30->unk_2b4 )
        {
            Level->VirtualSlot35(unk_30->unk_2b4, 1);
        }
        if ( unk_30->unk_428 != 20 && unk_30->unk_428 != 21 )
        {
            Level->VirtualSlot35(unk_30, 1);
        }
        unk_30 = 0;
    }
    UnkType_10a39300_Base::Unk_10cd8ea0();
}
