// campaign_leaf_264790.cpp -- a member function at VA 0x10b64790 taking an event: it returns true
// when the member at VA 0x10b65920 handles the event. Otherwise, when the event's int at 0x04 equals
// the global at VA 0x1122e428 it calls virtual slot 20 of the object the pointer at 0x14 refers to,
// and when it equals the global at VA 0x1122e42c it calls its own virtual slot 22; it stores in the
// byte at 0x14 of the object at 0x14 whether either happened and returns that. The class, method,
// member, parameter and global names are invented; the offsets, addresses and slots are the
// binary's.

#include "campaign_global_1122e428.h"
#include "campaign_global_1122e42c.h"

class UnkType_10b64790_Event
{
public:
    int unk_00;
    int unk_04;
};

class UnkType_10b64790_Owner
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

private:
    unsigned char unk_04[0x14 - 0x04];

public:
    bool unk_14;
};

class UnkType_10b64790
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

    bool Unk_10b65920(UnkType_10b64790_Event* Event);
    bool Unk_10b64790(UnkType_10b64790_Event* Event);

private:
    unsigned char unk_04[0x14 - 0x04];
    UnkType_10b64790_Owner* unk_14;
};

// UnkType_10b64790::Unk_10b64790
bool UnkType_10b64790::Unk_10b64790(UnkType_10b64790_Event* Event)
{
    if ( Unk_10b65920(Event) )
    {
        return true;
    }
    bool Result = false;
    if ( Event->unk_04 == GUnk_1122e428 )
    {
        unk_14->VirtualSlot20();
        Result = true;
    }
    else if ( Event->unk_04 == GUnk_1122e42c )
    {
        VirtualSlot22();
        Result = true;
    }
    unk_14->unk_14 = Result;
    return Result;
}
