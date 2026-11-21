// w4_item_0128.cpp -- UGUIController join-IP script natives (Versus RVA 0x158320-0x15847b)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

#define RESULT_DECL void *const Result
#define DECLARE_NATIVE(Name) void Name(FFrame &Stack, RESULT_DECL);

struct FGuid;
struct FFrame;
struct FStateFrame;
class UClass;
class UStruct;
class UViewport;
class UInteractionMaster;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T>
class TArray : public FArray
{
public:
    T &operator()(INT i)
    {
        return ((T *)Data)[i];
    }
    const T &operator()(INT i) const
    {
        return ((T *)Data)[i];
    }
};

class FString : public FArray
{
public:
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
    static FString __cdecl Printf(const TCHAR *Fmt, ...);
};

class __declspec(novtable) FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

struct FFrame : public FOutputDevice
{
    UStruct *Node;
    class UObject *Object;
    BYTE *Code;
    BYTE *Locals;
};

#define P_FINISH Stack.Code++

class FUnknown
{
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown
{
public:
    virtual ~UObject();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();

    INT Index;
    BYTE unk_8[0x4];
    FStateFrame *StateFrame;
    BYTE unk_10[0xc];
    DWORD ObjectFlags;
    BYTE unk_20[0x4];
    UClass *Class;
};

class USubsystem : public UObject
{
public:
    virtual ~USubsystem();
    virtual void VirtualSlot22();
};

class UMatchmakingSubsystem : public USubsystem
{
public:
    virtual ~UMatchmakingSubsystem();
    virtual void VirtualSlot23();
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
    virtual void VirtualSlot37();
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
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void VirtualSlot63();
    virtual void VirtualSlot64();
    virtual void VirtualSlot65();
    virtual void VirtualSlot66();
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void VirtualSlot73();
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    // Slot 80 (0x140); named after UGUIController::execTryJoinIp.
    virtual void TryJoinIp(const FString &Ip, INT Port, UViewport *Viewport);
};

struct UnkType_3923C0
{
    BYTE unk_0[0x40];
    UMatchmakingSubsystem *unk_40;
};

class UClient : public UObject
{
public:
    DWORD unk_28;
    TArray<UViewport *> Viewports; // 0x2c
};

class UInteractions : public UObject
{
public:
    virtual ~UInteractions();
};

class UInteraction : public UInteractions
{
public:
    virtual ~UInteraction();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();

    DWORD bActive : 1;
    DWORD bVisible : 1;
    DWORD bRequiresTick : 1;
    DWORD bNativeEvents : 1;
    UViewport *ViewportOwner;      // 0x2c
    UInteractionMaster *Master;    // 0x30
};

class UInteractionMaster : public UInteractions
{
public:
    virtual ~UInteractionMaster();

    UClient *Client;               // 0x28
    UInteraction *BaseMenu;        // 0x2c
    UInteraction *Console;         // 0x30
    TArray<UInteraction *> GlobalInteractions; // 0x34
};

class UBaseGUIController : public UInteraction
{
public:
    virtual ~UBaseGUIController();
};

class UGUIController : public UBaseGUIController
{
public:
    virtual ~UGUIController();

    DECLARE_NATIVE(execTryJoinIp)
    DECLARE_NATIVE(execGetJoinIpIp)
    DECLARE_NATIVE(execGetJoinIpPort)
};

extern UnkType_3923C0 *unk_3923c0;       // 0x10c923c0 (versus_matchmaking.h)
extern TCHAR GJoinIpAddress[];           // 0x10c9232c (name inferred from execGetJoinIpIp)
extern INT GJoinIpPort;                  // 0x10c923ac (name inferred from execGetJoinIpPort)
extern const TCHAR TEXT_JoinIpPortFmt[]; // L"%d" (retail 0x10c46724, writable .data)

// UGUIController::execTryJoinIp (RVA 0x158320)
void UGUIController::execTryJoinIp(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    unk_3923c0->unk_40->TryJoinIp(
        FString(GJoinIpAddress),
        GJoinIpPort,
        Master->Client->Viewports(0));
}

// UGUIController::execGetJoinIpIp (RVA 0x1583a0)
void UGUIController::execGetJoinIpIp(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FString *)Result = FString(GJoinIpAddress);
}

// UGUIController::execGetJoinIpPort (RVA 0x158410)
void UGUIController::execGetJoinIpPort(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FString *)Result = FString::Printf(TEXT_JoinIpPortFmt, GJoinIpPort);
}
