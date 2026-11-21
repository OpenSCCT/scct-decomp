// Work item w3 0314: Versus RVA 0x1097c0-0x109a93 (LTCG objects, VC7.0 /GL).
// Three instantiations of TArray<T>'s operator<<(FArchive&, TArray<T>&) from
// UE2 UnTemplate.h, for element types whose names are not recovered (neutral
// names after their size):
//  0x1097c0  TArray<UnnamedElement_70>: archive and array on the stack; the
//            element serializer is inlined (FName, a 4-byte-item array, a
//            QWORD and an INT, plus a version-gated record when ArVer >= 0x74).
//  0x109930  TArray<UnnamedElement_38>: array in EBX, archive on the stack.
//  0x1099f0  TArray<UnnamedElement_4>: archive in EAX, array on the stack.
// Callees are written out so the link gives each call its retail register
// convention. Several of them also match retail (listed near the end); the
// ones built from Touch() calls, and the 4-byte-item array serializer at
// 0xc3280, are stand-ins only.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;
typedef float FLOAT;

#pragma pack(push, 4)

inline void *operator new(unsigned int, void *Mem) { return Mem; }

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

struct FName
{
    INT Index;
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(void *Object);                     // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual FArchive &operator<<(FName &N);                 // +0x18

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, INT &I)
    {
        Ar.Serialize(&I, 4);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F)
    {
        Ar.Serialize(&F, 4);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, QWORD &Q)
    {
        Ar.Serialize(&Q, 8);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);   // RVA 0x1ea40

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
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);        // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);     // RVA 0x4550
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack = 0);

};

// UE2 placement new into an array (UnTemplate.h).
inline void *operator new(unsigned int Size, FArray &Array)
{
    INT Index = Array.Add(1, Size);
    return (BYTE *)Array.Data + Index * Size;
}

// UE2 TArray serializer (a friend template in UnTemplate.h).
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

// TArray<T>::Empty (instantiations published in w3 item 0313, 0x109670 and
// 0x1096b0).
template <class T> __declspec(noinline) void TArray<T>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~T();
    FArray::Empty(sizeof(T), Slack);
}

void Touch(void *);

// RVA 0x1ea40 (published elsewhere; defined here so the link gives it its
// register convention).
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


// Sub-records of the 0x70-byte element (neutral names).
// +0x08 is a TArray of 4-byte items; its serializer (RVA 0xc3280) is a
// separate instantiation with a bulk path, stood in here.
struct UnnamedRecord_c : public FArray {};      // serializer RVA 0xc3280
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedRecord_c &A)
{
    Ar.CountBytes(A.ArrayNum * 4, A.ArrayMax * 4);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) { A.ArrayMax = A.ArrayNum; Touch(A.Data); }
    Ar.Serialize(A.Data, A.ArrayNum * 4);
    return Ar;
}
struct UnnamedVec_18
{
    BYTE Pad[0x18];
    UnnamedVec_18();            // RVA 0x10a6b0
    ~UnnamedVec_18();           // RVA 0xa8df0
};
FArchive &operator<<(FArchive &Ar, UnnamedVec_18 &V);   // RVA 0xe5b80
BYTE CeilLogTwo_12050(INT V);                          // RVA 0x12050
// Polymorphic record (vtable 0x10c03ac8): ctor RVA 0x10a5c0, serializer RVA 0x10a6c0.
class UnnamedRecord_50
{
public:
    UnnamedRecord_50();
    ~UnnamedRecord_50();
    virtual void V00();
    UnnamedVec_18 V[2];         // +0x04, +0x1c
    BYTE B34;                   // +0x34
    INT I38;                    // +0x38
    INT I3c;                    // +0x3c
    INT I40, I44;
    INT I48;                    // +0x48
    BYTE B4c, B4d;              // +0x4c
};
__declspec(noinline) UnnamedRecord_50::UnnamedRecord_50() {}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedRecord_50 &R)
{
    Ar << R.V[0] << R.V[1];
    Ar.Serialize(&R.B34, 1);
    Ar << R.I38 << R.I3c << R.I48;
    R.B4c = CeilLogTwo_12050(R.I38);
    R.B4d = CeilLogTwo_12050(R.I3c);
    return Ar;
}

// 0x70-byte polymorphic element (vtable 0x10c03b18): ctor RVA 0x10a550,
// dtor RVA 0x9a8d90 (non-virtual: TArray::Empty calls it directly).
class UnnamedElement_70
{
public:
    virtual void V00();
    FName Name;                 // +0x04
    UnnamedRecord_c RecordA;    // +0x08
    UnnamedRecord_50 RecordB;   // +0x14
    QWORD Value64;              // +0x64
    INT Value6c;                // +0x6c
    UnnamedElement_70();
    ~UnnamedElement_70();

    friend FArchive &operator<<(FArchive &Ar, UnnamedElement_70 &E)
    {
        Ar << E.Name << E.RecordA << E.Value64 << E.Value6c;
        if (Ar.Ver() >= 0x74)
            Ar << E.RecordB;
        return Ar;
    }
};
__declspec(noinline) UnnamedElement_70::UnnamedElement_70() {}
__declspec(noinline) UnnamedElement_70::~UnnamedElement_70() { Touch(&Name); Touch(&Name); Touch(this); }

// Render-resource style head of the 0x38-byte element (vtable 0x10c03b58,
// neutral name): an item array, a cache id from the global counter and a
// revision; ctor RVA 0x10a250 (this in ESI).
// 0x28-byte item: two vectors and four floats; the second vector moved after
// the floats before version 0xab. Serializer RVA 0x10a480 (item in EAX,
// archive in ESI); its array serializer is the template above (RVA 0x10a3d0).
struct FVector
{
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V)
    {
        return Ar << V.X << V.Y << V.Z;
    }
};
struct UnnamedItem_28
{
    FVector A;                  // +0x00
    FVector B;                  // +0x0c
    FLOAT C[4];                 // +0x18
};
template <> inline void TArray<UnnamedItem_28>::Empty(INT Slack)
{
    FArray::Empty(sizeof(UnnamedItem_28), Slack);
}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedItem_28 &I)
{
    Ar << I.A;
    if (Ar.Ver() >= 0xab)
        Ar << I.B;
    Ar << I.C[0] << I.C[1] << I.C[2] << I.C[3];
    if (Ar.Ver() < 0xab)
        Ar << I.B;
    return Ar;
}
extern QWORD GCacheIDCounter;
struct UnnamedResource_1c
{
    virtual void V00();
    TArray<UnnamedItem_28> Items;   // +0x04
    QWORD CacheId;                  // +0x10
    INT Revision;                   // +0x18
    UnnamedResource_1c();
};
__declspec(noinline) UnnamedResource_1c::UnnamedResource_1c()
{
    CacheId = GCacheIDCounter++ * 256 + 0xe1;
    Revision = 0;
}

// 0x38-byte element: ctor RVA 0x10a220 (this in EAX), dtor RVA 0x9a8c70,
// serializer RVA 0x10a350 (element in EAX, archive on the stack).
struct UnnamedElement_38
{
    UnnamedResource_1c Res;         // +0x00
    INT Value1c;                    // +0x1c
    FName Name;                     // +0x20
    INT Value24;                    // +0x24
    INT Value28;                    // +0x28
    INT Value2c;                    // +0x2c
    INT Value30;                    // +0x30
    INT Value34;                    // +0x34
    UnnamedElement_38();
    ~UnnamedElement_38();
};
__declspec(noinline) UnnamedElement_38::UnnamedElement_38()
    : Value1c(0), Value24(0), Value28(-1), Value2c(-1), Value30(0), Value34(0)
{
    Name.Index = 0;
}
__declspec(noinline) UnnamedElement_38::~UnnamedElement_38() { Touch(this); Touch(&Value24); }
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedElement_38 &E)
{
    Ar << E.Res.Items << E.Res.Revision;
    Ar << E.Name << E.Value1c << E.Value24 << E.Value28;
    if (Ar.Ver() < 0x6b && Ar.IsLoading())
        E.Value28 = -1;
    return Ar;
}

// 4-byte element: two 16-bit values stored as compact indices; serializer
// RVA 0x10a1b0 (archive in EAX, element in EBX). Versions up to 0x9a carry an
// extra index and eight bytes that are read and dropped.
struct UnnamedElement_4
{
    unsigned short A;
    short B;
};
// With no destructor to run, Empty reduces to FArray::Empty and retail
// inlines it here (written as an inline specialisation).
template <> inline void TArray<UnnamedElement_4>::Empty(INT Slack)
{
    FArray::Empty(sizeof(UnnamedElement_4), Slack);
}

__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedElement_4 &E)
{
    INT V = E.A;
    Ar << AR_INDEX(V);
    E.A = (unsigned short)V;
    V = E.B;
    Ar << AR_INDEX(V);
    E.B = (short)V;
    Ar << AR_INDEX(V);
    if (Ar.Ver() <= 0x9a) {
        QWORD Dropped;
        Ar << Dropped;
    }
    return Ar;
}

// The three functions of this item are instantiations of the template
// operator<< above:
//   RVA 0x1097c0  operator<<(FArchive&, TArray<UnnamedElement_70>&)
//   RVA 0x109930  operator<<(FArchive&, TArray<UnnamedElement_38>&)
//   RVA 0x1099f0  operator<<(FArchive&, TArray<UnnamedElement_4>&)
// (also matching: 0x10a550 UnnamedElement_70 ctor, 0x10a350 / 0x10a480 /
// 0x10a1b0 element serializers, 0x10a3d0 TArray<UnnamedItem_28> serializer.)

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
// The three serializers are called from one owner's Serialize (RVA 0x107c00
// region): this mirrors that chain so the link picks the retail conventions.
struct UnnamedPart_a4 { BYTE Pad[0x0c]; };
struct UnnamedPart_c8 { BYTE Pad[0x0c]; };
FArchive &operator<<(FArchive &Ar, UnnamedPart_a4 &P);   // RVA 0x9de00
FArchive &operator<<(FArchive &Ar, UnnamedPart_c8 &P);   // RVA 0xf85a0
struct UnnamedOwner
{
    BYTE Pad00[0xa4];
    UnnamedPart_a4 PartA4;                      // +0xa4
    UnnamedRecord_c ArrayB0;                    // +0xb0
    TArray<UnnamedElement_4> ArrayBc;           // +0xbc
    UnnamedPart_c8 PartC8;                      // +0xc8
    TArray<UnnamedElement_38> ArrayD4;          // +0xd4
    TArray<UnnamedElement_70> ArrayE0;          // +0xe0
    BYTE PadEc[0x104 - 0xec];
    INT Value104;                               // +0x104
    INT Value108;                               // +0x108
};
void Driver_107c00(FArchive *ArP, UnnamedOwner *O)
{
    FArchive &Ar = *ArP;
    Escape(&GMalloc);
    Ar << O->PartA4 << O->ArrayB0 << O->ArrayBc << O->PartC8;
    Ar << O->Value104 << O->Value108;
    Ar << O->ArrayD4;
    Ar << O->ArrayE0;
}
