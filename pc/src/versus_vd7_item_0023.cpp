// w4_item_0023.cpp -- Versus work item 0023 (APlayerController::execSetVoiceChatterId)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;

enum EName {
    NAME_None = 0
};

struct FGuid;
struct FFrame;

#define RESULT_DECL void *const Result
#define DECLARE_NATIVE(Name) void Name(FFrame &Stack, RESULT_DECL);

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

// Core.Object (Versus): 0x28 bytes, 22 virtual functions
class UObject : public FUnknown {
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

    BYTE unk_4[0x24];
};

// Core.Subsystem (Versus): 0x28 bytes, 23 virtual functions
class USubsystem : public UObject {
public:
    virtual ~USubsystem();
    virtual void VirtualSlot22();
};

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    class UStruct *Node;
    UObject       *Object;
    BYTE          *Code;
    BYTE          *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_BYTE(Var) BYTE Var = 0; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class UAudioSubsystem : public USubsystem {
public:
    virtual ~UAudioSubsystem();
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
    virtual void SetVoiceChatterId(BYTE Id);
};

class UEngine : public USubsystem {
public:
    virtual ~UEngine();

    BYTE             unk_28[0xc];
    UAudioSubsystem *Audio;
};

class ULevel : public UObject {
public:
    virtual ~ULevel();

    BYTE     unk_28[0xc8];
    UEngine *Engine;
};

class AActor : public UObject {
public:
    virtual ~AActor();

    BYTE    unk_28[0x17c];
    ULevel *XLevel;
};

class AController : public AActor {
public:
    virtual ~AController();
};

class APlayerController : public AController {
public:
    virtual ~APlayerController();

    DECLARE_NATIVE(execSetVoiceChatterId)
};

// APlayerController::execSetVoiceChatterId (RVA 0x1267c0)
void APlayerController::execSetVoiceChatterId(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(Id);
    P_FINISH;
    if (XLevel->Engine->Audio) {
        XLevel->Engine->Audio->SetVoiceChatterId(Id);
    }
}
