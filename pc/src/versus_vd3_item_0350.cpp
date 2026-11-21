// Work item 0350: Versus RVA 0x99520-0x997b2 (LTCG object).
// Two UObject-derived classes whose Serialize writes an INT/FLOAT at 0x28
// and a TArray at 0x2c, plus the TArray serializers they use.
// Class names not recovered: UnnamedClass_99520 / UnnamedClass_99550.
// 0x99520 UnnamedClass_99520::Serialize  (TArray<_WORD> at 0x2c)
// 0x99550 UnnamedClass_99550::Serialize  (TArray<FUnnamedStruct_99630> at 0x2c)
// 0x99580 operator<<(FArchive&, TArray<FUnnamedStruct_99630>&)  (Ar in EAX, array in EBX)
// 0x99630 operator<<(FArchive&, FUnnamedStruct_99630&)          (Ar in ESI, item in EAX)
// 0x99710 operator<<(FArchive&, TArray<_WORD>&), bulk serializer (Ar in EAX, array in EBX)
typedef unsigned short TCHAR;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;                 // 0x10c73bf0

// Retail keeps this literal in writable data (0x10c748fc).
extern const TCHAR OperatorShlTArray[];  // L"operator<<(TArray)"

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);                    // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);                 // RVA 0x4550
    void Realloc(INT ElementSize);                          // RVA 0x4600
};
template<class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void Slot08(); virtual void Slot0c(); virtual void Slot10();
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    INT ArVer, ArNetVer, ArLicenseeVer, ArIsLoading, ArIsSaving, ArIsTrans, ArIsPersistent;
    INT ArForEdit, ArForClient, ArForServer, ArIsError, ArIsCriticalError, ArContainsCode;
    INT ArFlags3, ArMaxSerializeSize;
};

FArchive &SerializeIndex(FArchive &Ar, INT &Value);   // RVA 0x1ea40

inline FArchive &operator<<(FArchive &Ar, INT &V) { Ar.Serialize(&V, sizeof(V)); return Ar; }
inline FArchive &operator<<(FArchive &Ar, FLOAT &V) { Ar.Serialize(&V, sizeof(V)); return Ar; }

struct FVector
{
    FLOAT X, Y, Z;
};
inline FArchive &operator<<(FArchive &Ar, FVector &V)
{
    return Ar << V.X << V.Y << V.Z;
}

// 64-byte element; field meanings not recovered.
struct FUnnamedStruct_99630
{
    FLOAT A, B, C;
    FVector V;
    FLOAT D0, D1, D2, D3, D4, D5, D6, D7, D8, D9;
};

__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedStruct_99630 &S)
{
    return Ar << S.A << S.B << S.C << S.V << S.D0 << S.D1 << S.D2 << S.D3 << S.D4
              << S.D5 << S.D6 << S.D7 << S.D8 << S.D9;
}

__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<FUnnamedStruct_99630> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FUnnamedStruct_99630), A.ArrayMax * sizeof(FUnnamedStruct_99630));
    if (Ar.ArIsLoading) {
        INT NewNum;
        SerializeIndex(Ar, NewNum);
        A.Empty(sizeof(FUnnamedStruct_99630), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.FArray::Add(1, sizeof(FUnnamedStruct_99630)));
    } else {
        SerializeIndex(Ar, A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<_WORD> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(_WORD), A.ArrayMax * sizeof(_WORD));
    SerializeIndex(Ar, A.ArrayNum);
    if (Ar.ArIsLoading) {
        A.ArrayMax = A.ArrayNum;
        if (!A.Data) {
            if (!A.ArrayNum)
                return Ar;
            A.Data = GMalloc->Malloc(A.ArrayNum * sizeof(_WORD), OperatorShlTArray);
        } else if (A.ArrayNum) {
            A.Realloc(sizeof(_WORD));
        } else {
            A.ArrayNum = 0;
            A.ArrayMax = 0;
            GMalloc->Free(A.Data);
            A.Data = 0;
            return Ar;
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(_WORD));
    return Ar;
}

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    void *Class;
    void Serialize(FArchive &Ar);                         // RVA 0x15f50
};

class UnnamedClass_99520 : public UObject
{
public:
    INT Field28;
    TArray<_WORD> Words;
    void Serialize(FArchive &Ar);
};

class UnnamedClass_99550 : public UObject
{
public:
    INT Field28;
    TArray<FUnnamedStruct_99630> Items;
    void Serialize(FArchive &Ar);
};

__declspec(noinline) void UnnamedClass_99520::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << Field28 << Words;
}

__declspec(noinline) void UnnamedClass_99550::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << Field28 << Items;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
// Stand-in for the compact index serializer (RVA 0x1ea40), defined so the
// link gives calls to it retail's convention (Ar in ESI, value in EDI).
__declspec(noinline) FArchive &SerializeIndex(FArchive &Ar, INT &Value)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving) {
        Ar.Serialize(&Value, sizeof(INT));
        return Ar;
    }
    unsigned char B0 = (unsigned char)Value;
    Ar.Serialize(&B0, 1);
    Value = B0;
    return Ar;
}
void Driver_99520(UnnamedClass_99520 *A, UnnamedClass_99550 *B, FArchive *Ar)
{
    Escape(&GMalloc);
    void (UnnamedClass_99520::*PA)(FArchive &) = &UnnamedClass_99520::Serialize;
    void (UnnamedClass_99550::*PB)(FArchive &) = &UnnamedClass_99550::Serialize;
    Escape(&PA);
    Escape(&PB);
    (A->*PA)(*Ar);
    (B->*PB)(*Ar);
}
