// versus_matchmaking.h -- the online service interface the Versus script natives call
#ifndef VERSUS_MATCHMAKING_H
#define VERSUS_MATCHMAKING_H

#include "versus_build.h"
#include "unreal_containers.h"
#include "unreal_subsystem.h"

// Engine.MatchmakingSubsystem: 0x30 bytes, 203 virtual functions. The class is abstract; the one
// implementation is GameService.GameServiceSubsystem. A method called by a USXBoxLiveRef native
// is named after that native (the method names themselves are not recorded anywhere); the
// other slots are not identified.
class UMatchmakingSubsystem : public USubsystem {
public:
    virtual ~UMatchmakingSubsystem();
    virtual FString GetLobbyName(INT Index);
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
    virtual FString GetUserName(INT Index);
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
    virtual INT MatchQueryGetGameMode(INT A, INT B);
    virtual INT MatchQueryGetMapAmateur(INT A, INT B);
    virtual INT MatchQueryIsLadderGame(INT A, INT B);
    virtual INT MatchQueryGetGameLevel(INT A, INT B);
    virtual void VirtualSlot61();
    virtual INT MatchQueryGetGameState(INT A, INT B);
    virtual INT MatchQueryGetTimeRemaining(INT A, INT B);
    virtual INT MatchQueryIsSpyAvailable(INT A, INT B);
    virtual INT MatchQueryIsSentryAvailable(INT A, INT B);
    virtual INT MatchQueryGetNumSlotsUsed(INT A, INT B);
    virtual INT MatchQueryGetNumSlotsFree(INT A, INT B);
    virtual INT MatchQueryGetPrivateSlotsFree(INT A, INT B);
    virtual INT MatchQueryGetPublicSlotsFree(INT A, INT B);
    virtual INT MatchQueryGetPrivateSlotsUsed(INT A, INT B);
    virtual INT MatchQueryGetPublicSlotsUsed(INT A, INT B);
    virtual INT MatchQueryGetMaxPlayers(INT A, INT B);
    virtual INT MatchQueryGetNbrPlayers(INT A, INT B);
    virtual INT MatchQueryGetbGamesInARowPlaying(INT A, INT B);
    virtual INT MatchQueryIsPunkBusterEnabled(INT A, INT B);
    virtual INT MatchQueryIsLocked(INT A, INT B);
    virtual FString MatchQueryGetCompatibilityVersion(INT Index);
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual void VirtualSlot80();
    virtual void VirtualSlot81();
    virtual void VirtualSlot82();
    virtual void VirtualSlot83();
    virtual void VirtualSlot84();
    virtual void VirtualSlot85();
    virtual void VirtualSlot86();
    virtual void VirtualSlot87();
    virtual void VirtualSlot88();
    virtual void VirtualSlot89();
    virtual void VirtualSlot90();
    virtual FString GetResultPlayerName(INT Index);
    virtual void VirtualSlot92();
    virtual void VirtualSlot93();
    virtual void VirtualSlot94();
    virtual void MatchSetServerName(FString Value);
    virtual void MatchSetServerPassword(FString Value);
    virtual void VirtualSlot97();
    virtual void MatchSetMapName(FString Value);
    virtual void MatchSetMapPublicName(FString Value);
    virtual void VirtualSlot100();
    virtual void VirtualSlot101();
    virtual void VirtualSlot102();
    virtual void VirtualSlot103();
    virtual void VirtualSlot104();
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
    virtual INT MatchQueryIsTutoratMode(INT A, INT B);
    virtual void VirtualSlot119();
    virtual INT MatchQueryIsAlternateMode(INT A, INT B);
    virtual void VirtualSlot121();
    virtual INT MatchQueryIsDedicatedServerMode(INT A, INT B);
    virtual void VirtualSlot123();
    virtual void VirtualSlot124();
    virtual void VirtualSlot125();
    virtual void VirtualSlot126();
    virtual FString BlackListGetName(INT Index);
    virtual void BLIgnorePlayer(FString Value);
    virtual void BLUnIgnorePlayer(FString Value);
    virtual void VirtualSlot130();
    virtual void VirtualSlot131();
    virtual void VirtualSlot132();
    virtual void VirtualSlot133();
    virtual void VirtualSlot134();
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
    virtual FString GetInvitePassword(INT Index);
    virtual void VirtualSlot156();
    virtual void AddFriend(FString Value);
    virtual void VirtualSlot158();
    virtual FString GetFriendName(INT Index);
    virtual void VirtualSlot160();
    virtual void VirtualSlot161();
    virtual void VirtualSlot162();
    virtual void VirtualSlot163();
    virtual void VirtualSlot164();
    virtual void VirtualSlot165();
    virtual void VirtualSlot166();
    virtual void VirtualSlot167();
    virtual FString GetFriendGameTitle(INT Index);
    virtual void VirtualSlot169();
    virtual void VirtualSlot170();
    virtual void VirtualSlot171();
    virtual void VirtualSlot172();
    virtual FString GetInviteSenderName(INT Index);
    virtual void VirtualSlot174();
    virtual FString RecentPlayerGetName(INT Index);
    virtual void VirtualSlot176();
    virtual void VirtualSlot177();
    virtual void VirtualSlot178();
    virtual void DownloadContent(FString Value);
    virtual INT LadderDyn_GetPlayerScore(INT A, INT B);
    virtual INT LadderDyn_GetPlayerLevel(INT A, INT B);
    virtual void VirtualSlot182();
    virtual void VirtualSlot183();
    virtual void VirtualSlot184();
    virtual void VirtualSlot185();
    virtual void VirtualSlot186();
    virtual void VirtualSlot187();
    virtual void VirtualSlot188();
    virtual void VirtualSlot189();
    virtual void ActivateCdKey(FString Value);
    virtual void VirtualSlot191();
    virtual void VirtualSlot192();
    virtual void VirtualSlot193();
    virtual void VirtualSlot194();
    virtual void VirtualSlot195();
    virtual void VirtualSlot196();
    virtual void VirtualSlot197();
    virtual void VirtualSlot198();
    virtual void VirtualSlot199();
    virtual void VirtualSlot200();
    virtual void VirtualSlot201();
    virtual void VirtualSlot202();

    BYTE unk_28[0x8];
};

// The object the natives reach the service through: only its pointer to the subsystem is known.
struct UnkType_3923C0 {
    BYTE                   unk_0[0x40];
    UMatchmakingSubsystem *unk_40;
};

extern UnkType_3923C0 *unk_3923c0;

#endif // VERSUS_MATCHMAKING_H
