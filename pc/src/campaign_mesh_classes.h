// campaign_mesh_classes.h -- meshes and mesh instances as the Campaign executable builds them
#ifndef CAMPAIGN_MESH_CLASSES_H
#define CAMPAIGN_MESH_CLASSES_H

#include "unreal_object.h"
#include "unreal_math.h"
#include "unreal_containers.h"

// Engine.Primitive: 0x54 bytes, 32 virtual functions
class UPrimitive : public UObject {
public:
    virtual ~UPrimitive();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();

    BYTE unk_28[0x2c];
};

// Engine.Mesh: 0x5c bytes, 34 virtual functions
class UMesh : public UPrimitive {
public:
    virtual ~UMesh();
    virtual void VirtualSlot32();
    virtual class UMeshInstance *MeshGetInstance(const AActor *Owner);

    BYTE unk_54[0x8];
};

// Engine.LodMesh: 0x118 bytes, 34 virtual functions
class ULodMesh : public UMesh {
public:
    virtual ~ULodMesh();

    BYTE unk_5c[0xbc];
};

// A bone of a skeletal mesh's reference skeleton: 0x40 bytes.
struct FMeshBone {
    FName Name;
    BYTE  unk_4[0x3c];
};

// Engine.SkeletalMesh: 0x3e0 bytes, 34 virtual functions
class USkeletalMesh : public ULodMesh {
public:
    virtual ~USkeletalMesh();

    BYTE              unk_118[0x30];
    TArray<FMeshBone> RefSkeleton;
    BYTE              unk_154[0x25c];
    TArray<FName>     TagAliases;
    TArray<FName>     TagNames;
    BYTE              unk_3c8[0x18];

    DECLARE_LAZY_CLASS(USkeletalMesh)
};

// Engine.MeshInstance: 0x54 bytes, 79 virtual functions
class UMeshInstance : public UPrimitive {
public:
    virtual ~UMeshInstance();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual UMesh *GetMesh();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    // Returns the animation named Sequence, or 0 (execHasAnim tests it, execAnimIsInGroup passes it
    // to AnimIsInGroup). Name invented.
    virtual void *FindAnim(FName Sequence);
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual UBOOL AnimIsInGroup(void *Anim, FName Group); // named after AActor::execAnimIsInGroup
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void StopAnimating();              // named after AActor::execStopAnimating, its caller
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual UBOOL IsAnimTweening(INT Channel); // named after AActor::execIsTweening, its caller
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void VirtualSlot63();
    virtual void VirtualSlot64();
    virtual void VirtualSlot65();
    virtual void VirtualSlot66();
    virtual FName GetActiveAnimSequence(INT Channel);
    virtual FLOAT GetActiveAnimRate(INT Channel);
    virtual FLOAT GetActiveAnimFrame(INT Channel);
    virtual FLOAT GetActiveAnimBlend(INT Channel);
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void VirtualSlot73();
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();
    virtual void VirtualSlot78();
};

// Engine.LodMeshInstance: 0x78 bytes, 80 virtual functions
class ULodMeshInstance : public UMeshInstance {
public:
    virtual ~ULodMeshInstance();
    virtual void VirtualSlot79();

    BYTE unk_54[0x24];
};

// A per-bone scale of a skeletal mesh instance: 0x3c bytes.
struct FBoneScaler {
    INT   Bone;
    FName Name;
    FLOAT ScaleUniform;
    BYTE  unk_c[0x30];
};

// Engine.SkeletalMeshInstance: 0x39c bytes, 80 virtual functions
class USkeletalMeshInstance : public ULodMeshInstance {
public:
    virtual ~USkeletalMeshInstance();

    BYTE                unk_78[0x24];
    TArray<FBoneScaler> Scalers;
    BYTE                unk_a8[0x14];
    INT                 unk_bc;     // read by AActor::execGetNotifyChannel
    BYTE                unk_c0[0x2dc];

    UBOOL SetBoneScale(INT Slot, FLOAT BoneScale, FName BoneName);
    void SetBoneDirection(FName BoneName, FRotator BoneTurn, FVector BoneTrans, FLOAT Alpha, INT Space);
    INT MatchRefBone(FName BoneName);
    FRotator GetBoneRotation(INT BoneIdx, INT Space);
    FCoords GetBoneCoords(INT BoneIdx, INT Space);
    void SetBoneLocation(FName BoneName, FVector BoneTrans, FLOAT Alpha, FLOAT BlendTime, INT Space);
    void SetBoneRotation(FName BoneName, FRotator BoneTurn, INT Space, FLOAT Alpha, FLOAT BlendTime,
                         INT bAdditive, INT bExtra);
    // Named after the natives that call them.
    void LockRootTrack(INT Option);
    void EnableChannelNotify(INT Channel, INT Switch);
};

#endif // CAMPAIGN_MESH_CLASSES_H
