// Work item w3 0346: Versus RVA 0x110940-0x110d03 (LTCG object).
// TArray template instantiations for three unidentified element types
// (neutral names): a 16-byte {UObject*, FString} pair with a constructor and
// destructor, a 20-byte record of four INTs and a BYTE, and an 8-byte record
// whose two WORDs at +4/+6 are serialized. Plus the implicit destructor of an
// unidentified record holding an 8-byte-element TArray and a raw buffer.
// LTCG conventions: the compact-index serializer takes the archive in ESI and
// the index in EDI; the FString serializer takes the archive in EAX.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short _WORD;

class UObject;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

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

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, _WORD &W) { Ar.Serialize(&W, 2); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
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
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Add(INT Count, INT ElementSize);                // 0x44e0
    void Empty(INT ElementSize, INT Slack);             // 0x4550
    void Remove(INT Index, INT Count, INT ElementSize); // 0x119c0
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    __declspec(noinline) ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    void Empty(INT Slack = 0)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }

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
    INT Index = Array.Add(1, sizeof(T));
    return &((T *)Array.Data)[Index];
}

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    ~FString();
};

// RVA 0x1ea40 (published in versus_vd2_item_0116.cpp).
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

// 16-byte plain element of the pair's inner array (neutral name); its array
// serializer is RVA 0xc2830 (not part of this unit).
struct UnnamedElem16_c2830
{
    INT A, B, C, D;
    friend FArchive &operator<<(FArchive &Ar, UnnamedElem16_c2830 &E)
    {
        return Ar << E.A << E.B << E.C << E.D;
    }
};

// 16-byte element (neutral name): constructor RVA 0xcd0e0, destructor RVA 0x110990.
struct UnnamedPair_110990
{
    UObject *Object;
    TArray<UnnamedElem16_c2830> Items;
    __declspec(noinline) UnnamedPair_110990() {}
    __declspec(noinline) ~UnnamedPair_110990() {}
    friend FArchive &operator<<(FArchive &Ar, UnnamedPair_110990 &P)
    {
        return Ar << P.Object << P.Items;
    }
};

// RVA 0x110940 and 0x110ba0: the pair array's Remove and Empty, which retail
// keeps out of line (the generic inline bodies, not inlined for this type).
template <> __declspec(noinline) void TArray<UnnamedPair_110990>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~UnnamedPair_110990();
    FArray::Remove(Index, Count, sizeof(UnnamedPair_110990));
}
template <> __declspec(noinline) void TArray<UnnamedPair_110990>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~UnnamedPair_110990();
    FArray::Empty(sizeof(UnnamedPair_110990), Slack);
}

// 20-byte element (neutral name).
struct UnnamedRecord20_110a70
{
    INT A, B, C, D;
    BYTE E;
    friend FArchive &operator<<(FArchive &Ar, UnnamedRecord20_110a70 &R)
    {
        return Ar << R.A << R.B << R.C << R.D << R.E;
    }
};

// 8-byte element (neutral name); only the two WORDs are serialized.
struct UnnamedRecord8_110be0
{
    INT Key;
    _WORD X, Y;
    friend FArchive &operator<<(FArchive &Ar, UnnamedRecord8_110be0 &R)
    {
        return Ar << R.X << R.Y;
    }
};

// Out-of-line array destructor (RVA 0x17f6a0 for 8-byte elements, 0x1fb4d0 for
// 16-byte elements; not part of this unit).
template <class T> __declspec(noinline) TArray<T>::~TArray()
{
    FArray::Remove(0, ArrayNum, sizeof(T));
}

// Raw buffer member (neutral name).
struct UnnamedBuffer_110ca0
{
    void *Data;
    INT Size;
    ~UnnamedBuffer_110ca0()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        Size = 0;
    }
};

// RVA 0x110ca0: implicit destructor of an unidentified record.
struct UnnamedRecord_110ca0
{
    TArray<UnnamedRecord8_110be0> Items;   // 0x00
    UnnamedBuffer_110ca0 Buffer;           // 0x0c
    __declspec(noinline) ~UnnamedRecord_110ca0() {}
};

// Scaffolding for the link, not part of the unit.
template class TArray<UnnamedRecord20_110a70>;
template class TArray<UnnamedRecord8_110be0>;
void Escape(void *);
void Driver_110940(TArray<UnnamedPair_110990> *A16, TArray<UnnamedRecord20_110a70> *A20,
    TArray<UnnamedRecord8_110be0> *A8, FArchive *Ar, INT I, INT C, UnnamedRecord_110ca0 *R)
{
    Escape(&GMalloc);
    A16->Remove(I, C);
    *Ar << *A16;
    *Ar << *A20;
    *Ar << *A8;
    R->~UnnamedRecord_110ca0();
}
