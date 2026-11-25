// unreal_pawn.h -- AController, APawn and APlayerController
#ifndef UNREAL_PAWN_H
#define UNREAL_PAWN_H

#include "unreal_actor.h"
#include "unreal_containers.h"

#ifdef SCCT_VERSUS
#include "versus_ltcg.h"

// Engine.Controller: 0x3c4 bytes, 83 virtual functions
class AController : public AActor {
public:
    virtual ~AController();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual void VirtualSlot80();
    virtual void VirtualSlot81();
    virtual void VirtualSlot82();

    BYTE    unk_2f8[0x7c];
    FString unk_374;
    BYTE    unk_380[0x44];
};

// Engine.PlayerController: 0x604 bytes, 84 virtual functions
class APlayerController : public AController {
public:
    virtual ~APlayerController();
    virtual void VirtualSlot83();

    BYTE unk_3c4[0x240];
};

// Engine.Pawn: 0x4b0 bytes, 84 virtual functions
class APawn : public AActor {
public:
    virtual ~APawn();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual void VirtualSlot80();
    virtual void VirtualSlot81();
    virtual void VirtualSlot82();
    virtual void VirtualSlot83();

    BYTE              unk_2f8[0x150];
    TArray<UnkType_4> unk_448;
    FString           unk_454;
    BYTE              unk_460[0x30];
    FString           unk_490;
    BYTE              unk_49c[0x14];
};

#else // Campaign

// Engine.Controller: 0x394 bytes, 176 virtual functions
class AController : public AActor {
public:
    virtual ~AController();
    virtual void VirtualSlot166();
    virtual void VirtualSlot167();
    virtual void VirtualSlot168();
    virtual void VirtualSlot169();
    virtual void VirtualSlot170();
    virtual void VirtualSlot171();
    virtual void VirtualSlot172();
    virtual void VirtualSlot173();
    virtual void VirtualSlot174();
    virtual void VirtualSlot175();

    class APawn *Pawn;          // the pawn this controller drives
    BYTE         unk_2b8[0x1c];
    AController *NextController;    // the next controller in the level's list (name invented)
    BYTE         unk_2d8[0x10];
    FVector      Destination;
    BYTE         unk_2f4[0xa0];

    DECLARE_NATIVE(execPickWallAdjust)
    DECLARE_NATIVE(execpointReachable)
    DECLARE_NATIVE(execFindPathTo)
    DECLARE_NATIVE(execEAdjustJump)
    DECLARE_NATIVE(execAddController)
    DECLARE_NATIVE(execStopWaiting)
    DECLARE_NATIVE(execFinishRotation)
    DECLARE_NATIVE(execWaitForLanding)
    DECLARE_NATIVE(execClearPaths)
    DECLARE_NATIVE(execRemoveController)
    DECLARE_NATIVE(execCanSee)

    UBOOL CanSee(class APawn *Other, INT Option2);  // named after execCanSee, its caller
};

// Engine.Pawn: 0x6d8 bytes, 190 virtual functions
class APawn : public AActor {
public:
    virtual ~APawn();
    virtual void VirtualSlot166();
    virtual void VirtualSlot167();
    virtual void VirtualSlot168();
    virtual void VirtualSlot169();
    virtual void VirtualSlot170();
    virtual void VirtualSlot171();
    virtual void VirtualSlot172();
    virtual void VirtualSlot173();
    virtual void VirtualSlot174();
    virtual void VirtualSlot175();
    virtual void VirtualSlot176();
    virtual void VirtualSlot177();
    virtual void VirtualSlot178();
    virtual void VirtualSlot179();
    virtual void VirtualSlot180();
    virtual void VirtualSlot181();
    virtual void VirtualSlot182();
    virtual void VirtualSlot183();
    virtual void VirtualSlot184();
    virtual void VirtualSlot185();
    virtual void VirtualSlot186();
    virtual void VirtualSlot187();
    virtual void VirtualSlot188();
    virtual void VirtualSlot189();

    BYTE  unk_2b4[0x4];
    DWORD unk_2b8;              // flag word: a bone trace clears 0x100
    BYTE  unk_2bc[0x41c];

    UBOOL PickWallAdjust(FVector WallHitNormal);
    UBOOL pointReachable(FVector aPoint, INT bKnowVisible, INT bExtra);
    FLOAT findPathToward(AActor *Goal, FVector Dest, void *NodeEval, UBOOL bClearPaths, INT bExtra);
    FVector SuggestJumpVelocity(FVector Dest, FLOAT XYSpeed, FLOAT BaseZ);
    void ClearPaths();          // named after AController::execClearPaths, its caller
};

// Engine.PlayerController: 0x494 bytes, 186 virtual functions
class APlayerController : public AController {
public:
    virtual ~APlayerController();
    virtual void VirtualSlot176();
    virtual void VirtualSlot177();
    virtual void VirtualSlot178();
    virtual void VirtualSlot179();
    virtual void VirtualSlot180();
    virtual void VirtualSlot181();
    virtual void VirtualSlot182();
    virtual void VirtualSlot183();
    virtual void VirtualSlot184();
    virtual void VirtualSlot185();

    class UPlayer *Player;      // the viewport or connection that controls this actor
    BYTE           unk_398[0x9c];
    AActor        *ViewTarget;  // the actor the view follows (name invented)
    BYTE           unk_438[0x5c];

    DECLARE_NATIVE(execCopyToClipboard)
    DECLARE_NATIVE(execSetViewTarget)
    DECLARE_NATIVE(execResetKeyboard)
    DECLARE_NATIVE(execGetEntryLevel)
};

#endif // SCCT_VERSUS

#endif // UNREAL_PAWN_H
