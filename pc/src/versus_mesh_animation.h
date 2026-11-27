// Skeletal animation records returned by UMeshAnimation to GetFrame.
#ifndef VERSUS_MESH_ANIMATION_H
#define VERSUS_MESH_ANIMATION_H

#include "versus_build.h"
#include "unreal_object.h"
#include "unreal_math.h"
#include "versus_static_mesh_arrays.h"

class USkeletalMeshInstance;
class UAnimNotify;

struct FNamedBone
{
    FName Name;
    DWORD Flags;
    INT ParentIndex;
};

struct FMeshAnimNotify
{
    FLOAT Time;
    FName Function;
    UAnimNotify *NotifyObject;
};

struct FMeshAnimSeq
{
    FName Name;
    TArray<FName> Groups;
    INT StartFrame;
    INT NumFrames;
    FLOAT Rate;
    TArray<FMeshAnimNotify> Notifys;
    INT unk_28;
};

// MotionChunk's key readers at 0xb3760
// and 0xb3800 unpack four or three signed 16-bit components per key.
struct FCompressedQuatKey { short X, Y, Z, W; };
struct FCompressedVectorKey { short X, Y, Z; };

struct AnalogTrack
{
    DWORD Flags;
    TArray<FCompressedQuatKey> KeyQuat;
    TArray<FCompressedVectorKey> KeyPos;
    TArray<short> KeyTime;
};

struct MotionChunk
{
    virtual ~MotionChunk();
    virtual void SampleTrack(INT TrackIndex, FLOAT Time, FQuat &Orientation, FVector &Position,
                             USkeletalMeshInstance *Instance, INT SampleFlags,
                             UBOOL bBackwards, UBOOL bLoop);
    virtual void VirtualSlot2();
    virtual INT GetTrackCount();
    virtual void GetTrackOrientation(INT TrackIndex, INT KeyIndex, FQuat &Orientation);
    virtual void GetTrackPosition(INT TrackIndex, INT KeyIndex, FVector &Position);

    FVector RootSpeed3D;
    FLOAT TrackTime;
    INT StartBone;
    DWORD Flags;
    TArray<INT> BoneIndices;
    TArray<AnalogTrack> AnimTracks;
    AnalogTrack RootTrack;
    TArray<AnalogTrack> unk_5c;
};

class UMeshAnimation : public UObject
{
public:
    virtual FMeshAnimSeq *FindAnimSeq(FName Name);
    virtual void VirtualSlot23();
    virtual MotionChunk *FindMotionChunk(FName Name);

    INT InternalVersion;
    TArray<FNamedBone> RefBones;
    TArray<MotionChunk> Moves;
    TArray<FMeshAnimSeq> AnimSeqs;
};

#endif
