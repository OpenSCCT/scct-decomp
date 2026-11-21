// Work item w4_0037: Versus RVA 0x12a0c0-0x12a413, 6 functions.
//   0x12a0c0 AVolume::execEncompasses
//   0x12a130 AHUD::execDraw3DLine
//   0x12a280 AActor::execIsLightEchelon
//   0x12a2a0 AActor::AttachProjector
//   0x12a340 AActor::Slot75 (vtable slot 75; neutral name)
//   0x12a370 AActor::execGetRenderBoundingSphere

typedef unsigned short TCHAR;
typedef unsigned short _WORD;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned int size_t;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned __int64 QWORD;

#define FORCEINLINE __forceinline
#define RESULT_DECL void *const Result

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

inline void *operator new(size_t, void *Mem) { return Mem; }

enum EName { NAME_None = 0 };
enum EDrawType { DT_Mesh = 2 };
enum ELightType { LT_Echelon = 0x16 };

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

extern const TCHAR FArrayAddTag[];
extern const TCHAR FArrayTag[];

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data) { GMalloc->Free(Data); Data = 0; }
        ArrayMax = ArrayNum = 0;
    }
    INT Add(INT Count, INT ElementSize);
    void Remove(INT Index, INT Count, INT ElementSize);
    INT Num() const { return ArrayNum; }
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray() { Remove(0, ArrayNum); }
    INT Add(INT n = 1) { return FArray::Add(n, sizeof(T)); }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++) (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT GrowBy(INT Count)
    {
        INT Index = ArrayNum;
        if ((ArrayNum += Count) > ArrayMax)
        {
            ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
            if (Data == 0)
                Data = GMalloc->Malloc(ArrayMax * sizeof(T), FArrayAddTag);
            else
                Data = GMalloc->Realloc(Data, ArrayMax * sizeof(T), FArrayTag);
        }
        return Index;
    }
    INT AddUniqueItem(const T &Item);
};

template <class T> inline void *operator new(size_t, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};

struct FVector4 : public FPlane
{
    FVector4() {}
    FVector4(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FPlane(InX, InY, InZ, InW) {}
};

struct FSphere : public FPlane
{
    FSphere TransformBy(const struct FMatrix &M) const;
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FColor
{
    BYTE B, G, R, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : B(InB), G(InG), R(InR), A(InA) {}
};

struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *S, FLOAT *C) const;
};
extern FGlobalMath GMath;

struct FMatrix
{
    FLOAT M[4][4];
    FMatrix() {}
    FVector4 TransformFVector4(const FVector4 &P) const;
    FORCEINLINE FMatrix(const FVector &Location, const FRotator &Rotation, const FVector &DrawScale3D,
                        const FLOAT &DrawScale, const FVector &PrePivot)
    {
        FLOAT SY, CY, SP, CP, SR, CR;
        GMath.SinCos(Rotation.Yaw, &SY, &CY);
        GMath.SinCos(Rotation.Pitch, &SP, &CP);
        GMath.SinCos(Rotation.Roll, &SR, &CR);

        FLOAT LX = Location.X, LY = Location.Y, LZ = Location.Z;
        FLOAT PX = PrePivot.X, PY = PrePivot.Y, PZ = PrePivot.Z;
        FLOAT DX = DrawScale3D.X * DrawScale,
              DY = DrawScale3D.Y * DrawScale,
              DZ = DrawScale3D.Z * DrawScale;

        M[0][3] = 0.f;
        FLOAT CPSY = CP * SY, CPCY = CP * CY;
        M[0][0] = CPCY * DX;
        M[0][1] = CPSY * DX;
        M[0][2] = SP * DX;

        FLOAT CRSY = CR * SY, CRCY = CR * CY, SRCP = SR * CP;
        FLOAT SRCY = SR * CY, SRCYSP = SRCY * SP;
        FLOAT YY = SR * SP * SY + CRCY;
        M[1][0] = (SRCYSP - CRSY) * DY;
        M[1][1] = YY * DY;
        M[1][2] = -(SRCP * DY);
        M[1][3] = 0.f;

        FLOAT SRSY = SR * SY, CRCYSP = CRCY * SP, CRSYSP = CRSY * SP, CRCP = CR * CP;
        FLOAT ZX = CRCYSP + SRSY;
        FLOAT ZY = SRCY - CRSYSP;
        M[2][0] = -(ZX * DZ);
        M[2][1] = ZY * DZ;
        M[2][2] = CRCP * DZ;
        M[2][3] = 0.f;
        M[3][3] = 1.f;

        FLOAT TX = DX * PX, TY = DY * PY, TZ = DZ * PZ;
        M[3][0] = (LX - TX * CPCY) + (CRSY - SRCYSP) * TY + ZX * TZ;
        M[3][1] = LY - (ZY * TZ + YY * TY + TX * CPSY);
        M[3][2] = LZ - ((TX * SP - TY * SRCP) + TZ * CRCP);
    }
};

inline FLOAT appSqrt(FLOAT V) { return (FLOAT)sqrt(V); }
inline FLOAT FloatMax(FLOAT A, FLOAT B) { return *(DWORD *)&A >= *(DWORD *)&B ? A : B; }

// ---- Core objects and script frame ----

class UClass;
class UStruct;
struct FFrame;

class UField
{
public:
    virtual void V00();
    BYTE Pad04[0x24];
    UField *SuperField; // 0x28
};

class UClass : public UField
{
};

class UObject
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21();

    BYTE Pad04[0x20];
    UClass *Class; // 0x24

    UBOOL IsA(UClass *SomeBase) const
    {
        for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
            if (TempClass == SomeBase)
                return 1;
        return SomeBase == 0;
    }
};

template <class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

class __declspec(novtable) FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_ACTOR(Var) P_GET_OBJECT(AActor, Var)
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_GET_STRUCT(Type, Var) Type Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

// ---- Render / LineBatcher ----

class FRenderInterface;

class FVertexStream
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
};

struct FLineVertex
{
    FVector Position;
    FColor Color;
    FLineVertex(FVector InPosition, FColor InColor) { Position = InPosition; Color = InColor; }
};

extern QWORD GCacheId;
inline QWORD MakeCacheID(INT Type) { return GCacheId++ * 256 + Type; }

class FLineBatcher : public FVertexStream
{
public:
    TArray<FLineVertex> Vertices;
    QWORD CacheId;
    UBOOL ZTest;
    FRenderInterface *RI;

    FLineBatcher(FRenderInterface *InRI, UBOOL InZTest);
    ~FLineBatcher();
    void DrawLine(FVector P1, FVector P2, FColor Color);
    void Flush(DWORD PolyFlags = 0);
};

// ---- Projector / Level / Mesh / Primitive / Viewport ----

struct FTimedGlobal_Inner { BYTE Pad[0x58]; INT Flag; };
struct FTimedGlobal_Mid { BYTE Pad[0x38]; FTimedGlobal_Inner *Inner; };
struct FTimedGlobal
{
    BYTE Pad0[0x28];
    FTimedGlobal_Mid *Mid;
    BYTE Pad2C[0x4c - 0x2c];
    INT A;
    BYTE Pad50[4];
    INT B;
};
extern FTimedGlobal *GUnnamed_c9245c;

class AProjector;
class FProjectorRenderInfo
{
public:
    AProjector *Projector;
    INT ReferenceCount;     // 0x04
    DOUBLE LastTime;        // 0x08
    DOUBLE ExpireTime;      // 0x10

    FProjectorRenderInfo *AddReference() { ReferenceCount++; return this; }
    UBOOL Render(DOUBLE Time);
};

class ALevelInfo
{
public:
    BYTE Pad0[0x3b0];
    FLOAT TimeSeconds;      // 0x3b0
};

class ULevel
{
public:
    BYTE Pad0[0x4ac8];
    TArray<TArray<FProjectorRenderInfo *> *> ActorProjectors; // 0x4ac8
};

class UPlayer : public UObject
{
};

class UViewport : public UPlayer
{
public:
    BYTE Pad28[0x140 - 0x28];
    FRenderInterface *RI;   // 0x140

    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class AActor;

class UPrimitive : public UObject
{
public:
    virtual void P22(); virtual void P23(); virtual void P24();
    virtual FSphere GetRenderBoundingSphere(const AActor *Owner); // slot 25 (0x64)
};

class UMeshInstance : public UPrimitive
{
public:
    virtual void M26(); virtual void M27(); virtual void M28(); virtual void M29();
    virtual void M30(); virtual void M31(); virtual void M32(); virtual void M33();
    virtual void M34(); virtual void M35(); virtual void M36(); virtual void M37();
    virtual void M38(); virtual void M39(); virtual void M40(); virtual void M41();
    virtual void M42(); virtual void M43(); virtual void M44(); virtual void M45();
    virtual void M46(); virtual void M47(); virtual void M48(); virtual void M49();
    virtual void M50(); virtual void M51(); virtual void M52(); virtual void M53();
    virtual void M54(); virtual void M55(); virtual void M56(); virtual void M57();
    virtual void M58(); virtual void M59(); virtual void M60(); virtual void M61();
    virtual void M62(); virtual void M63(); virtual void M64(); virtual void M65();
    virtual void M66();
    virtual FMatrix MeshToWorld(); // slot 67 (0x10c)
};

class UMesh : public UPrimitive
{
public:
    UMeshInstance *MeshGetInstance(const AActor *InActor);
};

// ---- AActor and subclasses ----

class AActor : public UObject
{
public:
    virtual void A22(); virtual void A23(); virtual void A24(); virtual void A25();
    virtual void A26(); virtual void A27(); virtual void A28(); virtual void A29();
    virtual void A30(); virtual void A31(); virtual void A32(); virtual void A33();
    virtual void A34(); virtual void A35(); virtual void A36(); virtual void A37();
    virtual void A38(); virtual void A39(); virtual void A40(); virtual void A41();
    virtual void A42(); virtual void A43();
    virtual UPrimitive *GetPrimitive(); // slot 44 (0xb0)
    virtual void A45(); virtual void A46(); virtual void A47(); virtual void A48();
    virtual void A49(); virtual void A50(); virtual void A51(); virtual void A52();
    virtual void A53(); virtual void A54(); virtual void A55(); virtual void A56();
    virtual void A57(); virtual void A58(); virtual void A59(); virtual void A60();
    virtual void A61(); virtual void A62(); virtual void A63(); virtual void A64();
    virtual void A65(); virtual void A66(); virtual void A67(); virtual void A68();
    virtual void A69(); virtual void A70(); virtual void A71(); virtual void A72();
    virtual void A73(); virtual void A74();
    virtual AActor *Slot75(); // slot 75 (0x12c)

    BYTE Pad28[0x80 - 0x28];
    FVector Location;       // 0x80
    BYTE Pad8C[0xb0 - 0x8c];
    FVector DrawScale3D;    // 0xb0
    FVector PrePivot;       // 0xbc
    BYTE PadC8[0xe0 - 0xc8];
    FRotator Rotation;      // 0xe0
    BYTE PadEC[0x108 - 0xec];
    AActor *Base;           // 0x108
    BYTE Pad10C[0x1a0 - 0x10c];
    ALevelInfo *Level;      // 0x1a0
    ULevel *XLevel;         // 0x1a4
    BYTE Pad1A8[0x1bc - 0x1a8];
    UMesh *Mesh;            // 0x1bc
    BYTE Pad1C0[0x210 - 0x1c0];
    TArray<FProjectorRenderInfo *> Projectors; // 0x210
    BYTE Pad21C[0x23c - 0x21c];
    FLOAT DrawScale;        // 0x23c
    BYTE Pad240[0x2d2 - 0x240];
    BYTE LightType;         // 0x2d2
    BYTE Pad2D3[0x2d9 - 0x2d3];
    BYTE DrawType;          // 0x2d9
    BYTE Pad2DA[0x2e8 - 0x2da];
    DWORD Pad2E8Bits : 25;
    DWORD bFlag2E8_25 : 1;  // 0x2e8 bit 25 (0x02000000)
    DWORD Pad2E8Rest : 6;
    DWORD Flags2EC;         // 0x2ec
    DWORD Pad2F0Bits : 12;
    DWORD bCollideActors : 1; // 0x2f0 bit 12 (0x1000)
    DWORD Pad2F0Rest : 19;
    DWORD Field2F4;         // 0x2f4 (total AActor size 0x2f8)

    inline bool IsLightEchelon() const { return LightType == LT_Echelon; }
    inline FMatrix GetRenderLocalToWorld()
    {
        if (DrawType == DT_Mesh && Mesh)
        {
            FMatrix Matrix;
            Matrix = Mesh->MeshGetInstance(this)->MeshToWorld();
            return Matrix;
        }
        return LocalToWorld();
    }

    FMatrix LocalToWorld();
    void AttachProjector(AProjector *Projector);
    void execIsLightEchelon(FFrame &Stack, RESULT_DECL);
    void execGetRenderBoundingSphere(FFrame &Stack, RESULT_DECL);
};

class AVolume : public AActor
{
public:
    UBOOL Encompasses(FVector Point);
    void execEncompasses(FFrame &Stack, RESULT_DECL);
};

class APlayerController : public AActor
{
public:
    BYTE Pad2F8[0x4a4 - 0x2f8];
    UPlayer *Player;        // 0x4a4
};

class AHUD : public AActor
{
public:
    BYTE Pad2F8[0x3e0 - 0x2f8];
    APlayerController *PlayerOwner; // 0x3e0

    void execDraw3DLine(FFrame &Stack, RESULT_DECL);
};

class AProjector : public AActor
{
public:
    BYTE Pad2F8[0x464 - 0x2f8];
    FProjectorRenderInfo *RenderInfo; // 0x464
};

// ============================================================================
// Target functions
// ============================================================================

// RVA 0x12a0c0
void AVolume::execEncompasses(FFrame &Stack, RESULT_DECL)
{
    P_GET_ACTOR(Other);
    P_FINISH;
    *(UBOOL *)Result = Encompasses(Other->Location);
}

// RVA 0x12a130
void AHUD::execDraw3DLine(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Start);
    P_GET_VECTOR(End);
    P_GET_STRUCT(FColor, LineColor);
    P_FINISH;

    if (PlayerOwner)
    {
        UViewport *Viewport = Cast<UViewport>(PlayerOwner->Player);
        if (Viewport)
        {
            FLineBatcher LineBatcher(Viewport->RI, 1);
            LineBatcher.DrawLine(Start, End, LineColor);
        }
    }
}

// RVA 0x12a280
void AActor::execIsLightEchelon(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(UBOOL *)Result = IsLightEchelon();
}

// RVA 0x12a2a0
void AActor::AttachProjector(AProjector *Projector)
{
    for (INT i = 0; i < Projectors.Num(); i++)
    {
        if (!Projectors(i)->Render(Level->TimeSeconds))
            Projectors.Remove(i--);
    }
    Projectors.AddUniqueItem(Projector->RenderInfo->AddReference());
    XLevel->ActorProjectors.AddUniqueItem(&Projectors);
}

// RVA 0x12a340
AActor *AActor::Slot75()
{
    if (!bCollideActors && bFlag2E8_25 && Base)
        return Base->Slot75();
    return this;
}

// RVA 0x12a370
void AActor::execGetRenderBoundingSphere(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    FMatrix LocalToWorldMatrix = GetRenderLocalToWorld();
    *(FSphere *)Result = GetPrimitive()->GetRenderBoundingSphere(this).TransformBy(LocalToWorldMatrix);
}

// ============================================================================
// Out-of-line LTCG callees from other units, defined here only so the linker
// gives them their retail register conventions (not part of this work item).
// ============================================================================

// Callee of 0x12a0c0 (retail 0x12eec0: LTCG this in ESI, FVector on stack, ret 0xc).
extern UBOOL VolumeEncompassesHelper(AVolume *Self, FVector *Pt);
__declspec(noinline) UBOOL AVolume::Encompasses(FVector Point)
{
    return VolumeEncompassesHelper(this, &Point) + VolumeEncompassesHelper(this, &Point);
}

// Callees of 0x12a130 (retail 0x1116c0, 0x111730, 0x1119a0 from item 0349).
__declspec(noinline) FLineBatcher::FLineBatcher(FRenderInterface *InRI, UBOOL InZTest)
{
    RI = InRI;
    ZTest = InZTest;
    CacheId = MakeCacheID(0xe1);
}

__declspec(noinline) FLineBatcher::~FLineBatcher()
{
    Flush();
}

__declspec(noinline) void FLineBatcher::DrawLine(FVector P1, FVector P2, FColor Color)
{
    new(Vertices) FLineVertex(P1, Color);
    new(Vertices) FLineVertex(P2, Color);
}

// Callees of 0x12a2a0 (retail 0x9e510 from item 0360, 0xc9bb0 from item 0160).
__declspec(noinline) UBOOL FProjectorRenderInfo::Render(DOUBLE Time)
{
    if (ExpireTime != 0.0 && !(GUnnamed_c9245c->A && GUnnamed_c9245c->B && GUnnamed_c9245c->Mid->Inner->Flag))
        goto Expired;
    if (ExpireTime != 0.0)
    {
        if (ExpireTime <= Time)
            goto Expired;
        if (LastTime != 0.0 && Time - LastTime > 1.0)
            goto Expired;
    }
    LastTime = Time;
    return 1;
Expired:
    if (--ReferenceCount == 0)
        GMalloc->Free(this);
    return 0;
}

template <class T> __declspec(noinline) INT TArray<T>::AddUniqueItem(const T &Item)
{
    INT Index;
    for (Index = 0; Index < Num(); Index++)
        if ((*this)(Index) == Item)
            return Index;
    Index = GrowBy(1);
    (*this)(Index) = Item;
    return Index;
}

// Callees of 0x12a370 (retail 0x9e5b0 from item 0361, 0x117db0 from item 0370).
FMatrix AActor::LocalToWorld()
{
    return FMatrix(Location, Rotation, DrawScale3D, DrawScale, PrePivot);
}

__declspec(noinline) FSphere FSphere::TransformBy(const FMatrix &M) const
{
    FSphere Result;
    (FVector &)Result = M.TransformFVector4(FVector4(X, Y, Z, 1.0f));
    FVector XAxis(M.M[0][0], M.M[0][1], M.M[0][2]);
    FVector YAxis(M.M[1][0], M.M[1][1], M.M[1][2]);
    FVector ZAxis(M.M[2][0], M.M[2][1], M.M[2][2]);
    Result.W = appSqrt(FloatMax(XAxis | XAxis, FloatMax(YAxis | YAxis, ZAxis | ZAxis))) * W;
    return Result;
}

// ============================================================================
// Scaffolding for LTCG links, not part of the unit.
// ============================================================================
void Escape(void *);
void UseMatrix(const FMatrix &M);

typedef void (AVolume::*ExecEncompassesFn)(FFrame &, RESULT_DECL);
typedef void (AHUD::*ExecDraw3DLineFn)(FFrame &, RESULT_DECL);
typedef void (AActor::*ExecIsLightEchelonFn)(FFrame &, RESULT_DECL);
typedef AActor *(AActor::*Slot75Fn)();
typedef void (AActor::*ExecGetRenderBoundingSphereFn)(FFrame &, RESULT_DECL);
void Escape(ExecEncompassesFn);
void Escape(ExecDraw3DLineFn);
void Escape(ExecIsLightEchelonFn);
void Escape(Slot75Fn);
void Escape(ExecGetRenderBoundingSphereFn);

void Driver_12a0c0(AVolume *V, FFrame *S, void *R, FVector Pt)
{
    Escape(&AVolume::execEncompasses);
    V->execEncompasses(*S, R);
    V->Encompasses(Pt);
}

void Driver_12a130(AHUD *H, FFrame *S, void *R, UViewport *V, FVector A, FVector B, FColor C)
{
    Escape(&AHUD::execDraw3DLine);
    Escape(&GMalloc);
    Escape(&GCacheId);
    H->execDraw3DLine(*S, R);
    for (INT i = 0; i < 4; i++)
    {
        FLineBatcher LB(V[i].RI, i & 1);
        LB.DrawLine(A, B, C);
    }
}

void Driver_12a280(AActor *A, FFrame *S, void *R)
{
    Escape(&AActor::execIsLightEchelon);
    A->execIsLightEchelon(*S, R);
}

void Driver_12a2a0(AActor *A, AProjector *P)
{
    Escape(&GMalloc);
    Escape(&GUnnamed_c9245c);
    A->AttachProjector(P);
    A[1].AttachProjector(P);
}

AActor *Driver_12a340(AActor *A)
{
    AActor Tmp;
    Escape(&Tmp);
    return A->AActor::Slot75();
}

void Driver_12a370(AActor *A, FFrame *S, void *R, FSphere *Sp, FMatrix *M)
{
    Escape(&AActor::execGetRenderBoundingSphere);
    Escape(&GMath);
    A->execGetRenderBoundingSphere(*S, R);
    UseMatrix(A->LocalToWorld());
    *Sp = Sp->TransformBy(*M);
}
