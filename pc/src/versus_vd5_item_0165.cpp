// Work item w3 0165: Versus RVA 0xcc270-0xcc4be.
//  0xcc270 UPrimitive::GetEncroachExtent  (vc71 /O2 /Gy)
//  0xcc2d0 UPrimitive::GetEncroachCenter  (vc71 /O2 /Gy)
//  0xcc330 UStaticMeshInstance::Serialize (LTCG object, VC7.0 /GL)
//  0xcc430 TArray<FUnnamedElem_cd430>::Empty(Slack), this in ESI (LTCG)
//  0xcc470 TSArray<FUnnamedElem_cc470>::Add(Count), Count in EAX, this in ESI (LTCG)
// Element types are not named anywhere in the binary; names are neutral, after an RVA.
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

struct FCompactIndex { INT Value; };
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(void *Object);                     // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, DWORD &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;          // +0x04
    INT ArNetVer;       // +0x08
    INT ArLicenseeVer;  // +0x0c
    UBOOL ArIsLoading;  // +0x10
    UBOOL ArIsSaving;   // +0x14
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

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
    INT Add(INT Count, INT ElementSize);                    // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);                 // RVA 0x4550
    void Remove(INT Index, INT Count, INT ElementSize);     // RVA 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }
};

template <class T> inline void *operator new(unsigned int Size, TArray<T> &A)
{
    INT Index = A.Add(1, sizeof(T));
    return &A(Index);
}

struct FColor
{
    BYTE B, G, R, A;
    friend FArchive &operator<<(FArchive &Ar, FColor &Color)
    {
        return Ar << Color.R << Color.G << Color.B << Color.A;
    }
};

// 20-byte element (destructor 0xa4770, constructor 0xcd0e0, serializer 0xcd0f0).
struct FUnnamedElem_a4770
{
    INT Unknown[5];
    FUnnamedElem_a4770();
    ~FUnnamedElem_a4770();
    friend FArchive &operator<<(FArchive &Ar, FUnnamedElem_a4770 &E);
};

// 0x1c-byte record: constructor 0xa128d0, destructor 0xa4780.
struct FUnnamedElem_a128d0
{
    INT Header;                 // +0x00
    TArray<FColor> Colors;      // +0x04
    INT Pad10, Pad14;           // +0x10
    INT Value;                  // +0x18
    __declspec(noinline) FUnnamedElem_a128d0();
    __declspec(noinline) ~FUnnamedElem_a128d0();
};

class FUnnamedArray_a128d0 : public TArray<FUnnamedElem_a128d0>
{
public:
    FUnnamedArray_a128d0() {}
    __declspec(noinline) ~FUnnamedArray_a128d0();           // RVA 0xcc5b0
    __declspec(noinline) void Empty(INT Slack);             // RVA 0xcce40
    __declspec(noinline) void Remove(INT Index, INT Count); // RVA 0xcc6c0
};

class FUnnamedArray_a4770 : public TArray<FUnnamedElem_a4770>
{
public:
    __declspec(noinline) void Empty(INT Slack);             // RVA 0xcc570
};

// Unnamed global at 0x10c946cc (field 0x68 is the target platform, see 0x10770).
struct UnnamedPlatformInfo_c946cc
{
    char Pad[0x80];
    INT Unknown80;
};
extern UnnamedPlatformInfo_c946cc *GPlatformInfo;

class UObject
{
public:
    virtual ~UObject();
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08();
    virtual void V09();
    virtual void Serialize(FArchive &Ar);                   // slot 10, RVA 0x15f50
    INT ObjectFields[9];
};

class UStaticMeshInstance : public UObject
{
public:
    FUnnamedArray_a4770 Arr28;  // +0x28
    INT Unknown34;              // +0x34
    TArray<FColor> ColorStream; // +0x38
    INT Unknown44, Unknown48;   // +0x44
    DWORD Unknown4c;            // +0x4c
    virtual void Serialize(FArchive &Ar);
};

FArchive &operator<<(FArchive &Ar, TArray<FColor> &A);              // RVA 0xf48e0
FArchive &operator<<(FArchive &Ar, FUnnamedArray_a128d0 &A);        // RVA 0xccd50
FArchive &operator<<(FArchive &Ar, FUnnamedArray_a4770 &A);         // RVA 0xcc820

// RVA 0xcc330
void UStaticMeshInstance::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    if (Ar.Ver() < 0x70) {
        FUnnamedArray_a128d0 OldData;
        Ar << OldData;
    } else {
        Ar << ColorStream << Unknown4c;
    }
    if (Ar.Ver() >= 0x6e) {
        if (Ar.Ver() < 0xa0) {
            Ar << Arr28;
            if (GPlatformInfo->Unknown80 == 1 || GPlatformInfo->Unknown80 == 2 || GPlatformInfo->Unknown80 == 3)
                Arr28.Empty(0);
        } else if (GPlatformInfo->Unknown80 != 1 && GPlatformInfo->Unknown80 != 2 && GPlatformInfo->Unknown80 != 3) {
            Ar << Arr28;
        }
    }
}


// ---- UPrimitive encroachment helpers (Engine, UnPrim.cpp). ----
class AActor;


class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator/(FLOAT Scale) const { const FLOAT RScale = 1.f / Scale; return FVector(X * RScale, Y * RScale, Z * RScale); }
    friend FVector operator*(FLOAT Scale, const FVector &V) { return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale); }
};

// This build's FBox has no IsValid byte (0x18 bytes).
class FBox
{
public:
    FVector Min, Max;
    FVector GetExtent() const { return (Max - Min) * 0.5f; }
    // The zero vector added here reproduces retail spilling the sum before scaling.
    FVector GetCenter() const { return FVector(0, 0, 0) + (Min + Max) * 0.5f; }
};

// UPrimitive (Unreal Engine 2): slot 26 (+0x68) GetCollisionBoundingBox,
// slot 28 (+0x70) GetEncroachExtent, slot 29 (+0x74) GetEncroachCenter.
class UPrimitive
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25();
    virtual FBox GetCollisionBoundingBox(const AActor *Owner) const;
    virtual void V27();
    virtual FVector GetEncroachExtent(AActor *Owner);
    virtual FVector GetEncroachCenter(AActor *Owner);
};

// RVA 0xcc270
FVector UPrimitive::GetEncroachExtent(AActor *Owner)
{
    return GetCollisionBoundingBox(Owner).GetExtent();
}

// RVA 0xcc2d0
FVector UPrimitive::GetEncroachCenter(AActor *Owner)
{
    return GetCollisionBoundingBox(Owner).GetCenter();
}


// A simple array with only Data and Num (neutral name, as in 0x11a70).
extern const TCHAR FSArray_Tag[];      // L"FSArray"
extern const TCHAR FSArray_Add_Tag[];  // L"FSArray::Add"
class FSArray
{
public:
    void *Data;
    INT ArrayNum;
    INT Add(INT Count, INT ElementSize)
    {
        INT Index = ArrayNum;
        ArrayNum += Count;
        if (Data == 0)
            Data = ArrayNum * ElementSize > 0 ? GMalloc->Malloc(ArrayNum * ElementSize, FSArray_Add_Tag) : 0;
        else
            Data = GMalloc->Realloc(Data, ArrayNum * ElementSize, FSArray_Tag);
        return Index;
    }
};
template <class T> class TSArray : public FSArray
{
public:
    INT Add(INT Count) { return FSArray::Add(Count, sizeof(T)); }
};

// 0x1c-byte element of the array destroyed by 0xa7f6a0 (this on the stack).
struct FUnnamedElem_a7f6a0
{
    INT V[7];
    __declspec(noinline) ~FUnnamedElem_a7f6a0();
};
class FUnnamedArray_a7f6a0 : public TArray<FUnnamedElem_a7f6a0>
{
public:
    __declspec(noinline) ~FUnnamedArray_a7f6a0();           // RVA 0xa7f6a0
};

// 32-byte element; its destructor (0xcd430, this in EAX) destroys the array at +4.
struct FUnnamedElem_cd430
{
    INT Header;
    FUnnamedArray_a7f6a0 List;
    INT Rest[4];
    __declspec(noinline) ~FUnnamedElem_cd430();
};

struct FUnnamedElem_cc470 { DWORD Fields[2]; };

// RVA 0xcc430
template <> __declspec(noinline) void TArray<FUnnamedElem_cd430>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~FUnnamedElem_cd430();
    FArray::Empty(sizeof(FUnnamedElem_cd430), Slack);
}

// RVA 0xcc470
template <> __declspec(noinline) INT TSArray<FUnnamedElem_cc470>::Add(INT Count)
{
    return FSArray::Add(Count, sizeof(FUnnamedElem_cc470));
}

// ---- Stand-ins for out-of-unit callees, defined so the LTCG link gives them
// their retail register conventions. Not part of the unit. ----
void External_Scaffold(void *);
void External_Scaffold2(void *, void *);
FUnnamedElem_a128d0::FUnnamedElem_a128d0() {}
FUnnamedElem_a128d0::~FUnnamedElem_a128d0() { Colors.Empty(0); }
__declspec(noinline) FUnnamedElem_a4770::FUnnamedElem_a4770() { External_Scaffold(this); }
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedElem_a4770 &E) { External_Scaffold2(&Ar, &E); return Ar; }
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
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
void FUnnamedArray_a128d0::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~FUnnamedElem_a128d0();
    FArray::Remove(Index, Count, sizeof(FUnnamedElem_a128d0));
}
FUnnamedArray_a128d0::~FUnnamedArray_a128d0() { Remove(0, ArrayNum); }
void FUnnamedArray_a128d0::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~FUnnamedElem_a128d0();
    FArray::Empty(sizeof(FUnnamedElem_a128d0), Slack);
}
void FUnnamedArray_a4770::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~FUnnamedElem_a4770();
    FArray::Empty(sizeof(FUnnamedElem_a4770), Slack);
}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<FColor> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(&((FColor *)A.Data)[A.Add(1, sizeof(FColor))]) FColor;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedArray_a128d0 &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++) {
            FUnnamedElem_a128d0 &E = *new(&A(A.Add(1, sizeof(FUnnamedElem_a128d0)))) FUnnamedElem_a128d0;
            Ar << E.Colors << E.Value;
        }
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i).Colors << A(i).Value;
    }
    return Ar;
}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedArray_a4770 &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(A) FUnnamedElem_a4770;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

FUnnamedElem_cd430::~FUnnamedElem_cd430() {}
FUnnamedElem_a7f6a0::~FUnnamedElem_a7f6a0() { External_Scaffold(this); }
FUnnamedArray_a7f6a0::~FUnnamedArray_a7f6a0()
{
    INT Count = ArrayNum;
    for (INT i = 0; i < Count; i++)
        (&(*this)(i))->~FUnnamedElem_a7f6a0();
    FArray::Remove(0, Count, sizeof(FUnnamedElem_a7f6a0));
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
extern "C" void Driver_cc330(UStaticMeshInstance *M, FArchive *Ar)
{
    Escape(&GMalloc);
    Escape(&GPlatformInfo);
    M->UStaticMeshInstance::Serialize(*Ar);
    Escape(M);
}
void Use(INT);
extern "C" void Driver_cc430(TArray<FUnnamedElem_cd430> *A, INT N, TArray<FUnnamedElem_cd430> *B) { Escape(&GMalloc); A->Empty(N); B->Empty(0); }
extern "C" void Driver_cc470(TSArray<FUnnamedElem_cc470> *A, INT N, TSArray<FUnnamedElem_cc470> *B) { Escape(&GMalloc); Use(A->Add(N)); Use(B->Add(1)); }
