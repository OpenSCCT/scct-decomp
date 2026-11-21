// campaign_actor_methods_2.cpp -- AActor::TraceCheck and skeletal mesh instance methods
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"
#include "unreal_class.h"
#include "unreal_actor.h"
#include "unreal_pawn.h"
#include "campaign_engine_classes.h"

// AActor::TraceCheck
AActor *AActor::TraceCheck(FVector &HitLocation, FVector &HitNormal, const FVector &TraceEnd, const FVector &TraceStart, const FVector &Extent, UMaterial **Material, INT TraceFlags, INT bOption8, UPrimitive **Primitive, INT Mode)
{
    FCheckResult Hit(1.0f);
    if (Mode > 0 && Mode < 3)
        return TraceMode(Mode, HitLocation, HitNormal, TraceEnd, TraceStart, Extent, Material, TraceFlags, bOption8, Primitive);
    DWORD TraceType = 0x17;
    if (TraceFlags == 1)
        TraceType = 0x8017;
    else if (TraceFlags == 2)
        TraceType = 0x10017;
    else if (TraceFlags == 3)
        TraceType = 0x20017;
    else if (TraceFlags == 4)
        TraceType = 0x80017;
    else if (TraceFlags == 5)
        TraceType = 0x400017;
    else if (TraceFlags == 6)
        TraceType = 0x18017;
    if (bOption8)
        TraceType |= 8;
    if (Material)
        TraceType |= 0x80;
    GetLevel()->SingleLineCheck(Hit, this, TraceEnd, TraceStart, TraceType, Extent, 0, 0);
    HitLocation = Hit.Location;
    HitNormal = Hit.Normal;
    if (Material)
        *Material = Hit.Material;
    if (Primitive)
        *Primitive = Hit.Primitive;
    return Hit.Actor;
}

// USkeletalMeshInstance::SetBoneScale
UBOOL USkeletalMeshInstance::SetBoneScale(INT Slot, FLOAT BoneScale, FName BoneName)
{
    if (Slot < 0 || Slot > 256)
        return 0;
    while (Scalers.Num() <= Slot)
    {
        Scalers.AddZeroed();
        Scalers(Scalers.Num() - 1).Bone = -1;
    }
    if (BoneScale != 1.0f && BoneName != NAME_None)
    {
        INT BoneIdx = MatchRefBone(BoneName);
        if (BoneIdx >= 0)
        {
            Scalers(Slot).Bone = BoneIdx;
            Scalers(Slot).Name = BoneName;
            Scalers(Slot).ScaleUniform = BoneScale;
        }
    }
    else
    {
        Scalers(Slot).Bone = -1;
        Scalers(Slot).Name = NAME_None;
    }
    return 1;
}

// USkeletalMeshInstance::MatchRefBone
INT USkeletalMeshInstance::MatchRefBone(FName StartBoneName)
{
    USkeletalMesh *Mesh = (USkeletalMesh *)GetMesh();
    INT Bone = -1;
    if (StartBoneName != NAME_None)
    {
        for (INT t = 0; t < Mesh->TagAliases.Num(); t++)
        {
            if (StartBoneName == Mesh->TagAliases(t))
            {
                StartBoneName = Mesh->TagNames(t);
                break;
            }
        }
        for (INT p = 0; p < ((USkeletalMesh *)GetMesh())->RefSkeleton.Num(); p++)
        {
            if (((USkeletalMesh *)GetMesh())->RefSkeleton(p).Name == StartBoneName)
            {
                Bone = p;
                break;
            }
        }
    }
    return Bone;
}
