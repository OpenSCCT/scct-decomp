// Archive the animation channels and bone controllers of a skeletal mesh instance.
#include "versus_build.h"
#include "unreal_name.h"
#include "unreal_math.h"
#include "versus_static_mesh_arrays.h"
#include "versus_lazy_archive.h"
#include "versus_compact_index.inl"

#include "versus_mesh_animation_channels.h"

// The object vtable prefix used by this archive includes Serialize at slot 10.
class FUnknown
{
public:
    virtual DWORD __stdcall QueryInterface(const struct FGuid &, void **);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown
{
public:
    virtual ~UObject();
    virtual void ProcessEvent(class UFunction *, void *, void *);
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void Serialize(FArchive &Ar);

    INT Index;
    BYTE unk_08[4];
    class FStateFrame *StateFrame;
    BYTE unk_10[12];
    DWORD ObjectFlags;
    FName Name;
    class UClass *Class;
};

struct FBox
{
    FVector Min, Max;
};

struct FSphere
{
    FVector Center;
    FLOAT Radius;
};

class UPrimitive : public UObject
{
public:
    virtual void Serialize(FArchive &Ar);
    FBox BoundingBox;
    FSphere BoundingSphere;
};

class UMeshInstance : public UPrimitive {};

#pragma pack(push, 4)
class ULodMeshInstance : public UMeshInstance
{
public:
    BYTE unk_50[0x5c - 0x50];
    unsigned __int64 LastFrame;
    FLOAT LastAnimFrame;
    BYTE unk_68[0x74 - 0x68];
    INT unk_74;
};

struct MeshAnimLinkup;
class USkeletalMeshInstance : public ULodMeshInstance
{
public:
    virtual void Serialize(FArchive &Ar);

    BYTE unk_78[0xa8 - 0x78];
    TArray<MeshAnimLinkup> AnimLinkups;
    TArray<FCoords> CachedCoords;
    FCoords MeshCoords;
    INT unk_f0, unk_f4;
    BYTE unk_f8[8];
    TArray<MeshAnimChannel> Blends;
    TArray<FBoneScaler> Scalers;
    TArray<FBoneControl> BoneAdjustments, BoneDirections;
    BYTE unk_130[8];
    TArray<FQuat> CachedOrientations;
    TArray<FVector> CachedPositions;
    TArray<DWORD> unk_150;
};
#pragma pack(pop)

typedef char UObjectSize[sizeof(UObject) == 0x28 ? 1 : -1];
typedef char UPrimitiveSize[sizeof(UPrimitive) == 0x50 ? 1 : -1];
typedef char UMeshInstanceSize[sizeof(UMeshInstance) == 0x50 ? 1 : -1];
typedef char ULodMeshInstanceSize[sizeof(ULodMeshInstance) == 0x78 ? 1 : -1];
typedef char MeshAnimChannelSize[sizeof(MeshAnimChannel) == 0x90 ? 1 : -1];
typedef char FBoneControlSize[sizeof(FBoneControl) == 0x44 ? 1 : -1];

FArchive &operator<<(FArchive &, TArray<FBoneScaler> &);
FArchive &operator<<(FArchive &, TArray<FQuat> &);
FArchive &operator<<(FArchive &, TArray<FVector> &);
FArchive &operator<<(FArchive &, TArray<DWORD> &);
FArchive &operator<<(FArchive &, TArray<FCoords> &);

inline FArchive &operator<<(FArchive &Ar, DWORD &Value)
{
    Ar.Serialize(&Value, sizeof(Value));
    return Ar;
}

inline FArchive &operator<<(FArchive &Ar, FVector &V)
{
    return Ar << V.X << V.Y << V.Z;
}

inline FArchive &operator<<(FArchive &Ar, FRotator &R)
{
    return Ar << R.Pitch << R.Yaw << R.Roll;
}

FArchive &operator<<(FArchive &Ar, FBoneControl &Bone)
{
    return Ar << Bone.BoneIndex << Bone.BoneName << Bone.Turn << Bone.Trans
              << Bone.RotationAlpha << Bone.TranslationAlpha << Bone.RotationFadeIn << Bone.TranslationFadeIn
              << Bone.RotationFadeOut << Bone.TranslationFadeOut << Bone.bTranslationFading << Bone.bRotationFading;
}

FArchive &operator<<(FArchive &Ar, MeshAnimChannel &Channel)
{
    if (!Ar.IsPersistent()) {
        Ar << Channel.unk_00;
        Ar << Channel.MeshAnimIndex;
        Ar << Channel.AnimSequence;
        Ar << Channel.AnimRate;
        Ar << Channel.AnimFrame;
        Ar << Channel.LastFrame;
        Ar << Channel.TweenRate;
        Ar << Channel.unk_1c[0];
        Ar << Channel.unk_1c[1];
        Ar << Channel.unk_1c[2];
        Ar << Channel.unk_1c[3];
        Ar << Channel.bAnimFinished;
        Ar << Channel.bAnimLoop;
        Ar << Channel.unk_34;
        Ar << Channel.unk_38;
        Ar << Channel.unk_3c;
        Ar << Channel.unk_40;
        Ar << Channel.bAnimBackwards;
        Ar << Channel.unk_48;
        Ar << Channel.bGlobalPoseCurrent;
        Ar << Channel.CurrentAlpha;
        Ar << Channel.CurrentInTime;
        Ar << Channel.CurrentOutTime;
        Ar << Channel.unk_60;
        Ar << Channel.unk_5c;
        Ar << Channel.TweenProgress;
        Ar << Channel.StartBoneIndex;
        Ar << Channel.CachedAnimFrame;
        Ar << Channel.CachedSequence;

        // SetBlendParams writes a float at +0x78 and an FName at +0x84.
        // The archive visits +0x78 through its virtual name operator and +0x84 as raw bytes.
        Ar << reinterpret_cast<FName &>(Channel.BlendAlpha);
        Ar << Channel.BlendInTime;
        Ar << Channel.BlendOutTime;
        Ar.Serialize(&Channel.StartBone, sizeof(Channel.StartBone));
        Ar << Channel.bGlobalPose;
        Ar << Channel.bBlendSet;
    }
    return Ar;
}

#include "versus_element_array_archive.inl"

// UObject and its primitive bounds are serialized before transient animation data.
void USkeletalMeshInstance::Serialize(FArchive &Ar)
{
    UPrimitive::Serialize(Ar);
    if (!Ar.IsPersistent()) {
        Ar << Blends;
        Ar << Scalers;
        Ar << BoneAdjustments;
        Ar << unk_f0;
        Ar << unk_f4;
        Ar << CachedOrientations;
        Ar << CachedPositions;
        Ar << unk_150;
        TArray<FVector> OldPositions;
        TArray<DWORD> OldIndices;
        Ar << OldPositions;
        Ar << OldIndices;
        Ar << CachedCoords;
    }
}
