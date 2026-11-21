// Work item 0337: Versus RVA 0x92880-0x92b3d. All six functions are LTCG
// (custom register conventions); verified with try_ltcg.py.
//   0x92880 FBox::GetCenterAndExtents (this in EAX, Center in EDX, Extents in ECX)
//   0x92920 FPointBoxIntersection (box in ECX, point in EDX)
//   0x92980 light record constructor (this on the stack, actor in ESI). Unnamed:
//           size 0x2a4, Update() at 0x11de70 takes this in EDI.
//   0x92a50 / 0x92aa0 AActor probe events for FName indices 0x13a / 0x139
//           (names not recovered; this in ESI).
//   0x92b20 AActor flag test (this in EAX), unnamed.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
extern const TCHAR FArray_ProtectedCtorTag[]; // L"Farray::protectedcstor"

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector &operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
};

class FBox
{
public:
    FVector Min;
    FVector Max;
    BYTE IsValid;

    __declspec(noinline) void GetCenterAndExtents(FVector &Center, FVector &Extents) const
    {
        Extents = Max - Min;
        Extents *= 0.5f;
        Center = Min + Extents;
    }
};

// UE2 UnMath.h.
__declspec(noinline) UBOOL FPointBoxIntersection(const FVector &Point, const FBox &Box)
{
    if (Point.X >= Box.Min.X && Point.X <= Box.Max.X &&
        Point.Y >= Box.Min.Y && Point.Y <= Box.Max.Y &&
        Point.Z >= Box.Min.Z && Point.Z <= Box.Max.Z)
        return 1;
    else
        return 0;
}

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_ProtectedCtorTag);
    }
    ~FArray();
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    TArray(INT InNum) : FArray(InNum, sizeof(T)) {}
    ~TArray();
};

enum EName { NAME_None = 0 };
class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

#pragma pack(push, 4)
struct FStateFrame
{
    BYTE Pad[0x1c];
    QWORD ProbeMask;
};
#pragma pack(pop)

class UFunction;

class UObject
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);

    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
};

class AActor : public UObject
{
public:
    BYTE Pad10[0x238 - 0x10];
    INT Field238;
    BYTE Pad23c[0x2e8 - 0x23c];
    DWORD Flags2e8;
    BYTE Pad2ec[0x2f4 - 0x2ec];
    DWORD Flags2f4;

    __declspec(noinline) void eventUnnamed_13a(INT A);
    void eventUnnamed_139(INT A, FVector B, FVector C);
    __declspec(noinline) UBOOL TestFlag_92b20()
    {
        return Field238 && (Flags2f4 & 0x8000);
    }
};

// RVA 0x92a50: probe event, FName index 0x13a (probe bit 14).
void AActor::eventUnnamed_13a(INT A)
{
    if (!StateFrame || (StateFrame->ProbeMask & ((QWORD)1 << 14)))
    {
        struct { INT A; } Parms;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(FName((EName)0x13a)), &Parms);
    }
}

// RVA 0x92aa0: probe event, FName index 0x139 (probe bit 13).
void AActor::eventUnnamed_139(INT A, FVector B, FVector C)
{
    if (!StateFrame || (StateFrame->ProbeMask & ((QWORD)1 << 13)))
    {
        struct Unnamed_139_Parms { INT A; FVector B; FVector C; } Parms;
        Parms.A = A;
        Parms.B = B;
        Parms.C = C;
        ProcessEvent(FindFunctionChecked(FName((EName)0x139)), &Parms);
    }
}

// Base light record (inlined constructor). Name not recovered.
class UnnamedLight_92980Base
{
public:
    AActor *Actor;          // 0x00
    INT Revision;           // 0x04
    BYTE Pad08[0x34 - 0x08];
    DWORD Flag0 : 2;        // 0x34
    DWORD bFlag2 : 1;
    DWORD bFlag3 : 1;
    DWORD bFlag4 : 1;
    DWORD bFlag5 : 1;
    DWORD bFlag6 : 1;
    DWORD bFlag7 : 1;
    DWORD bFlag8 : 1;
    DWORD FlagRest : 23;
    INT Pad38;
    FLOAT Scale;            // 0x3c
    BYTE Pad40[0x280 - 0x40];

    UnnamedLight_92980Base(AActor *InActor)
    {
        Actor = InActor;
        bFlag2 = 0; bFlag3 = 0; bFlag4 = 0; bFlag5 = 0;
        bFlag6 = 0; bFlag7 = 0; bFlag8 = 0;
        Scale = 1.0f;
        Revision = -1;
        Update();
    }
    void Update();
};

// RVA 0x92980. Name not recovered; allocated with size 0x2a4.
class UnnamedLight_92980 : public UnnamedLight_92980Base
{
public:
    TArray<INT> ArrayA;     // 0x280
    TArray<INT> ArrayB;     // 0x28c
    TArray<INT> ArrayC;     // 0x298

    UnnamedLight_92980(AActor *InActor);
};

UnnamedLight_92980::UnnamedLight_92980(AActor *InActor)
    : UnnamedLight_92980Base(InActor), ArrayC(((InActor->Flags2e8 >> 17) & 1) * 4)
{
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *P) { return P; }
// Stand-in body for Update (retail 0x11de70, not part of this unit) so the
// linker gives it retail's register convention (this in EDI).
__declspec(noinline) void UnnamedLight_92980Base::Update() { for (INT i = 0; i < Revision; i++) Escape(Actor); }
struct BoxOwner { BYTE Pad[0x68]; FVector Center; FVector Extents; };
void Driver_92880(FBox *B, BoxOwner *O) { B->GetCenterAndExtents(O->Center, O->Extents); }
UBOOL Driver_92920(FBox *B, FVector P) { return FPointBoxIntersection(P, *B); }
UnnamedLight_92980 *Driver_92980(AActor *A, void *Mem) { Escape(&GMalloc); return new (Mem) UnnamedLight_92980(A); }
void Driver_92a50(AActor *A, INT X) { A->eventUnnamed_13a(X); }
void Driver_92aa0(AActor *A, INT X, FVector B, FVector C) { A->eventUnnamed_139(X, B, C); }
UBOOL Driver_92b20(AActor *A) { return A->TestFlag_92b20(); }
