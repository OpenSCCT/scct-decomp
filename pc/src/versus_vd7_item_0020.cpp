// w4_item_0020.cpp -- Versus AActor::execGetSoundDuration (RVA 0x126440)

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

#define RESULT_DECL void *const Result

class FOutputDevice {
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

#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class USound : public UObject {
public:
    virtual ~USound();
    virtual FLOAT GetDuration();
};

class AActor : public UObject {
public:
    void execGetSoundDuration(FFrame &Stack, RESULT_DECL);
};

// AActor::execGetSoundDuration
void AActor::execGetSoundDuration(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Sound);
    P_FINISH;
    if (Sound) {
        *(FLOAT *)Result = Sound->GetDuration();
    } else {
        *(FLOAT *)Result = 0.0f;
    }
}
