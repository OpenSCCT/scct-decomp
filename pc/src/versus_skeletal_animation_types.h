// Skeletal mesh and instance layouts shared with the pawn's action dispatcher.
#ifndef VERSUS_SKELETAL_ANIMATION_TYPES_H
#define VERSUS_SKELETAL_ANIMATION_TYPES_H

struct MeshAnimChannel;
struct FBoneScaler;
struct FBoneControl;
class AActor;
class UMeshInstance;
class UMeshAnimation;
class USkeletalMesh;
class FStaticLODModel;

class UMesh : public UPrimitive
{
public:
    virtual void VirtualSlot30();
    UMeshInstance *MeshGetInstance(const AActor *Owner);
    UMeshInstance *DefaultInstance;
};

class ULodMesh : public UMesh {
public:
    BYTE unk_54[0xf4 - 0x54];
};
class USkeletalMesh : public ULodMesh {
public:
    static UClass PrivateStaticClass;
    BYTE unk_f4[0x1ac - 0xf4];
    TArray<FStaticLODModel> LODModels;
    BYTE unk_1b8[0x1dc - 0x1b8];
    UMeshAnimation *DefaultAnim;
    UMesh *DefaultRefMesh;
};

struct MeshAnimLinkup {
    UMeshAnimation *Anim;
    UMesh *RefMesh;
    BYTE unk_08[4];
    TArray<INT> BoneLinks;
};

class USkeletalMeshInstance : public ULodMeshInstance
{
public:
    virtual void LinkupsChanged();
    virtual void VirtualSlot73();
    virtual void ForceBoneRefresh();
    virtual UMeshAnimation *CurrentSkelAnim(INT Channel);
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }

    BYTE unk_78[0xa8 - 0x78];
    TArray<MeshAnimLinkup> AnimLinkups;
    TArray<FCoords> CachedCoords;
    FCoords MeshCoords;
    BYTE unk_f0[0x100 - 0xf0];
    TArray<MeshAnimChannel> Channels; // +0x100
    TArray<FBoneScaler> Scalers;
    TArray<FBoneControl> BoneAdjustments;          // +0x118
    TArray<FBoneControl> BoneDirections;          // +0x124

    UBOOL ApplyBlendParams(INT Stage, FLOAT Alpha, FLOAT InTime, FLOAT OutTime, FName Bone, UBOOL bGlobal);
    void BlendToAlpha(INT Channel, FLOAT TargetAlpha, FLOAT Seconds);
    UBOOL StopAnimating(UBOOL ClearAllButBase);
    UBOOL SetAnimLinkup(UMeshAnimation *Anim, UMesh *RefMesh);
    void ActualizeAnimLinkups();
};

#endif
