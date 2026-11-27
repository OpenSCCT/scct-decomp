#ifndef VERSUS_GAME_REPLICATION_INFO_H
#define VERSUS_GAME_REPLICATION_INFO_H

#if !defined(UNREAL_ACTOR_H) && !defined(VERSUS_PAWN_ACTION_EVENTS_H)
#include "unreal_actor.h"
#endif
class APlayerReplicationInfo;
struct FPropertyRetirement;
class UPackageMap;
class UActorChannel;

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
    virtual INT *GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr,
                                      UPackageMap *Map, UActorChannel *Channel);
};

// Engine.TeamInfo: 0x324 bytes, 78 virtual functions
class ATeamInfo : public AReplicationInfo {
public:
    virtual ~ATeamInfo();

    FString unk_2f8;
    BYTE    unk_304[0x20];
};

// Engine.GameReplicationInfo: 0x3c0 bytes, 78 virtual functions
class AGameReplicationInfo : public AReplicationInfo {
public:
    virtual ~AGameReplicationInfo();
    virtual INT *GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr,
                                      UPackageMap *Map, UActorChannel *Channel);
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }

    FString               GameName;
    FString               m_ActualMapName;
    BITFIELD              bTeamGame : 1;
    BITFIELD              bStopCountDown : 1;
    BITFIELD              bMatchHasBegun : 1;
    BITFIELD              bMatchLaunching : 1;
    BITFIELD              bMatchLaunchingNow : 1;
    BITFIELD              bTeamSymbolsUpdated : 1;
    BITFIELD              ServerOnly : 1;
    BITFIELD              Revenge : 1;
    BITFIELD              GameWithRanking : 1;
    BITFIELD              allowVoiceChat : 1;
    BITFIELD              allowVoiceChatInLobby : 1;
    BITFIELD              bAlternateMode : 1;
    BITFIELD              bTutorMode : 1;
    BITFIELD              bRandomMap : 1;
    INT                   RemainingTime, ElapsedTime, RemainingMinute;
    FLOAT                 SecondCount;
    INT                   TimeLimit;
    INT                   TotalTeamLives[2], TimesRespawn, TeamLivesATT, TeamLivesDEF;
    INT                   NumObjectives, NumDogTagsTaken, NbPublicSlots, iGamesInARow;
    INT                   iScoresInARow[2], NumDisks, NumDisksToWin, NumDisksMax;
    INT                   sessionId, GamesInARow, LastTimeObjectif;
    BYTE                  voiceChatQuality;
    class ATeamInfo      *Teams[2];
    FString               ServerName;
    FString               ShortName;
    FString               AdminName;
    FString               AdminEmail;
    INT                   ServerRegion;
#ifdef VERSUS_LTCG_H
    // The legacy destructor receipt models the private stack-this calling convention.
    TArrayLtcg<UnkType_4> PRIArray;
#else
    TArray<APlayerReplicationInfo *> PRIArray;
#endif
    BITFIELD              bAvlb_SPY_ThermalVision : 1;
    BITFIELD              bAvlb_SPY_NightVision : 1;
    BITFIELD              bAvlb_SPY_Grab : 1;
    BITFIELD              bAvlb_SPY_Elbow : 1;
    BITFIELD              bAvlb_SPY_LeathalDropTech : 1;
    BITFIELD              bAvlb_MERC_Elbow : 1;
    BITFIELD              bAvlb_MERC_LeathalDropTech : 1;
    BITFIELD              bAvlb_MERC_EMFVision : 1;
    BITFIELD              bAvlb_MERC_MotiontrackingVision : 1;
    BITFIELD              bAvlb_MERC_Torche : 1;
    BITFIELD              bAvlb_MERC_Laser : 1;
    BITFIELD              bAvlb_MERC_Berserk : 1;
    BITFIELD              bAvlb_MERC_Charge : 1;
    BYTE                  WinningTeam, WinningReason, GameMode;
};

#endif
