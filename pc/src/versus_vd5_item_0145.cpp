// Work item w3 0145: Versus RVA 0xc3510-0xc3abe (LTCG object, VC7.0 /GL).
// 0xc3510 operator<<(FArchive&, TLazyArray<FMeshWedge>&)  (Ar in ECX, array in EAX)
// 0xc3720 operator<<(FArchive&, TLazyArray<FVector>&)     (Ar in ECX, array in EAX)
// 0xc3910 FPackedVector_c3910::Set (neutral name; out in ESI, vector in EDI)
// 0xc39d0 FUnnamedRecord_c39d0::~FUnnamedRecord_c39d0 (this on the stack)
// 0xc3a30 TArray<FUnnamedElem6>::~TArray (this on the stack)
// 0xc3aa0 FUnnamedRecord_c39d0::FUnnamedRecord_c39d0 (this in EAX)
// The lazy-array template is the one matched in w3_item_0139 (0xc1950).
#include "versus_build.h"
#include "versus_lazy_archive.h"
#include "unreal_math.h"

extern "C" __declspec(dllimport) double floor(double);   // MSVCR70

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;                 // 0x10c73bf0
// Retail keeps these literals in writable data.
extern const TCHAR OperatorShlTArray[];  // L"operator<<(TArray)", 0x10c748fc
extern const TCHAR FSArray_Tag[];        // L"FSArray"

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

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack) { FArray::Empty(sizeof(T), Slack); }
};

// A simple array with only Data and Num (neutral name, as in 0x11a70).
class FSArray
{
public:
    void *Data;
    INT ArrayNum;
    void Realloc(INT ElementSize);                          // RVA 0x11a70
};
template <class T> class TSArray : public FSArray {};

inline void *operator new(unsigned int, void *Mem) { return Mem; }

// UE2 element types (UnSkeletalMesh.h / UnMath.h).
struct FMeshUV
{
    FLOAT U, V;
    friend FArchive &operator<<(FArchive &Ar, FMeshUV &M) { return Ar << M.U << M.V; }
};
struct FMeshWedge
{
    _WORD iVertex;
    FMeshUV TexUV;
    friend FArchive &operator<<(FArchive &Ar, FMeshWedge &W)
    {
        Ar.Serialize(&W.iVertex, 2);
        return Ar << W.TexUV;
    }
};

// Retail callees that LTCG gives register conventions; defined here so the
// linker can choose them (scaffolding, matched elsewhere, not part of this item).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FCompactIndex &I)   // RVA 0x1ea40
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
    BYTE B0 = (BYTE)I.Value;
    Ar << B0;
    I.Value = B0;
    return Ar;
}

// RVA 0xa5a80 (scaffolding): per-element TArray<FMeshWedge> serializer.
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<FMeshWedge> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(&((FMeshWedge *)A.Data)[A.Add(1, sizeof(FMeshWedge))]) FMeshWedge;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// RVA 0x86bb0 (scaffolding): bulk TArray<FVector> serializer.
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<FVector> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FVector), A.ArrayMax * sizeof(FVector));
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (!A.Data) {
            if (!A.ArrayNum)
                return Ar;
            A.Data = GMalloc->Malloc(A.ArrayNum * sizeof(FVector), OperatorShlTArray);
        } else if (A.ArrayNum) {
            A.Realloc(sizeof(FVector));
        } else {
            A.ArrayNum = 0;
            A.ArrayMax = 0;
            GMalloc->Free(A.Data);
            A.Data = 0;
            return Ar;
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(FVector));
    return Ar;
}

// RVA 0xc3510: operator<<(FArchive&, TLazyArray<FMeshWedge>&) and
// RVA 0xc3720: operator<<(FArchive&, TLazyArray<FVector>&), instantiated from
// the template above (Ar in ECX/ESI, lazy array in EAX).
template FArchive &operator<<(FArchive &Ar, TLazyArray<FMeshWedge> &This);
template FArchive &operator<<(FArchive &Ar, TLazyArray<FVector> &This);

// RVA 0xc3910: packs a vector into three clamped fixed-point shorts
// (1/32 unit steps). Neutral name; the struct's UE2 name is not recovered.
inline INT appFloor(FLOAT F) { return (INT)floor(F); }
struct FPackedVector_c3910
{
    short X, Y, Z;
    void Set(const FVector &V);
};
__declspec(noinline) void FPackedVector_c3910::Set(const FVector &V)
{
    X = Clamp(appFloor(V.X * 32.f), -32767, 32767);
    Y = Clamp(appFloor(V.Y * 32.f), -32767, 32767);
    Z = Clamp(appFloor(V.Z * 32.f), -32767, 32767);
}

// 0x28-byte record with three arrays (neutral names, element sizes from the
// Remove strides and the destructors retail calls).
struct FUnnamedElem8 { INT A, B; };              // 8 bytes, array dtor 0xa7f6a0
struct FUnnamedElem6 { _WORD A, B, C; };          // 6 bytes, array dtor 0xc3a30
struct FUnnamedElemA8A60 { INT A[3]; };           // array dtor 0xa8a60 (size not recovered here)

class FArrayD
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArrayD() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArrayD()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);   // RVA 0x119c0
};
template <class T> class TArrayD : public FArrayD
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArrayD::Remove(Index, Count, sizeof(T));
    }
    ~TArrayD();
};
// RVA 0xc3a30: TArray<FUnnamedElem6>::~TArray. The same template gives the
// other two member destructors (retail 0xa7f6a0 and 0xa8a60, matched elsewhere).
template <class T> TArrayD<T>::~TArrayD() { Remove(0, ArrayNum); }

struct FUnnamedRecord_c39d0
{
    INT Header;                              // +0x00
    TArrayD<FUnnamedElem8> Pairs;            // +0x04
    TArrayD<FUnnamedElem6> Triples;          // +0x10
    TArrayD<FUnnamedElemA8A60> Others;       // +0x1c
    FUnnamedRecord_c39d0() {}                // RVA 0xc3aa0
    ~FUnnamedRecord_c39d0() {}               // RVA 0xc39d0
};

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c3510(FArchive *Ar, TLazyArray<FMeshWedge> *W, TLazyArray<FVector> *V)
{
    Escape(&GLazyLoad); Escape(&GUglyHackFlags); Escape(&GMalloc);
    *Ar << *W;
    *Ar << *V;
}
void Driver_c3910(FPackedVector_c3910 *P, const FVector *V) { P->Set(*V); }
void Driver_c39d0(FUnnamedRecord_c39d0 *R, void *Mem)
{
    Escape(&GMalloc);
    new(Mem) FUnnamedRecord_c39d0;
    R->~FUnnamedRecord_c39d0();
}
