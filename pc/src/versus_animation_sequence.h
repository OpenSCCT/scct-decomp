// Versus legacy mesh animation sequences, shared by vertex and skeletal animation.
#ifndef VERSUS_ANIMATION_SEQUENCE_H
#define VERSUS_ANIMATION_SEQUENCE_H
#include "versus_build.h"
#include "unreal_name.h"
#include "versus_static_mesh_arrays.h"
class UObject;
class UAnimNotify;

struct FMeshAnimNotify
{
    FMeshAnimNotify() : Time(0.f), Function(NAME_None), NotifyObject(0) {}
    FLOAT Time;
    FName Function;
    UAnimNotify *NotifyObject;
};

struct FMeshAnimSeq
{
    FMeshAnimSeq();
    void UpdateOldNotifies(UObject *Outer);
    FName Name;
    TArray<FName> Groups;
    INT StartFrame;
    INT NumFrames;
    FLOAT Rate;
    TArray<FMeshAnimNotify> Notifys;
    INT unk_28;
};

#endif
