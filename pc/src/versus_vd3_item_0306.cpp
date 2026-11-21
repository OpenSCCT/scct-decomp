// Work item 0306: ASecurity::execNativePerform and three particle-emitter
// virtuals (Engine). Layouts are recovered from the retail code only; field
// names follow Unreal Engine 2 (UT2004 UnParticleSystem) where the shape fits.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT S) const { return FVector(X * S, Y * S, Z * S); }
    FVector operator*(const FVector &V) const { return FVector(X * V.X, Y * V.Y, Z * V.Z); }
    FVector &operator*=(const FVector &V) { X *= V.X; Y *= V.Y; Z *= V.Z; return *this; }
    FVector &operator-=(const FVector &V) { X -= V.X; Y -= V.Y; Z -= V.Z; return *this; }
    FLOAT Size() const { return appSqrt(X * X + Y * Y + Z * Z); }
    FLOAT GetMax() const { return Max(Max(X, Y), Z); }
};

// Two-vector box (24 bytes; Versus copies it as six dwords).
struct FBox {
    FVector Min, Max;
    FBox() {}
    FBox(const FVector &A, const FVector &B);          // 0x81ad0, not part of this item
    FBox &operator+=(const FVector &Other);            // 0x4f820
    FVector GetCenter() const { return FVector((Min + Max) * 0.5f); }
    FBox ExpandBy(FLOAT W) const;                      // 0x81a70, not part of this item
};

struct FRange {
    FLOAT Min, Max;
    FLOAT GetMax() const { return ::Max(Min, Max); }
};

struct FRangeVector {
    FRange X, Y, Z;
    __forceinline FLOAT GetMax() const { return ::Max(::Max(X.GetMax(), Y.GetMax()), Z.GetMax()); }
};

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();
};

struct FFrame;
class UObject {
public:
    virtual ~UObject();
};
typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FOutputDevice {
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

struct FFrame : public FOutputDevice {
    void *Node;
    UObject *Object;
    BYTE *Code;
    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

class ASecurity : public UObject {
public:
    void execNativePerform(FFrame &Stack, void *const Result);
};

// native function NativePerform(int SecType, string Param1, string Param2);
// The Versus body is empty.
void ASecurity::execNativePerform(FFrame &Stack, void *const Result)
{
    INT SecType = 0;
    Stack.Step(Stack.Object, &SecType);
    FString Param1;
    Stack.Step(Stack.Object, &Param1);
    FString Param2;
    Stack.Step(Stack.Object, &Param2);
    Stack.Code++;
}

class UStaticMesh {
public:
    BYTE Pad00[0x28];
    FBox BoundingBox;
};

class AActor {
public:
    BYTE Pad00[0xbc];
    FVector Velocity; // 0xbc (name inferred)
};

class UParticleEmitter : public UObject {
public:
    // vtable slots 1..15 (neutral)
#define SLOT(n) virtual void Slot##n();
    SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
    SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
#undef SLOT
    virtual void Reinitialize_80ba0();               // slot 16, neutral name
#define SLOT(n) virtual void Slot##n();
    SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21)
#undef SLOT
    virtual void Initialize(INT InMaxParticles);     // slot 22 (+0x58)
    virtual void CleanUp();                          // slot 23 (+0x5c)
#define SLOT(n) virtual void Slot##n();
    SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
#undef SLOT
    virtual INT UpdateParticles(FLOAT DeltaTime);    // slot 29

    BYTE Pad04[0x34 - 0x04];
    FVector ExtentMultiplier;    // 0x34
    BYTE Pad40[0x90 - 0x40];
    FVector RealExtentMultiplier; // 0x90
    BYTE Pad9c[0xc0 - 0x9c];
    FBox BoundingBox;            // 0xc0
    BYTE Padd8[0x150 - 0xd8];
    INT MaxParticles;            // 0x150
    BYTE Pad154[0x1e0 - 0x154];
    DWORD Flags1e0 : 7;
    DWORD ResetFlag : 1;         // 0x1e0 bit 7 (neutral name)
    DWORD Flags1e0b : 19;
    DWORD UniformSize : 1;       // 0x1e0 bit 27
    DWORD Flags1e0c : 4;
    BYTE Pad1e4[0x294 - 0x1e4];
    FRangeVector StartSizeRange; // 0x294
    BYTE Pad2ac[0x39c - 0x2ac];
    AActor *Owner39c;            // 0x39c (neutral name)
    BYTE Pad3a0[0x3a8 - 0x3a0];
    INT MaxActiveParticles;      // 0x3a8
    BYTE Pad3ac[0x3d8 - 0x3ac];
    FLOAT Scale3d8;              // 0x3d8 (neutral name)
};

class UMeshEmitter : public UParticleEmitter {
public:
    BYTE Pad3dc[0x3e8 - 0x3dc];
    FVector MeshExtent;          // 0x3e8
    UStaticMesh *StaticMesh;     // 0x3f4

    void Initialize(INT InMaxParticles);
    INT UpdateParticles(FLOAT DeltaTime);
};

void UParticleEmitter::Reinitialize_80ba0()
{
    if (MaxActiveParticles != MaxParticles || ResetFlag) {
        CleanUp();
        Initialize(MaxParticles);
    }
    CleanUp();
    Initialize(MaxParticles);
}

void UMeshEmitter::Initialize(INT InMaxParticles)
{
    UParticleEmitter::Initialize(InMaxParticles);
    if (StaticMesh) {
        MeshExtent.X = Max(StaticMesh->BoundingBox.Min.X, StaticMesh->BoundingBox.Max.X);
        MeshExtent.Y = Max(StaticMesh->BoundingBox.Min.Y, StaticMesh->BoundingBox.Max.Y);
        MeshExtent.Z = Max(StaticMesh->BoundingBox.Min.Z, StaticMesh->BoundingBox.Max.Z);
        MeshExtent -= StaticMesh->BoundingBox.GetCenter();
    }
    RealExtentMultiplier = MeshExtent * ExtentMultiplier;
}

// FBox::ExpandBy (0x81a70) belongs to the next work item; it is defined here so
// the LTCG link gives it retail's register convention (this in EAX, result in ECX).
// Neutral names: two engine vectors the box constructor seeds itself from.
extern FVector *GUnnamed_10ccacc4;
extern FVector *GUnnamed_10ccacc0;
FBox::FBox(const FVector &A, const FVector &B) : Min(A), Max(B)
{
    Min = *GUnnamed_10ccacc4;
    Max = *GUnnamed_10ccacc0;
    *this += A;
    *this += B;
}

FBox FBox::ExpandBy(FLOAT W) const
{
    return FBox(Min - FVector(W, W, W), Max + FVector(W, W, W));
}

INT UMeshEmitter::UpdateParticles(FLOAT DeltaTime)
{
    INT Result = UParticleEmitter::UpdateParticles(DeltaTime);
    if (BoundingBox.Min.X - BoundingBox.Max.X != 0.f) {
        FLOAT Scale = Scale3d8;
        FLOAT Size = (UniformSize ? StartSizeRange.X.GetMax() : StartSizeRange.GetMax()) * Scale;
        BoundingBox = BoundingBox.ExpandBy(MeshExtent.GetMax() * Size * 2.f);
        if (Owner39c)
            BoundingBox = BoundingBox.ExpandBy(Owner39c->Velocity.Size() * Size);
    }
    return Result;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
INT Driver_80d20(UMeshEmitter *E, FLOAT D) { return E->UpdateParticles(D); }
void Driver_80bf0(UMeshEmitter *E, INT N) { E->Initialize(N); }
void Driver_80ad0(ASecurity *S, FFrame &F, void *R) { S->execNativePerform(F, R); }
