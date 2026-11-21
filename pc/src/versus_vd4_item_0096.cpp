// Work item 0096: UObject::InitExecution (RVA 0x16590).
// Layout from Unreal Engine 2 UObject: StateFrame at 0xc, ObjectFlags at 0x1c,
// Class at 0x24; RF_HasStack = 0x02000000. LTCG unit: the FStateFrame
// constructor (0x159f0) takes `this` in EAX and the object in ECX.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;
typedef unsigned char BYTE;

// Unreal Core is built with 4-byte packing.
#pragma pack(push, 4)

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size, const TCHAR *Tag)
{
    return GMalloc->Malloc(Size, Tag);
}
inline void operator delete(void *Ptr)
{
    GMalloc->Free(Ptr);
}

// Retail shares this literal; bound as an extern array.
extern const TCHAR ObjectStateFrameTag[];

enum { RF_HasStack = 0x02000000 };

class UObject;
class UClass;
class UStruct;
class UState;

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event);
};

struct FFrame : public FOutputDevice
{
    UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    FFrame(UObject *InObject);
    virtual void Serialize(const TCHAR *V, INT Event);
};

struct FStateFrame : public FFrame
{
    FFrame *CurrentFrame;
    UState *StateNode;
    QWORD ProbeMask;
    INT LatentAction;

    FStateFrame(UObject *InObject);
    virtual void Serialize(const TCHAR *V, INT Event);
};

class UObject
{
public:
    UObject() {}
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    UClass *Class;

    void SetFlags(DWORD NewFlags) { ObjectFlags |= NewFlags; }
    virtual void InitExecution();
};

inline FFrame::FFrame(UObject *InObject)
    : Node(InObject ? (UStruct *)InObject->Class : 0), Object(InObject), Code(0), Locals(0)
{
}

__declspec(noinline) FStateFrame::FStateFrame(UObject *InObject)
    : FFrame(InObject), CurrentFrame(0), StateNode((UState *)InObject->Class), ProbeMask(~(QWORD)0)
{
}

#pragma pack(pop)

void UObject::InitExecution()
{
    if (StateFrame)
        delete StateFrame;
    StateFrame = new(ObjectStateFrameTag) FStateFrame(this);
    SetFlags(RF_HasStack);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
// InitExecution is virtual (vtable slot 14 in retail). Constructing a local
// object emits the vtable, which keeps the function out of line.
// Retail constructs FStateFrame from several callers, so it stays out of line.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_16590(UObject *Obj, FStateFrame *Mem)
{
    Escape(&GMalloc);
    Obj->InitExecution();
    UObject Local;
    Escape(&Local);
    Escape(new (Mem) FStateFrame(Obj));
    Escape(new (Mem + 1) FStateFrame((UObject *)Mem));
    Escape(new (Mem + 2) FStateFrame(Obj + 1));
}
