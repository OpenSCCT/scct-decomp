#ifndef VERSUS_GAME_REPLICATION_INFO_H
#define VERSUS_GAME_REPLICATION_INFO_H

#if !defined(UNREAL_ACTOR_H) && !defined(VERSUS_PAWN_ACTION_EVENTS_H)
#include "unreal_actor.h"
#endif
class APlayerReplicationInfo;

// Core.Object.EGameMode is serialized as a byte on Engine.GameReplicationInfo.
enum EGameMode {
    GM_Undefined, GM_Extraction, GM_Sabotage, GM_Neutralization,
    GM_DiskHunt, GM_Multi, GM_DeathMatch
};

#include "versus_info.h"

// Engine.ReplicationInfo: 0x2f8 bytes, 78 virtual functions
class AReplicationInfo : public AInfo {
public:
    virtual ~AReplicationInfo();
};

// Engine.GameReplicationInfo: 0x3c0 bytes, 78 virtual functions
class AGameReplicationInfo : public AReplicationInfo {
public:
    virtual ~AGameReplicationInfo();

    FString               unk_2f8;
    FString               unk_304;
    DWORD                 GameFlags;
    INT                   RemainingTime, ElapsedTime, RemainingMinute;
    FLOAT                 SecondCount;
    INT                   TimeLimit;
    BYTE                  unk_328[0x378 - 0x328];
    FString               unk_378;
    FString               unk_384;
    FString               unk_390;
    FString               unk_39c;
    BYTE                  unk_3a8[0x4];
#ifdef VERSUS_LTCG_H
    // The legacy destructor receipt models the private stack-this calling convention.
    TArrayLtcg<UnkType_4> PRIArray;
#else
    TArray<APlayerReplicationInfo *> PRIArray;
#endif
    BYTE                  unk_3b8[4];
    BYTE                  WinningTeam, WinningReason, GameMode;
};

#endif
