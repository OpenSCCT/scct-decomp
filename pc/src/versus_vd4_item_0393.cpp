// Work item 0393 (RVA 0xa6f50-0xa7095): the TArray<FUntransformedVertex>
// serializer (0xa6f50, array in EBX, archive in EAX) and the
// FUntransformedVertex serializer (0xa7000, archive in ESI, vertex in EAX).
// Both are LTCG-compiled inline friends from the UE2 headers. The 0x2c-byte
// element (Position, Normal, Color, U, V, U2, V2) matches UE2's
// FUntransformedVertex used by the neighbouring UVertexBuffer; Color is
// serialized as one 4-byte value here, so it is declared as a DWORD.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

#pragma pack(push, 4)

class UObject;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

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

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F)
    {
        Ar.Serialize(&F, 4);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, DWORD &D)
    {
        Ar.Serialize(&D, 4);
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

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
};

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack) { FArray::Empty(sizeof(T), Slack); }

};

class FVector
{
public:
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V)
    {
        return Ar << V.X << V.Y << V.Z;
    }
};

struct FUntransformedVertex
{
    FVector Position;
    FVector Normal;
    DWORD Color;
    FLOAT U, V;
    FLOAT U2, V2;

    friend FArchive &operator<<(FArchive &Ar, FUntransformedVertex &V)
    {
        return Ar << V.Position << V.Normal << V.Color << V.U << V.V << V.U2 << V.V2;
    }
};

template <class T> FArchive &operator<<(FArchive &Ar, TArray<T> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(&((T *)A.Data)[A.Add(1, sizeof(T))]) T;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

#pragma pack(pop)

// RVA 0x1ea40 (matched in item 0116; defined here so the link gives
// it retail's ESI/EDI convention). Not part of this item.
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

// RVA 0xa6f50: operator<<(FArchive &, TArray<FUntransformedVertex> &).
// RVA 0xa7000: operator<<(FArchive &, FUntransformedVertex &).
// Both are generated from the inline friends above.

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_a6f50(FArchive *Ar, TArray<FUntransformedVertex> *A)
{
    *Ar << *A;
}
