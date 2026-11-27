// Voice recipient selection and the PlayerController voice natives.
#include "versus_build.h"
#include "unreal_actor.h"
#include "unreal_script.h"

class UField : public UObject {
public:
    UField *SuperField; // +0x28
};

class UStruct : public UField {};
class UState : public UStruct {};
class UClass : public UState {};

inline UBOOL UObject::IsA(UClass *SomeBase) const {
    for (UClass *C = Class; C; C = (UClass *)C->SuperField)
        if (C == SomeBase)
            return 1;
    return 0;
}

class AController : public AActor {
public:
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual UBOOL UsesViewport();   // +0x140, PlayerController implementation at 0xefa90.
};

class APlayerController : public AController {
public:
    static UClass PrivateStaticClass;
    DECLARE_NATIVE(execMuteMeForVoiceChatter)
    DECLARE_NATIVE(execAmIMutedForVoiceChatter)
    DECLARE_NATIVE(execSetVoiceLoopBack)
    DECLARE_NATIVE(execSetVoiceMask)
};

inline APlayerController *CastPlayerController(UObject *Object) {
    return Object && Object->IsA(&APlayerController::PrivateStaticClass)
        ? (APlayerController *)Object : 0;
}

class UNetConnection
{
public:
    BYTE unk_00[0x30];
    APlayerController *Actor; // UPlayer::Actor at +0x30
    BYTE unk_34[0x49c0 - 0x34];
    APlayerController *VoiceRecipients[8]; // +0x49c0
    // A muted recipient is removed from this connection's delivery list (RVA 0x10e9f0).
    void UpdateMuteSlot(APlayerController *Player, UBOOL bMute);
};

class UNetDriver
{
public:
    BYTE unk_00[0x2c];
    TArray<UNetConnection *> ClientConnections; // +0x2c
    UNetConnection *ServerConnection;           // +0x38
    BYTE unk_3c[0x4fc - 0x3c];
    APlayerController *VoiceRecipients[8];                  // +0x4fc
    UNetConnection *GetClientConnection(INT Index) const {
        return ((UNetConnection **)ClientConnections.Data)[Index];
    }
    void UpdateMuteSlot(APlayerController *Player, UBOOL bMute);
    void MuteMeForVoiceChatter(APlayerController *Player, UObject *Actor, UBOOL bMute);
    UBOOL IsVoiceRecipientMuted(UObject *Actor, APlayerController *Player);
};

class UAudioSubsystem
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual void V32(); virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36(); virtual void V37(); virtual void V38(); virtual void V39();
    virtual void V40();
    virtual void SetVoiceLoopBack(UBOOL bLoopBack); // vtable +0xa4 (slot 41)
    virtual void SetVoiceMask(INT Mask);            // vtable +0xa8 (slot 42)
};

class UEngine
{
public:
    BYTE unk_00[0x34];
    UAudioSubsystem *Audio; // +0x34
};

class ULevel
{
public:
    BYTE unk_00[0xec];
    UNetDriver *NetDriver; // +0xec
    UEngine *Engine;       // +0xf0
    inline UBOOL IsServer() { return !NetDriver || !NetDriver->ServerConnection; }
};

// UNetConnection::UpdateMuteSlot (RVA 0x10e9f0)
__declspec(noinline) void UNetConnection::UpdateMuteSlot(APlayerController *Player, UBOOL bMute)
{
    if (bMute)
    {
        for (INT i = 0; i < 8; i++)
            if (VoiceRecipients[i] == Player)
                VoiceRecipients[i] = 0;
    }
    else
    {
        INT i;
        for (i = 0; i < 8; i++)
            if (VoiceRecipients[i] == Player)
                break;
        if (i == 8)
        {
            for (i = 0; i < 8; i++)
                if (VoiceRecipients[i] == 0)
                {
                    VoiceRecipients[i] = Player;
                    break;
                }
        }
    }
}

// UNetDriver::UpdateMuteSlot (RVA 0xef3d0)
__declspec(noinline) void UNetDriver::UpdateMuteSlot(APlayerController *Player, UBOOL bMute)
{
    if (bMute)
    {
        for (INT i = 0; i < 8; i++)
            if (VoiceRecipients[i] == Player)
                VoiceRecipients[i] = 0;
    }
    else
    {
        INT i;
        for (i = 0; i < 8; i++)
            if (VoiceRecipients[i] == Player)
                break;
        if (i == 8)
        {
            for (i = 0; i < 8; i++)
                if (VoiceRecipients[i] == 0)
                {
                    VoiceRecipients[i] = Player;
                    break;
                }
        }
    }
}

// UNetDriver::MuteMeForVoiceChatter (RVA 0xef2c0)
__declspec(noinline) void UNetDriver::MuteMeForVoiceChatter(APlayerController *Player, UObject *Actor,
                                                            UBOOL bMute)
{
    for (INT i = 0; i < ClientConnections.ArrayNum; i++)
    {
        UNetConnection *Conn = GetClientConnection(i);
        if (Conn->Actor == Actor)
            Conn->UpdateMuteSlot(Player, bMute);
    }
    if (CastPlayerController(Actor)->UsesViewport())
        UpdateMuteSlot(Player, bMute);
}

// UNetDriver::IsVoiceRecipientMuted (RVA 0xef330)
__declspec(noinline) UBOOL UNetDriver::IsVoiceRecipientMuted(UObject *Actor, APlayerController *Player)
{
    for (INT i = 0; i < ClientConnections.ArrayNum; i++)
    {
        UNetConnection *Conn = GetClientConnection(i);
        if (Conn->Actor == Actor)
            for (INT j = 0; j < 8; j++)
                if (Conn->VoiceRecipients[j] == Player)
                    return 0;
    }
    if (CastPlayerController(Actor)->UsesViewport())
        for (INT j = 0; j < 8; j++)
            if (VoiceRecipients[j] == Player)
                return 0;
    return 1;
}

// APlayerController::execMuteMeForVoiceChatter (RVA 0x126920)
void APlayerController::execMuteMeForVoiceChatter(FFrame &Stack, void *const Result)
{
    P_GET_OBJECT(APlayerController, Player);
    P_GET_UBOOL(bMute);
    P_FINISH;
    if (XLevel->IsServer() && XLevel->NetDriver)
        XLevel->NetDriver->MuteMeForVoiceChatter(Player, this, bMute);
}

// APlayerController::execAmIMutedForVoiceChatter (RVA 0x1269b0)
void APlayerController::execAmIMutedForVoiceChatter(FFrame &Stack, void *const Result)
{
    P_GET_OBJECT(APlayerController, Player);
    P_FINISH;
    if (XLevel->IsServer())
    {
        *(BYTE *)Result = (BYTE)(XLevel->NetDriver
            ? XLevel->NetDriver->IsVoiceRecipientMuted(this, Player)
            : 1);
    }
    else
    {
        *(BYTE *)Result = 1;
    }
}

// APlayerController::execSetVoiceLoopBack (RVA 0x126a40)
void APlayerController::execSetVoiceLoopBack(FFrame &Stack, void *const Result)
{
    P_GET_UBOOL(bLoopBack);
    P_FINISH;
    if (XLevel->Engine->Audio)
        XLevel->Engine->Audio->SetVoiceLoopBack(bLoopBack);
}

// APlayerController::execSetVoiceMask (RVA 0x126aa0)
void APlayerController::execSetVoiceMask(FFrame &Stack, void *const Result)
{
    P_GET_BYTE(Mask);
    P_FINISH;
    if (XLevel->Engine->Audio)
        XLevel->Engine->Audio->SetVoiceMask(Mask);
}
