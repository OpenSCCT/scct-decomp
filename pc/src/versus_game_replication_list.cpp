#include "versus_build.h"
#include "versus_replication_properties.h"

inline INT *AReplicationInfo::GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel)
{
    if (!bSkipActorPropertyReplication)
        Ptr = AActor::GetOptimizedRepList(Recent, Retire, Ptr, Map, Channel);
    return Ptr;
}

INT *AGameReplicationInfo::GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel)
{
    Ptr = AReplicationInfo::GetOptimizedRepList(Recent, Retire, Ptr, Map, Channel);
    if (Role == ROLE_Authority) {
        DOREP(AGameReplicationInfo, bAvlb_SPY_ThermalVision);
        DOREP(AGameReplicationInfo, bAvlb_SPY_NightVision);
        DOREP(AGameReplicationInfo, bAvlb_SPY_Grab);
        DOREP(AGameReplicationInfo, bAvlb_SPY_Elbow);
        DOREP(AGameReplicationInfo, bAvlb_SPY_LeathalDropTech);
        DOREP(AGameReplicationInfo, bAvlb_MERC_Elbow);
        DOREP(AGameReplicationInfo, bAvlb_MERC_LeathalDropTech);
        DOREP(AGameReplicationInfo, bAvlb_MERC_EMFVision);
        DOREP(AGameReplicationInfo, bAvlb_MERC_MotiontrackingVision);
        DOREP(AGameReplicationInfo, bAvlb_MERC_Torche);
        DOREP(AGameReplicationInfo, bAvlb_MERC_Laser);
        DOREP(AGameReplicationInfo, bAvlb_MERC_Berserk);
        DOREP(AGameReplicationInfo, bAvlb_MERC_Charge);
        DOREP(AGameReplicationInfo, RemainingTime);
        DOREP(AGameReplicationInfo, bStopCountDown);
        DOREP(AGameReplicationInfo, bMatchHasBegun);
        DOREP(AGameReplicationInfo, sessionId);
        DOREP(AGameReplicationInfo, bMatchLaunching);
        DOREP(AGameReplicationInfo, bMatchLaunchingNow);
        DOREP(AGameReplicationInfo, ElapsedTime);
        DOREP(AGameReplicationInfo, GamesInARow);
        DOREPARRAY(AGameReplicationInfo, TotalTeamLives);
        DOREPARRAY(AGameReplicationInfo, Teams);
        DOREP(AGameReplicationInfo, TimesRespawn);
        DOREP(AGameReplicationInfo, ServerName);
        DOREP(AGameReplicationInfo, TimeLimit);
        DOREP(AGameReplicationInfo, GameMode);
        DOREP(AGameReplicationInfo, TeamLivesATT);
        DOREP(AGameReplicationInfo, TeamLivesDEF);
        DOREP(AGameReplicationInfo, NumObjectives);
        DOREP(AGameReplicationInfo, NumDogTagsTaken);
        DOREP(AGameReplicationInfo, ServerOnly);
        DOREP(AGameReplicationInfo, Revenge);
        DOREP(AGameReplicationInfo, WinningReason);
        DOREP(AGameReplicationInfo, WinningTeam);
        DOREP(AGameReplicationInfo, GameWithRanking);
        DOREP(AGameReplicationInfo, NbPublicSlots);
        DOREP(AGameReplicationInfo, ShortName);
        DOREP(AGameReplicationInfo, m_ActualMapName);
        DOREP(AGameReplicationInfo, NumDisks);
        DOREP(AGameReplicationInfo, NumDisksToWin);
        DOREP(AGameReplicationInfo, bAlternateMode);
        DOREP(AGameReplicationInfo, bTutorMode);
        DOREP(AGameReplicationInfo, iGamesInARow);
        DOREP(AGameReplicationInfo, bRandomMap);
        DOREP(AGameReplicationInfo, LastTimeObjectif);
        DOREPARRAY(AGameReplicationInfo, iScoresInARow);
        DOREP(AGameReplicationInfo, allowVoiceChat);
        DOREP(AGameReplicationInfo, voiceChatQuality);
        DOREP(AGameReplicationInfo, allowVoiceChatInLobby);
        if (bNetInitial) {
            DOREP(AGameReplicationInfo, GameName);
            DOREP(AGameReplicationInfo, bTeamGame);
            DOREP(AGameReplicationInfo, AdminName);
            DOREP(AGameReplicationInfo, AdminEmail);
        }
    }
    return Ptr;
}
