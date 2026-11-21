// w4_item_0014.cpp -- AActor::execSetSwitch and AActor::execSetSoundVolume (Versus)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef unsigned short TCHAR;

enum EName {
    NAME_None = 0
};

struct FGuid;
struct FFrame;
struct FStateFrame;
class UClass;
class UStruct;
class ULevel;
class UEngine;
class UAudioSubsystem;

#define RESULT_DECL void *const Result
#define DECLARE_NATIVE(Name) void Name(FFrame &Stack, RESULT_DECL);

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

    INT          Index;
    BYTE         unk_8[0x4];
    FStateFrame *StateFrame;
    BYTE         unk_10[0xc];
    DWORD        ObjectFlags;
    BYTE         unk_20[0x4];
    UClass      *Class;
};

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
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

#define P_GET_BYTE(Var) BYTE Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
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
    virtual void SetSwitch(BYTE Switch);
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
    virtual FLOAT GetSoundVolume();
    virtual void SetSoundVolume(FLOAT Volume);
};

class UEngine : public USubsystem {
public:
    BYTE             unk_28[0xc];
    UAudioSubsystem *Audio;
};

class ULevel : public UObject {
public:
    BYTE     unk_28[0xc8];
    UEngine *Engine;
};

class AActor : public UObject {
public:
    BYTE    unk_28[0x17c];
    ULevel *XLevel;

    ULevel *GetLevel() const { return XLevel; }

    DECLARE_NATIVE(execSetSwitch)
    DECLARE_NATIVE(execSetSoundVolume)
};

// AActor::execSetSwitch
void AActor::execSetSwitch(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(Switch);
    P_FINISH;

    UAudioSubsystem *Audio = GetLevel()->Engine->Audio;
    if (Audio) {
        Audio->SetSwitch(Switch);
    }
}

// AActor::execSetSoundVolume
void AActor::execSetSoundVolume(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Volume);
    P_FINISH;

    UAudioSubsystem *Audio = GetLevel()->Engine->Audio;
    if (Audio) {
        Audio->SetSoundVolume(Volume);
    }
}
