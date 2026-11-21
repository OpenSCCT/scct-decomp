// USXBoxLiveRef UnrealScript natives from the Steam Versus payload that forward to
// the online game service. Each reads its parameters with the engine's P_GET
// macros and calls one virtual method of the service the global host keeps.
// Slot<N> names stand for service methods this translation unit does not call.
class UObject { public: int Index; };
struct FFrame;
typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FFrame {
    void *OutputDeviceTable;
    void *Node;
    UObject *Object;
    unsigned char *Code;
    void *Locals;
    void Step(UObject *Context, void *const Result)
    {
        int B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

class FString {
public:
    unsigned short *Data;
    int ArrayNum;
    int ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const FString &Other);
    ~FString();
    FString &operator=(const FString &Other);
};

#define P_GET_INT(Var) int Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class FGameService {
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual FString GetLobbyName(int Index);
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    virtual FString GetUserName(int Index);
    virtual void Slot38();
    virtual void Slot39();
    virtual void Slot40();
    virtual void Slot41();
    virtual void Slot42();
    virtual void Slot43();
    virtual void Slot44();
    virtual void Slot45();
    virtual void Slot46();
    virtual void Slot47();
    virtual void Slot48();
    virtual void Slot49();
    virtual void Slot50();
    virtual void Slot51();
    virtual void Slot52();
    virtual void Slot53();
    virtual void Slot54();
    virtual void Slot55();
    virtual void Slot56();
    virtual int MatchQueryGetGameMode(int A, int B);
    virtual int MatchQueryGetMapAmateur(int A, int B);
    virtual int MatchQueryIsLadderGame(int A, int B);
    virtual int MatchQueryGetGameLevel(int A, int B);
    virtual void Slot61();
    virtual int MatchQueryGetGameState(int A, int B);
    virtual int MatchQueryGetTimeRemaining(int A, int B);
    virtual int MatchQueryIsSpyAvailable(int A, int B);
    virtual int MatchQueryIsSentryAvailable(int A, int B);
    virtual int MatchQueryGetNumSlotsUsed(int A, int B);
    virtual int MatchQueryGetNumSlotsFree(int A, int B);
    virtual int MatchQueryGetPrivateSlotsFree(int A, int B);
    virtual int MatchQueryGetPublicSlotsFree(int A, int B);
    virtual int MatchQueryGetPrivateSlotsUsed(int A, int B);
    virtual int MatchQueryGetPublicSlotsUsed(int A, int B);
    virtual int MatchQueryGetMaxPlayers(int A, int B);
    virtual int MatchQueryGetNbrPlayers(int A, int B);
    virtual int MatchQueryGetbGamesInARowPlaying(int A, int B);
    virtual int MatchQueryIsPunkBusterEnabled(int A, int B);
    virtual int MatchQueryIsLocked(int A, int B);
    virtual FString MatchQueryGetCompatibilityVersion(int Index);
    virtual void Slot78();
    virtual void Slot79();
    virtual void Slot80();
    virtual void Slot81();
    virtual void Slot82();
    virtual void Slot83();
    virtual void Slot84();
    virtual void Slot85();
    virtual void Slot86();
    virtual void Slot87();
    virtual void Slot88();
    virtual void Slot89();
    virtual void Slot90();
    virtual FString GetResultPlayerName(int Index);
    virtual void Slot92();
    virtual void Slot93();
    virtual void Slot94();
    virtual void MatchSetServerName(FString Value);
    virtual void MatchSetServerPassword(FString Value);
    virtual void Slot97();
    virtual void MatchSetMapName(FString Value);
    virtual void MatchSetMapPublicName(FString Value);
    virtual void Slot100();
    virtual void Slot101();
    virtual void Slot102();
    virtual void Slot103();
    virtual void Slot104();
    virtual void Slot105();
    virtual void Slot106();
    virtual void Slot107();
    virtual void Slot108();
    virtual void Slot109();
    virtual void Slot110();
    virtual void Slot111();
    virtual void Slot112();
    virtual void Slot113();
    virtual void Slot114();
    virtual void Slot115();
    virtual void Slot116();
    virtual void Slot117();
    virtual int MatchQueryIsTutoratMode(int A, int B);
    virtual void Slot119();
    virtual int MatchQueryIsAlternateMode(int A, int B);
    virtual void Slot121();
    virtual int MatchQueryIsDedicatedServerMode(int A, int B);
    virtual void Slot123();
    virtual void Slot124();
    virtual void Slot125();
    virtual void Slot126();
    virtual FString BlackListGetName(int Index);
    virtual void BLIgnorePlayer(FString Value);
    virtual void BLUnIgnorePlayer(FString Value);
    virtual void Slot130();
    virtual void Slot131();
    virtual void Slot132();
    virtual void Slot133();
    virtual void Slot134();
    virtual void Slot135();
    virtual void Slot136();
    virtual void Slot137();
    virtual void Slot138();
    virtual void Slot139();
    virtual void Slot140();
    virtual void Slot141();
    virtual void Slot142();
    virtual void Slot143();
    virtual void Slot144();
    virtual void Slot145();
    virtual void Slot146();
    virtual void Slot147();
    virtual void Slot148();
    virtual void Slot149();
    virtual void Slot150();
    virtual void Slot151();
    virtual void Slot152();
    virtual void Slot153();
    virtual void Slot154();
    virtual FString GetInvitePassword(int Index);
    virtual void Slot156();
    virtual void AddFriend(FString Value);
    virtual void Slot158();
    virtual FString GetFriendName(int Index);
    virtual void Slot160();
    virtual void Slot161();
    virtual void Slot162();
    virtual void Slot163();
    virtual void Slot164();
    virtual void Slot165();
    virtual void Slot166();
    virtual void Slot167();
    virtual FString GetFriendGameTitle(int Index);
    virtual void Slot169();
    virtual void Slot170();
    virtual void Slot171();
    virtual void Slot172();
    virtual FString GetInviteSenderName(int Index);
    virtual void Slot174();
    virtual FString RecentPlayerGetName(int Index);
    virtual void Slot176();
    virtual void Slot177();
    virtual void Slot178();
    virtual void DownloadContent(FString Value);
    virtual int LadderDyn_GetPlayerScore(int A, int B);
    virtual int LadderDyn_GetPlayerLevel(int A, int B);
    virtual void Slot182();
    virtual void Slot183();
    virtual void Slot184();
    virtual void Slot185();
    virtual void Slot186();
    virtual void Slot187();
    virtual void Slot188();
    virtual void Slot189();
    virtual void ActivateCdKey(FString Value);
};

struct FServiceHost {
    unsigned char Reserved[0x40];
    FGameService *Service;
};
extern FServiceHost *GServiceHost;

class USXBoxLiveRef : public UObject {
public:
    void execGetUserName(FFrame &Stack, void *const Result);
    void execGetLobbyName(FFrame &Stack, void *const Result);
    void execMatchQueryGetMapAmateur(FFrame &Stack, void *const Result);
    void execMatchQueryGetGameMode(FFrame &Stack, void *const Result);
    void execMatchQueryIsLadderGame(FFrame &Stack, void *const Result);
    void execMatchQueryGetGameLevel(FFrame &Stack, void *const Result);
    void execMatchQueryGetGameState(FFrame &Stack, void *const Result);
    void execMatchQueryGetTimeRemaining(FFrame &Stack, void *const Result);
    void execMatchQueryIsSpyAvailable(FFrame &Stack, void *const Result);
    void execMatchQueryIsSentryAvailable(FFrame &Stack, void *const Result);
    void execMatchQueryGetNumSlotsUsed(FFrame &Stack, void *const Result);
    void execMatchQueryGetMaxPlayers(FFrame &Stack, void *const Result);
    void execMatchQueryGetNbrPlayers(FFrame &Stack, void *const Result);
    void execMatchQueryGetbGamesInARowPlaying(FFrame &Stack, void *const Result);
    void execMatchQueryGetNumSlotsFree(FFrame &Stack, void *const Result);
    void execMatchQueryGetPrivateSlotsFree(FFrame &Stack, void *const Result);
    void execMatchQueryGetPublicSlotsFree(FFrame &Stack, void *const Result);
    void execMatchQueryGetPrivateSlotsUsed(FFrame &Stack, void *const Result);
    void execMatchQueryGetPublicSlotsUsed(FFrame &Stack, void *const Result);
    void execMatchQueryIsPunkBusterEnabled(FFrame &Stack, void *const Result);
    void execMatchQueryIsLocked(FFrame &Stack, void *const Result);
    void execMatchQueryGetCompatibilityVersion(FFrame &Stack, void *const Result);
    void execActivateCdKey(FFrame &Stack, void *const Result);
    void execGetResultPlayerName(FFrame &Stack, void *const Result);
    void execMatchSetServerName(FFrame &Stack, void *const Result);
    void execMatchSetServerPassword(FFrame &Stack, void *const Result);
    void execMatchSetMapName(FFrame &Stack, void *const Result);
    void execMatchSetMapPublicName(FFrame &Stack, void *const Result);
    void execBlackListGetName(FFrame &Stack, void *const Result);
    void execBLIgnorePlayer(FFrame &Stack, void *const Result);
    void execBLUnIgnorePlayer(FFrame &Stack, void *const Result);
    void execAddFriend(FFrame &Stack, void *const Result);
    void execGetFriendName(FFrame &Stack, void *const Result);
    void execGetInvitePassword(FFrame &Stack, void *const Result);
    void execGetFriendGameTitle(FFrame &Stack, void *const Result);
    void execGetInviteSenderName(FFrame &Stack, void *const Result);
    void execRecentPlayerGetName(FFrame &Stack, void *const Result);
    void execDownloadContent(FFrame &Stack, void *const Result);
    void execLadderDyn_GetPlayerScore(FFrame &Stack, void *const Result);
    void execLadderDyn_GetPlayerLevel(FFrame &Stack, void *const Result);
    void execMatchQueryIsTutoratMode(FFrame &Stack, void *const Result);
    void execMatchQueryIsAlternateMode(FFrame &Stack, void *const Result);
    void execMatchQueryIsDedicatedServerMode(FFrame &Stack, void *const Result);
};

void USXBoxLiveRef::execGetUserName(FFrame &Stack, void *const Result)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = GServiceHost->Service->GetUserName(Index);
}

void USXBoxLiveRef::execGetLobbyName(FFrame &Stack, void *const Result)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = GServiceHost->Service->GetLobbyName(Index);
}

void USXBoxLiveRef::execMatchQueryGetMapAmateur(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetMapAmateur(A, B);
}

void USXBoxLiveRef::execMatchQueryGetGameMode(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetGameMode(A, B);
}

void USXBoxLiveRef::execMatchQueryIsLadderGame(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryIsLadderGame(A, B);
}

void USXBoxLiveRef::execMatchQueryGetGameLevel(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetGameLevel(A, B);
}

void USXBoxLiveRef::execMatchQueryGetGameState(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetGameState(A, B);
}

void USXBoxLiveRef::execMatchQueryGetTimeRemaining(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetTimeRemaining(A, B);
}

void USXBoxLiveRef::execMatchQueryIsSpyAvailable(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryIsSpyAvailable(A, B);
}

void USXBoxLiveRef::execMatchQueryIsSentryAvailable(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryIsSentryAvailable(A, B);
}

void USXBoxLiveRef::execMatchQueryGetNumSlotsUsed(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetNumSlotsUsed(A, B);
}

void USXBoxLiveRef::execMatchQueryGetMaxPlayers(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetMaxPlayers(A, B);
}

void USXBoxLiveRef::execMatchQueryGetNbrPlayers(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetNbrPlayers(A, B);
}

void USXBoxLiveRef::execMatchQueryGetbGamesInARowPlaying(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetbGamesInARowPlaying(A, B);
}

void USXBoxLiveRef::execMatchQueryGetNumSlotsFree(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetNumSlotsFree(A, B);
}

void USXBoxLiveRef::execMatchQueryGetPrivateSlotsFree(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetPrivateSlotsFree(A, B);
}

void USXBoxLiveRef::execMatchQueryGetPublicSlotsFree(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetPublicSlotsFree(A, B);
}

void USXBoxLiveRef::execMatchQueryGetPrivateSlotsUsed(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetPrivateSlotsUsed(A, B);
}

void USXBoxLiveRef::execMatchQueryGetPublicSlotsUsed(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryGetPublicSlotsUsed(A, B);
}

void USXBoxLiveRef::execMatchQueryIsPunkBusterEnabled(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryIsPunkBusterEnabled(A, B);
}

void USXBoxLiveRef::execMatchQueryIsLocked(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryIsLocked(A, B);
}

void USXBoxLiveRef::execMatchQueryGetCompatibilityVersion(FFrame &Stack, void *const Result)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = GServiceHost->Service->MatchQueryGetCompatibilityVersion(Index);
}

void USXBoxLiveRef::execActivateCdKey(FFrame &Stack, void *const Result)
{
    P_GET_STR(Value);
    P_FINISH;
    GServiceHost->Service->ActivateCdKey(Value);
}

void USXBoxLiveRef::execGetResultPlayerName(FFrame &Stack, void *const Result)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = GServiceHost->Service->GetResultPlayerName(Index);
}

void USXBoxLiveRef::execMatchSetServerName(FFrame &Stack, void *const Result)
{
    P_GET_STR(Value);
    P_FINISH;
    GServiceHost->Service->MatchSetServerName(Value);
}

void USXBoxLiveRef::execMatchSetServerPassword(FFrame &Stack, void *const Result)
{
    P_GET_STR(Value);
    P_FINISH;
    GServiceHost->Service->MatchSetServerPassword(Value);
}

void USXBoxLiveRef::execMatchSetMapName(FFrame &Stack, void *const Result)
{
    P_GET_STR(Value);
    P_FINISH;
    GServiceHost->Service->MatchSetMapName(Value);
}

void USXBoxLiveRef::execMatchSetMapPublicName(FFrame &Stack, void *const Result)
{
    P_GET_STR(Value);
    P_FINISH;
    GServiceHost->Service->MatchSetMapPublicName(Value);
}

void USXBoxLiveRef::execBlackListGetName(FFrame &Stack, void *const Result)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = GServiceHost->Service->BlackListGetName(Index);
}

void USXBoxLiveRef::execBLIgnorePlayer(FFrame &Stack, void *const Result)
{
    P_GET_STR(Value);
    P_FINISH;
    GServiceHost->Service->BLIgnorePlayer(Value);
}

void USXBoxLiveRef::execBLUnIgnorePlayer(FFrame &Stack, void *const Result)
{
    P_GET_STR(Value);
    P_FINISH;
    GServiceHost->Service->BLUnIgnorePlayer(Value);
}

void USXBoxLiveRef::execAddFriend(FFrame &Stack, void *const Result)
{
    P_GET_STR(Value);
    P_FINISH;
    GServiceHost->Service->AddFriend(Value);
}

void USXBoxLiveRef::execGetFriendName(FFrame &Stack, void *const Result)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = GServiceHost->Service->GetFriendName(Index);
}

void USXBoxLiveRef::execGetInvitePassword(FFrame &Stack, void *const Result)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = GServiceHost->Service->GetInvitePassword(Index);
}

void USXBoxLiveRef::execGetFriendGameTitle(FFrame &Stack, void *const Result)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = GServiceHost->Service->GetFriendGameTitle(Index);
}

void USXBoxLiveRef::execGetInviteSenderName(FFrame &Stack, void *const Result)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = GServiceHost->Service->GetInviteSenderName(Index);
}

void USXBoxLiveRef::execRecentPlayerGetName(FFrame &Stack, void *const Result)
{
    P_GET_INT(Index);
    P_FINISH;
    *(FString *)Result = GServiceHost->Service->RecentPlayerGetName(Index);
}

void USXBoxLiveRef::execDownloadContent(FFrame &Stack, void *const Result)
{
    P_GET_STR(Value);
    P_FINISH;
    GServiceHost->Service->DownloadContent(Value);
}

void USXBoxLiveRef::execLadderDyn_GetPlayerScore(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->LadderDyn_GetPlayerScore(A, B);
}

void USXBoxLiveRef::execLadderDyn_GetPlayerLevel(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->LadderDyn_GetPlayerLevel(A, B);
}

void USXBoxLiveRef::execMatchQueryIsTutoratMode(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryIsTutoratMode(A, B);
}

void USXBoxLiveRef::execMatchQueryIsAlternateMode(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryIsAlternateMode(A, B);
}

void USXBoxLiveRef::execMatchQueryIsDedicatedServerMode(FFrame &Stack, void *const Result)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(int *)Result = GServiceHost->Service->MatchQueryIsDedicatedServerMode(A, B);
}
