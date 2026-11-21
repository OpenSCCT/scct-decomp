// Work item w3 0266: Versus RVA 0xf8640-0xf8945 (LTCG objects, VC7.0 /GL).
// 0xf8640 operator<<(FArchive&, TArray<TMap<FString,FString>::TPair>&).
// 0xf8750 a script event thunk with parms (FString, FString, out FString),
//         event name index 0xcfc; class and event names not recovered.
// 0xf8810 FGuid operator==; 0xf8840 an actor predicate (neutral name);
// 0xf8870 FColor::FColor(const FPlane&).
// The archive class and FCompactIndex serializer below are copied from
// pc/src/versus_vd3_item_0139.cpp (RVA 0x1ea40, not part of this item; defined
// so the link gives it its retail register convention).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short _WORD;
typedef unsigned char BYTE;
typedef float FLOAT;

class UObject;
class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(UObject *Object);
    virtual void CountBytes(INT InNum, INT InMax);
    virtual FArchive &operator<<(UObject *&Res);
    virtual void v1c(); virtual void v20(); virtual void v24();
    virtual INT GetStringKey(); // slot 0x28; Versus string obfuscation key (by use)

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    BYTE Pad18[0x14];
    UBOOL ArIsError;
    UBOOL ArIsCriticalError;
    INT Pad34;
    INT ArMaxSerializeSize;

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, _WORD &W) { Ar.Serialize(&W, 2); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, DWORD &D) { Ar.Serialize(&D, 4); return Ar; }
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();                                 // RVA 0x48b0
    FString &operator=(const FString &Other);   // RVA 0x4800
};

inline INT Abs(INT A) { return A >= 0 ? A : -A; }

struct FCompactIndex
{
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

// RVA 0x1ea40 (not part of this item; defined for its register convention).
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving)
    {
        Ar.Serialize(&I.Value, sizeof(I.Value));
        return Ar;
    }
    INT Original = I.Value;
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
    return Ar;
}

// RVA 0x11b80 (not part of this item). Body approximated, not a match: it
// stands in so the link gives the call its retail convention (Ar in EAX,
// the string in EBX).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FString &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(TCHAR), A.ArrayMax * sizeof(TCHAR));
    INT SaveNum = A.ArrayNum;
    Ar << AR_INDEX(SaveNum);
    Ar.Serialize(A.Data, SaveNum * sizeof(TCHAR));
    return Ar;
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);         // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);      // RVA 0x4550
};
// TMap<FString,FString>::TPair (0x1c bytes, as in pc/src/versus_vd2_item_0082.cpp).
struct TPair
{
    INT HashNext;
    FString Key;
    FString Value;
    TPair();
    ~TPair();
    friend FArchive &operator<<(FArchive &Ar, TPair &F) { return Ar << F.Key << F.Value; }
};
// RVA 0xf8730 (not part of this item; defined for its convention, this in EAX).
__declspec(noinline) TPair::TPair() {}

// TArray<TPair> (named TPairArray in pc/src/versus_vd2_item_0082.cpp).
class TPairArray : public FArray
{
public:
    TPair &operator()(INT i) { return ((TPair *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(TPair), ArrayMax * sizeof(TPair)); }
    void Empty(INT Slack);
};
// RVA 0x149f0 (published in versus_vd2_item_0082.cpp; defined for its
// convention, this in ESI).
__declspec(noinline) void TPairArray::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~TPair();
    FArray::Empty(sizeof(TPair), Slack);
}
inline void *operator new(unsigned int Size, TPairArray &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(TPair));
    return &Array(Index);
}

// RVA 0xf8640: TArray<TPair> serializer (TMap<FString,FString> pairs).
FArchive &operator<<(FArchive &Ar, TPairArray &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading())
    {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(A) TPair;
    }
    else
    {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// RVA 0xf8750: a script event thunk (UE2 eventXxx pattern). The class, the
// event (FName index 0xcfc) and the parameter names are not recovered.
class UFunction;
struct FName
{
    INT Index;
    FName(INT N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};
class UnnamedObject_f8750
{
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);  // +0x10
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);                    // RVA 0x16830
    void eventUnnamed_f8750(const FString &A, const FString &B, FString &C);
};
struct UnnamedObject_f8750_eventUnnamed_Parms
{
    FString A;
    FString B;
    FString C;
    ~UnnamedObject_f8750_eventUnnamed_Parms();
};
// RVA 0x6200 (identical code folded with ~FPreferencesInfo; defined for its
// convention, this on the stack).
__declspec(noinline) UnnamedObject_f8750_eventUnnamed_Parms::~UnnamedObject_f8750_eventUnnamed_Parms() {}

void UnnamedObject_f8750::eventUnnamed_f8750(const FString &A, const FString &B, FString &C)
{
    UnnamedObject_f8750_eventUnnamed_Parms Parms;
    Parms.A = A;
    Parms.B = B;
    Parms.C = C;
    ProcessEvent(FindFunctionChecked(FName(0xcfc)), &Parms);
    C = Parms.C;
}

extern "C" __declspec(dllimport) double __cdecl floor(double);

inline INT appFloor(FLOAT F) { return (INT)floor(F); }
inline INT Clamp(INT X, INT Min, INT Max) { return X < Min ? Min : X < Max ? X : Max; }

// RVA 0xf8810: FGuid equality (this in ECX, other in EAX after LTCG).
struct FGuid
{
    DWORD A, B, C, D;
    friend UBOOL operator==(const FGuid& X, const FGuid& Y)
    {
        return X.A == Y.A && X.B == Y.B && X.C == Y.C && X.D == Y.D;
    }
};
__declspec(noinline) UBOOL GuidsEqual(const FGuid& X, const FGuid& Y) { return X == Y; }

// RVA 0xf8840: actor predicate. Neutral names; offsets only.
struct UnnamedActor_f8840
{
    BYTE Pad0[0x214];
    void *Ptr214;            // +0x214
    BYTE Pad1[0x2d9 - 0x218];
    BYTE Byte2d9;            // +0x2d9
    BYTE Pad2[0x2e8 - 0x2da];
    DWORD Flags2e8;          // +0x2e8
};
__declspec(noinline) UBOOL IsActor_f8840(UnnamedActor_f8840 *A)
{
    return A->Byte2d9 == 8 && (A->Flags2e8 & 0x800) && A->Ptr214 == 0;
}

// RVA 0xf8870: FColor from FPlane.
struct FPlane { FLOAT X, Y, Z, W; };
struct FColor
{
    BYTE B, G, R, A;
    FColor(const FPlane& P);
};
__declspec(noinline) FColor::FColor(const FPlane& P)
:   B((BYTE)Clamp(appFloor(P.Z * 256.f), 0, 255))
,   G((BYTE)Clamp(appFloor(P.Y * 256.f), 0, 255))
,   R((BYTE)Clamp(appFloor(P.X * 256.f), 0, 255))
,   A((BYTE)Clamp(appFloor(P.W * 256.f), 0, 255))
{
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
UBOOL Driver_f8810(FGuid *X, FGuid *Y) { return GuidsEqual(*X, *Y) + GuidsEqual(*Y, *X); }
UBOOL Driver_f8840(UnnamedActor_f8840 *A, UnnamedActor_f8840 *B) { return IsActor_f8840(A) + IsActor_f8840(B); }
inline void *operator new(unsigned int, void *M) { return M; }
void Driver_f8870(FColor *C, FPlane *P, FColor *C2, FPlane *P2) { new (C) FColor(*P); new (C2) FColor(*P2); }
typedef FArchive &(*EntrySerializeFn)(FArchive &, TPairArray &);
void Driver_f8640(FArchive *Ar, TPairArray *A)
{
    EntrySerializeFn Fn = &operator<<;
    Escape(&GMalloc);
    Escape(&Fn);
    *Ar << *A;
}
void Driver_f8750(UnnamedObject_f8750 *O, const FString *A, const FString *B, FString *C) { O->eventUnnamed_f8750(*A, *B, *C); }
