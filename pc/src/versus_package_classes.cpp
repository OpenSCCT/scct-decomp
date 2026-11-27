// Construct each package's stock UClass objects in the order used by its native registrar.
#include "versus_build.h"
#include "unreal_types.h"
#include "unreal_name.h"

enum ENativeConstructor { EC_NativeConstructor };

struct FGuid
{
    DWORD A, B, C, D;
    FGuid(DWORD InA, DWORD InB, DWORD InC, DWORD InD) : A(InA), B(InB), C(InC), D(InD) {}
};

class UObject;
typedef void (UObject::*StaticConstructorType)();

class UClass
{
public:
    UClass(ENativeConstructor, DWORD Size, DWORD ClassFlags, UClass *BaseClass,
           UClass *WithinClass, FGuid Guid, FName Name, FName Package, FName Config,
           DWORD ObjectFlags, void (*Constructor)(void *), StaticConstructorType StaticConstructor);
};

inline void *operator new(unsigned int, void *Storage) { return Storage; }

static const EName NAME_WindowManager = (EName)16;
static const EName NAME_WindowsViewport = (EName)18;
static const EName NAME_IpDrv = (EName)25;
static const EName NAME_ESBChainActor = (EName)26;
static const EName NAME_ESBPatchActor = (EName)27;
static const EName NAME_ESBRopeActor = (EName)28;
static const EName NAME_ESBStripDoorActor = (EName)29;
static const EName NAME_ESBPatch = (EName)30;
static const EName NAME_ESBRope = (EName)31;
static const EName NAME_ESBStripDoor = (EName)32;
static const EName NAME_ESBChain = (EName)33;
static const EName NAME_SoftBody = (EName)179;
static const EName NAME_GameService = (EName)184;
static const EName NAME_GameServiceSubsystem = (EName)185;
static const EName NAME_Window = (EName)190;
static const EName NAME_D3DDrv = (EName)191;
static const EName NAME_UNIAudio = (EName)192;
static const EName NAME_WinDrv = (EName)193;
static const EName NAME_WindowsClient = (EName)198;
static const EName NAME_D3DRenderDevice = (EName)200;
static const EName NAME_PCSaveGameDevice = (EName)202;
static const EName NAME_UNIAudioSubsystem = (EName)207;
static const EName NAME_TcpNetDriver = (EName)209;
static const EName NAME_System = (EName)598;
static const EName NAME_Menus = (EName)2002;
static const EName NAME_MenuManager = (EName)2029;
static const EName NAME_UdpLink = (EName)40164;
static const EName NAME_InternetLink = (EName)40165;
static const EName NAME_TcpLink = (EName)40198;
static const EName NAME_TcpipConnection = (EName)134199;

enum { NativeClassObjectFlags = 0x04084004 };

class UObject
{
public:
    static UClass PrivateStaticClass;
    static FName StaticConfigName() { return NAME_System; }
    void StaticConstructor();
};

class AActor : public UObject { public: static UClass PrivateStaticClass; };
class AESoftBodyActor : public AActor { public: static UClass PrivateStaticClass; };
class AInfo : public AActor { public: static UClass PrivateStaticClass; };
class AInternetInfo : public AInfo { public: static UClass PrivateStaticClass; };
class UClient : public UObject { public: static UClass PrivateStaticClass; };
class UPlayer : public UObject { public: static UClass PrivateStaticClass; };
class UPrimitive : public UObject { public: static UClass PrivateStaticClass; };
class USubsystem : public UObject { public: static UClass PrivateStaticClass; };
class UViewport : public UPlayer { public: static UClass PrivateStaticClass; };
class UAudioSubsystem : public USubsystem { public: static UClass PrivateStaticClass; };
class UESoftBody : public UPrimitive { public: static UClass PrivateStaticClass; };
class UMatchmakingSubsystem : public USubsystem { public: static UClass PrivateStaticClass; };
class UMenuManagerSubsystem : public USubsystem { public: static UClass PrivateStaticClass; };
class UNetConnection : public UPlayer { public: static UClass PrivateStaticClass; };
class UNetDriver : public USubsystem { public: static UClass PrivateStaticClass; };
class URenderDevice : public USubsystem { public: static UClass PrivateStaticClass; };
class USaveGameDevice : public USubsystem { public: static UClass PrivateStaticClass; };

class UD3DRenderDevice : public URenderDevice
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
    void StaticConstructor();
};

class AInternetLink : public AInternetInfo
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class ATcpLink : public AInternetLink
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class UTcpipConnection : public UNetConnection
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class UTcpNetDriver : public UNetDriver
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
    void StaticConstructor();
};

class AUdpLink : public AInternetLink
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class AESBPatchActor : public AESoftBodyActor
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class AESBRopeActor : public AESoftBodyActor
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class AESBStripDoorActor : public AESBPatchActor
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class UESBPatch : public UESoftBody
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class UESBRope : public UESoftBody
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class UESBStripDoor : public UESBPatch
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class UUNIAudioSubsystem : public UAudioSubsystem
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
    void StaticConstructor();
};

class UWindowsClient : public UClient
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
    void StaticConstructor();
};

class UWindowsViewport : public UViewport
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class UPCSaveGameDevice : public USaveGameDevice
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class UGameServiceSubsystem : public UMatchmakingSubsystem
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class UWindowManager : public UObject
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class UMenuManager : public UMenuManagerSubsystem
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class AESBChainActor : public AESBRopeActor
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

class UESBChain : public UESBRope
{
public:
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};

// Each callback initializes the class named by the registration; inherited static constructors
// remain inherited here. The sizes are the values passed to the retail UClass constructor.
#define REGISTER_CLASS(type, size, flags, base, within, name, package) \
    new (&type::PrivateStaticClass) UClass(EC_NativeConstructor, size, flags, \
        &base::PrivateStaticClass, &within::PrivateStaticClass, FGuid(0, 0, 0, 0), name, \
        package, type::StaticConfigName(), NativeClassObjectFlags, type::InternalConstructor, \
        (StaticConstructorType)&type::StaticConstructor)

void RegisterD3DDrvClasses()
{
    REGISTER_CLASS(UD3DRenderDevice, 0x30fc0, 0x4, URenderDevice, UObject,
                   NAME_D3DRenderDevice, NAME_D3DDrv);
}

void RegisterIpDrvClasses()
{
    REGISTER_CLASS(AInternetLink, 0x314, 0x8, AInternetInfo, UObject,
                   NAME_InternetLink, NAME_IpDrv);
    REGISTER_CLASS(ATcpLink, 0x330, 0x8, AInternetLink, UObject,
                   NAME_TcpLink, NAME_IpDrv);
    REGISTER_CLASS(UTcpipConnection, 0x4a04, 0xc, UNetConnection, UObject,
                   NAME_TcpipConnection, NAME_IpDrv);
    REGISTER_CLASS(UTcpNetDriver, 0x52c, 0xc, UNetDriver, UObject,
                   NAME_TcpNetDriver, NAME_IpDrv);
    REGISTER_CLASS(AUdpLink, 0x32c, 0x8, AInternetLink, UObject,
                   NAME_UdpLink, NAME_IpDrv);
}

void RegisterSoftBodyClasses()
{
    REGISTER_CLASS(AESBChainActor, 0x3bc, 0x0, AESBRopeActor, UObject,
                   NAME_ESBChainActor, NAME_SoftBody);
    REGISTER_CLASS(AESBPatchActor, 0x3c0, 0x0, AESoftBodyActor, UObject,
                   NAME_ESBPatchActor, NAME_SoftBody);
    REGISTER_CLASS(AESBRopeActor, 0x3b8, 0x0, AESoftBodyActor, UObject,
                   NAME_ESBRopeActor, NAME_SoftBody);
    REGISTER_CLASS(AESBStripDoorActor, 0x3c0, 0x0, AESBPatchActor, UObject,
                   NAME_ESBStripDoorActor, NAME_SoftBody);
    REGISTER_CLASS(UESBChain, 0x19c, 0x0, UESBRope, UObject,
                   NAME_ESBChain, NAME_SoftBody);
    REGISTER_CLASS(UESBPatch, 0x1a4, 0x0, UESoftBody, UObject,
                   NAME_ESBPatch, NAME_SoftBody);
    REGISTER_CLASS(UESBRope, 0x19c, 0x0, UESoftBody, UObject,
                   NAME_ESBRope, NAME_SoftBody);
    REGISTER_CLASS(UESBStripDoor, 0x1a4, 0x0, UESBPatch, UObject,
                   NAME_ESBStripDoor, NAME_SoftBody);
}

void RegisterUNIAudioClasses()
{
    REGISTER_CLASS(UUNIAudioSubsystem, 0x1e0, 0x4, UAudioSubsystem, UObject,
                   NAME_UNIAudioSubsystem, NAME_UNIAudio);
}

void RegisterWinDrvClasses()
{
    REGISTER_CLASS(UWindowsClient, 0xec, 0xc, UClient, UObject,
                   NAME_WindowsClient, NAME_WinDrv);
    REGISTER_CLASS(UWindowsViewport, 0x1fc, 0x8, UViewport, UWindowsClient,
                   NAME_WindowsViewport, NAME_WinDrv);
    REGISTER_CLASS(UPCSaveGameDevice, 0x144, 0x0, USaveGameDevice, UObject,
                   NAME_PCSaveGameDevice, NAME_WinDrv);
}

void RegisterGameServiceClasses()
{
    REGISTER_CLASS(UGameServiceSubsystem, 0xa0, 0xc, UMatchmakingSubsystem, UObject,
                   NAME_GameServiceSubsystem, NAME_GameService);
}

void RegisterWindowClasses()
{
    REGISTER_CLASS(UWindowManager, 0x28, 0x8, UObject, UObject,
                   NAME_WindowManager, NAME_Window);
}

void RegisterMenusClasses()
{
    REGISTER_CLASS(UMenuManager, 0x54, 0x4, UMenuManagerSubsystem, UObject,
                   NAME_MenuManager, NAME_Menus);
}

#undef REGISTER_CLASS
