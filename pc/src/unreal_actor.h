// unreal_actor.h -- AActor
#ifndef UNREAL_ACTOR_H
#define UNREAL_ACTOR_H

#include "unreal_containers.h"
#include "unreal_object.h"

#ifdef SCCT_VERSUS
#include "versus_ltcg.h"

// Engine.Actor: 0x2f8 bytes, 78 virtual functions
class AActor : public UObject {
public:
    virtual ~AActor();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
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
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void VirtualSlot63();
    virtual void VirtualSlot64();
    virtual void VirtualSlot65();
    virtual void VirtualSlot66();
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void VirtualSlot73();
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();

    BYTE                  unk_28[0xe4 - 0x28];
    DWORD                 unk_e4;       // observed 32-bit scalar access; meaning unknown
    BYTE                  unk_e8[0x104 - 0xe8];
    void                 *unk_104;
    BYTE                  unk_108[0x138 - 0x108];
    TArrayLtcg<UnkType_8> unk_138;
    BYTE                  unk_144[0x80];
    TArray<UnkType_4>     unk_1c4;
    BYTE                  unk_1d0[0x4];
    void                 *unk_1d4;      // observed pointer access; pointee unknown
    BYTE                  unk_1d8[0x4];
    TArrayLtcg<UnkType_4> unk_1dc;
    TArray<UnkType_4>     unk_1e8;
    BYTE                  unk_1f4[0x10];
    TArrayLtcg<UnkType_4> unk_204;
    TArrayLtcg<UnkType_4> unk_210;
    TArrayLtcg<UnkType_4> unk_21c;
    BYTE                  unk_228[0x18];
    TArrayLtcg<UnkType_4> unk_240;
    BYTE                  unk_24c[0x10];
    TArrayLtcg<UnkType_4> unk_25c;
    BYTE                  unk_268[0x76];
    BYTE                  unk_2de;
    BYTE                  unk_2df[0x11];
    DWORD                 unk_2f0_0 : 12;
    DWORD                 bCollideActors : 1;
    DWORD                 unk_2f0_b13 : 1;
    DWORD                 bBlockActors : 1;
    DWORD                 bBlockPlayers : 1;
    DWORD                 unk_2f0_16 : 16;
    BYTE                  unk_2f4[4];

    void SetCollision(UBOOL NewCollideActors, UBOOL NewBlockActors, UBOOL NewBlockPlayers);
    void SetDrawType(INT NewDrawType);
    DECLARE_NATIVE(execCheckSignature)
};

#else // Campaign
#include "unreal_math.h"

// Native indices of the latent poll functions that a latent native leaves in
// FStateFrame::LatentAction, from the Campaign native registration.
enum EPollSlowFuncs {
    EPOLL_FinishInterpolation = 302,    // AActor::execPollFinishInterpolation
    EPOLL_Sleep               = 384,    // AActor::execPollSleep
    EPOLL_FinishAnim          = 385,    // AActor::execPollFinishAnim
    EPOLL_FinishSequence      = 386,    // AActor::execPollFinishSequence
    EPOLL_509                 = 509,    // registered without a name; set by FinishRotation
    EPOLL_528                 = 528     // registered without a name; set by WaitForLanding
};

// Engine.Actor: 0x2b4 bytes, 166 virtual functions
class AActor : public UObject {
public:
    virtual ~AActor();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void PlayOwnedSound(class USound *Sound, BYTE Slot);
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
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
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void VirtualSlot63();
    virtual void VirtualSlot64();
    virtual void SetBase(AActor *NewBase, FVector NewFloor, INT bNotifyActor);
    virtual void VirtualSlot66();
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
    virtual void VirtualSlot71();
    virtual UBOOL AnimationFinished(INT Channel);
    virtual void VirtualSlot73();
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual void VirtualSlot80();
    virtual void VirtualSlot81();
    virtual void setPhysics(BYTE NewPhysics, AActor *NewFloor, FVector NewFloorV, INT bExtra);
    virtual void VirtualSlot83();
    virtual void VirtualSlot84();
    virtual void VirtualSlot85();
    virtual void VirtualSlot86();
    virtual void VirtualSlot87();
    virtual void VirtualSlot88();
    virtual void VirtualSlot89();
    virtual void VirtualSlot90();
    virtual void VirtualSlot91();
    virtual void VirtualSlot92();
    virtual void VirtualSlot93();
    virtual void VirtualSlot94();
    virtual void VirtualSlot95();
    virtual void VirtualSlot96();
    virtual void VirtualSlot97();
    virtual void VirtualSlot98();
    virtual void VirtualSlot99();
    virtual void VirtualSlot100();
    virtual void VirtualSlot101();
    virtual void VirtualSlot102();
    virtual void PlayAnim(INT Channel, FName Sequence, FLOAT Rate, FLOAT TweenTime, INT bLoop,
                          INT A, INT B, INT C);
    virtual void AnimBlendToAlpha(INT Channel, FLOAT DestAlpha, FLOAT TweenTime);
    virtual void VirtualSlot105();
    virtual void VirtualSlot106();
    virtual void VirtualSlot107();
    virtual void VirtualSlot108();
    virtual void VirtualSlot109();
    virtual void VirtualSlot110();
    virtual void VirtualSlot111();
    virtual void VirtualSlot112();
    virtual void VirtualSlot113();
    virtual void VirtualSlot114();
    virtual void VirtualSlot115();
    virtual void VirtualSlot116();
    virtual void VirtualSlot117();
    virtual void VirtualSlot118();
    virtual void VirtualSlot119();
    virtual void VirtualSlot120();
    virtual void VirtualSlot121();
    virtual void VirtualSlot122();
    virtual void VirtualSlot123();
    virtual void VirtualSlot124();
    virtual void VirtualSlot125();
    virtual void VirtualSlot126();
    virtual void VirtualSlot127();
    virtual void VirtualSlot128();
    virtual void VirtualSlot129();
    virtual void VirtualSlot130();
    virtual void VirtualSlot131();
    virtual void MakeNoise(FLOAT Loudness, INT NoiseType, const FVector &NoiseLocation, INT Option4,
                           const FVector &Option5, INT Option6, UBOOL bOption7);
    virtual void VirtualSlot133();
    virtual void StopAllSoundsActor(INT Flags, FLOAT FadeTime, INT Slot);
    virtual void VirtualSlot135();
    virtual void VirtualSlot136();
    virtual void VirtualSlot137();
    virtual void VirtualSlot138();
    virtual void VirtualSlot139();
    virtual void VirtualSlot140();
    virtual void VirtualSlot141();
    virtual void VirtualSlot142();
    virtual void VirtualSlot143();
    virtual void VirtualSlot144();
    virtual void VirtualSlot145();
    virtual void VirtualSlot146();
    virtual void VirtualSlot147();
    virtual void VirtualSlot148();
    virtual void VirtualSlot149();
    virtual void VirtualSlot150();
    virtual void VirtualSlot151();
    virtual void VirtualSlot152();
    virtual void VirtualSlot153();
    virtual void VirtualSlot154();
    virtual void VirtualSlot155();
    virtual void VirtualSlot156();
    virtual void VirtualSlot157();
    virtual void VirtualSlot158();
    virtual void VirtualSlot159();
    virtual void VirtualSlot160();
    virtual void VirtualSlot161();
    virtual void VirtualSlot162();
    virtual void VirtualSlot163();
    virtual void VirtualSlot164();
    virtual void VirtualSlot165();

    DWORD                unk_28;        // flag word: PlayActorSound tests 4
    // Engine.u's Actor BoolProperty chain places bIsPawn twenty flags before bInterpolating
    // and bJustTeleported immediately after it. PlaySound, the interpolation poll and
    // MoveSmooth access those three bits.
    BITFIELD             unk_2c_0 : 4;
    BITFIELD             bIsPawn : 1;
    BITFIELD             unk_2c_5 : 19;
    BITFIELD             bInterpolating : 1;
    BITFIELD             bJustTeleported : 1;
    BITFIELD             unk_2c_26 : 6;
    BITFIELD             unk_30_0 : 25;
    BITFIELD             bCollideActors : 1;    // the actor is in the level's collision hash
    BITFIELD             unk_30_26 : 6;
    BYTE                 unk_34[0x18];
    BYTE                 unk_4c;        // movement mode: WaitForLanding waits while it is 2
    BYTE                 unk_4d[0x3];
    FLOAT                unk_50;        // a level time: execPlayerCanSeeMe tests it is under a second old
    FName                Tag;
    BYTE                 unk_58[0xc];
    class UMeshInstance *MeshInstance;
    BYTE                 unk_68[0x4];
    AActor              *Owner;
    BYTE                 unk_70[0x8];
    class ALevelInfo    *Level;         // the level's info actor (name invented)
    class ULevel        *XLevel;        // the level the actor is in
    BYTE                 unk_80[0x4];
    class APawn         *Instigator;
    BYTE                 unk_88[0x3c];
    FLOAT                LatentFloat;   // parameter of the latent function in progress
    BYTE                 unk_c8[0x20];
    FVector              Location;
    FRotator             Rotation;
    BYTE                 unk_100[0x84];
    class UMesh         *Mesh;
    BYTE                 unk_188[0x10];
    FVector              DrawScale3D;
    BYTE                 unk_1a4[0x110];

    UBOOL SetRotation(const FRotator &NewRotation);
    UBOOL SetRelativeRotation(const FRotator &NewRotation);
    UBOOL SetRelativeLocation(const FVector &NewLocation);
    UBOOL SetLocation(const FVector &NewLocation, UBOOL bNoCheck);
    void SetDrawScale3D(FVector NewScale3D);
    void ClearRenderData();
    UBOOL MoveSmooth(FVector Delta);
    UBOOL PlayActorSound(class USound *Sound, BYTE Slot, FLOAT Volume, INT Option4, FLOAT Option5,
                         FLOAT Option6);
    AActor *TraceBoneCheck(FName &HitBone, FVector &HitLocation, FVector &HitNormal, const FVector &TraceEnd,
                           const FVector &TraceStart, class UMaterial **Material, INT TraceFlags,
                           INT bOption8);
    AActor *TraceCheck(FVector &HitLocation, FVector &HitNormal, const FVector &TraceEnd,
                       const FVector &TraceStart, const FVector &Extent, class UMaterial **Material,
                       INT TraceFlags, INT bOption8, class UPrimitive **Primitive, INT Mode);
    AActor *TraceMode(INT Mode, FVector &HitLocation, FVector &HitNormal, const FVector &TraceEnd,
                      const FVector &TraceStart, const FVector &Extent, class UMaterial **Material,
                      INT TraceFlags, INT bOption8, class UPrimitive **Primitive);
    UBOOL FastTraceCheck(const FVector &TraceEnd, const FVector &TraceStart, const FVector &Extent,
                         INT TraceFlags, UBOOL bOption);
    UBOOL AttachToBone(AActor *Attachment, const FName &BoneName, INT Slot, INT Option4, INT Option5,
                       INT Option6, INT Option7, FVector RelLocation, FRotator RelRotation);
    class ULevel *GetLevel() const { return XLevel; }
    // Named after execSetDrawType, its caller. The parameter is passed as a full word (an
    // enumeration, most likely), although the script passes a byte.
    void SetDrawType(INT NewDrawType);
    // Named after the natives that call them.
    void SetIKFade(FLOAT Option1, FLOAT Option2);
    void SetCollisionSize(FLOAT NewRadius, FLOAT NewHeight, INT Option3);

    DECLARE_NATIVE(execPollFinishAnim)
    DECLARE_NATIVE(execSetRotation)
    DECLARE_NATIVE(execSetRelativeLocation)
    DECLARE_NATIVE(execSetLocation)
    DECLARE_NATIVE(execSetDrawScale3D)
    DECLARE_NATIVE(execMoveSmooth)
    DECLARE_NATIVE(execSetBase)
    DECLARE_NATIVE(execError)
    DECLARE_NATIVE(execMultiply_ColorFloat)
    DECLARE_NATIVE(execMultiply_FloatColor)
    DECLARE_NATIVE(execInterpolateRotatorValue)
    DECLARE_NATIVE(execStopSound)
    DECLARE_NATIVE(execChangeSoundVolume)
    DECLARE_NATIVE(execScreenLog)
    DECLARE_NATIVE(execConsoleCommand)
    DECLARE_NATIVE(execSetRelativeRotation)
    DECLARE_NATIVE(execStopAllSoundsActor)
    DECLARE_NATIVE(execInterpolateRotator)
    DECLARE_NATIVE(execSetPhysics)
    DECLARE_NATIVE(execTweenAnim)
    DECLARE_NATIVE(execPlayAnim)
    DECLARE_NATIVE(execLoopAnim)
    DECLARE_NATIVE(execSetBoneScale)
    DECLARE_NATIVE(execSetBoneDirection)
    DECLARE_NATIVE(execGetBoneRotation)
    DECLARE_NATIVE(execGetBoneCoords)
    DECLARE_NATIVE(execSetBoneLocation)
    DECLARE_NATIVE(execSetBoneRotation)
    DECLARE_NATIVE(execAddSoundRequest)
    DECLARE_NATIVE(execMakeNoise)
    DECLARE_NATIVE(execMove)
    DECLARE_NATIVE(execFastTrace)
    DECLARE_NATIVE(execDistancePointToLine)
    DECLARE_NATIVE(execAttachToBone)
    DECLARE_NATIVE(execGetAnimParams)
    DECLARE_NATIVE(execSpawn)
    DECLARE_NATIVE(execPlaySound)
    DECLARE_NATIVE(execTraceBone)
    DECLARE_NATIVE(execTrace)
    DECLARE_NATIVE(execPollFinishSequence)
    DECLARE_NATIVE(execPollSleep)
    DECLARE_NATIVE(execFinishInterpolation)
    DECLARE_NATIVE(execPollFinishInterpolation)
    DECLARE_NATIVE(execDestroy)
    DECLARE_NATIVE(execStopAllSounds)
    DECLARE_NATIVE(execVerifyOcclusion)
    DECLARE_NATIVE(execFlushRequests)
    DECLARE_NATIVE(execAddMaskingFadeOut)
    DECLARE_NATIVE(execNotifyAudioEndConversation)
    DECLARE_NATIVE(execIsGameOver)
    DECLARE_NATIVE(execIsAConversationPlaying)
    DECLARE_NATIVE(execStopAllSoundsType)
    DECLARE_NATIVE(execStartFadeOut)
    DECLARE_NATIVE(execSetLaserMicSession)
    DECLARE_NATIVE(execSetReverbEffect)
    DECLARE_NATIVE(execResumeSound)
    DECLARE_NATIVE(execPauseSound)
    DECLARE_NATIVE(execGetVolumeLineValue)
    DECLARE_NATIVE(execSleep)
    DECLARE_NATIVE(execFinishAnim)
    DECLARE_NATIVE(execSetDrawType)
    DECLARE_NATIVE(execStopAllVoicesActor)
    DECLARE_NATIVE(execIsPlayingAnyActor)
    DECLARE_NATIVE(execIsPlaying)
    DECLARE_NATIVE(execGetSoundPosition)
    DECLARE_NATIVE(execSetVolumeLineValue)
    DECLARE_NATIVE(execIsTweening)
    DECLARE_NATIVE(execHasAnim)
    DECLARE_NATIVE(execStopAnimating)
    DECLARE_NATIVE(execGetNotifyChannel)
    DECLARE_NATIVE(execAnimBlendToAlpha)
    DECLARE_NATIVE(execLockRootTrack)
    DECLARE_NATIVE(execEnableChannelNotify)
    DECLARE_NATIVE(execAnimIsInGroup)
    DECLARE_NATIVE(execLinkSkelAnim)
    DECLARE_NATIVE(execSetMesh)
    DECLARE_NATIVE(execGetSoundDuration)
    DECLARE_NATIVE(execPlayerCanSeeMe)
    DECLARE_NATIVE(execSetIKFade)
    DECLARE_NATIVE(execSetCollisionSize)
    DECLARE_NATIVE(execAdd_ColorColor)
    DECLARE_NATIVE(execSubtract_ColorColor)
};

#endif // SCCT_VERSUS

#endif // UNREAL_ACTOR_H
