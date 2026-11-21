// Work item 0315: Versus RVA 0x861a0-0x86542.
// FVector/FCoords/FScale math helpers (Core UnMath.h) plus an owner-chain walk.

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

template <class T> inline T Abs(const T A) { return (A >= (T)0) ? A : -A; }
template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector &operator-=(const FVector &V) { X -= V.X; Y -= V.Y; Z -= V.Z; return *this; }
    FVector operator*=(const FVector &V) { X *= V.X; Y *= V.Y; Z *= V.Z; return *this; }
    FLOAT GetAbsMax() const;
};

struct FScale {
    FVector Scale;
    FLOAT SheerRate;
    BYTE SheerAxis;
};

enum ESheerAxis {
    SHEER_None = 0,
    SHEER_XY = 1,
    SHEER_XZ = 2,
    SHEER_YX = 3,
    SHEER_YZ = 4,
    SHEER_ZX = 5,
    SHEER_ZY = 6,
};

FLOAT FSheerSnap(FLOAT Sheer);

struct FCoords {
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords &operator*=(const FCoords &TransformCoords);
    FCoords &operator*=(const FVector &Point) { Origin -= Point; return *this; }
    FCoords operator*(const FVector &Point) const;
    FCoords &operator*=(const FScale &Scale);
    FCoords operator*(const FScale &Scale) const;
};

struct FGlobalMath {
    FCoords UnitCoords;
};
extern FGlobalMath GMath;

// 0x86230
FLOAT FVector::GetAbsMax() const
{
    return Max(Max(Abs(X), Abs(Y)), Abs(Z));
}

// 0x862a0
FCoords FCoords::operator*(const FVector &Point) const
{
    return FCoords(*this) *= Point;
}

// 0x86410
FCoords &FCoords::operator*=(const FScale &Scale)
{
    // Apply sheering.
    FLOAT Sheer = FSheerSnap(Scale.SheerRate);
    FCoords TempCoords = GMath.UnitCoords;
    switch (Scale.SheerAxis) {
    case SHEER_XY: TempCoords.XAxis.Y = Sheer; break;
    case SHEER_XZ: TempCoords.XAxis.Z = Sheer; break;
    case SHEER_YX: TempCoords.YAxis.X = Sheer; break;
    case SHEER_YZ: TempCoords.YAxis.Z = Sheer; break;
    case SHEER_ZX: TempCoords.ZAxis.X = Sheer; break;
    case SHEER_ZY: TempCoords.ZAxis.Y = Sheer; break;
    default: break;
    }
    *this *= TempCoords;

    // Apply scaling.
    XAxis *= Scale.Scale;
    YAxis *= Scale.Scale;
    ZAxis *= Scale.Scale;
    Origin.X /= Scale.Scale.X;
    Origin.Y /= Scale.Scale.Y;
    Origin.Z /= Scale.Scale.Z;

    return *this;
}

// 0x86360
FCoords FCoords::operator*(const FScale &Scale) const
{
    return FCoords(*this) *= Scale;
}

// 0x86200: walks the owner chain while flag 0x10000000 at +0x2ec is set.
// Neutral name; the class is an AActor-like object (owner/base pointer at +0x108).
// Owner is typed as a base class whose identical GetTopOwner the linker folded
// into this one (/OPT:ICF), which is why retail tail-jumps instead of looping.
struct UnnamedBase_86200 {
    UnnamedBase_86200 *GetTopOwner();
};
struct UnnamedClass_86200 {
    BYTE Pad0[0x108];
    UnnamedBase_86200 *Owner;       // +0x108
    BYTE Pad10c[0x2ec - 0x10c];
    DWORD BitsLow : 28;             // +0x2ec
    DWORD bAttachedToOwner : 1;     // +0x2ec bit 28 (neutral name)
    UnnamedBase_86200 *GetTopOwner();
};

UnnamedBase_86200 *UnnamedClass_86200::GetTopOwner()
{
    if (bAttachedToOwner && Owner)
        return Owner->GetTopOwner();
    return (UnnamedBase_86200 *)this;
}

// 0x861a0: compiler-generated destructor of a class holding two dynamic arrays:
// a TArray of 32-byte elements at +0x1c (destructor 0x1ee510, built in this
// LTCG module) and a 2-byte-element array at +0x44 (destructor 0xc4e0, plain
// thiscall from another module). Class and element names are neutral.
class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const unsigned short *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const unsigned short *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray {
public:
    void Remove(INT Index, INT Count, INT ElementSize);
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray {
public:
    ~TArray() { Remove(0, ArrayNum, sizeof(T)); }
};

struct UnnamedElement_861a0 {
    BYTE Pad[0x20];
};
struct UnnamedWordArray_861a0 {     // TArray<WORD>-like; destructor lives elsewhere
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~UnnamedWordArray_861a0();
};
struct UnnamedClass_861a0 {
    BYTE Pad0[0x1c];
    TArray<UnnamedElement_861a0> A; // +0x1c
    BYTE Pad28[0x44 - 0x28];
    UnnamedWordArray_861a0 B;       // +0x44
    ~UnnamedClass_861a0();
};

UnnamedClass_861a0::~UnnamedClass_861a0()
{
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_862a0(FCoords *R, const FCoords *C, const FVector *V) { *R = *C * *V; }
void Driver_86360(FCoords *R, const FCoords *C, const FScale *S) { Escape(&GMath); *R = *C * *S; }
void Driver_86410(FCoords *C, const FScale *S) { Escape(&GMath); *C *= *S; }
void Driver_861a0(UnnamedClass_861a0 *P) { P->~UnnamedClass_861a0(); }
FLOAT Driver_86230(const FVector *V) { return V->GetAbsMax(); }
UnnamedBase_86200 *Driver_86200(UnnamedClass_86200 *P) { return P->GetTopOwner(); }
