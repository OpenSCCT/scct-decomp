// Work item 0382: TLazyArray<T> (UE2 UnTemplate.h) instances used by the
// skeletal mesh code, RVA 0xa56e0-0xa5a74. Built with VC7.0 /O2 /Gy /GX /Ob1
// /GL, linked /LTCG (with /Ob2 the link inlines the member destructors into
// ~USkeletalMesh, which retail does not).
//
// Layout (FLazyLoader is the only polymorphic base, so it comes first):
//   0x00 vtable (Load, Unload), 0x04 SavedAr, 0x08 SavedPos, 0x0c TArray<T>.
// SCCT's FArchive has two more virtual slots than stock UE2 before Seek:
// Tell 0x28, Seek 0x3c, DetachLazyLoader 0x44.
//
// Element types are not identified; they are named after their size and how
// their TArray serializer works (bulk vs per-element).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;
typedef unsigned char BYTE;

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
    virtual void Free(void* Original);
};
extern FMalloc* GMalloc;

class FLazyLoader;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);
    virtual void SerializeBits(void* V, INT LengthBits);
    virtual void SerializeInt(DWORD& Value, DWORD Max);
    virtual void Preload(void* Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive& operator<<(class FName& N);
    virtual FArchive& operator<<(class UObject*& Res);
    virtual INT MapName(class FName* Name);
    virtual INT MapObject(class UObject* Object);
    virtual INT Tell();
    virtual INT TotalSize();
    virtual UBOOL AtEnd();
    virtual void Unknown34();
    virtual void Unknown38();
    virtual void Seek(INT InPos);
    virtual void AttachLazyLoader(FLazyLoader* LazyLoader);
    virtual void DetachLazyLoader(FLazyLoader* LazyLoader);

    INT ArVer, ArNetVer, ArLicenseeVer;
    UBOOL ArIsLoading, ArIsSaving;
    UBOOL IsLoading() { return ArIsLoading; }
};

// AR_INDEX serialization (retail 0x1ea40).
FArchive& SerializeCompactIndex(FArchive& Ar, INT& Value);

extern const TCHAR FArrayTag[];
class FArray
{
public:
    void Remove(INT Index, INT Count, INT ElementSize);
    void Realloc(INT ElementSize);
    void Resize(INT ElementSize)
    {
        if (Data == 0)
        {
            if (ArrayMax)
                Data = GMalloc->Malloc(ArrayMax * ElementSize, FArrayTag);
        }
        else if (ArrayMax)
            Realloc(ElementSize);
        else
        {
            ArrayNum = ArrayMax = 0;
            GMalloc->Free(Data);
            Data = 0;
        }
    }
    void Empty(INT ElementSize, INT Slack);
    INT Add(INT Count, INT ElementSize);
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    TArray() { Data = 0; ArrayNum = ArrayMax = 0; }
    ~TArray();
    T& operator()(INT i) { return ((T*)Data)[i]; }
};

class FLazyLoader
{
public:
    FLazyLoader() : SavedAr(0), SavedPos(0) {}
    FArchive* SavedAr;
    INT SavedPos;
    virtual void Load() = 0;
    virtual void Unload() = 0;
};

template<class T> class TLazyArray : public TArray<T>, public FLazyLoader
{
public:
    ~TLazyArray();
    void Load()
    {
        if (SavedPos > 0)
        {
            INT PushedPos = SavedAr->Tell();
            SavedAr->Seek(SavedPos);
            *SavedAr << (TArray<T>&)*this;
            SavedPos *= -1;
            SavedAr->Seek(PushedPos);
        }
    }
    void Unload();
};

// Serializers of the other lazy arrays live elsewhere.
template<class T> FArchive& operator<<(FArchive& Ar, TArray<T>& A);

template<class T> TLazyArray<T>::~TLazyArray()
{
    if (SavedAr)
        SavedAr->DetachLazyLoader(this);
}

// Element types (unidentified).
struct FBulkElem12 { INT A, B, C; };  // 12 bytes, serialized in bulk
typedef unsigned short _WORD;
struct FElem4 { INT A; };                 // 4 bytes, serialized per element
struct FElem12 { _WORD A; INT B; INT C; }; // 12 bytes, serialized per element
inline FArchive& operator<<(FArchive& Ar, INT& V) { Ar.Serialize(&V, sizeof(V)); return Ar; }
inline FArchive& operator<<(FArchive& Ar, _WORD& V) { Ar.Serialize(&V, sizeof(V)); return Ar; }
inline FArchive& operator<<(FArchive& Ar, FElem4& E) { return Ar << E.A; }
inline FArchive& operator<<(FArchive& Ar, FElem12& E) { return Ar << E.A << E.B << E.C; }

// The TArray serializers and destructors below are not part of this unit;
// they are defined so the link gives them retail's link-time conventions.
FArchive& operator<<(FArchive& Ar, TArray<FBulkElem12>& A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FBulkElem12), A.ArrayMax * sizeof(FBulkElem12));
    SerializeCompactIndex(Ar, A.ArrayNum);
    if (Ar.IsLoading())
    {
        A.ArrayMax = A.ArrayNum;
        A.Resize(sizeof(FBulkElem12));
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(FBulkElem12));
    return Ar;
}

FArchive& operator<<(FArchive& Ar, TArray<FElem4>& A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FElem4), A.ArrayMax * sizeof(FElem4));
    if (Ar.IsLoading())
    {
        INT NewNum;
        SerializeCompactIndex(Ar, NewNum);
        A.Empty(sizeof(FElem4), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.Add(1, sizeof(FElem4)));
    }
    else
    {
        SerializeCompactIndex(Ar, A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

FArchive& operator<<(FArchive& Ar, TArray<FElem12>& A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FElem12), A.ArrayMax * sizeof(FElem12));
    if (Ar.IsLoading())
    {
        INT NewNum;
        SerializeCompactIndex(Ar, NewNum);
        A.Empty(sizeof(FElem12), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.Add(1, sizeof(FElem12)));
    }
    else
    {
        SerializeCompactIndex(Ar, A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

FArchive& SerializeCompactIndex(FArchive& Ar, INT& Value)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving)
    {
        Ar.Serialize(&Value, 4);
        return Ar;
    }
    INT Original = Value;
    DWORD V = Original >= 0 ? Original : -Original;
    BYTE B0 = (BYTE)((Original >= 0 ? 0 : 0x80) + (V < 0x40 ? V : (V & 0x3f) + 0x40));
    Value = 0;
    Ar.Serialize(&B0, 1);
    if (B0 & 0x40)
    {
        V >>= 6;
        BYTE B1 = (BYTE)(V < 0x80 ? V : (V & 0x7f) + 0x80);
        Ar.Serialize(&B1, 1);
        Value = B1 & 0x7f;
    }
    Value |= B0 & 0x3f;
    if (B0 & 0x80)
        Value = -Value;
    return Ar;
}

// TArray<T>::~TArray for the element types whose destructor the link
// converts (this on the stack); see the note above the serializers.
#define TARRAY_DESTRUCTOR(T)     template<> TArray<T>::~TArray() { Remove(0, ArrayNum, sizeof(T)); }
TARRAY_DESTRUCTOR(FElem4)
TARRAY_DESTRUCTOR(FElem12)

// ---------------------------------------------------------------------------
// USkeletalMesh::~USkeletalMesh (RVA 0xa56e0). The member types are not
// identified; they are named after their element sizes. Members whose
// destructors retail reaches through a plain thiscall (0x86750, 0xc4e0,
// 0x1ef20) live in other objects and are declared only.
enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class UObject
{
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    // Retail calls Destroy (slot 9) through memory at the vtable slot
    // (call [vftable+0x24]); the slot holds UObject::Destroy (0x15ce0 thunk).
    // As in the sibling units (item_0016_ltcg), it is declared dllimport and
    // ConditionalDestroy names UObject::Destroy, which reproduces that
    // indirect call: an ordinary virtual call gives the same bytes, but the
    // verifier cannot bind an address inside the vtable.
    __declspec(dllimport) virtual void Destroy();
    INT Index;
    DWORD Reserved[5];
    DWORD ObjectFlags;
    INT ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed))
        {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            UObject::Destroy();
            return 1;
        }
        return 0;
    }
};

class ULodMesh : public UObject
{
public:
    virtual ~ULodMesh();
    BYTE LodMeshData[0xf4 - 0x20];
};

struct FElem12b { INT A, B, C; };
struct FElem8 { INT A, B; };
struct FElem2 { _WORD A; };
struct FElem64 { INT A[16]; };
// Elements with destructors of their own (the array destructors at 0xa5fe0
// and 0xa6330 destroy each element before freeing).
struct FElemA12 { INT A, B, C; ~FElemA12(); };
struct FElemB12 { INT A, B, C; ~FElemB12(); };
struct FElem16 { INT A[4]; };
struct FElem20 { INT A[5]; };
struct FElem48 { INT A[12]; };
struct FElem24 { INT A[6]; };
TARRAY_DESTRUCTOR(FElem12b)
TARRAY_DESTRUCTOR(FElem8)
TARRAY_DESTRUCTOR(FElem64)
template<> TArray<FElemA12>::~TArray()
{
    for (INT i = 0; i < ArrayNum; i++)
        (*this)(i).~FElemA12();
    Remove(0, ArrayNum, sizeof(FElemA12));
}
template<> TArray<FElemB12>::~TArray()
{
    for (INT i = 0; i < ArrayNum; i++)
        (*this)(i).~FElemB12();
    Remove(0, ArrayNum, sizeof(FElemB12));
}
TARRAY_DESTRUCTOR(FElem16)
TARRAY_DESTRUCTOR(FElem20)
TARRAY_DESTRUCTOR(FElem48)
TARRAY_DESTRUCTOR(FElem24)

// A 0x2c-byte element held in a fixed array of four.
struct FMeshSection2C
{
    INT A, B;
    TArray<FElem2> Words;   // 0x08
    INT C, D, E;            // 0x14
    TArray<FElem24> Items;  // 0x20
};

// An array without a capacity field (Data, Num), 0x30-byte elements, built
// like TArray: the derived destructor removes the elements, the base frees.
class FCompactArray
{
public:
    void Remove(INT Index, INT Count, INT ElementSize);
    ~FCompactArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = 0;
    }
    void* Data;
    INT ArrayNum;
};
template<class T> class TCompactArray : public FCompactArray
{
public:
    ~TCompactArray();
};
template<> TCompactArray<FElem48>::~TCompactArray() { Remove(0, ArrayNum, sizeof(FElem48)); }

class USkeletalMesh : public ULodMesh
{
public:
    virtual ~USkeletalMesh();
    TLazyArray<FBulkElem12> LazyF4;     // 0x0f4
    TLazyArray<FElem4> Lazy10C;         // 0x10c
    TLazyArray<FElem12> Lazy124;        // 0x124
    TLazyArray<FElem12b> Lazy13C;       // 0x13c
    TLazyArray<FElem8> Lazy154;         // 0x154
    TLazyArray<FElem2> Lazy16C;         // 0x16c
    TLazyArray<FElem2> Lazy184;         // 0x184
    TArray<FElem64> Array19C;           // 0x19c
    INT Int1A8;                         // 0x1a8
    TArray<FElemA12> Array1AC;          // 0x1ac
    TArray<FBulkElem12> Array1B8;       // 0x1b8
    TArray<FElemB12> Array1C4;          // 0x1c4
    TArray<FElem4> Array1D0;            // 0x1d0
    INT Int1DC, Int1E0;                 // 0x1dc
    FMeshSection2C Sections[4];         // 0x1e4
    TArray<FElem16> Array294;           // 0x294
    TArray<FElem20> Array2A0;           // 0x2a0
    TArray<FElem16> Array2AC;           // 0x2ac
    TCompactArray<FElem48> Compact2B8;       // 0x2b8
    TArray<FElem16> Array2C0;           // 0x2c0
    TArray<INT> Array2CC;               // 0x2cc
    TArray<INT> Array2D8;               // 0x2d8
    TArray<FElem48> Array2E4;           // 0x2e4
};

USkeletalMesh::~USkeletalMesh()
{
    ConditionalDestroy();
}

// Explicit instances of the lazy arrays this unit holds.
template class TLazyArray<FBulkElem12>;
template class TLazyArray<FElem4>;
template class TLazyArray<FElem12>;

// Scaffolding for the link, not part of the unit.
inline void* operator new(unsigned int, void* Mem) { return Mem; }
FLazyLoader* Driver_a58d0(void* Mem) { return new(Mem) TLazyArray<FBulkElem12>; }
FLazyLoader* Driver_a5980(void* Mem) { return new(Mem) TLazyArray<FElem4>; }
FLazyLoader* Driver_a5a30(void* Mem) { return new(Mem) TLazyArray<FElem12>; }
void Driver_a5920(TLazyArray<FBulkElem12>* A) { A->~TLazyArray<FBulkElem12>(); }
void Driver_a59d0(TLazyArray<FElem4>* A) { A->~TLazyArray<FElem4>(); }
// Retail calls the member destructors from elsewhere too, so the link keeps
// them out of line; the extra calls here stand in for those callers.
void Driver_a56e0(USkeletalMesh* M, TLazyArray<FElem12>* A, TLazyArray<FElem12b>* B,
                  TLazyArray<FElem8>* C, TLazyArray<FElem2>* D)
{
    M->USkeletalMesh::~USkeletalMesh();
    A->~TLazyArray<FElem12>();
    B->~TLazyArray<FElem12b>();
    C->~TLazyArray<FElem8>();
    D->~TLazyArray<FElem2>();
}
