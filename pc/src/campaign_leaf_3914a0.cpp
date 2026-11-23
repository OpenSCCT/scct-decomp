// campaign_leaf_3914a0.cpp -- one function at file offset 0x3914a0, preferred VA 0x10c914a0. It
// builds two equal rectangles from the origin at (0x11230370, 0x1123036c) and the size (Width,
// Height), and passes the surface at 0x4b8c of the object at 0x1a4 with one, the surface at 0x4b98
// with the other, and 0 to virtual slot 34 of that object's member at 0x4d3c. The class, method,
// member, slot, local and parameter names are invented; the offsets and the bytes are the binary's.

#include "campaign_global_1123036c.h"
#include "campaign_global_11230370.h"
#include "campaign_import_RECT.h"

class UnkType_10c914a0_Device
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
    virtual long __stdcall VirtualSlot34(void* Source, const RECT* SourceRect, void* Dest,
        const RECT* DestRect, int Filter);
};

class UnkType_10c914a0_Owner
{
public:
    unsigned char unk_0[0x4b8c];
    void* unk_4b8c;
    unsigned char unk_4b90[0x8];
    void* unk_4b98;
    unsigned char unk_4b9c[0x1a0];
    UnkType_10c914a0_Device* unk_4d3c;
};

class UnkType_10c914a0
{
public:
    void Unk_10c914a0(int Width, int Height);

    unsigned char unk_0[0x1a4];
    UnkType_10c914a0_Owner* unk_1a4;
};

// UnkType_10c914a0::Unk_10c914a0
void UnkType_10c914a0::Unk_10c914a0(int Width, int Height)
{
    RECT DestRect;
    RECT SourceRect;

    SourceRect.left = GUnk_11230370;
    SourceRect.top = GUnk_1123036c;
    SourceRect.right = GUnk_11230370 + Width;
    SourceRect.bottom = GUnk_1123036c + Height;
    DestRect.left = GUnk_11230370;
    DestRect.top = GUnk_1123036c;
    DestRect.right = GUnk_11230370 + Width;
    DestRect.bottom = GUnk_1123036c + Height;
    unk_1a4->unk_4d3c->VirtualSlot34(unk_1a4->unk_4b8c, &SourceRect, unk_1a4->unk_4b98,
        &DestRect, 0);
}
