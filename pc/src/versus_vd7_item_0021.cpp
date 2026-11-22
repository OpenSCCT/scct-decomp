// w4_item_0021.cpp -- Versus work item 0021 (RVA 0x126570)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;

struct FGuid;
struct FFrame;

#define RESULT_DECL void *const Result

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
};

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
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

#define P_GET_INT(Var) INT Var = 0; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

// Neutral names: the global at 0x10c923c4 and the subsystem at +0x44 are not yet identified.
class FScriptEventSink {
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
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
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void OnScriptEvent(INT Kind, INT EventId);
};

class FScriptEventHost {
public:
    BYTE              unk_0[0x44];
    FScriptEventSink *EventSink;
};

extern FScriptEventHost *GScriptEventHost;

class AActor : public UObject {
public:
    void execOnScriptEvent(FFrame &Stack, RESULT_DECL);
};

// AActor::execOnScriptEvent (RVA 0x126570)
void AActor::execOnScriptEvent(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(EventId);
    P_FINISH;
    GScriptEventHost->EventSink->OnScriptEvent(4, EventId);
}
