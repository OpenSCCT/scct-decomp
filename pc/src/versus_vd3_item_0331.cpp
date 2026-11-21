// Work item 0331: Versus RVA 0x91680-0x91929.
// AActor collision helpers (link-time code generated) and two controller
// helpers that attach and detach a pawn. Field names are offsets where the
// UE2 name is not certain; the class names follow the vtable labels.

typedef unsigned long DWORD;
typedef int INT;
typedef DWORD UBOOL;
typedef float FLOAT;

struct FName { INT Index; };
struct FVector { FLOAT X, Y, Z; };

class UObject;

// UE2 UStruct: Class at UObject+0x24, SuperField at +0x28.
class UClass
{
public:
    void   *VTable;
    DWORD   Pad04[8];
    UClass *Class;          // 0x24
    UClass *SuperField;     // 0x28
};

class UObject
{
public:
    void   *VTable;
    DWORD   Pad04[8];
    UClass *Class;          // 0x24

    // UObject::IsA, inlined.
    UBOOL IsA(UClass *SomeBase) const
    {
        for (UClass *TempClass = Class; TempClass; TempClass = TempClass->SuperField)
            if (TempClass == SomeBase)
                return 1;
        return 0;
    }
};

// UE2 Cast<T>, inlined; the target class is the PrivateStaticClass at
// retail 0x10cc0a78 (class not identified).
extern UClass UnnamedClass_10cc0a78;
class UnnamedObject_10cc0a78 : public UObject {};
inline UnnamedObject_10cc0a78 *CastUnnamed(UObject *Src)
{
    return (Src && Src->IsA(&UnnamedClass_10cc0a78)) ? (UnnamedObject_10cc0a78 *)Src : 0;
}

class AActor
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual UBOOL IsPlayer() const;                       // slot 24 (+0x60)
    virtual void V25();
    virtual void V26();                                   // slot 26: IsBlockedBy
    virtual void V27(); virtual void V28(); virtual void V29(); virtual void V30();
    virtual void V31(); virtual void V32(); virtual void V33(); virtual void V34();
    virtual void V35(); virtual void V36(); virtual void V37(); virtual void V38();
    virtual void V39(); virtual void V40(); virtual void V41(); virtual void V42();
    virtual void V43(); virtual void V44(); virtual void V45(); virtual void V46();
    virtual void Slot47(AActor *Other, FVector *Value, UBOOL Flag); // slot 47 (+0xbc)

    DWORD   Pad004[(0x100 - 0x004) / 4];
    DWORD   F100;           // 0x100
    DWORD   Pad104;
    AActor *Owner;          // 0x108
    DWORD   Pad10C[(0x1bc - 0x10c) / 4];
    UObject *F1BC;          // 0x1bc
    DWORD   Pad1C0[(0x200 - 0x1c0) / 4];
    DWORD   F200;           // 0x200
    DWORD   Pad204[(0x238 - 0x204) / 4];
    DWORD   F238;           // 0x238
    DWORD   Pad23C[(0x2b8 - 0x23c) / 4];
    FName   F2B8;           // 0x2b8
    DWORD   Pad2BC[(0x2e8 - 0x2bc) / 4];
    DWORD   Flags2E8;       // 0x2e8
    DWORD   Pad2EC;
    DWORD   Flags2F0;       // 0x2f0
    DWORD   Flags2F4;       // 0x2f4
    DWORD   Pad2F8[(0x304 - 0x2f8) / 4];

    // RVA 0x92b80 (neutral name).
    __declspec(noinline) UBOOL Test2B80() const
    {
        return (Flags2F0 & 0x1000) && F100 && (Flags2F4 & 0x4000);
    }
    // RVA 0x92bb0 (neutral name).
    __declspec(noinline) UBOOL Test2BB0() const
    {
        return F238 && (Flags2F4 & 0x2000);
    }
    __forceinline UBOOL BlocksActor(const AActor *Other) const
    {
        return (Other->IsPlayer() || (Other->Flags2F4 & 0x40000)) ? (Flags2F0 >> 15) & 1 : (Flags2F0 >> 14) & 1;
    }

    UBOOL IsBlockedBy(const AActor *Other) const;
};

// RVA 0x91680: walks A's owner chain looking for B or for an actor sharing
// B's non-zero field 0x200.
__declspec(noinline) UBOOL ActorsRelated_91680(AActor *A, AActor *B)
{
    for (; A; A = A->Owner) {
        if (A == B)
            return 1;
        if (A && B && A->F200 == B->F200 && A->F200)
            return 1;
    }
    return 0;
}

// RVA 0x916c0, AActor vtable slot 26.
UBOOL AActor::IsBlockedBy(const AActor *Other) const
{
    if (Other->Flags2E8 & 0x1000000)
        return (Flags2F0 >> 13) & 1;
    if ((Flags2F0 & 0x1000) && F100 && (Flags2F4 & 0x4000) && (Other->Flags2E8 & 0x20000000))
        return 0;
    if ((Other->Flags2F0 & 0x1000) && Other->F100 && (Other->Flags2F4 & 0x4000) && (Flags2E8 & 0x20000000))
        return 0;
    if (!(Other->F238 && (Other->Flags2F4 & 0x2000)) && !Other->Test2B80()) {
        if (!Test2BB0() && !Test2B80())
            return Other->BlocksActor(this) && BlocksActor(Other);
        return (Other->Flags2F0 & 0x2000) && (Other->IsPlayer() ? (Flags2F0 >> 15) & 1 : (Flags2F0 >> 14) & 1);
    }
    return (Flags2F0 & 0x2000) && (IsPlayer() ? (Other->Flags2F0 >> 15) & 1 : (Other->Flags2F0 >> 14) & 1);
}

// Controller helpers (neutral names).
class UnnamedList_df4e0
{
public:
    INT FindItem(FName Item);                 // retail 0x109b57b0
};

class APawn : public AActor
{
public:
    UBOOL Check15CB0();                     // retail 0x10915cb0
};

class AController : public AActor
{
public:
    __declspec(noinline) UBOOL AttachPawn_91840(APawn *P, FName Param);
    __declspec(noinline) UBOOL DetachPawn_918b0(APawn *P);
};

UnnamedList_df4e0 *__stdcall FUN_109df4e0(AController *C);
extern FVector *GUnnamedVector_10ccacbc;

// RVA 0x91840.
UBOOL AController::AttachPawn_91840(APawn *P, FName Param)
{
    if (CastUnnamed(F1BC)) {
        if (FUN_109df4e0(this)->FindItem(Param) > -1 && P && P->Check15CB0()) {
            P->F2B8 = Param;
            P->Slot47(this, GUnnamedVector_10ccacbc, 1);
            return 1;
        }
    }
    return 0;
}

// RVA 0x918b0.
UBOOL AController::DetachPawn_918b0(APawn *P)
{
    if (F1BC && F1BC->IsA(&UnnamedClass_10cc0a78)) {
        P->Slot47(0, GUnnamedVector_10ccacbc, 1);
        P->F2B8.Index = 0;
        return 1;
    }
    return 0;
}

// ASPawnAttaque (vtable label), slot 47 override.
class ASPawnAttaque : public AActor
{
public:
    FVector F304;           // 0x304
    virtual void Slot47(AActor *Other, FVector *Value, UBOOL Flag);
};

// RVA 0x91900, ASPawnAttaque vtable slot 47; the parent is AActor slot 47 (retail 0x913a0).
void ASPawnAttaque::Slot47(AActor *Other, FVector *Value, UBOOL Flag)
{
    F304 = *Value;
    AActor::Slot47(Other, Value, Flag);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
typedef UBOOL (AActor::*IsBlockedByPtr)(const AActor *) const;
INT Driver_91680(AActor *A, AActor *B) { return ActorsRelated_91680(A, B) + ActorsRelated_91680(B, A); }
void Driver_916c0() { IsBlockedByPtr P = &AActor::IsBlockedBy; Escape(&P); }
INT Driver_91840(AController *C, APawn *P, FName Param)
{
    Escape(&GUnnamedVector_10ccacbc);
    return C->AttachPawn_91840(P, Param);
}
INT Driver_918b0(AController *C, APawn *P) { Escape(&GUnnamedVector_10ccacbc); return C->DetachPawn_918b0(P); }
