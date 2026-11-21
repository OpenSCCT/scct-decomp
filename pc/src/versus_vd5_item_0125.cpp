// Work item w3 0125: Versus RVA 0xb7b10-0xb7f2c (LTCG object, mesh instance
// bone queries). 0xb7b10 is USkeletalMeshInstance vtable slot 24 (reflected
// vtable label). The other methods share the same object layout: a TArray of
// FCoords bone space bases (0x178), a second FCoords array (0xb4), the mesh
// coordinate frame (0xc0) and a 64-bit frame stamp (0x5c) compared with a
// global frame counter. Method and field names other than the UE2 math types
// are neutral guesses.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef __int64 SQWORD;

struct FCoords;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector TransformPointBy(const FCoords &Coords) const;     // retail 0x10940b20
    inline FVector TransformVectorBy(const FCoords &Coords) const;
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
};

struct FCoords
{
    FVector Origin, XAxis, YAxis, ZAxis;
    FCoords() {}
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}
    FCoords(const FCoords &Other);                  // retail 0x10940890 (out of line)
    FCoords operator*(const FRotator &R) const;     // retail 0x109411a0
    FCoords operator*(const FCoords &C) const;      // retail 0x10992d00
    FCoords Transpose() const;                      // retail 0x10992c40
    FRotator OrthoRotation() const;                 // retail 0x10950770
};

// UnMath.h ASMTransformVector, retail 0x10940ab0.
void ASMTransformVector(const FCoords &Coords, const FVector &InVector, FVector &OutVector);

inline FVector FVector::TransformVectorBy(const FCoords &Coords) const
{
    FVector Temp;
    ASMTransformVector(Coords, *this, Temp);
    return Temp;
}

struct FGlobalMath
{
    FCoords UnitCoords;
};
extern FGlobalMath GMath;                           // retail 0x10ccac00
extern const FVector &GZeroVector_acc0;             // retail 0x10ccacc0 (reference to a zero vector)

extern SQWORD GUnnamedFrame_c71ae0;                 // retail 0x10c71ae0

struct FBox { FVector Min, Max; };

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
};
template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class AActor;

// Object returned by mesh instance vtable slot 32 (UE2: the mesh).
class UnnamedMesh
{
public:
    BYTE Pad00[0x28];
    FBox BoundingBox;                               // 0x28
};

// Object at +0x100 of the instance (neutral).
struct UnnamedOwner_100
{
    BYTE Pad00[0x44];
    INT Field44;
};

#pragma pack(push, 4)
class USkeletalMeshInstance
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1c();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3c();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4c();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5c();
    virtual FBox GetRenderBoundingBox(const AActor *Owner);                     // slot 24
    virtual void V64(); virtual void V68(); virtual void V6c();
    virtual void V70(); virtual void V74();
    virtual AActor *GetActor();                                                 // slot 30
    virtual void V7c();
    virtual UnnamedMesh *GetMesh();                                             // slot 32
    virtual void V84(); virtual void V88(); virtual void V8c();
    virtual void V90(); virtual void V94(); virtual void V98(); virtual void V9c();
    virtual void Va0(); virtual void Va4(); virtual void Va8(); virtual void Vac();
    virtual void Vb0(); virtual void Vb4(); virtual void Vb8(); virtual void Vbc();
    virtual void Vc0(); virtual void Vc4(); virtual void Vc8(); virtual void Vcc();
    virtual void Vd0(); virtual void Vd4(); virtual void Vd8(); virtual void Vdc();
    virtual void Ve0(); virtual void Ve4(); virtual void Ve8(); virtual void Vec();
    virtual void Vf0(); virtual void Vf4(); virtual void Vf8(); virtual void Vfc();
    virtual void V100(); virtual void V104();
    virtual INT UpdateAnimation(AActor *Owner, INT A, INT B, INT C, INT *D, INT Mode);  // slot 66

    BYTE Pad004[0x5c - 0x04];
    SQWORD LastFrame;                               // 0x5c
    BYTE Pad064[0xb4 - 0x64];
    TArray<FCoords> CachedCoords;                   // 0xb4
    FCoords MeshCoords;                             // 0xc0
    BYTE PadF0[0x100 - 0xf0];
    UnnamedOwner_100 *Owner100;                     // 0x100
    BYTE Pad104[0x178 - 0x104];
    TArray<FCoords> SpaceBases;                     // 0x178
    BYTE Pad184[0x188 - 0x184];
    FVector Location188;                            // 0x188
    FRotator Rotation194;                           // 0x194
    FVector OldLocation1a0;                         // 0x1a0
    BYTE Pad1AC[0x1e8 - 0x1ac];
    INT Field1e8;                                   // 0x1e8
    BYTE Pad1EC[0x1f0 - 0x1ec];
    FCoords Coords1f0;                              // 0x1f0
    BYTE Pad220[0x2b0 - 0x220];
    FCoords Coords2b0;                              // 0x2b0

    FCoords GetBoneCoords(DWORD BoneIdx, UBOOL bForce);
    FRotator GetBoneRotation(DWORD BoneIdx, INT Unused);
    FVector GetLocation188();
    FRotator GetRotation194();
    FVector ConsumeDelta();
};
#pragma pack(pop)

// RVA 0xb7b10, vtable slot 24.
FBox USkeletalMeshInstance::GetRenderBoundingBox(const AActor *Owner)
{
    return GetMesh()->BoundingBox;
}

// RVA 0xb7b50. NEAR: 26 bytes differ, only the copy of the transformed
// origin into Result (retail loads all three words before storing them).
FCoords USkeletalMeshInstance::GetBoneCoords(DWORD BoneIdx, UBOOL bForce)
{
    AActor *Actor = GetActor();
    if (!Actor)
        return GMath.UnitCoords;
    if (!SpaceBases.Num() || (LastFrame < GUnnamedFrame_c71ae0 && bForce))
        UpdateAnimation(Actor, 0, 0, 0, (INT *)&bForce, 2);
    if (SpaceBases.Num() && BoneIdx < (DWORD)SpaceBases.Num())
    {
        FCoords Result = SpaceBases(BoneIdx).Transpose() * MeshCoords;
        Result.Origin = SpaceBases(BoneIdx).Origin.TransformPointBy(MeshCoords);
        return Result;
    }
    return GMath.UnitCoords;
}

// RVA 0xb7c50. LTCG: this ECX, BoneIdx EAX, result EBX; retail keeps one
// unused stack argument (ret 4), modelled as Unused.
FRotator USkeletalMeshInstance::GetBoneRotation(DWORD BoneIdx, INT Unused)
{
    if (!CachedCoords.Num() || LastFrame < GUnnamedFrame_c71ae0)
    {
        AActor *Actor = GetActor();
        if (Actor)
        {
            INT Dummy;
            UpdateAnimation(Actor, 0, 0, 0, &Dummy, 2);
        }
    }
    if (CachedCoords.Num() && BoneIdx < (DWORD)CachedCoords.Num())
    {
        FCoords T = CachedCoords(BoneIdx).Transpose();
        FCoords M = T * MeshCoords;
        FRotator R = M.OrthoRotation();
        return R;
    }
    return FRotator(0, 0, 0);
}

// RVA 0xb7d30.
FVector USkeletalMeshInstance::GetLocation188()
{
    if (Field1e8)
    {
        AActor *Actor = GetActor();
        if (Actor)
        {
            INT Dummy;
            UpdateAnimation(Actor, 0, 0, 0, &Dummy, 3);
        }
    }
    return Location188;
}

// RVA 0xb7d80.
FRotator USkeletalMeshInstance::GetRotation194()
{
    if (Field1e8)
    {
        AActor *Actor = GetActor();
        if (Actor)
        {
            INT Dummy;
            UpdateAnimation(Actor, 0, 0, 0, &Dummy, 3);
        }
    }
    return Rotation194;
}

// RVA 0xb7dd0.
FVector USkeletalMeshInstance::ConsumeDelta()
{
    FVector Delta = Location188 - OldLocation1a0;
    if (Owner100->Field44)
    {
        INT Yaw = Coords1f0.OrthoRotation().Yaw;
        FRotator R;
        R.Pitch = 0;
        R.Yaw = Yaw - Coords2b0.OrthoRotation().Yaw;
        R.Roll = 0;
        FCoords C = GMath.UnitCoords * R;
        C = GMath.UnitCoords * C;
        C.Origin = GZeroVector_acc0;
        Delta = Delta.TransformVectorBy(C);
    }
    OldLocation1a0 = Location188;
    return Delta;
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
INT appRound(FLOAT F);
FLOAT appAtan2(FLOAT Y, FLOAT X);
FLOAT appSqrt(FLOAT F);
void MulCoords(FCoords &A, const FCoords &B);

// Stand-in bodies for the LTCG callees so the linker gives them retail's
// register conventions (Transpose: this EAX, result ESI; operator*: this
// EAX, result ESI, operand on the stack; OrthoRotation: this ESI, result EDI).
__declspec(noinline) FCoords FCoords::Transpose() const
{
    return FCoords
    (
        -Origin.TransformVectorBy(*this),
        FVector(XAxis.X, YAxis.X, ZAxis.X),
        FVector(XAxis.Y, YAxis.Y, ZAxis.Y),
        FVector(XAxis.Z, YAxis.Z, ZAxis.Z)
    );
}

__declspec(noinline) FCoords FCoords::operator*(const FCoords &C) const
{
    FCoords R(*this);
    MulCoords(R, C);
    return R;
}

__declspec(noinline) FRotator FCoords::OrthoRotation() const
{
    FRotator R;
    R.Pitch = appRound(appAtan2(XAxis.Z, appSqrt(XAxis.X * XAxis.X + XAxis.Y * XAxis.Y)) * 10430.378f);
    R.Yaw = appRound(appAtan2(XAxis.Y, XAxis.X) * 10430.378f);
    R.Roll = appRound(appAtan2(YAxis.Z, ZAxis.Z) * 10430.378f);
    return R;
}

#pragma inline_depth(0)

typedef FBox (USkeletalMeshInstance::*BoxMethod)(const AActor *);
typedef FCoords (USkeletalMeshInstance::*CoordsMethod)(DWORD, UBOOL);

void Driver_b7b10(USkeletalMeshInstance *M, FBox *Out)
{
    BoxMethod F = &USkeletalMeshInstance::GetRenderBoundingBox;
    Escape(&F);
    *Out = (M->*F)(0);
}

void Driver_b7b50(USkeletalMeshInstance *M, FCoords *Out, DWORD I, UBOOL B)
{
    Escape(&GMath);
    Escape(&GUnnamedFrame_c71ae0);
    CoordsMethod F = &USkeletalMeshInstance::GetBoneCoords;
    Escape(&F);
    Escape(&(M->*F)(I, B));
}

void Driver_b7c50(USkeletalMeshInstance *M, FRotator *Out, DWORD I)
{
    Escape(&GUnnamedFrame_c71ae0);
    *Out = M->GetBoneRotation(I, 0);
}

void Driver_b7d30(USkeletalMeshInstance *M, FVector *Out)
{
    *Out = M->GetLocation188();
}

USkeletalMeshInstance *UnnamedFindInstance();
void Driver_b7d80(FRotator *Out)
{
    *Out = UnnamedFindInstance()->GetRotation194();
}

void Driver_b7dd0(USkeletalMeshInstance *M, FVector *Out)
{
    Escape(&GMath);
    Escape((void *)&GZeroVector_acc0);
    *Out = M->ConsumeDelta();
}
