// versus_live_service_natives.cpp -- USXBoxLiveRef natives that forward to the online service
//
// Each native reads its parameters and calls one method of the matchmaking subsystem.
#include "versus_build.h"
#include "unreal_containers.h"
#include "unreal_script.h"
#include "versus_matchmaking.h"
#include "versus_sbase_classes.h"

// USXBoxLiveRef::execGetUserName
void USXBoxLiveRef::execGetUserName(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = unk_3923c0->unk_40->GetUserName(Index);
}

// USXBoxLiveRef::execGetLobbyName
void USXBoxLiveRef::execGetLobbyName(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = unk_3923c0->unk_40->GetLobbyName(Index);
}

// USXBoxLiveRef::execMatchQueryGetMapAmateur
void USXBoxLiveRef::execMatchQueryGetMapAmateur(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetMapAmateur(A, B);
}

// USXBoxLiveRef::execMatchQueryGetGameMode
void USXBoxLiveRef::execMatchQueryGetGameMode(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetGameMode(A, B);
}

// USXBoxLiveRef::execMatchQueryIsLadderGame
void USXBoxLiveRef::execMatchQueryIsLadderGame(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryIsLadderGame(A, B);
}

// USXBoxLiveRef::execMatchQueryGetGameLevel
void USXBoxLiveRef::execMatchQueryGetGameLevel(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetGameLevel(A, B);
}

// USXBoxLiveRef::execMatchQueryGetGameState
void USXBoxLiveRef::execMatchQueryGetGameState(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetGameState(A, B);
}

// USXBoxLiveRef::execMatchQueryGetTimeRemaining
void USXBoxLiveRef::execMatchQueryGetTimeRemaining(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetTimeRemaining(A, B);
}

// USXBoxLiveRef::execMatchQueryIsSpyAvailable
void USXBoxLiveRef::execMatchQueryIsSpyAvailable(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryIsSpyAvailable(A, B);
}

// USXBoxLiveRef::execMatchQueryIsSentryAvailable
void USXBoxLiveRef::execMatchQueryIsSentryAvailable(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryIsSentryAvailable(A, B);
}

// USXBoxLiveRef::execMatchQueryGetNumSlotsUsed
void USXBoxLiveRef::execMatchQueryGetNumSlotsUsed(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetNumSlotsUsed(A, B);
}

// USXBoxLiveRef::execMatchQueryGetMaxPlayers
void USXBoxLiveRef::execMatchQueryGetMaxPlayers(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetMaxPlayers(A, B);
}

// USXBoxLiveRef::execMatchQueryGetNbrPlayers
void USXBoxLiveRef::execMatchQueryGetNbrPlayers(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetNbrPlayers(A, B);
}

// USXBoxLiveRef::execMatchQueryGetbGamesInARowPlaying
void USXBoxLiveRef::execMatchQueryGetbGamesInARowPlaying(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetbGamesInARowPlaying(A, B);
}

// USXBoxLiveRef::execMatchQueryGetNumSlotsFree
void USXBoxLiveRef::execMatchQueryGetNumSlotsFree(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetNumSlotsFree(A, B);
}

// USXBoxLiveRef::execMatchQueryGetPrivateSlotsFree
void USXBoxLiveRef::execMatchQueryGetPrivateSlotsFree(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetPrivateSlotsFree(A, B);
}

// USXBoxLiveRef::execMatchQueryGetPublicSlotsFree
void USXBoxLiveRef::execMatchQueryGetPublicSlotsFree(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetPublicSlotsFree(A, B);
}

// USXBoxLiveRef::execMatchQueryGetPrivateSlotsUsed
void USXBoxLiveRef::execMatchQueryGetPrivateSlotsUsed(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetPrivateSlotsUsed(A, B);
}

// USXBoxLiveRef::execMatchQueryGetPublicSlotsUsed
void USXBoxLiveRef::execMatchQueryGetPublicSlotsUsed(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryGetPublicSlotsUsed(A, B);
}

// USXBoxLiveRef::execMatchQueryIsPunkBusterEnabled
void USXBoxLiveRef::execMatchQueryIsPunkBusterEnabled(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryIsPunkBusterEnabled(A, B);
}

// USXBoxLiveRef::execMatchQueryIsLocked
void USXBoxLiveRef::execMatchQueryIsLocked(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryIsLocked(A, B);
}

// USXBoxLiveRef::execMatchQueryGetCompatibilityVersion
void USXBoxLiveRef::execMatchQueryGetCompatibilityVersion(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = unk_3923c0->unk_40->MatchQueryGetCompatibilityVersion(Index);
}

// USXBoxLiveRef::execActivateCdKey
void USXBoxLiveRef::execActivateCdKey(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Value);
    P_FINISH;
    unk_3923c0->unk_40->ActivateCdKey(Value);
}

// USXBoxLiveRef::execGetResultPlayerName
void USXBoxLiveRef::execGetResultPlayerName(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = unk_3923c0->unk_40->GetResultPlayerName(Index);
}

// USXBoxLiveRef::execMatchSetServerName
void USXBoxLiveRef::execMatchSetServerName(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Value);
    P_FINISH;
    unk_3923c0->unk_40->MatchSetServerName(Value);
}

// USXBoxLiveRef::execMatchSetServerPassword
void USXBoxLiveRef::execMatchSetServerPassword(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Value);
    P_FINISH;
    unk_3923c0->unk_40->MatchSetServerPassword(Value);
}

// USXBoxLiveRef::execMatchSetMapName
void USXBoxLiveRef::execMatchSetMapName(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Value);
    P_FINISH;
    unk_3923c0->unk_40->MatchSetMapName(Value);
}

// USXBoxLiveRef::execMatchSetMapPublicName
void USXBoxLiveRef::execMatchSetMapPublicName(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Value);
    P_FINISH;
    unk_3923c0->unk_40->MatchSetMapPublicName(Value);
}

// USXBoxLiveRef::execBlackListGetName
void USXBoxLiveRef::execBlackListGetName(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = unk_3923c0->unk_40->BlackListGetName(Index);
}

// USXBoxLiveRef::execBLIgnorePlayer
void USXBoxLiveRef::execBLIgnorePlayer(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Value);
    P_FINISH;
    unk_3923c0->unk_40->BLIgnorePlayer(Value);
}

// USXBoxLiveRef::execBLUnIgnorePlayer
void USXBoxLiveRef::execBLUnIgnorePlayer(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Value);
    P_FINISH;
    unk_3923c0->unk_40->BLUnIgnorePlayer(Value);
}

// USXBoxLiveRef::execAddFriend
void USXBoxLiveRef::execAddFriend(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Value);
    P_FINISH;
    unk_3923c0->unk_40->AddFriend(Value);
}

// USXBoxLiveRef::execGetFriendName
void USXBoxLiveRef::execGetFriendName(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = unk_3923c0->unk_40->GetFriendName(Index);
}

// USXBoxLiveRef::execGetInvitePassword
void USXBoxLiveRef::execGetInvitePassword(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = unk_3923c0->unk_40->GetInvitePassword(Index);
}

// USXBoxLiveRef::execGetFriendGameTitle
void USXBoxLiveRef::execGetFriendGameTitle(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = unk_3923c0->unk_40->GetFriendGameTitle(Index);
}

// USXBoxLiveRef::execGetInviteSenderName
void USXBoxLiveRef::execGetInviteSenderName(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = unk_3923c0->unk_40->GetInviteSenderName(Index);
}

// USXBoxLiveRef::execRecentPlayerGetName
void USXBoxLiveRef::execRecentPlayerGetName(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = unk_3923c0->unk_40->RecentPlayerGetName(Index);
}

// USXBoxLiveRef::execDownloadContent
void USXBoxLiveRef::execDownloadContent(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Value);
    P_FINISH;
    unk_3923c0->unk_40->DownloadContent(Value);
}

// USXBoxLiveRef::execLadderDyn_GetPlayerScore
void USXBoxLiveRef::execLadderDyn_GetPlayerScore(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->LadderDyn_GetPlayerScore(A, B);
}

// USXBoxLiveRef::execLadderDyn_GetPlayerLevel
void USXBoxLiveRef::execLadderDyn_GetPlayerLevel(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->LadderDyn_GetPlayerLevel(A, B);
}

// USXBoxLiveRef::execMatchQueryIsTutoratMode
void USXBoxLiveRef::execMatchQueryIsTutoratMode(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryIsTutoratMode(A, B);
}

// USXBoxLiveRef::execMatchQueryIsAlternateMode
void USXBoxLiveRef::execMatchQueryIsAlternateMode(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryIsAlternateMode(A, B);
}

// USXBoxLiveRef::execMatchQueryIsDedicatedServerMode
void USXBoxLiveRef::execMatchQueryIsDedicatedServerMode(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT *)Result = unk_3923c0->unk_40->MatchQueryIsDedicatedServerMode(A, B);
}
