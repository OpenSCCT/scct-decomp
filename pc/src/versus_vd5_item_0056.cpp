// Work item w3 0056: Versus RVA 0x905c0, reflected vtable slot 45 of AActor
// and its subclasses. The body follows Unreal Engine 2's
// AActor::IsOverlapping(AActor* Other, FCheckResult* Hit): brush/level/self
// rejection, owner and collision-class filters, a primitive encroachment
// test when either actor is an encroacher, otherwise the cylinder test.
// Compiled with VC7.0 /GL and linked with /LTCG (its small callees take their
// arguments in EAX/EDX). Field names past Unreal's known ones are neutral.
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef int INT;
typedef float FLOAT;

struct FVector
{
    FLOAT X, Y, Z;
};

// The check result; only the three dwords at +0x2c are set by its
// constructor in this build.
struct FCheckResult
{
    DWORD Unk00[11];
    DWORD Unk2c;
    DWORD Unk30;
    DWORD Unk34;
    FCheckResult() : Unk2c(0), Unk30(0), Unk34(0) {}
};

class AActor;

// UPrimitive (Unreal Engine 2): slot 22 (+0x58) PointCheck, slot 28 (+0x70)
// GetEncroachExtent, slot 29 (+0x74) GetEncroachCenter.
class UPrimitive
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21();
    virtual UBOOL PointCheck(FCheckResult& Result, AActor* Owner, const FVector& Location, const FVector& Extent, DWORD ExtraNodeFlags);
    virtual void V23(); virtual void V24(); virtual void V25(); virtual void V26();
    virtual void V27();
    virtual FVector GetEncroachExtent(AActor* Owner);
    virtual FVector GetEncroachCenter(AActor* Owner);
};

// UClass; this build tests class inheritance with per-class numbers: a class
// derives from another when its +0x110 value is a multiple of the other's
// +0x10c value.
struct UClass
{
    char Pad00[0x88];
    DWORD ClassFlags;               // +0x88
    char Pad8c[0x80];
    DWORD ParentDivisor;            // +0x10c
    DWORD ClassProduct;             // +0x110
};

// Static class objects passed to IsA (0x10cc1568 and 0x10cc03e8).
extern UClass Unnamed_10cc1568;
extern UClass Unnamed_10cc03e8;

class AActor
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual void V32(); virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36(); virtual void V37(); virtual void V38(); virtual void V39();
    virtual void V40(); virtual void V41(); virtual void V42(); virtual void V43();
    virtual UPrimitive* GetPrimitive();                         // slot 44
    virtual UBOOL IsOverlapping(AActor* Other, FCheckResult* Hit);  // slot 45

    char Pad04[0x20];
    UClass* Class;          // +0x24
    char Pad28[0x58];
    FVector Location;               // +0x80
    char Pad8c[0x74];
    void* Unk100;                   // +0x100
    char Pad104[4];
    AActor* Owner;                  // +0x108
    char Pad10c[0x94];
    AActor* Level;                  // +0x1a0
    char Pad1a4[0x5c];
    void* Unk200;                   // +0x200
    char Pad204[0x34];
    void* Brush;                    // +0x238
    char Pad23c[0x2c];
    FLOAT CollisionRadius;          // +0x268
    FLOAT CollisionHeight;          // +0x26c
    char Pad270[0x78];
    DWORD Flags2e8;                 // +0x2e8
    char Pad2ec[4];
    DWORD Flags2f0;                 // +0x2f0
    DWORD Flags2f4;                 // +0x2f4

    UBOOL IsA(UClass* SomeBase);    // FUN_10992b40

    UBOOL IsBrush() const { return Brush && (Flags2f4 & 0x2000); }
    UBOOL IsMovingBrush() const     // FUN_10992b20
    {
        return Brush && (Flags2f4 & 0x8000);
    }
    UBOOL IsEncroacher() const      // FUN_10992b80
    {
        return (Flags2f0 & 0x1000) && Unk100 && (Flags2f4 & 0x4000);
    }
    UBOOL IsOwnedBy(const AActor* TestOwner) const;  // FUN_10991680
};

__declspec(noinline) UBOOL AActor::IsA(UClass* SomeBase)
{
    if (!SomeBase || Class == SomeBase)
        return 1;
    return Class->ClassProduct % SomeBase->ParentDivisor == 0;
}

static inline UBOOL SharesUnk200(const AActor* A, const AActor* B)
{
    return A && B && A->Unk200 == B->Unk200 && A->Unk200;
}

UBOOL AActor::IsOwnedBy(const AActor* TestOwner) const
{
    for (const AActor* Arg = this; Arg; Arg = Arg->Owner)
    {
        if (Arg == TestOwner || SharesUnk200(Arg, TestOwner))
            return 1;
    }
    return 0;
}

UBOOL AActor::IsOverlapping(AActor* Other, FCheckResult* Hit)
{
    if ((IsBrush() && Other->IsBrush()) || Other == Level)
        return false;
    if (this == Other)
        return 0;

    if (IsEncroacher() && Other->IsEncroacher())
        return 0;
    if (IsOwnedBy(Other) || Other->IsOwnedBy(this))
        return 0;

    if ((Flags2e8 & 0x8000000) && !Other->IsA(&Unnamed_10cc1568))
        return 0;
    if ((Other->Flags2e8 & 0x8000000) && !IsA(&Unnamed_10cc1568))
        return 0;

    if (!(Flags2f0 & 0x80000) && !(Class->ClassFlags & 0x400000))
        return 0;
    if (!(Other->Flags2f0 & 0x80000) && !(Other->Class->ClassFlags & 0x400000))
        return 0;

    AActor* PrimitiveActor;
    AActor* BoxActor;
    if (IsA(&Unnamed_10cc03e8))
    {
        PrimitiveActor = this;
        BoxActor = Other;
    }
    else if (Other->IsA(&Unnamed_10cc03e8))
    {
        PrimitiveActor = Other;
        BoxActor = this;
    }
    else if (IsMovingBrush())
    {
        PrimitiveActor = this;
        BoxActor = Other;
    }
    else if (Other->IsMovingBrush())
    {
        PrimitiveActor = Other;
        BoxActor = this;
    }
    else if (IsEncroacher())
    {
        PrimitiveActor = this;
        BoxActor = Other;
    }
    else if (Other->IsEncroacher())
    {
        PrimitiveActor = Other;
        BoxActor = this;
    }
    else
    {
        // Cylinder overlap.
        FLOAT DZ = Location.Z - Other->Location.Z;
        FLOAT H = Other->CollisionHeight + CollisionHeight;
        if (!(DZ * DZ < H * H))
            return 0;
        FLOAT DX = Location.X - Other->Location.X;
        FLOAT DY = Location.Y - Other->Location.Y;
        FLOAT R = Other->CollisionRadius + CollisionRadius;
        if (!(DX * DX + DY * DY < R * R))
            return 0;
        return 1;
    }

    FCheckResult TestHit;
    if (Hit == 0)
        Hit = &TestHit;
    FVector Extent = BoxActor->GetPrimitive()->GetEncroachExtent(BoxActor);
    if (Extent.Z == 0.f)
        Extent.Z = 1.f;
    return PrimitiveActor->GetPrimitive()->PointCheck(*Hit, PrimitiveActor,
        BoxActor->GetPrimitive()->GetEncroachCenter(BoxActor), Extent, 0) == 0;
}

// Scaffolding for the link, not part of the unit: retail calls the function
// through the vtable; constructing an actor here makes the unit emit it.
inline void* operator new(unsigned int, void* Where) { return Where; }
void Escape(void*);
void Driver_905c0(void* Mem, AActor* B, FCheckResult* Hit)
{
    // IsA is called from code the linker cannot see, which keeps it thiscall.
    UBOOL (AActor::*IsAPtr)(UClass*) = &AActor::IsA;
    Escape(&IsAPtr);
    AActor* A = new (Mem) AActor;
    A->IsOverlapping(B, Hit);
}
