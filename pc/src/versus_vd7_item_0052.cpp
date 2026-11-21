// Work item 0052: Versus RVA 0x130ba0-0x130cbb
// ULevel::ServerTickClients (0x130ba0) and ULevel::IsPaused (0x130c80).

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;

class FArray
{
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};

class UNetConnection;
class APlayerController;

class UActorChannel
{
public:
    BYTE unk_00[0x7d];
    BYTE bDirty;                    // +0x7d (inferred name: dirty flag set by ServerTickClients)
};

// Inferred struct name: 4-slot inline connection/channel cache on AActor.
struct FActorChannelEntry
{
    UNetConnection *Connection;     // +0x00
    UActorChannel *Channel;         // +0x04
};

class AActor
{
public:
    BYTE unk_00[0x10c];
    FActorChannelEntry Channels[4]; // +0x10c
    BYTE unk_12c[0x2e8 - 0x12c];
    DWORD bFlag2E8 : 1;             // +0x2e8 bit 0 (neutral name; cleared in AActor ctor)
    DWORD unk_2e8_bits : 31;
    DWORD unk_2ec_bits0 : 2;
    DWORD bNetDirty : 1;            // +0x2ec bit 2
    DWORD unk_2ec_bits3 : 29;

    inline UActorChannel *FindChannel(UNetConnection *Conn)
    {
        if (bFlag2E8)
            return 0;
        for (INT i = 0; i < 4; i++)
        {
            if (Channels[i].Connection == Conn)
                return Channels[i].Channel;
        }
        return 0;
    }
};

class ALevelInfo : public AActor
{
public:
    BYTE unk_2f0[0x3d4 - 0x2f0];
    FLOAT PauseDelay;               // +0x3d4
    BYTE unk_3d8[0x410 - 0x3d8];
    void *Pauser;                   // +0x410
};

enum EConnectionState
{
    USOCK_Invalid = 0,
    USOCK_Closed  = 1,
    USOCK_Pending = 2,
    USOCK_Open    = 3,
};

class UNetConnection
{
public:
    BYTE unk_00[0x30];
    APlayerController *Actor;       // +0x30
    BYTE unk_34[0x6c - 0x34];
    EConnectionState State;         // +0x6c
};

class UNetDriver
{
public:
    BYTE unk_00[0x2c];
    TArray<UNetConnection *> ClientConnections; // +0x2c
};

class UEngine
{
public:
    BYTE unk_00[0x94];
    UBOOL bPaused_94;               // +0x94 (neutral name: forces IsPaused true when non-zero)
};

class ULevel;

// RVA 0x130730: ULevel::ServerTickClient; link-time convention takes Level on the stack.
void __stdcall ULevel_ServerTickClient(ULevel *Level, UNetConnection *Connection, FLOAT DeltaSeconds);

class ULevel
{
public:
    BYTE unk_00[0x2c];
    TArray<AActor *> Actors;        // +0x2c
    BYTE unk_38[0xdc - 0x38];
    TArray<AActor *> NetActors;     // +0xdc (inferred name: actors checked for bNetDirty)
    BYTE unk_e8[0xec - 0xe8];
    UNetDriver *NetDriver;          // +0xec
    UEngine *Engine;                // +0xf0
    BYTE unk_f4[0x190 - 0xf4];
    DOUBLE TimeSeconds;             // +0x190

    inline ALevelInfo *GetLevelInfo()
    {
        return (ALevelInfo *)Actors(0);
    }

    void ServerTickClients(FLOAT DeltaSeconds);
    UBOOL IsPaused();
};

// RVA 0x130ba0: ULevel::ServerTickClients
void ULevel::ServerTickClients(FLOAT DeltaSeconds)
{
    INT NumClients = NetDriver->ClientConnections.Num();
    UNetConnection **Connections = &NetDriver->ClientConnections(0);
    INT NumActors = NetActors.Num();
    AActor **ActorPtr = &NetActors(0);

    for (INT i = 0; i < NumActors; i++, ActorPtr++)
    {
        AActor *Actor = *ActorPtr;
        if (Actor && Actor->bNetDirty)
        {
            UNetConnection **ConnPtr = Connections;
            for (INT j = 0; j < NumClients; j++, ConnPtr++)
            {
                UNetConnection *Conn = *ConnPtr;
                if (Conn->Actor && Conn->State == USOCK_Open)
                {
                    UActorChannel *Ch = Actor->FindChannel(Conn);
                    if (Ch)
                        Ch->bDirty = 1;
                }
            }
            Actor->bNetDirty = 0;
        }
    }

    UNetConnection **ConnPtr = Connections;
    for (INT j = 0; j < NumClients; j++, ConnPtr++)
        ULevel_ServerTickClient(this, *ConnPtr, DeltaSeconds);
}

// RVA 0x130c80: ULevel::IsPaused
UBOOL ULevel::IsPaused()
{
    return Engine->bPaused_94 || (GetLevelInfo()->Pauser && TimeSeconds >= GetLevelInfo()->PauseDelay);
}

// Scaffolding for LTCG link, not part of the unit.
void Driver_130ba0(ULevel *Level, FLOAT DeltaSeconds)
{
    Level->ServerTickClients(DeltaSeconds);
}
