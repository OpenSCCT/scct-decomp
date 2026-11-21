// w4_item_0024.cpp -- APlayerController voice chatter and audio UnrealScript natives
// Versus RVA 0x126920-0x126af2:
//   0x126920 APlayerController::execMuteMeForVoiceChatter
//   0x1269b0 APlayerController::execAmIMutedForVoiceChatter
//   0x126a40 APlayerController::execSetVoiceLoopBack
//   0x126aa0 APlayerController::execSetVoiceMask

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

class UClass;
class UObject;
struct FFrame;

typedef void (UObject::*Native)(FFrame &TheStack, void *const Result);
extern Native GNatives[]; // retail 0x10c819d8

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event);
};

struct FFrame : public FOutputDevice
{
    void *Node;
    UObject *Object;
    BYTE *Code;
    inline void Step(UObject *Context, void *const Result);
};

class UObject
{
public:
    // Vtable slot 0x140 (80): virtual query used by UNetDriver voice-mute helpers
    // (copied from pc/src/versus_vd5_item_0227.cpp; exact name not yet identified).
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
    virtual void V40(); virtual void V41(); virtual void V42(); virtual void V43();
    virtual void V44(); virtual void V45(); virtual void V46(); virtual void V47();
    virtual void V48(); virtual void V49(); virtual void V50(); virtual void V51();
    virtual void V52(); virtual void V53(); virtual void V54(); virtual void V55();
    virtual void V56(); virtual void V57(); virtual void V58(); virtual void V59();
    virtual void V60(); virtual void V61(); virtual void V62(); virtual void V63();
    virtual void V64(); virtual void V65(); virtual void V66(); virtual void V67();
    virtual void V68(); virtual void V69(); virtual void V70(); virtual void V71();
    virtual void V72(); virtual void V73(); virtual void V74(); virtual void V75();
    virtual void V76(); virtual void V77(); virtual void V78(); virtual void V79();
    virtual UBOOL Query140();
    BYTE unk_04[0x20];
    UClass *Class; // +0x24
    inline UBOOL IsA(UClass *SomeBase) const;
};

class UClass : public UObject
{
public:
    UClass *SuperClass; // +0x28
};

// UObject::IsA
inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *C = Class; C; C = C->SuperClass)
        if (C == SomeBase)
            return 1;
    return 0;
}

// FFrame::Step
inline void FFrame::Step(UObject *Context, void *const Result)
{
    INT B = *Code++;
    (Context->*GNatives[B])(*this, Result);
}

#define P_GET_INT(var)   INT var = 0;   Stack.Step(Stack.Object, &var);
#define P_GET_UBOOL(var) UBOOL var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_BYTE(var)  BYTE var = 0;  Stack.Step(Stack.Object, &var);
#define P_FINISH         Stack.Code++;

template <class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

// Retail 0x10cc6ce8: class cast target in UNetDriver voice-mute helpers
// (exact class name not yet identified from symbols).
extern UClass UnnamedKeyClass_ef2c0_StaticClass;

// CastKey
inline UObject *CastKey(UObject *Src)
{
    return Src && Src->IsA(&UnnamedKeyClass_ef2c0_StaticClass) ? Src : 0;
}

class UNetConnection
{
public:
    BYTE unk_00[0x30];
    UObject *Actor; // +0x30
    BYTE unk_34[0x49c0 - 0x34];
    INT MutedVoiceChatters[8]; // +0x49c0
    // Inferred from APlayerController voice-chatter callers (RVA 0x10e9f0).
    void UpdateMuteSlot(INT ChatterID, UBOOL bMute);
};

class UNetDriver
{
public:
    BYTE unk_00[0x2c];
    TArray<UNetConnection *> ClientConnections; // +0x2c
    UNetConnection *ServerConnection;           // +0x38
    BYTE unk_3c[0x4fc - 0x3c];
    INT MutedVoiceChatters[8];                  // +0x4fc
    // Inferred from APlayerController voice-chatter callers (RVAs 0xef3d0, 0xef2c0, 0xef330).
    void UpdateMuteSlot(INT ChatterID, UBOOL bMute);
    void MuteMeForVoiceChatter(INT ChatterID, UObject *Actor, UBOOL bMute);
    UBOOL IsVoiceChatterUnmuted(UObject *Actor, INT ChatterID);
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

class AActor : public UObject
{
public:
    BYTE unk_28[0x1a4 - 0x28];
    ULevel *XLevel; // +0x1a4
};

class APlayerController : public AActor
{
public:
    void execMuteMeForVoiceChatter(FFrame &Stack, void *const Result);
    void execAmIMutedForVoiceChatter(FFrame &Stack, void *const Result);
    void execSetVoiceLoopBack(FFrame &Stack, void *const Result);
    void execSetVoiceMask(FFrame &Stack, void *const Result);
};

// UNetConnection::UpdateMuteSlot (RVA 0x10e9f0)
// Kept in this TU so LTCG assigns the retail custom calling convention to callers.
__declspec(noinline) void UNetConnection::UpdateMuteSlot(INT ChatterID, UBOOL bMute)
{
    if (bMute)
    {
        for (INT i = 0; i < 8; i++)
            if (MutedVoiceChatters[i] == ChatterID)
                MutedVoiceChatters[i] = 0;
    }
    else
    {
        INT i;
        for (i = 0; i < 8; i++)
            if (MutedVoiceChatters[i] == ChatterID)
                break;
        if (i == 8)
        {
            for (i = 0; i < 8; i++)
                if (MutedVoiceChatters[i] == 0)
                {
                    MutedVoiceChatters[i] = ChatterID;
                    break;
                }
        }
    }
}

// UNetDriver::UpdateMuteSlot (RVA 0xef3d0)
// Kept in this TU so LTCG assigns the retail custom calling convention to callers.
__declspec(noinline) void UNetDriver::UpdateMuteSlot(INT ChatterID, UBOOL bMute)
{
    if (bMute)
    {
        for (INT i = 0; i < 8; i++)
            if (MutedVoiceChatters[i] == ChatterID)
                MutedVoiceChatters[i] = 0;
    }
    else
    {
        INT i;
        for (i = 0; i < 8; i++)
            if (MutedVoiceChatters[i] == ChatterID)
                break;
        if (i == 8)
        {
            for (i = 0; i < 8; i++)
                if (MutedVoiceChatters[i] == 0)
                {
                    MutedVoiceChatters[i] = ChatterID;
                    break;
                }
        }
    }
}

// UNetDriver::MuteMeForVoiceChatter (RVA 0xef2c0)
// Kept in this TU so LTCG assigns the retail custom calling convention to callers.
__declspec(noinline) void UNetDriver::MuteMeForVoiceChatter(INT ChatterID, UObject *Actor,
                                                            UBOOL bMute)
{
    for (INT i = 0; i < ClientConnections.Num(); i++)
    {
        UNetConnection *Conn = ClientConnections(i);
        if (Conn->Actor == Actor)
            Conn->UpdateMuteSlot(ChatterID, bMute);
    }
    if (CastKey(Actor)->Query140())
        UpdateMuteSlot(ChatterID, bMute);
}

// UNetDriver::IsVoiceChatterUnmuted (RVA 0xef330)
// Kept in this TU so LTCG assigns the retail custom calling convention to callers.
__declspec(noinline) UBOOL UNetDriver::IsVoiceChatterUnmuted(UObject *Actor, INT ChatterID)
{
    for (INT i = 0; i < ClientConnections.Num(); i++)
    {
        UNetConnection *Conn = ClientConnections(i);
        if (Conn->Actor == Actor)
            for (INT j = 0; j < 8; j++)
                if (Conn->MutedVoiceChatters[j] == ChatterID)
                    return 0;
    }
    if (CastKey(Actor)->Query140())
        for (INT j = 0; j < 8; j++)
            if (MutedVoiceChatters[j] == ChatterID)
                return 0;
    return 1;
}

// APlayerController::execMuteMeForVoiceChatter (RVA 0x126920)
void APlayerController::execMuteMeForVoiceChatter(FFrame &Stack, void *const Result)
{
    P_GET_INT(ChatterID);
    P_GET_UBOOL(bMute);
    P_FINISH;
    if (XLevel->IsServer() && XLevel->NetDriver)
        XLevel->NetDriver->MuteMeForVoiceChatter(ChatterID, this, bMute);
}

// APlayerController::execAmIMutedForVoiceChatter (RVA 0x1269b0)
void APlayerController::execAmIMutedForVoiceChatter(FFrame &Stack, void *const Result)
{
    P_GET_INT(ChatterID);
    P_FINISH;
    if (XLevel->IsServer())
    {
        *(BYTE *)Result = (BYTE)(XLevel->NetDriver
            ? XLevel->NetDriver->IsVoiceChatterUnmuted(this, ChatterID)
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
