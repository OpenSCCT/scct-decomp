// Work item 0335: Versus RVA 0x92200-0x92508. LTCG unit (custom conventions).
//
//   0x92200  UnnamedClass_92200::SetPair      (this in EDX, Key in EBX, Value on the stack)
//   0x92280  FindObjectFast<UUnnamedClass_92280> (last argument in EAX)
//   0x92300  Exchange<FVector>                (A in ECX, B in EAX)
//   0x92360  operator<<(FArchive&, TArray<FRecordA*>&)  (Ar in EAX, array in EBX)
//   0x92420  operator<<(FArchive&, TArray<FRecordB*>&)  (Ar in EAX, array in EBX)
//   0x922b0  another 12-byte Exchange instance; not matched (retail keeps the
//            temporary on the stack, our builds keep it in registers).
//
// Class and record names marked Unnamed/FRecord are neutral: the evidence
// gives only their layouts.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

class UObject;
class UClass;

// ---------------------------------------------------------------------------
// Core declarations (layouts follow Unreal Engine 2).

class FName
{
public:
    INT Index;
    FName() {}
    FName(INT N) : Index(N) {}
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);         // 0x44e0
    void Empty(INT ElementSize, INT Slack);      // 0x4550
};

struct FCompactIndex
{
    INT Value;
};
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

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);   // 0x1ea40

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
};

inline void *operator new(unsigned int Size, void *Mem) { return Mem; }

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Empty(INT Slack = 0) { FArray::Empty(sizeof(T), Slack); }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    friend FArchive &operator<<(FArchive &Ar, TArray &A)
    {
        A.CountBytes(Ar);
        if (Ar.IsLoading()) {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << *new(A) T;
        } else {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

// ---------------------------------------------------------------------------
// RVA 0x92200: a table of four key/value pairs at 0x10c, cleared first when
// the flag bit at 0x2e8 is set. Updates the pair holding Key, else fills the
// first empty slot.

struct FPair
{
    INT Key;
    INT Value;
};

class UnnamedClass_92200
{
public:
    BYTE Pad0[0x10c];
    FPair Pairs[4];                  // 0x10c
    BYTE Pad1[0x2e8 - 0x12c];
    DWORD bResetPairs : 1;           // 0x2e8 bit 0

    void SetPair(INT Key, INT Value);
};

void UnnamedClass_92200::SetPair(INT Key, INT Value)
{
    INT i;
    if (bResetPairs) {
        for (i = 0; i < 4; i++) {
            Pairs[i].Key = 0;
            Pairs[i].Value = 0;
        }
        bResetPairs = 0;
    }
    for (i = 0; i < 4; i++) {
        if (Pairs[i].Key == Key) {
            Pairs[i].Value = Value;
            return;
        }
    }
    for (i = 0; i < 4; i++) {
        if (Pairs[i].Key == 0) {
            Pairs[i].Key = Key;
            Pairs[i].Value = Value;
            return;
        }
    }
}

// ---------------------------------------------------------------------------
// RVA 0x92280: typed wrapper around the object finder at 0x17720 (it treats
// its second argument as a package, -1 meaning any package). The three
// name-like arguments are small objects passed by value (retail callers
// build them in place).

class UObjectFinder
{
public:
    static UObject *StaticFindObjectFast(UClass *ObjectClass, UObject *ObjectPackage,
                                         FName A, FName B, FName C, DWORD Flags);   // 0x17720
};

class UUnnamedClass_92280
{
public:
    static UClass PrivateStaticClass;    // retail 0x10cc8610
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template <class T> T *FindObjectFast(UObject *Outer, FName A, FName B, FName C, DWORD Flags)
{
    return (T *)UObjectFinder::StaticFindObjectFast(T::StaticClass(), Outer, A, B, C, Flags);
}

// ---------------------------------------------------------------------------
// RVA 0x92300: Exchange (UnTemplate.h) for a 12-byte vector.

struct FVector
{
    FLOAT X, Y, Z;
};

template <class T> void Exchange(T &A, T &B)
{
    const T Temp = A;
    A = B;
    B = Temp;
}

// ---------------------------------------------------------------------------
// RVA 0x92360 / 0x92420: TArray serialisation for two record-pointer arrays.

struct FRecordA
{
    BYTE Pad[0x18];
    UObject *ObjA;      // 0x18
    UObject *ObjB;      // 0x1c
    friend FArchive &operator<<(FArchive &Ar, FRecordA *R) { return Ar << R->ObjA << R->ObjB; }
};

struct FRecordB
{
    FRecordA *Record;   // 0x00
    UObject *Obj;       // 0x04
    friend FArchive &operator<<(FArchive &Ar, FRecordB *R) { return Ar << R->Record << R->Obj; }
};

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit.
//
// The compact-index serializer lives in another object (RVA 0x1ea40, item
// 0116); it is defined here only so the link gives it the retail convention
// (archive in ESI, index in EDI).
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
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
    return Ar;
}

// Retail caller of SetPair (0xe0910): this = [obj+0x5c], Key = [obj+0x28], Value = obj.
struct Caller_92200
{
    BYTE Pad0[0x28];
    INT Key;                          // 0x28
    BYTE Pad1[0x5c - 0x2c];
    UnnamedClass_92200 *Target;       // 0x5c
};
void Driver_92200(Caller_92200 *C, INT K)
{
    C->Target->SetPair(C->Key, (INT)C);
    C->Target->SetPair(K, (INT)C->Target);
}

extern UObject *GFindOuter;
void Driver_92280(INT N, UUnnamedClass_92280 **Out)
{
    Out[0] = FindObjectFast<UUnnamedClass_92280>(GFindOuter, FName(0), FName(0), FName(N), 0);
    Out[1] = FindObjectFast<UUnnamedClass_92280>(GFindOuter, FName(1), FName(0), FName(N), 0);
}

void Driver_92300(FVector *A, FVector *B)
{
    Exchange(*A, *B);
}

// Retail caller (0x90b00) chains both arrays: Ar << A << B.
struct Holder_92360
{
    TArray<FRecordA *> A;
    TArray<FRecordB *> B;
};
void Driver_92360(FArchive *Ar, Holder_92360 *H, Holder_92360 *H2)
{
    *Ar << H->A << H->B;
    *Ar << H2->A << H2->B;
}
