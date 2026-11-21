// Work item w3 0142 (Versus RVA 0xc26a0-0xc2ad3): archive serializers for a
// group of packed animation/mesh records. The record names are not
// recovered; neutral names are used (FUnnamedRecord_<rva>).
// These functions come from a /GL + /LTCG object: the archive and the
// record travel in registers (EAX/ESI/EBX/EDI), chosen by the linker.
// Checked with try_ltcg.py: 0xc26a0, 0xc2830, 0xc2950, 0xc2a00 with /O2 /Gy and
// root Driver_c2830; 0xc2a80 with /O2 /Gy /Ob1 and root Driver_c2a80.
// 0xc2710 (the record that owns all of these) is not done: it calls six
// serializers outside this item whose register conventions need their bodies.
typedef unsigned short TCHAR;
typedef unsigned short _WORD;
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
    // MSVC lays overloaded virtuals out in reverse order.
    virtual FArchive &operator<<(class FName &N);           // +0x1c
    virtual FArchive &operator<<(UObject *&Res);            // +0x18

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    UBOOL IsPersistent() { return ArIsPersistent; }

    friend FArchive &operator<<(FArchive &Ar, _WORD &W) { Ar.Serialize(&W, 2); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);   // 0x1ea40

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
    UBOOL ArIsPersistent;
};

// RVA 0x1ea40 (published in versus_vd2_item_0116.cpp); defined here so the
// link gives it the same register convention (archive in ESI, index in EDI).
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

template <class T> FArchive &operator<<(FArchive &Ar, TArray<T> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.Add(1, sizeof(T)));
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// Eight packed words (16 bytes).
struct FUnnamedRecord_c26a0
{
    _WORD W[8];
    friend FArchive &operator<<(FArchive &Ar, FUnnamedRecord_c26a0 &R);
};

// RVA 0xc26a0.
FArchive &operator<<(FArchive &Ar, FUnnamedRecord_c26a0 &R)
{
    return Ar << R.W[0] << R.W[1] << R.W[2] << R.W[3] << R.W[4] << R.W[5] << R.W[6] << R.W[7];
}

// Four 32-bit values (16 bytes), serialized inline.
struct FUnnamedRecord_c2830
{
    FLOAT X, Y, Z, W;
    FUnnamedRecord_c2830() {}
    friend FArchive &operator<<(FArchive &Ar, FUnnamedRecord_c2830 &R)
    {
        return Ar << R.X << R.Y << R.Z << R.W;
    }
};

// RVA 0xc2830: operator<<(FArchive&, TArray<FUnnamedRecord_c2830>&), the
// template above instantiated.
template FArchive &operator<<(FArchive &Ar, TArray<FUnnamedRecord_c2830> &A);

// 20-byte record: nine words; the word at +0x0a is not serialized.
struct FUnnamedRecord_c2a00
{
    _WORD A0, A1, A2, A3, A4;
    _WORD Unused0A;
    _WORD B0, B1, B2, B3;
    friend FArchive &operator<<(FArchive &Ar, FUnnamedRecord_c2a00 &R);
};

// RVA 0xc2a00.
FArchive &operator<<(FArchive &Ar, FUnnamedRecord_c2a00 &R)
{
    return Ar << R.A0 << R.A1 << R.A2 << R.A3 << R.A4 << R.B0 << R.B1 << R.B2 << R.B3;
}

// RVA 0xc2950: operator<<(FArchive&, TArray<FUnnamedRecord_c2a00>&), the
// template above instantiated.
template FArchive &operator<<(FArchive &Ar, TArray<FUnnamedRecord_c2a00> &A);

// Element of the array at +0x20 of FUnnamedRecord_c2a80 (not recovered).
struct FUnnamedRecord_afd420
{
    INT Unknown[4];
    friend FArchive &operator<<(FArchive &Ar, FUnnamedRecord_afd420 &R);
};

// 0x2c-byte record: two object references, three ints and an array.
struct FUnnamedRecord_c2a80
{
    INT Unknown00;
    UObject *ObjectA;
    UObject *ObjectB;
    INT Unknown0C;
    INT Unknown10;
    INT IntA;
    INT IntB;
    INT IntC;
    TArray<FUnnamedRecord_afd420> Items;
    friend FArchive &operator<<(FArchive &Ar, FUnnamedRecord_c2a80 &R);
};

// RVA 0xc2a80.
FArchive &operator<<(FArchive &Ar, FUnnamedRecord_c2a80 &R)
{
    if (!Ar.IsPersistent()) {
        Ar << R.ObjectA;
        Ar << R.ObjectB;
    }
    Ar << R.IntA << R.IntB << R.IntC;
    Ar << R.Items;
    return Ar;
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c2a80(FArchive *Ar, FUnnamedRecord_c2a80 *Q, TArray<FUnnamedRecord_c2830> *A, TArray<FUnnamedRecord_c2a00> *B, INT *I)
{
    *Ar << *A;
    *Ar << I[0];
    *Ar << *B;
    *Ar << B[1];
    *Ar << I[1];
    *Ar << I[2];
    *Ar << *Q;
    *Ar << I[3] << I[4] << I[5] << I[6] << I[7] << I[8];
}
void Driver_c2830(FArchive *Ar, TArray<FUnnamedRecord_c2830> *A, TArray<FUnnamedRecord_c2a00> *B, FUnnamedRecord_c26a0 *R)
{
    *Ar << *A;
    *Ar << *B;
    *Ar << *R;
}
