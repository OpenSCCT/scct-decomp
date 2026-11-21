// Work item w3 0138: Versus RVA 0xc14e0-0xc194c. LTCG unit (custom conventions):
// five TArray serializers (operator<<(FArchive&, TArray<T>&), UnTemplate.h).
//
//   0xc14e0  bulk TArray<UnnamedStruct48_c14e0> serializer   (Ar in EAX, array in EBX)
//   0xc1580  TArray<UnnamedStruct16_c1580>                  (Ar in EAX, array on the stack)
//   0xc16a0  TArray<UnnamedStruct20_c16a0>                  (Ar in EAX, array in EBX)
//   0xc1750  TArray<UnnamedStruct16_c1750>                  (Ar in EAX, array on the stack)
//   0xc1880  TArray<UnnamedStruct272_c1880>                 (Ar on the stack, array in EBX)
//
// Element type names are neutral: the evidence gives only their sizes and
// how their fields are serialized.
// All five match with try_ltcg.py --flags "/O2 /Gy /GX" and
// --root "?Driver_<rva>@@YAXPAVFArchive@@PAUHolder_c14e0@@1@Z" (0xc1880 needs /GX:
// its element constructor 0xc21f0 has an exception frame, which gives it the
// this-on-the-stack convention and pushes Ar onto the stack in 0xc1880).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

class UObject;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR TEXT_operator_TArray[];   // L"operator<<(TArray)"

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
    INT LicenseeVer() { return ArLicenseeVer; }

    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);   // 0x1ea40

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
};

inline void *operator new(unsigned int, void *Mem) { return Mem; }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
    void Realloc(INT ElementSize);              // 0x4600
};

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack = 0) { FArray::Empty(sizeof(T), Slack); }
    INT Add(INT Count) { return FArray::Add(Count, sizeof(T)); }

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

// UnTemplate.h: placement new that appends one element to the array.
template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

// ---------------------------------------------------------------------------
// RVA 0xc14e0: a 48-byte plain record array serialized in bulk.
struct UnnamedStruct48_c14e0
{
    BYTE Bytes[0x30];
};

FArchive &operator<<(FArchive &Ar, TArray<UnnamedStruct48_c14e0> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) {
            if (A.ArrayMax == 0)
                return Ar;
            A.Data = GMalloc->Malloc(A.ArrayMax * sizeof(UnnamedStruct48_c14e0), TEXT_operator_TArray);
        } else if (A.ArrayMax) {
            A.Realloc(sizeof(UnnamedStruct48_c14e0));
        } else {
            A.ArrayNum = 0;
            A.ArrayMax = 0;
            GMalloc->Free(A.Data);
            A.Data = 0;
            return Ar;
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(UnnamedStruct48_c14e0));
    return Ar;
}

// ---------------------------------------------------------------------------
// RVA 0xc1580: a 4-byte field followed by a vector (serialized through the
// vector's own inline operator<<).
struct FVector
{
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V) { return Ar << V.X << V.Y << V.Z; }
};
struct UnnamedStruct16_c1580
{
    INT A;          // 0x00
    FVector V;      // 0x04
    friend FArchive &operator<<(FArchive &Ar, UnnamedStruct16_c1580 &S)
    {
        return Ar << S.A << S.V;
    }
};

// ---------------------------------------------------------------------------
// RVA 0xc16a0: 20-byte record whose serializer (0xc2cf0) lives out of line.
struct UnnamedStruct20_c16a0
{
    INT A, B, C, D, E;
};
FArchive &operator<<(FArchive &Ar, UnnamedStruct20_c16a0 &S);   // 0xc2cf0

// ---------------------------------------------------------------------------
// RVA 0xc1750: 16-byte record; field 8 was added at licensee version 9 and
// defaults to 1 in older archives.
struct UnnamedStruct16_c1750
{
    INT A;          // 0x00
    INT B;          // 0x04
    UBOOL C;        // 0x08
    INT D;          // 0x0c
    friend FArchive &operator<<(FArchive &Ar, UnnamedStruct16_c1750 &S)
    {
        Ar << S.A << S.D << S.B;
        if (Ar.LicenseeVer() < 9)
            S.C = 1;
        else
            Ar << *(INT *)&S.C;
        return Ar;
    }
};

// ---------------------------------------------------------------------------
// RVA 0xc1880: 272-byte record with constructor (0xc21f0), destructor and an
// out-of-line serializer (0xc2710).
struct UnnamedMember_c1880
{
    BYTE Bytes[0x1c];
    UnnamedMember_c1880();        // 0x2126e0
    ~UnnamedMember_c1880();
};
struct UnnamedStruct272_c1880
{
    BYTE Bytes[0x1c];
    TArray<UnnamedStruct48_c14e0> ArrA;   // 0x1c
    TArray<UnnamedStruct48_c14e0> ArrB;   // 0x28
    UnnamedMember_c1880 M1;       // 0x34
    UnnamedMember_c1880 M2;       // 0x50
    BYTE Tail[0x110 - 0x6c];
    UnnamedStruct272_c1880();     // 0xc21f0
    ~UnnamedStruct272_c1880();
};
FArchive &operator<<(FArchive &Ar, UnnamedStruct272_c1880 &S);   // 0xc2710

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit.
//
// 0x1ea40 (archive in ESI, index in EDI in retail), from item 0116.
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
    Ar.Serialize(&B0, 1);
    if (B0 & 0x40) {
        V >>= 6;
        BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
        Ar.Serialize(&B1, 1);
        if (B1 & 0x80) {
            V >>= 7;
            BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar.Serialize(&B2, 1);
            if (B2 & 0x80) {
                V >>= 7;
                BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar.Serialize(&B3, 1);
                if (B3 & 0x80) {
                    V >>= 7;
                    BYTE B4 = V;
                    Ar.Serialize(&B4, 1);
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

// 0xc2cf0 (record in EAX in retail); the real body is in another unit.
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedStruct20_c16a0 &S)
{
    return Ar << S.A << S.B << S.C << S.D << S.E;
}

// 0xc21f0 (this on the stack, ret 4), destructor, TArray::Empty at 0xc2300
// (array in ESI) and the record serializer 0xc2710 (Ar in EAX, record on the
// stack). These are stand-ins shaped like retail's bodies (0xc2710 serializes
// two bulk arrays at 0x1c/0x28) so the link gives them retail's conventions;
// they are not matched here.
extern INT GRecordCount_c1880;
__declspec(noinline) UnnamedStruct272_c1880::UnnamedStruct272_c1880() { Bytes[0] = 0; GRecordCount_c1880++; }
UnnamedStruct272_c1880::~UnnamedStruct272_c1880() { GRecordCount_c1880--; }
template <> __declspec(noinline) void TArray<UnnamedStruct272_c1880>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~UnnamedStruct272_c1880();
    FArray::Empty(sizeof(UnnamedStruct272_c1880), Slack);
}
__declspec(noinline) void SerializeHead_c1880(FArchive &Ar, UnnamedStruct272_c1880 &S)
{
    for (INT i = 0; i < 3; i++)
        Ar.Serialize(S.Bytes + i * 4, 4);
}
__declspec(noinline) void SerializeMember_c1880(FArchive &Ar, UnnamedMember_c1880 *M)
{
    Ar.Serialize(M->Bytes, 4);
    Ar.Serialize(M->Bytes + 4, 4);
}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedStruct272_c1880 &S)
{
    SerializeHead_c1880(Ar, S);
    SerializeMember_c1880(Ar, &S.M1);
    Ar.Serialize(S.Bytes + 0x18, 4);
    Ar << S.ArrA;
    Ar << S.ArrB;
    SerializeMember_c1880(Ar, &S.M2);
    Ar.Serialize(S.Tail - 0x6c + 0xf8, 4);
    Ar.Serialize(S.Tail - 0x6c + 0xfc, 4);
    Ar.Serialize(S.Tail - 0x6c + 0x100, 4);
    Ar.Serialize(S.Tail - 0x6c + 0x104, 4);
    Ar.Serialize(S.Tail - 0x6c + 0x108, 4);
    Ar.Serialize(S.Tail - 0x6c + 0x10c, 4);
    return Ar;
}

void Escape(void *);

struct Holder_c14e0
{
    TArray<UnnamedStruct48_c14e0> A;
    TArray<UnnamedStruct16_c1580> B;
    TArray<UnnamedStruct20_c16a0> C;
    TArray<UnnamedStruct16_c1750> D;
    TArray<UnnamedStruct272_c1880> E;
};

void Driver_c14e0(FArchive *Ar, Holder_c14e0 *H, Holder_c14e0 *H2)
{
    Escape(&GMalloc);
    *Ar << H->A;
    *Ar << H2->A;
}
void Driver_c1580(FArchive *Ar, Holder_c14e0 *H, Holder_c14e0 *H2)
{
    *Ar << H->B;
    *Ar << H2->B;
}
void Driver_c16a0(FArchive *Ar, Holder_c14e0 *H, Holder_c14e0 *H2)
{
    *Ar << H->C;
    *Ar << H2->C;
}
void Driver_c1750(FArchive *Ar, Holder_c14e0 *H, Holder_c14e0 *H2)
{
    *Ar << H->D;
    *Ar << H2->D;
}
// Like retail's caller at 0xb4dfb: Ar kept in a register across the call and
// used again afterwards, a global flag saved and set around it.
extern INT GSerializeFlag_c1880;
void Driver_c1880(FArchive *Ar, Holder_c14e0 *H, Holder_c14e0 *H2)
{
    if (Ar->ArVer >= 2) {
        INT Saved = GSerializeFlag_c1880;
        GSerializeFlag_c1880 = 1;
        *Ar << H->E;
        Ar->Serialize(H2, 4);
        Ar->Serialize(H, 4);
        GSerializeFlag_c1880 = Saved;
    }
}
