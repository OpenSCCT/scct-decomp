/* Work item 0290: RVA 0x768c0 and 0x76950. Class names are neutral
   (UnnamedClass_768c0 etc.): no vtable labels or strings identify them. */
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;

class FArray
{
public:
    INT Add(INT Count, INT ElementSize);
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector& V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator-(const FVector& V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(const FVector& V, FLOAT InW) : FVector(V.X, V.Y, V.Z), W(InW) {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};

struct FMatrix
{
    FPlane TransformFPlane(const FPlane& P) const;
    FLOAT M[4][4];
};

struct UnnamedSlot_768c0
{
    char Pad0[0x34];
    INT Handle;                 /* 0x34 */
    char Pad38[0x84 - 0x38];
    FLOAT Scale84;              /* 0x84 */
    char Pad88[0x90 - 0x88];
    FLOAT Scale90;              /* 0x90 */
    char Pad94[0xa0 - 0x94];
    FLOAT InvZ;                 /* 0xa0 */
    FLOAT InvY;                 /* 0xa4 */
    char Pada8[0xb0 - 0xa8];
    INT HandleB0;               /* 0xb0 */
    char Padb4[0xec - 0xb4];
    FLOAT ScaleEC;              /* 0xec */
    char Padf0[0x11c - 0xf0];
    FLOAT InvX;                 /* 0x11c */
    char Pad120[0x41c - 0x120];
    FPlane Extra;               /* 0x41c */
    INT RefCount;               /* 0x42c */
};

struct UnnamedState_768c0
{
    char Pad0[0x78];
    FMatrix Matrix;             /* 0x78 */
    char PadB8[0x534 - 0xb8];
    UnnamedSlot_768c0* Slots[8]; /* 0x534 */
    INT NumSlots;               /* 0x554 */
};

struct UnnamedOwner_768c0;

class UnnamedObject_768c0
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0C();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1C();
    virtual void Refresh(INT A, INT B, INT C, INT D);   /* slot 0x20 */
    char Pad4[0x10c - 4];
    struct UnnamedOwner_768c0* Owner;    /* 0x10c */
    char Pad110[0x2af10 - 0x110];
    UnnamedState_768c0* State;  /* 0x2af10 */
    char Pad2af14[0x2b348 - 0x2af14];
    FArray FreeSlots;           /* 0x2b348 */
};

void __stdcall ReleaseSlots_768c0(UnnamedObject_768c0* Obj)
{
    for (INT i = 0; i < 8; i++)
    {
        Obj->State->Slots[i]->RefCount--;
        UnnamedSlot_768c0* Slot = Obj->State->Slots[i];
        if (Slot->RefCount == 0)
        {
            INT Index = Obj->FreeSlots.Add(1, sizeof(UnnamedSlot_768c0*));
            ((UnnamedSlot_768c0**)Obj->FreeSlots.Data)[Index] = Slot;
        }
        Obj->State->Slots[i] = 0;
    }
    Obj->State->NumSlots = 0;
    Obj->Refresh(1, 1, 1, 1);
}

/* RVA 0x76950: link-time code generation gives this a custom convention:
   List arrives in EAX, the unused this (caller's this+0x30) and Obj on the
   stack (ret 8). Near miss: the FPlane argument for TransformFPlane is built
   with integer moves for all of X/Y/Z where retail copies Y/Z through the x87
   stack, so the scheduling there and a register swap afterwards differ. */
class UnnamedHandleSource_76950
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0C();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1C();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2C();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3C();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4C();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5C();
    virtual void V60(); virtual void V64(); virtual void V68(); virtual void V6C();
    virtual void V70(); virtual void V74(); virtual void V78(); virtual void V7C();
    virtual void V80(); virtual void V84(); virtual void V88();
    virtual INT GetHandleKey();                                   /* 0x8c */
    virtual UnnamedHandleSource_76950* Find(INT A, INT B, struct UnnamedOwner_768c0* Owner); /* 0x90 */
};

struct UnnamedOwner_768c0
{
    char Pad0[0x130];
    INT Key130;
    INT Key134;
};

struct UnnamedLinkTarget_76950
{
    char Pad0[0x34c];
    UnnamedHandleSource_76950* Source;   /* 0x34c */
};

struct UnnamedInfo_76950
{
    char Pad0[0x80];
    FVector Location;           /* 0x80 */
    char Pad8c[0x174 - 0x8c];
    FLOAT Size;                 /* 0x174 */
    FLOAT Height;               /* 0x178 */
    char Pad17c[0x1a0 - 0x17c];
    UnnamedLinkTarget_76950* Link; /* 0x1a0 */
};

struct UnnamedEntry_76950
{
    UnnamedInfo_76950* Info;
};

struct UnnamedList_76950
{
    UnnamedEntry_76950* Entry;
    UnnamedList_76950* Next;
};

INT __stdcall MakeHandle_620f0(UnnamedObject_768c0* Obj, INT Key);

struct UnnamedHelper_76950
{
    void SetupSlots(UnnamedObject_768c0* Obj, UnnamedList_76950* List);
};

void UnnamedHelper_76950::SetupSlots(UnnamedObject_768c0* Obj, UnnamedList_76950* List)
{
    INT Handle = Obj->State->Slots[0]->Handle;
    if (Handle == 0)
    {
        Handle = MakeHandle_620f0(Obj,
            List->Entry->Info->Link->Source->Find(Obj->Owner->Key130, Obj->Owner->Key134, Obj->Owner)->GetHandleKey());
        Obj->State->Slots[0]->Handle = Handle;
    }
    Obj->State->NumSlots = 0;
    for (; List; List = List->Next)
    {
        if (Obj->State->NumSlots >= 8)
            break;
        UnnamedSlot_768c0* Slot = Obj->State->Slots[Obj->State->NumSlots];
        UnnamedEntry_76950* Entry = List->Entry;
        FLOAT Scale = 1.f / Entry->Info->Size;
        FVector Projected = Obj->State->Matrix.TransformFPlane(FPlane(Entry->Info->Location, 1.f));
        FVector Scaled = Projected * Scale;
        Slot->Scale84 = Scale;
        Slot->HandleB0 = Handle;
        Slot->Handle = Handle;
        Slot->Scale90 = Scale;
        Slot->ScaleEC = Scale;
        FVector Inv = FVector(1.f, 1.f, 1.f) - Scaled;
        Slot->InvZ = Inv.Z;
        Slot->InvY = Inv.Y;
        Slot->InvX = Inv.X;
        Slot->Extra = FPlane(0.f, Entry->Info->Height, 0.f, 0.f);
        Obj->State->NumSlots++;
    }
}

// Scaffolding for the link, not part of the unit: retail's caller at 0x621b0
// is a thiscall member passing this+0x30, this, and the list in EAX.
struct UnnamedCaller_621b0
{
    char Pad0[0x30];
    UnnamedHelper_76950 Helper;
    void Setup(UnnamedList_76950* List);
};
void UnnamedCaller_621b0::Setup(UnnamedList_76950* List)
{
    Helper.SetupSlots((UnnamedObject_768c0*)this, List);
}
void Driver_76950(UnnamedCaller_621b0* C, UnnamedList_76950* List)
{
    C->Setup(List);
}
