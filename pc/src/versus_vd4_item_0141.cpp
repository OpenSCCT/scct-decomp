// Work item 0141: Versus RVA 0x3e260 (LTCG object).
// 0x3e260 is operator<<(FArchive&, TArray<T>&) instantiated for a 12-byte
// element holding an object reference and two 4-byte values (Ar in EAX, the
// array on the stack). The element type is not recovered: FObjectPair_3e260
// is a neutral name. Same template as the TArray<UObject*> serializer at
// 0xf85a0.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class UObject;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);                    // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);                 // RVA 0x4550
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
    virtual FArchive &operator<<(UObject *&Res);            // +0x18
    FArchive &operator<<(INT &V) { Serialize(&V, sizeof(V)); return *this; }
    INT ArVer, ArNetVer, ArLicenseeVer, ArIsLoading, ArIsSaving;
};

FArchive &SerializeIndex(FArchive &Ar, INT &Value);   // RVA 0x1ea40

// Neutral name: element type not recovered.
struct FObjectPair_3e260
{
    UObject *Object;
    INT A;
    INT B;
    friend FArchive &operator<<(FArchive &Ar, FObjectPair_3e260 &P)
    {
        return Ar << P.Object << P.A << P.B;
    }
};

// RVA 0x3e260
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<FObjectPair_3e260> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FObjectPair_3e260), A.ArrayMax * sizeof(FObjectPair_3e260));
    if (Ar.ArIsLoading) {
        INT NewNum;
        SerializeIndex(Ar, NewNum);
        A.Empty(sizeof(FObjectPair_3e260), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.FArray::Add(1, sizeof(FObjectPair_3e260)));
    } else {
        SerializeIndex(Ar, A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
// Stand-in for the compact index serializer (RVA 0x1ea40).
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
void Driver_3e260(FArchive &Ar, TArray<FObjectPair_3e260> &A)
{
    Ar << A;
}
