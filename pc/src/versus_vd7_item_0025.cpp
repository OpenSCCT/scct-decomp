// w4_item_0025.cpp -- APlayerController::execOutputVoiceToSpeakers (Versus 0x126b40)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef int UBOOL;
typedef unsigned short TCHAR;

enum EName {
    NAME_None = 0
};

struct FGuid;
struct FFrame;
class UStruct;
class UAudioSubsystem;
class UEngine;
class ULevel;

#define RESULT_DECL void *const Result
#define DECLARE_NATIVE(Name) void Name(FFrame &Stack, RESULT_DECL);

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

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

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    UStruct *Node;
    UObject *Object;
    BYTE    *Code;
    BYTE    *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_UBOOL(Var) DWORD Var = 0; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class USubsystem : public UObject {
public:
    virtual ~USubsystem();
    virtual void VirtualSlot22();
};

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
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual UBOOL OutputVoiceToSpeakers(UBOOL bOutput);
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
    BYTE    unk_1a8[0x150];

    ULevel *GetLevel() const { return XLevel; }
};

class AController : public AActor {
public:
    virtual ~AController();

    BYTE unk_2f8[0xcc];
};

class APlayerController : public AController {
public:
    virtual ~APlayerController();

    BYTE unk_3c4[0x240];

    DECLARE_NATIVE(execOutputVoiceToSpeakers)
};

// APlayerController::execOutputVoiceToSpeakers
void APlayerController::execOutputVoiceToSpeakers(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(bOutput);
    P_FINISH;

    if (GetLevel()->Engine->Audio) {
        *(UBOOL *)Result = GetLevel()->Engine->Audio->OutputVoiceToSpeakers(bOutput);
    } else {
        *(UBOOL *)Result = 0;
    }
}
