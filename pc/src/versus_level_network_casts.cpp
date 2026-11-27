#include "versus_build.h"
#include "versus_native_class_init.h"

template<class T> T *Cast(UObject *Object)
{
    if (Object) {
        for (UField *Type = Object->GetClass(); Type; Type = Type->SuperField)
            if (Type == T::StaticClass())
                return (T *)Object;
    }
    return 0;
}

class AActor : public UObject {};
class AController : public AActor {};
class UPlayer : public UObject {};
class APlayerController : public AController {
public:
    BYTE unk_28[0x4a4 - sizeof(AController)];
    UPlayer *Player;

    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UChannel : public UObject {
public:
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void Close();
};

enum EConnectionState { USOCK_Closed = 1 };

class UNetConnection : public UPlayer {
public:
    BYTE unk_28[0x6c - sizeof(UPlayer)];
    EConnectionState State;
    BYTE unk_70[0xef0 - 0x70];
    UChannel *Channels[(0x26fc - 0xef0) / sizeof(UChannel *)];

    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

namespace ReconstructedCallers {

// ULevel::DestroyActor reaches this sequence for actors marked bIsAPlayerController.
// retail RVAs 0x11a7d4 through 0x11a80d. The sequence is inlined in the caller.
UBOOL ClosePlayerConnection(AActor *Actor)
{
    APlayerController *Controller = Cast<APlayerController>(Actor);
    if (Controller) {
        UNetConnection *Connection = Cast<UNetConnection>(Controller->Player);
        if (Connection && Connection->Channels[0] && Connection->State != USOCK_Closed) {
            Connection->Channels[0]->Close();
            return 1;
        }
    }
    return 0;
}

}
