// Work item 0357: Versus RVA 0x9d5b0-0x9da42 (UESBPatch unit, built /GL + /LTCG).
//
// 0x9d5b0 UESBPatch vtable slot 51: pushes every particle away from a world
//         point (name not recovered; neutral name ApplyBlast).
// 0x9d710 TArray<FESBLinkKey>::AddUniqueItem   (12-byte element, 2-field ==)
// 0x9d7a0 TArray<FESBKeyedEntry>::AddUniqueItem (16-byte element, keyed ==)
// 0x9d830 TArray<FESBSegment>::AddUniqueItem   (two FVectors)
// 0x9d910 TArray<FPlane>::AddUniqueItem
// 0x9d9d0 TArray<FESBRecord28>::operator=      (28-byte element)
// Element type names are neutral guesses; layouts and comparisons are retail.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

#define SMALL_NUMBER 1.e-8f

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

extern "C" __declspec(dllimport) int __cdecl rand(void);
inline FLOAT appFrand() { return rand() / (FLOAT)32768; }
inline FLOAT appSqrt(FLOAT F);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    void Realloc(INT ElementSize)
    {
        if (Data == 0)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, L"FArray::Add");
        else
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, L"FArray");
    }
    INT Add(INT Count, INT ElementSize)
    {
        INT Index = ArrayNum;
        if ((ArrayNum += Count) > ArrayMax)
        {
            ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
            Realloc(ElementSize);
        }
        return Index;
    }
    INT AddOutOfLine(INT Count, INT ElementSize);       // retail 0x44e0 (Core)
    void Empty(INT ElementSize, INT Slack = 0);          // retail 0x4550 (Core)
};

template<class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        ((T *)Data)[Index] = Item;
        return Index;
    }
    __declspec(noinline) INT AddUniqueItem(const T &Item)
    {
        for (INT Index = 0; Index < ArrayNum; Index++)
            if ((*this)(Index) == Item)
                return Index;
        return AddItem(Item);
    }
    __declspec(noinline) TArray &operator=(const TArray &Other)
    {
        if (this != &Other)
        {
            Empty(sizeof(T), Other.ArrayNum);
            for (INT i = 0; i < Other.ArrayNum; i++)
                new(*this) T(Other(i));
        }
        return *this;
    }
};
template<class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.AddOutOfLine(1, sizeof(T));
    return &Array(Index);
}

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector &operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
    UBOOL operator==(const FVector &V) const { return X == V.X && Y == V.Y && Z == V.Z; }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    UBOOL operator==(const FPlane &V) const { return X == V.X && Y == V.Y && Z == V.Z && W == V.W; }
};

class FMatrix
{
public:
    FPlane XPlane, YPlane, ZPlane, WPlane;
    FPlane TransformFPlane(const FPlane &P) const;      // retail 0x4fe60
    FMatrix operator*(const FMatrix &Other) const;
    FVector TransformFVector(const FVector &V) const { return TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.0f)); }
};

struct FESBLinkKey     // 12 bytes, equal when the first two fields match
{
    INT A, B, C;
    UBOOL operator==(const FESBLinkKey &O) const { return A == O.A && B == O.B; }
};
struct FESBKeyedEntry  // 16 bytes, equal when the key matches
{
    INT Key, B, C, D;
    UBOOL operator==(const FESBKeyedEntry &O) const { return Key == O.Key; }
};
struct FESBSegment     // 24 bytes
{
    FVector Start, End;
    UBOOL operator==(const FESBSegment &O) const { return Start == O.Start && End == O.End; }
};
struct FESBRecord28    // 28 bytes
{
    INT A;
    FVector B;
    FVector C;
};

class AActor
{
public:
    FMatrix WorldToLocal() const;                       // retail 0x9e3b0 (this in EAX)
    char Pad00[0x70];
    FLOAT Coeffs[16];
    FVector DrawScale3D;                                // 0xb0
};


struct FESBParticle    // 72 bytes
{
    INT Flags;
    FVector Location;
    char Pad10[0x38];
};

class UESBPatch
{
public:
    virtual void VirtualSlot00(); virtual void VirtualSlot01(); virtual void VirtualSlot02(); virtual void VirtualSlot03();
    virtual void VirtualSlot04(); virtual void VirtualSlot05(); virtual void VirtualSlot06(); virtual void VirtualSlot07();
    virtual void VirtualSlot08(); virtual void VirtualSlot09(); virtual void VirtualSlot10(); virtual void VirtualSlot11();
    virtual void VirtualSlot12(); virtual void VirtualSlot13(); virtual void VirtualSlot14(); virtual void VirtualSlot15();
    virtual void VirtualSlot16(); virtual void VirtualSlot17(); virtual void VirtualSlot18(); virtual void VirtualSlot19();
    virtual void VirtualSlot20(); virtual void VirtualSlot21(); virtual void VirtualSlot22(); virtual void VirtualSlot23();
    virtual void VirtualSlot24(); virtual void VirtualSlot25(); virtual void VirtualSlot26(); virtual void VirtualSlot27();
    virtual void VirtualSlot28(); virtual void VirtualSlot29(); virtual void VirtualSlot30(); virtual void VirtualSlot31();
    virtual void VirtualSlot32(); virtual void VirtualSlot33(); virtual void VirtualSlot34(); virtual void VirtualSlot35();
    virtual void VirtualSlot36(); virtual void VirtualSlot37(); virtual void VirtualSlot38(); virtual void VirtualSlot39();
    virtual void VirtualSlot40(); virtual void VirtualSlot41(); virtual void VirtualSlot42(); virtual void VirtualSlot43();
    virtual void VirtualSlot44(); virtual void VirtualSlot45(); virtual void VirtualSlot46(); virtual void VirtualSlot47();
    virtual void AddImpulse(INT Index, const FVector &Impulse);   // slot 48
    virtual void VirtualSlot49(); virtual void VirtualSlot50();
    virtual void ApplyBlast(const FVector &Origin, FLOAT Unused);  // slot 51
    char Pad04[0x50];
    AActor *Owner;                    // 0x54
    char Pad58[0x18];
    TArray<FESBParticle> Particles;   // 0x70
};

// Near miss: the body after the WorldToLocal call is instruction-identical;
// retail calls WorldToLocal with `this` in EAX and the result pointer pushed
// (ret 4), but the stand-in below always gets a register result pointer, which
// reorders the prologue and swaps ESI/EDI through the function.
void UESBPatch::ApplyBlast(const FVector &Origin, FLOAT Unused)
{
    FVector LocalOrigin = Owner->WorldToLocal().TransformFVector(Origin);
    FVector Delta;
    for (INT i = 0; i < Particles.Num(); i++)
    {
        Delta = Particles(i).Location - LocalOrigin;
        FLOAT Strength = appFrand();
        FLOAT SquareSum = Delta.SizeSquared();
        if (SquareSum >= SMALL_NUMBER)
        {
            FLOAT InvSize = 1.f / appSqrt(SquareSum);
            FLOAT Scale = InvSize * (Strength + 1.f) * 500.f;
            Delta *= Scale;
        }
        AddImpulse(i, Delta);
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_9d710(TArray<FESBLinkKey> *A, INT a, INT b, INT c)
{
    Escape(&GMalloc);
    FESBLinkKey K; K.A = a; K.B = b; K.C = c;
    A->AddUniqueItem(K);
}
void Driver_9d7a0(TArray<FESBKeyedEntry> *A, INT a, INT b, INT c, INT d)
{
    Escape(&GMalloc);
    FESBKeyedEntry K; K.Key = a; K.B = b; K.C = c; K.D = d;
    A->AddUniqueItem(K);
}
void Driver_9d830(TArray<FESBSegment> *A, FESBSegment S)
{
    Escape(&GMalloc);
    A->AddUniqueItem(S);
}
void Driver_9d910(TArray<FPlane> *A, FPlane P)
{
    Escape(&GMalloc);
    A->AddUniqueItem(P);
}
void Driver_9d9d0(TArray<FESBRecord28> *A, TArray<FESBRecord28> *B)
{
    *A = *B;
}
void Driver_9d5b0(UESBPatch *P, FVector *V, AActor *A, AActor *B)
{
    P->UESBPatch::ApplyBlast(*V, 0.f);
    FMatrix M1 = A->WorldToLocal();
    Escape(&M1);
    FMatrix M2 = B->WorldToLocal();
    Escape(&M2);
}
// Stand-in body for AActor::WorldToLocal (retail 0x9e3b0, not part of this
// item): defined only so the linker gives it retail's EAX `this` convention.
__declspec(noinline) FMatrix AActor::WorldToLocal() const
{
    const AActor *A = this;
    FMatrix S, T, R, P;
    FLOAT *Out;
    INT i;
    Out = &S.XPlane.X;
    for (i = 0; i < 16; i++) Out[i] = A->Coeffs[i] / A->DrawScale3D.X;
    Out = &T.XPlane.X;
    for (i = 0; i < 16; i++) Out[i] = A->Coeffs[i] / A->DrawScale3D.Y;
    Out = &R.XPlane.X;
    for (i = 0; i < 16; i++) Out[i] = A->Coeffs[i] / A->DrawScale3D.Z;
    Out = &P.XPlane.X;
    for (i = 0; i < 16; i++) Out[i] = -A->Coeffs[i];
    return T * R * S * P;
}
// Stand-in body for FMatrix::operator* (retail 0x7b110), for the same reason.
__declspec(noinline) FMatrix FMatrix::operator*(const FMatrix &Other) const
{
    FMatrix Result;
    const FLOAT *A = &XPlane.X, *B = &Other.XPlane.X;
    FLOAT *R = &Result.XPlane.X;
    for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
            R[i * 4 + j] = A[i * 4 + 0] * B[0 * 4 + j] + A[i * 4 + 1] * B[1 * 4 + j] + A[i * 4 + 2] * B[2 * 4 + j] + A[i * 4 + 3] * B[3 * 4 + j];
    return Result;
}
