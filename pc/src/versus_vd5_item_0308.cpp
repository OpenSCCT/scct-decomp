// Work item w3 0308 (RVA 0x1073d0-0x10795b).
// 0x1073d0 is an ordinary thiscall virtual (UFlicFlocEmitter slot 29).
// 0x107440-0x10795b are archive serializers from a /GL object with link-time
// register conventions (check with try_ltcg.py and the driver at the end).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned short _WORD;

class UObject;
class FName { public: INT Index; };

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

struct FCompactIndex { INT Value; };
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    // MSVC lays overloaded virtuals out in reverse order.
    virtual FArchive &operator<<(FName &N);                 // +0x1c
    virtual FArchive &operator<<(UObject *&Res);            // +0x18

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, DWORD &D) { Ar.Serialize(&D, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;          // 0x04
    INT ArNetVer;       // 0x08
    INT ArLicenseeVer;  // 0x0c
    UBOOL ArIsLoading;  // 0x10
    UBOOL ArIsSaving;   // 0x14
};

struct FVector
{
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V) { return Ar << V.X << V.Y << V.Z; }
};

// Unnamed engine object at 0x10c946cc; Platform 1..3 selects the console
// cooking targets (the same tests appear in items 0328 and w3 0011).
struct FPlatformInfo_46cc
{
    BYTE Pad[0x80];
    INT  Platform;      // 0x80
};
extern FPlatformInfo_46cc *GPlatformInfo;
inline UBOOL IsConsolePlatform()
{
    return GPlatformInfo->Platform == 1 || GPlatformInfo->Platform == 2 || GPlatformInfo->Platform == 3;
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Realloc(INT ElementSize);                          // 0x4600
};

template <class T> class TArray : public FArray
{
public:
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
};
FArchive &operator<<(FArchive &Ar, TArray<BYTE> &A);       // 0xa8ea0

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }

// ---------------------------------------------------------------------------
// 0x1073d0

// Particle record of the sprite emitters (stride 0xc8); only the two words
// copied from the owner's source are named.
struct FParticle_1073d0
{
    BYTE Pad0[0x18];
    INT  SourceA;       // 0x18
    INT  SourceB;       // 0x1c
    BYTE Pad20[0xc8 - 0x20];
};
struct FFlocSource_1073d0
{
    BYTE Pad0[0x8c];
    INT  A;             // 0x8c
    INT  B;             // 0x90
};
struct FFlocOwner_1073d0
{
    BYTE Pad0[0x104];
    FFlocSource_1073d0 *Source;   // 0x104
};

class USpriteEmitter
{
public:
    virtual void Slot0();
    // vtable slot 29 (USpriteEmitter vtable 0x30b5b8); name not recovered.
    void UpdateSlot29();
};

// UFlicFlocEmitter (vtable 0x30b530) slot 29: copies two values from the
// owner's source into each live particle, then defers to USpriteEmitter.
class UFlicFlocEmitter : public USpriteEmitter
{
public:
    BYTE Pad4[0x39c - 4];
    FFlocOwner_1073d0 *Owner;       // 0x39c
    BYTE Pad3a0[4];
    FParticle_1073d0 *Particles;    // 0x3a4
    BYTE Pad3a8[0x3b0 - 0x3a8];
    INT  MaxParticles;              // 0x3b0
    BYTE Pad3b4[0x3c8 - 0x3b4];
    INT  ActiveParticles;           // 0x3c8
    BYTE Pad3cc[0x420 - 0x3cc];
    DWORD Flags;                    // 0x420
    void UpdateSlot29();
};

void UFlicFlocEmitter::UpdateSlot29()
{
    if (Flags & 1)
    {
        for (INT i = 0; i < Min(ActiveParticles, MaxParticles); i++)
        {
            FParticle_1073d0 &P = Particles[i];
            P.SourceA = Owner->Source->A;
            P.SourceB = Owner->Source->B;
        }
    }
    USpriteEmitter::UpdateSlot29();
}

// ---------------------------------------------------------------------------
// LTCG part (0x107440-0x10795b). Type names are neutral; layouts come from
// the offsets used.

// 0xe4-byte shape record allocated by 0x107560 (allocation tag at 0x10c109d8).
struct FUnnamedShape_1077c0
{
    FVector A;                  // 0x00
    FVector B;                  // 0x0c
    FVector Points[16];         // 0x18
    FLOAT   Value;              // 0xd8
    UObject *Object;            // 0xdc
    _WORD   NumPoints;          // 0xe0
};

// 0x1077c0: archive in EBX, record on the stack (cdecl). Older fields that
// are no longer kept are read into locals and dropped.
FArchive &SerializeShape_1077c0(FArchive &Ar, FUnnamedShape_1077c0 *S)
{
    INT Num = S->NumPoints;
    Ar << AR_INDEX(Num);
    S->NumPoints = Num;
    Ar << S->A << S->B;
    {
        FVector Dropped;
        Ar << Dropped;
    }
    {
        FVector Dropped;
        Ar << Dropped;
    }
    for (INT i = 0; i < S->NumPoints; i++)
        Ar << S->Points[i];
    Ar << S->Value;
    UObject *DroppedObject = 0;
    Ar << DroppedObject;
    Ar << S->Object;
    FName DroppedName;
    DroppedName.Index = 0;
    INT DroppedIndex = 0;
    Ar << DroppedName;
    Ar << AR_INDEX(DroppedIndex) << AR_INDEX(DroppedIndex);
    FLOAT DroppedFloat;
    Ar << DroppedFloat;
    if (Ar.Ver() >= 0xa8)
        Ar << DroppedFloat;
    return Ar;
}

// 0x107760: archive in ECX, record in EAX.
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedShape_1077c0 *S)
{
    SerializeShape_1077c0(Ar, S);
    if (!IsConsolePlatform())
    {
        UObject *DroppedObject = 0;
        INT DroppedIndex = -1;
        Ar << DroppedObject;
        Ar << AR_INDEX(DroppedIndex);
    }
    return Ar;
}

extern const TCHAR Tag_10c109d8[];   // allocation tag at 0x10c109d8

struct FUnnamedRecord_107560
{
    DWORD   Data[4];                // 0x00
    UObject *Object;                // 0x10
    DWORD   Flags;                  // 0x14
    _WORD   Index[4];               // 0x18
    FUnnamedShape_1077c0 *Shape;    // 0x20
    FLOAT   SizeA;                  // 0x24
    FLOAT   SizeB;                  // 0x28
};

// 0x107560: archive in EAX, record in EBX.
FArchive &operator<<(FArchive &Ar, FUnnamedRecord_107560 &R)
{
    Ar << R.Object;
    Ar << R.Flags;
    INT Value;
    Value = R.Index[0]; Ar << AR_INDEX(Value); R.Index[0] = Value;
    Value = R.Index[1]; Ar << AR_INDEX(Value); R.Index[1] = Value;
    Value = R.Index[2]; Ar << AR_INDEX(Value); R.Index[2] = Value;
    Value = R.Index[3]; Ar << AR_INDEX(Value); R.Index[3] = Value;
    if (Ar.Ver() < 0x65)
    {
        INT Dropped = -1;
        Ar << AR_INDEX(Dropped);
    }
    INT Dropped2 = -1;
    if (Ar.Ver() < 0xa5)
        Ar << AR_INDEX(Dropped2);
    if (Ar.Ver() < 0x4e)
    {
        INT DroppedA = 0, DroppedB = 0;
        Ar.Serialize(&DroppedA, 2);
        Ar.Serialize(&DroppedB, 2);
    }
    UObject *DroppedObject = 0;
    if (Ar.Ver() < 0xa5)
        Ar << DroppedObject;
    if (Ar.Ver() > 0x56)
        Ar << R.Data[0] << R.Data[1] << R.Data[2] << R.Data[3];
    if (Ar.Ver() >= 0x6a)
    {
        Ar << R.SizeA;
        if (Ar.Ver() >= 0xa8)
            Ar << R.SizeB;
        else
            R.SizeB = R.SizeA;
    }
    else if (Ar.IsLoading())
    {
        R.SizeA = R.SizeB = 32.f;
    }
    if (IsConsolePlatform() && !(R.Flags & 0xc000000))
    {
        if (Ar.IsLoading())
            R.Shape = 0;
    }
    else if (Ar.IsLoading())
    {
        R.Shape = (FUnnamedShape_1077c0 *)GMalloc->Malloc(sizeof(FUnnamedShape_1077c0), Tag_10c109d8);
        if (Ar.Ver() >= 0xa5)
            Ar << R.Shape;
    }
    else if (Ar.IsSaving())
    {
        Ar << R.Shape;
    }
    return Ar;
}

// Actor referenced by 0x107440; class and field names not recovered.
class AUnnamedActor_107440
{
public:
    BYTE  Pad0[0x174];
    FLOAT FieldA;           // 0x174
    FLOAT FieldB;           // 0x178
    BYTE  Pad17c[0x2d2 - 0x17c];
    BYTE  Kind;             // 0x2d2
    BYTE  Pad2d3[0x2e8 - 0x2d3];
    DWORD FlagsA;           // 0x2e8
    DWORD FlagsB;           // 0x2ec
};

struct FUnnamedRecord_107440
{
    AUnnamedActor_107440 *Actor;    // 0x00
    TArray<BYTE> Bytes;             // 0x04
    DWORD F10;                      // 0x10
    DWORD F14;                      // 0x14
    DWORD F18;                      // 0x18
    DWORD F1c;                      // 0x1c
    DWORD F20;                      // 0x20
    DWORD F24;                      // 0x24
    BYTE  Pad28[8];
    DWORD F30;                      // 0x30
};

// 0x107440: archive in ESI, record in EAX. When cooking for a console the
// actor reference is cleared while saving if the actor is not worth keeping.
FArchive &operator<<(FArchive &Ar, FUnnamedRecord_107440 &R)
{
    AUnnamedActor_107440 *Saved = R.Actor;
    if (Ar.IsSaving() && IsConsolePlatform() && Saved
        && !(Saved->FlagsB & 0x800000) && !(Saved->FlagsA & 0x20000)
        && Saved->Kind != 0x16
        && (Saved->FieldA == 0.f || Saved->FieldB == 0.f))
        R.Actor = 0;
    Ar << *(UObject **)&R.Actor << R.Bytes << R.F10 << R.F14;
    if (Ar.IsSaving() && IsConsolePlatform())
        R.Actor = Saved;
    if (Ar.Ver() >= 0x5b)
        Ar << R.F30;
    if (Ar.Ver() >= 0x6b)
    {
        Ar << R.F18;
        Ar << R.F1c;
        Ar << R.F20;
        Ar << R.F24;
    }
    return Ar;
}

// ---- Stand-ins for callees of other units, defined so the link gives them
// their retail register conventions. Not part of this unit's match. ----

// 0x1ea40 (archive in ESI, index in EDI in retail), from item 0116.
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
    } else {
        INT Original = I.Value;
        DWORD V = Original >= 0 ? Original : -Original;
        BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
        I.Value = 0;
        Ar << B0;
        if (B0 & 0x40) {
            V >>= 6;
            BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B1;
            if (B1 & 0x80) {
                V >>= 7;
                BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B2;
                if (B2 & 0x80) {
                    V >>= 7;
                    BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                    Ar << B3;
                    if (B3 & 0x80) {
                        V >>= 7;
                        BYTE B4 = V;
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

extern const TCHAR OperatorShlTArray_Tag[];   // L"operator<<(TArray)"

// 0xa8ea0 (archive in EAX, array in EBX in retail), from w3 item 0074.
FArchive &operator<<(FArchive &Ar, TArray<BYTE> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) {
            if (A.ArrayNum)
                A.Data = GMalloc->Malloc(A.ArrayNum, OperatorShlTArray_Tag);
            else
                return Ar;
        } else {
            if (A.ArrayNum) {
                A.Realloc(1);
            } else {
                A.ArrayNum = 0;
                A.ArrayMax = 0;
                GMalloc->Free(A.Data);
                A.Data = 0;
                return Ar;
            }
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum);
    return Ar;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_107560(FArchive *Ar, FUnnamedRecord_107560 *R)
{
    Escape(&GMalloc);
    Escape(&GPlatformInfo);
    *Ar << *R;
}
void Driver_107440(FArchive *Ar, FUnnamedRecord_107440 *R)
{
    Escape(&GMalloc);
    Escape(&GPlatformInfo);
    *Ar << *R;
}
