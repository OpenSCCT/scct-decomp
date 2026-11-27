// Engine.Actor bone control natives and the USkeletalMeshInstance controllers they update.
#include "versus_build.h"
#include "unreal_types.h"
#include "unreal_script.h"

class AActor;
class UMeshInstance;
enum { INDEX_NONE = -1 };

// The native default vector copies its three components individually.
struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
};

extern const FVector &GMath_Zero;

class FArray
{
public:
    INT Add(INT Count, INT ElementSize);
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray {
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Add(INT Count = 1) { return FArray::Add(Count, sizeof(T)); }
};

class UClass : public UObject
{
public:
    UClass *SuperField; // +0x28

    UClass *GetSuperClass() const { return SuperField; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

class UMesh : public UObject
{
public:
    UMeshInstance *MeshGetInstance(const AActor *Owner); // RVA 0xdf4e0
};

class ULodMesh : public UMesh {};

class USkeletalMesh : public ULodMesh
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

// Only the mesh-instance fields accessed by these natives are shown.
class UPrimitive : public UObject {
public:
    BYTE Unknown028[0x50 - 0x28];
};
class UMeshInstance : public UPrimitive {};
class ULodMeshInstance : public UMeshInstance {
public:
    BYTE Unknown050[0x28];
};

struct FBoneControl
{
    INT BoneIndex;
    FName BoneName;
    FRotator Turn;
    FVector Trans;
    INT Space;
    FLOAT RotationAlpha, TranslationAlpha;
    FLOAT RotationFadeIn, TranslationFadeIn, RotationFadeOut, TranslationFadeOut;
    UBOOL bTranslationFading, bRotationFading;
};

typedef char FBoneControl_size[sizeof(FBoneControl) == 0x44 ? 1 : -1];

class USkeletalMeshInstance : public ULodMeshInstance
{
public:
    BYTE Unknown078[0x118 - 0x78];
    TArray<FBoneControl> BoneAdjustments;
    TArray<FBoneControl> BoneDirections;   // +0x124

    INT MatchRefBone(FName BoneName);
    UBOOL SetBoneLocation(FName BoneName, const FVector &BoneTrans, FLOAT Alpha, FLOAT FadeIn, FLOAT FadeOut);
    UBOOL SetBoneRotation(FName BoneName, const FRotator &BoneTurn, INT Space, FLOAT Alpha, FLOAT FadeIn, FLOAT FadeOut);
    UBOOL SetBoneDirection(FName BoneName, const FRotator &BoneTurn, const FVector &BoneTrans, FLOAT Alpha, INT Space);
};

class AActor : public UObject
{
public:
    BYTE unk_28[0x194];
    UMesh *Mesh; // +0x1bc

    void execSetBoneLocation(FFrame &Stack, RESULT_DECL);
    void execSetBoneRotation(FFrame &Stack, RESULT_DECL);
    void execSetBoneDirection(FFrame &Stack, RESULT_DECL);
};

// AActor::execSetBoneLocation
void AActor::execSetBoneLocation(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_VECTOR_OPTX(BoneTrans, GMath_Zero);
    P_GET_FLOAT(Alpha);
    P_GET_FLOAT(FadeIn);
    P_GET_FLOAT(FadeOut);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneLocation(BoneName, BoneTrans, Alpha, FadeIn, FadeOut);
}

// AActor::execSetBoneRotation
void AActor::execSetBoneRotation(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_ROTATOR_OPTX(BoneTurn, FRotator(0, 0, 0));
    P_GET_INT(Space);
    P_GET_FLOAT_OPTX(Alpha, 1.0f);
    P_GET_FLOAT(FadeIn);
    P_GET_FLOAT(FadeOut);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneRotation(BoneName, BoneTurn, Space, Alpha, FadeIn, FadeOut);
}

// AActor::execSetBoneDirection
void AActor::execSetBoneDirection(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_ROTATOR(BoneTurn);
    P_GET_VECTOR_OPTX(BoneTrans, GMath_Zero);
    P_GET_FLOAT_OPTX(Alpha, 1.0f);
    P_GET_INT(Space);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneDirection(BoneName, BoneTurn, BoneTrans, Alpha, Space);
}


UBOOL USkeletalMeshInstance::SetBoneLocation(FName BoneName, const FVector &BoneTrans, FLOAT Alpha, FLOAT FadeIn, FLOAT FadeOut)
{
    if (BoneAdjustments.Num() >= 256)
        return 0;
    INT boneIndex = MatchRefBone(BoneName);
    if (boneIndex >= 0) {
        INT i = INDEX_NONE;
        for (INT j = 0; j < BoneAdjustments.Num(); ++j) {
            if (BoneAdjustments(j).BoneName == BoneName) {
                i = j;
                break;
            }
        }
        if (i < 0) {
            i = BoneAdjustments.Num();
            BoneAdjustments.Add();
            BoneAdjustments(i).BoneName = BoneName;
            BoneAdjustments(i).RotationAlpha = 0;
            BoneAdjustments(i).BoneIndex = boneIndex;
            BoneAdjustments(i).bRotationFading = 0;
        }
        BoneAdjustments(i).TranslationAlpha = Alpha;
        BoneAdjustments(i).TranslationFadeOut = FadeOut;
        BoneAdjustments(i).TranslationFadeIn = FadeIn;
        BoneAdjustments(i).bTranslationFading = BoneAdjustments(i).TranslationFadeIn > 0.0f;
        BoneAdjustments(i).Trans = BoneTrans;
        return 1;
    }
    return 0;
}

UBOOL USkeletalMeshInstance::SetBoneRotation(FName BoneName, const FRotator &BoneTurn, INT Space, FLOAT Alpha, FLOAT FadeIn, FLOAT FadeOut)
{
    if (BoneAdjustments.Num() >= 256)
        return 0;
    INT boneIndex = MatchRefBone(BoneName);
    if (boneIndex >= 0) {
        INT i = INDEX_NONE;
        for (INT j = 0; j < BoneAdjustments.Num(); ++j) {
            if (BoneAdjustments(j).BoneName == BoneName) {
                i = j;
                break;
            }
        }
        if (i < 0) {
            i = BoneAdjustments.Num();
            BoneAdjustments.Add();
            BoneAdjustments(i).BoneName = BoneName;
            BoneAdjustments(i).TranslationAlpha = 0;
            BoneAdjustments(i).BoneIndex = boneIndex;
            BoneAdjustments(i).bTranslationFading = 0;
        }
        BoneAdjustments(i).Space = Space;
        BoneAdjustments(i).RotationAlpha = Alpha;
        BoneAdjustments(i).RotationFadeOut = FadeOut;
        BoneAdjustments(i).RotationFadeIn = FadeIn;
        BoneAdjustments(i).bRotationFading = BoneAdjustments(i).RotationFadeIn > 0.0f;
        BoneAdjustments(i).Turn = BoneTurn;
        return 1;
    }
    return 0;
}

UBOOL USkeletalMeshInstance::SetBoneDirection(FName BoneName, const FRotator &BoneTurn, const FVector &BoneTrans, FLOAT Alpha, INT Space)
{
    if (BoneDirections.Num() >= 256)
        return 0;
    INT boneIndex = MatchRefBone(BoneName);
    if (boneIndex >= 0) {
        INT i = INDEX_NONE;
        for (INT j = 0; j < BoneDirections.Num(); ++j) {
            if (BoneDirections(j).BoneName == BoneName) {
                i = j;
                break;
            }
        }
        if (i < 0) {
            i = BoneDirections.Num();
            BoneDirections.Add();
            BoneDirections(i).BoneName = BoneName;
            BoneDirections(i).TranslationAlpha = 0;
            BoneDirections(i).BoneIndex = boneIndex;
        }
        BoneDirections(i).Space = Space;
        BoneDirections(i).RotationAlpha = Alpha;
        BoneDirections(i).TranslationAlpha = Alpha;
        BoneDirections(i).Turn = BoneTurn;
        BoneDirections(i).Trans = BoneTrans;
        return 1;
    }
    return 0;
}
