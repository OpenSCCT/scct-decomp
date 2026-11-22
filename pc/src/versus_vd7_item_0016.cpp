// w4_item_0016.cpp -- Versus work item 0016 (AActor::execSetAmbientVolume)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;

enum EName {
    NAME_None = 0
};

struct FGuid;
struct FFrame;

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

#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

// Core.Subsystem (Versus): 0x28 bytes, 23 virtual functions
class USubsystem : public UObject {
public:
    virtual ~USubsystem();
    virtual void VirtualSlot22();
};

// Engine.AudioSubsystem (Versus): SetAmbientVolume at vtable offset 0xe4 (slot 57)
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
    virtual void SetAmbientVolume(FLOAT Volume);
};

// Engine.Engine (Versus): Audio at offset 0x34
class UEngine : public USubsystem {
public:
    virtual ~UEngine();

    BYTE             unk_28[0xc];
    UAudioSubsystem *Audio;
};

// Engine.Level (Versus): Engine at offset 0xf0
class ULevel : public UObject {
public:
    virtual ~ULevel();

    BYTE     unk_28[0xc8];
    UEngine *Engine;
};

// Engine.Actor (Versus): XLevel at offset 0x1a4
class AActor : public UObject {
public:
    virtual ~AActor();

    BYTE    unk_28[0x17c];
    ULevel *XLevel;

    ULevel *GetLevel() const { return XLevel; }

    DECLARE_NATIVE(execSetAmbientVolume)
};

// AActor::execSetAmbientVolume
void AActor::execSetAmbientVolume(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Volume);
    P_FINISH;

    if (GetLevel()->Engine->Audio) {
        GetLevel()->Engine->Audio->SetAmbientVolume(Volume);
    }
}
