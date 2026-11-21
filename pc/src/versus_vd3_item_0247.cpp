// Work item 0247 (RVA 0x5aec0): the TArray serializer (UnTemplate.h
// operator<<(FArchive&, TArray<T>&)) instantiated for a 12-byte element whose
// object reference (0x04) and 4-byte value (0x08) are serialized; the element
// type is not recovered (neutral name after the RVA).
// Built with /GL and linked with /LTCG: it takes the archive in EAX and the
// array on the stack. The compact index serializer (0x1ea40) takes the archive
// in ESI and the index in EDI; it is defined here (body from item 0116) so the
// link gives it that convention.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

class UObject;

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
    virtual FArchive &operator<<(class FName &N);           // +0x1c
    virtual FArchive &operator<<(UObject *&Res);            // +0x18

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, INT &I)
    {
        Ar.Serialize(&I, sizeof(I));
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
};

// RVA 0x1ea40 (not part of this item; defined for its register convention).
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

inline void *operator new(unsigned int Size, void *Mem) { return Mem; }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);           // 0x44e0
    void Empty(INT ElementSize, INT Slack);        // 0x4550
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar)
    {
        Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T));
    }
    void Empty(INT Slack) { FArray::Empty(sizeof(T), Slack); }
};

template <class T> inline void *operator new(unsigned int Size, TArray<T> &A)
{
    INT Index = A.Add(1, sizeof(T));
    return &A(Index);
}

// UnTemplate.h TArray serializer (a friend of TArray in Unreal's source).
template <class T> FArchive &operator<<(FArchive &Ar, TArray<T> &A)
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

struct UnnamedStruct_5aec0
{
    INT Unknown0;       // 0x00, not serialized
    UObject *Object;    // 0x04
    INT Value;          // 0x08

    friend FArchive &operator<<(FArchive &Ar, UnnamedStruct_5aec0 &S)
    {
        return Ar << S.Object << S.Value;
    }
};

// RVA 0x5aec0: operator<<(FArchive&, TArray<UnnamedStruct_5aec0>&).
// (instantiated by its use below)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_5aec0(FArchive *Ar, TArray<UnnamedStruct_5aec0> *A, FCompactIndex *I)
{
    Escape(&(*Ar << *A));
    Escape(&(*Ar << *I));
}
