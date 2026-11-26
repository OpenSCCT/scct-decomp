// Work item 0320: UWindowsViewport methods (RVA 0x10aaa0-0x10aee3).
// Names follow Unreal Engine 2 (UWindowsViewport vtable slots 10 and 37);
// fields without evidence for a name keep their offset.
#include "versus_render_device.h"

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef double DOUBLE;

class UObject;

class FArchive
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual FArchive &operator<<(UObject *&Res);
};

double appSeconds();

// Audio subsystem: GetViewport is slot 49, SetViewport slot 24.
class UAudioSubsystem
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void SetViewport(class UViewport *InViewport);
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    virtual void Slot37();
    virtual void Slot38();
    virtual void Slot39();
    virtual void Slot40();
    virtual void Slot41();
    virtual void Slot42();
    virtual void Slot43();
    virtual void Slot44();
    virtual void Slot45();
    virtual void Slot46();
    virtual void Slot47();
    virtual void Slot48();
    virtual class UViewport *GetViewport();
};

class UDeletable
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual ~UDeletable();
};

class UEngine
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void NotifyViewport(class UViewport *Viewport, INT Code, INT A, INT B);
    BYTE Pad04[0x30];
    UAudioSubsystem *Audio;        // 0x34
    URenderDevice *GRenDev;        // 0x38
};

class UClient
{
public:
    BYTE Pad00[0x28];
    UEngine *Engine;               // 0x28
};

class AActorLike
{
public:
    BYTE Pad00[0x1a4];
    void *XLevel;                  // 0x1a4
    BYTE Pad1a8[0x4a4 - 0x1a8];
    INT Field4a4;                  // 0x4a4
};

extern INT GIsEditorLike;          // 0x10c9690c
void __stdcall DestroyActorLike_10a1a790(void *Level, AActorLike *Actor, INT bNetForce);

class FArray
{
public:
    void Remove(INT Index, INT Count, INT ElementSize);
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
    __declspec(noinline) INT RemoveItem(const T &Item)
    {
        INT OriginalNum = ArrayNum;
        for (INT Index = 0; Index < ArrayNum; Index++)
            if ((*this)(Index) == Item)
                Remove(Index--);
        return OriginalNum - ArrayNum;
    }
};

class UObject
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Destroy();
    virtual void Serialize(FArchive &Ar);
    INT Index;                     // 0x04
    void *HashNext;                // 0x08
    void *StateFrame;              // 0x0c
    void *_Linker;                 // 0x10
    INT _LinkerIndex;              // 0x14
    UClient *Outer;                // 0x18
    DWORD ObjectFlags;             // 0x1c
    INT Name;                      // 0x20
    void *Class;                   // 0x24
};

class UViewport : public UObject
{
public:
};

class UWindowsViewport : public UViewport
{
public:
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    virtual INT SetField_c8(INT New);
    virtual void Slot38();
    virtual void Slot39();
    virtual void Slot40();
    virtual void Slot41();
    virtual void Slot42();
    virtual void Slot43Call();

    void Serialize(FArchive &Ar);
    void Destroy();
    UBOOL Lock(BYTE *HitData, INT *HitSize);

    BYTE Pad28[0x30 - 0x28];
    AActorLike *Actor;             // 0x30
    UDeletable *Obj34;             // 0x34
    BYTE Pad38[0x68 - 0x38];
    UDeletable *Obj68;             // 0x68
    UDeletable *Obj6c;             // 0x6c
    URenderDevice *RenDev;         // 0x70
    BYTE Pad74[0x8c - 0x74];
    UObject *Obj8c;                // 0x8c
    BYTE Pad90[0xbc - 0x90];
    INT LockCount;                 // 0xbc
    BYTE Padc0[0xc8 - 0xc0];
    INT Field_c8;                  // 0xc8
    BYTE Padcc[0x130 - 0xcc];
    DOUBLE LastLockTime;           // 0x130
    BYTE Pad138[0x140 - 0x138];
    FRenderInterface *RenderInterface; // 0x140, returned by the render device's Lock
    BYTE Pad144[0x148 - 0x144];
    BYTE bLocked;                  // 0x148
    BYTE Pad149[0x154 - 0x149];
    INT bHitTesting;               // 0x154
};

void UWindowsViewport::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << (UObject *&)Obj34;
    Ar << Obj8c;
    Ar << (UObject *&)Obj68 << (UObject *&)RenDev << (UObject *&)Obj6c;
}

INT UWindowsViewport::SetField_c8(INT New)
{
    INT Old = Field_c8;
    Field_c8 = New;
    if (GIsEditorLike)
    {
        if (New)
        {
            if (!Old)
                Outer->Engine->NotifyViewport(this, 8, 0, 0);
        }
        else if (Old)
            Outer->Engine->NotifyViewport(this, 0x10, 0, 0);
    }
    return Old;
}

class UClientViewports
{
public:
    BYTE Pad00[0x2c];
    TArray<UViewport *> Viewports; // 0x2c
};

void UWindowsViewport::Destroy()
{
    UAudioSubsystem *Audio = Outer->Engine->Audio;
    if (Audio && Audio->GetViewport() == this)
        Outer->Engine->Audio->SetViewport(0);
    Slot43Call();
    delete Obj6c;
    delete Obj34;
    delete Obj68;
    Obj68 = 0;
    if (RenDev)
    {
        RenDev->UnSetRes(this);
        if (RenDev != Outer->Engine->GRenDev)
            delete RenDev;
        RenDev = 0;
    }
    UViewport *This = this;
    ((UClientViewports *)Outer)->Viewports.RemoveItem(This);
    if (GIsEditorLike && Actor)
    {
        void *Level = Actor->XLevel;
        Actor->Field4a4 = 0;
        DestroyActorLike_10a1a790(Level, Actor, 1);
        Actor = 0;
    }
    UObject::Destroy();
}

UBOOL UWindowsViewport::Lock(BYTE *HitData, INT *HitSize)
{
    LastLockTime = appSeconds();
    bHitTesting = HitData != 0;
    LockCount++;
    RenderInterface = RenDev->Lock(this, HitData, HitSize);
    bLocked = 1;
    return RenderInterface != 0;
}

// Scaffolding for the link, not part of the unit: the local object emits the
// vtable so the virtuals keep their ordinary thiscall convention.
// RemoveItem is noinline because retail keeps it out of line (0x10bd60).
void Escape(void *);
void Driver_10adb0() { UWindowsViewport V; Escape(&V); V.Destroy(); }
