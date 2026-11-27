// In-memory animation channels and bone controllers shared with the instance archive.
#ifndef VERSUS_MESH_ANIMATION_CHANNELS_H
#define VERSUS_MESH_ANIMATION_CHANNELS_H

#include "versus_build.h"
#include "unreal_math.h"
#if !defined(VERSUS_PAWN_ACTION_EVENTS_H)
#include "unreal_name.h"
#endif

struct FBoneScaler
{
    INT Bone;
    FName BoneName;
    FLOAT ScaleUniform;
    FCoords Coords;
};

struct FBoneControl
{
    INT BoneIndex;
    FName BoneName;
    FRotator Turn;
    FVector Trans;
    INT Space;
    FLOAT RotationAlpha, TranslationAlpha;
    FLOAT RotationFadeIn, TranslationFadeIn;
    FLOAT RotationFadeOut, TranslationFadeOut;
    UBOOL bTranslationFading, bRotationFading;
};

struct MeshAnimChannel
{
    FName unk_00;
    INT MeshAnimIndex;
    FName AnimSequence;
    FLOAT AnimRate, AnimFrame;
    FLOAT LastFrame, TweenRate;
    INT unk_1c;
    FLOAT OrigRate;
    INT unk_24[2];
    UBOOL bAnimFinished, bAnimLoop;
    UBOOL bNotifies;
    FLOAT unk_38;
    INT unk_3c, unk_40;
    UBOOL bAnimBackwards;
    INT unk_48;
    UBOOL bGlobalPoseCurrent;
    FLOAT CurrentAlpha, CurrentInTime, CurrentOutTime;
    INT unk_5c, unk_60;
    FLOAT TweenProgress;
    INT StartBoneIndex;
    FLOAT CachedAnimFrame;
    FName CachedSequence;
    BYTE bMirror;
    BYTE unk_75[3];
    FLOAT BlendAlpha, BlendInTime, BlendOutTime;
    FName StartBone;
    UBOOL bGlobalPose, bBlendSet;
};

#endif
