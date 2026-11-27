// Work item 0328: Versus RVA 0x90870-0x90c71 (Engine, UnActor.cpp).
//
// 0x90870 AActor::GetPrimitive   (vtable slot 44 of AActor and subclasses)
// 0x908b0 AVolume::GetPrimitive  (vtable slot 44 of AVolume and subclasses)
//   Both follow UE2's GetPrimitive shape: the actor's own primitives, else the
//   engine's shared cylinder (XLevel->Engine->Cylinder).
// 0x908e0 TouchTo                (shipped editor guard at VA 0x1149210c)
// 0x909f0 AActor::BeginTouch     (reciprocal touch with the hit normal negated)
// 0x90a40 AActor::EndTouch       (UE2 EndTouch: UnTouch both ways, RemoveItem)
// 0x90b00 AActor::Serialize      (vtable slot 10; Super is UObject::Serialize)
//
// The last four come from an object built with /GL and linked with /LTCG:
// retail passes `this` and arguments in EAX/EBX/EDI/ESI. The script events
// (eventTouch, eventUnTouch), TArray::RemoveItem and the two array
// serializers are defined here so the linker can give them the same register
// conventions. Field names past what UE2 shows are guesses; offsets are retail.
//
// Helpers defined here that also match retail under try_ltcg.py:
//   0x1ea40  operator<<(FArchive&, FCompactIndex&)   (Core; Ar in ESI, I in EDI)
//   0x92360  operator<<(FArchive&, TArray<FUnnamedRecord_90b00*>&)
//   0x92420  operator<<(FArchive&, TArray<FUnnamedLink_90b00*>&)
//   0x92aa0  AActor::eventTouch                    (this in ESI)
//   0x10bd60 TArray<AActor*>::RemoveItem           (this in EDI)
// TouchTo and BeginTouch use the actual SetCollision caller and initialized global allocator.
// EndTouch is still incomplete in this link context.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

#define INDEX_NONE -1

enum EName
{
    NAME_PROBEMIN = 0x12c,
    NAME_Touch    = 0x139,
    NAME_UnTouch  = 0x13a,
    NAME_PROBEMAX = 0x16c,
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class UObject;
class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(UObject *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive &operator<<(UObject *&Res);

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    INT ArVer;              // 0x04
    INT ArNetVer;           // 0x08
    INT ArLicenseeVer;      // 0x0c
    UBOOL ArIsLoading;      // 0x10
    UBOOL ArIsSaving;       // 0x14
};

class FCompactIndex
{
public:
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

typedef unsigned char BYTE;
inline FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
inline INT Abs(INT A) { return A >= 0 ? A : -A; }

// Core's compact-index serializer (retail 0x1ea40), defined here so the link
// sees its register convention (archive in ESI, index in EDI).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving())
    {
        Ar.Serialize(&I.Value, sizeof(I.Value));
    }
    else
    {
        DWORD V = Abs(I.Value);
        BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
        I.Value = 0;
        Ar << B0;
        if (B0 & 0x40)
        {
            V >>= 6;
            BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B1;
            if (B1 & 0x80)
            {
                V >>= 7;
                BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B2;
                if (B2 & 0x80)
                {
                    V >>= 7;
                    BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                    Ar << B3;
                    if (B3 & 0x80)
                    {
                        V >>= 7;
                        BYTE B4 = (BYTE)V;
                        Ar << B4;
                        I.Value = B4;
                    }
                    I.Value = (I.Value << 7) + (B3 & 0x7f);
                }
                I.Value = (I.Value << 7) + (B2 & 0x7f);
            }
            I.Value = (I.Value << 7) + (B1 & 0x7f);
        }
        I.Value = (I.Value << 6) + (B0 & 0x3f);
        if (B0 & 0x80)
            I.Value = -I.Value;
    }
    return Ar;
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    INT Num() const { return ArrayNum; }
    void Realloc(INT ElementSize)
    {
        if (Data == 0)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, L"FArray::Add");
        else
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, L"FArray");
    }
    INT Add(INT Count, INT ElementSize)
    {
        INT Index = ArrayNum;
        if ((ArrayNum += Count) > ArrayMax)
        {
            ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
            Realloc(ElementSize);
        }
        return Index;
    }
    INT AddOutOfLine(INT Count, INT ElementSize);       // retail 0x44e0
    void Empty(INT ElementSize, INT Slack = 0);          // retail 0x4550
    void Remove(INT Index, INT Count, INT ElementSize);  // retail 0x119c0
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT FindItemIndex(const T &Item) const
    {
        for (INT Index = 0; Index < ArrayNum; Index++)
            if (((T *)Data)[Index] == Item)
                return Index;
        return INDEX_NONE;
    }
    UBOOL ContainsItem(const T &Item) const
    {
        for (INT Index = 0; Index < ArrayNum; Index++)
            if (((T *)Data)[Index] == Item)
                return 1;
        return 0;
    }
    __forceinline INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        ((T *)Data)[Index] = Item;
        return Index;
    }
    __declspec(noinline) INT RemoveItem(const T &Item)
    {
        INT OriginalNum = ArrayNum;
        for (INT Index = 0; Index < ArrayNum; Index++)
            if (((T *)Data)[Index] == Item)
                Remove(Index--, 1, sizeof(T));
        return OriginalNum - ArrayNum;
    }
    friend __declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray &A)
    {
        Ar.CountBytes(A.ArrayNum * sizeof(T), A.ArrayMax * sizeof(T));
        if (Ar.IsLoading())
        {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(sizeof(T), NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << A(A.AddOutOfLine(1, sizeof(T)));
        }
        else
        {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
};

class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
};

#pragma pack(push, 4)
struct FStateFrame
{
    char Pad0[0x1c];
    QWORD ProbeMask;        // 0x1c
};
#pragma pack(pop)

class UFunction;
class UPrimitive;

class UObject
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);  // slot 4
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Serialize(FArchive &Ar);                                            // slot 10

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);                     // retail 0x16830
    UBOOL IsProbing(FName ProbeName)
    {
        return ProbeName.GetIndex() < NAME_PROBEMIN
            || ProbeName.GetIndex() >= NAME_PROBEMAX
            || !StateFrame
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }

    INT Index;                      // 0x04
    UObject *HashNext;              // 0x08
    FStateFrame *StateFrame;        // 0x0c
    char PadUObject[0x2c - 0x10];
};

class UEngine
{
public:
    char Pad0[0x2c];
    UPrimitive *Cylinder;           // 0x2c
};

class ULevel
{
public:
    char Pad0[0xf0];
    UEngine *Engine;                // 0xf0
};

// Records kept in the two serialized arrays at 0x210 / 0x21c (types unknown).
struct FUnnamedRecord_90b00
{
    char Pad0[0x18];
    UObject *A;                     // 0x18
    UObject *B;                     // 0x1c
};
struct FUnnamedLink_90b00
{
    FUnnamedRecord_90b00 *Record;   // 0x00
    UObject *Object;                // 0x04
};

// Global object read by Serialize (retail 0x10c946cc); type not recovered.
struct FUnnamedSettings_90b00
{
    char Pad0[0x68];
    INT Field68;                    // 0x68
    char Pad6c[0x78 - 0x6c];
    INT Field78;                    // 0x78
    char Pad7c[0x80 - 0x7c];
    INT Field80;                    // 0x80
};
extern FUnnamedSettings_90b00 *GUnnamedSettings_90b00;

// Element serializers: a record is saved as its two object references, a
// link as its record followed by its own object reference.
inline FArchive &operator<<(FArchive &Ar, FUnnamedRecord_90b00 *R)
{
    return Ar << R->A << R->B;
}
inline FArchive &operator<<(FArchive &Ar, FUnnamedLink_90b00 *L)
{
    return Ar << L->Record << L->Object;
}

class AActor : public UObject
{
public:
    char Pad2c[0x100 - 0x2c];
    UPrimitive *Mesh;               // 0x100
    char Pad104[0x1a4 - 0x104];
    ULevel *XLevel;                 // 0x1a4
    char Pad1a8[0x1bc - 0x1a8];
    UPrimitive *StaticMesh;         // 0x1bc
    char Pad1c0[0x1dc - 0x1c0];
    TArray<AActor *> Touching;      // 0x1dc
    char Pad1e8[0x210 - 0x1e8];
    TArray<FUnnamedRecord_90b00 *> Records;     // 0x210
    TArray<FUnnamedLink_90b00 *> Links;         // 0x21c
    char Pad228[0x22c - 0x228];
    UObject *Current;               // 0x22c
    UObject *Saved1;                // 0x230
    UObject *Saved2;                // 0x234
    UPrimitive *VolumePrimitive;    // 0x238 (used by AVolume)
    char Pad23c[0x250 - 0x23c];
    UPrimitive *Brush;              // 0x250

    UPrimitive *GetPrimitive();
    virtual void Serialize(FArchive &Ar);
    __declspec(noinline) void BeginTouch(AActor *Other, const FVector &HitLocation, const FVector &HitNormal);
    void EndTouch(AActor *Other, UBOOL NoNotifySelf);

    __declspec(noinline) void eventTouch(AActor *Other, FVector HitLocation, FVector HitNormal)
    {
        if (IsProbing(NAME_Touch))
        {
            struct { AActor *Other; FVector HitLocation; FVector HitNormal; } Parms;
            Parms.Other = Other;
            Parms.HitLocation = HitLocation;
            Parms.HitNormal = HitNormal;
            ProcessEvent(FindFunctionChecked(NAME_Touch), &Parms);
        }
    }
    void eventUnTouch(AActor *Other)
    {
        if (IsProbing(NAME_UnTouch))
        {
            struct { AActor *Other; } Parms;
            Parms.Other = Other;
            ProcessEvent(FindFunctionChecked(NAME_UnTouch), &Parms);
        }
    }
};

class AVolume : public AActor
{
public:
    UPrimitive *GetPrimitive();
};

UPrimitive *AActor::GetPrimitive()
{
    if (StaticMesh)
        return StaticMesh;
    if (Mesh)
        return Mesh;
    if (Brush)
        return Brush;
    return XLevel->Engine ? XLevel->Engine->Cylinder : 0;
}

UPrimitive *AVolume::GetPrimitive()
{
    if (VolumePrimitive)
        return VolumePrimitive;
    return XLevel->Engine ? XLevel->Engine->Cylinder : 0;
}

static UBOOL TouchTo(AActor *Actor, AActor *Other, const FVector &HitLocation, const FVector &HitNormal)
{
    if (Actor->Touching.ContainsItem(Other))
        return 1;
    Actor->Touching.AddItem(Other);
    Actor->eventTouch(Other, HitLocation, HitNormal);
    return Actor->Touching.ContainsItem(Other);
}

void AActor::BeginTouch(AActor *Other, const FVector &HitLocation, const FVector &HitNormal)
{
    if (TouchTo(this, Other, HitLocation, HitNormal))
        TouchTo(Other, this, HitLocation, -HitNormal);
}

void AActor::EndTouch(AActor *Other, UBOOL NoNotifySelf)
{
    if (!NoNotifySelf && Touching.ContainsItem(Other))
        eventUnTouch(Other);
    Touching.RemoveItem(Other);
    if (Other->Touching.ContainsItem(this))
    {
        Other->eventUnTouch(this);
        Other->Touching.RemoveItem(this);
    }
}

void AActor::Serialize(FArchive &Ar)
{
    UObject *OldCurrent = Current;
    UObject *OldSaved1 = Saved1;
    UObject *OldSaved2 = Saved2;
    if (Ar.IsSaving())
    {
        switch (GUnnamedSettings_90b00->Field80)
        {
        case 1:
            if (GUnnamedSettings_90b00->Field68 > 0)
                Current = OldSaved1;
            Saved2 = 0;
            Saved1 = 0;
            break;
        case 2:
        case 3:
            if (GUnnamedSettings_90b00->Field68 > 0)
                Current = OldSaved2;
            Saved2 = 0;
            Saved1 = 0;
            break;
        case 0:
            if (GUnnamedSettings_90b00->Field68 <= 0)
            {
                Saved1 = OldCurrent;
                Saved2 = 0;
            }
            Current = 0;
            break;
        }
    }
    UObject::Serialize(Ar);
    if (!Ar.IsLoading() && !Ar.IsSaving())
        Ar << Records << Links;
    if (Ar.IsSaving())
    {
        Current = OldCurrent;
        Saved1 = OldSaved1;
        Saved2 = OldSaved2;
    }
    else if (Ar.IsLoading() && Ar.Ver() > 150)
    {
        if (GUnnamedSettings_90b00->Field80 == 0)
        {
            switch (GUnnamedSettings_90b00->Field78)
            {
            case 1:
                Current = Saved1;
                return;
            case 2:
            case 3:
                Current = Saved2;
                return;
            }
        }
        else if (Current)
            return;
        Current = Saved1 ? Saved1 : Saved2;
    }
}

// Scaffolding for the LTCG link, not part of the unit: call sites shaped like
// retail's (BeginTouch from a FCheckResult, EndTouch with both flag values,
// Serialize through its address as the vtable does).
struct FCheckResult
{
    FCheckResult *Next;
    AActor *Actor;
    FVector Location;
    FVector Normal;
};
void Escape(void *);
void Driver_909f0(AActor *A, FCheckResult *Hit, AActor *B, FCheckResult *Hit2, AActor *C, FCheckResult *Hit3)
{
    A->BeginTouch(Hit->Actor, Hit->Location, Hit->Normal);
    Escape(Hit);
    B->BeginTouch(Hit2->Actor, Hit2->Location, Hit2->Normal);
    Escape(Hit2);
    C->BeginTouch(Hit3->Actor, Hit3->Location, Hit3->Normal);
}
void Driver_90a40(AActor *A, AActor *B, AActor *C)
{
    A->EndTouch(B, 0);
    A->EndTouch(C, 1);
}
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_90b00(void *Mem)
{
    Escape(&GUnnamedSettings_90b00);
    new (Mem) AActor;
}
