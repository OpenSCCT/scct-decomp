// campaign_script_natives_7.cpp -- Campaign natives: skeletal bones and canvas lines
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"
#include "unreal_class.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// UECanvas::execDrawRectangle
// The PC build reads these console rendering natives' parameters and ignores them.
void UECanvas::execDrawRectangle(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(X);
    P_GET_INT(Y);
    P_GET_INT(XL);
    P_GET_INT(YL);
    P_GET_INT(Thickness);
    P_GET_STRUCT(FColor, Color);
    P_GET_INT(Alpha);
    P_GET_OBJECT(UMaterial, Material);
    P_FINISH;
    DrawRectangle(X, Y, XL, YL, Thickness, Color, Alpha, Material);
}

// UECanvas::execDrawLine
void UECanvas::execDrawLine(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(X1);
    P_GET_INT(Y1);
    P_GET_INT(X2);
    P_GET_INT(Y2);
    P_GET_STRUCT(FColor, Color);
    P_GET_INT(Alpha);
    P_GET_OBJECT(UMaterial, Material);
    P_FINISH;
    DrawLine(X1, Y1, X2, Y2, Color, Alpha, Material);
}

// AActor::execSetBoneScale
void AActor::execSetBoneScale(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Slot);
    P_GET_FLOAT_OPTX(BoneScale, 1.0f);
    P_GET_NAME(BoneName);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneScale(Slot, BoneScale, BoneName);
}

// AActor::execSetBoneLocation
void AActor::execSetBoneLocation(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_VECTOR_OPTX(BoneTrans, FVector(0, 0, 0));
    P_GET_FLOAT(Alpha);
    P_GET_FLOAT(BlendTime);
    P_GET_INT(Space);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneLocation(BoneName, BoneTrans, Alpha, BlendTime, Space);
}

// AActor::execSetBoneRotation
void AActor::execSetBoneRotation(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_ROTATOR_OPTX(BoneTurn, FRotator(0, 0, 0));
    P_GET_INT(Space);
    P_GET_FLOAT(Alpha);
    P_GET_FLOAT(BlendTime);
    P_GET_INT(bAdditive);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneRotation(BoneName, BoneTurn, Space, Alpha, BlendTime, bAdditive, 0);
}

// AActor::execSetBoneDirection
void AActor::execSetBoneDirection(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_ROTATOR(BoneTurn);
    P_GET_VECTOR_OPTX(BoneTrans, GDefaultVector);
    P_GET_FLOAT_OPTX(Alpha, 1.0f);
    P_GET_INT_OPTX(Space, 3);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneDirection(BoneName, BoneTurn, BoneTrans, Alpha, Space);
}

// AActor::execGetBoneRotation
void AActor::execGetBoneRotation(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_INT(Space);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
    {
        Mesh->MeshGetInstance(this);
        INT BoneIdx = ((USkeletalMeshInstance *)MeshInstance)->MatchRefBone(BoneName);
        if (BoneIdx >= 0)
            *(FRotator *)Result = ((USkeletalMeshInstance *)MeshInstance)->GetBoneRotation(BoneIdx, Space);
        else
            *(FRotator *)Result = FRotator(0, 0, 0);
    }
}

// AActor::execGetBoneCoords
void AActor::execGetBoneCoords(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_INT(Space);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
    {
        Mesh->MeshGetInstance(this);
        INT BoneIdx = ((USkeletalMeshInstance *)MeshInstance)->MatchRefBone(BoneName);
        if (BoneIdx >= 0)
            *(FCoords *)Result = ((USkeletalMeshInstance *)MeshInstance)->GetBoneCoords(BoneIdx, Space);
        else
            *(FCoords *)Result = GMath.UnitCoords;
    }
}
