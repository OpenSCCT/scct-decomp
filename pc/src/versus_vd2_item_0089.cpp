// Work item 0089: Versus RVA 0x15650 and 0x15730.
// 0x15650 is the destructor of an unnamed UObject-derived class (vtable 0x10c0d0b8)
// holding four TArrays and two 16-element FString arrays.
// 0x15730 is a script event thunk: it copies a TArray into the event parameters and
// runs ProcessEvent on the function named by FName index 0x214.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray {
public:
    TArray() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    ~TArray();
    TArray &operator=(const TArray &Other);
};

class FString : public TArray<TCHAR> {
public:
    ~FString();
};

enum EName { NAME_Unnamed_214 = 0x214 }; // event name index; real name not recovered

class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

class UFunction;

class UObject {
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    void *Class;
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
    INT ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

// Parent class whose destructor lives at RVA 0x15ee0 (name not recovered).
class UnnamedBase_15ee0 : public UObject {
public:
    virtual ~UnnamedBase_15ee0();
};

// Name not recovered; vtable 0x10c0d0b8.
class UnnamedClass_15650 : public UnnamedBase_15ee0 {
public:
    TArray<INT> ArrayA;     // 0x28
    TArray<INT> ArrayB;     // 0x34
    TArray<INT> ArrayC;     // 0x40
    TArray<INT> ArrayD;     // 0x4c
    FString StringsA[16];   // 0x58
    FString StringsB[16];   // 0x118
    virtual ~UnnamedClass_15650();
    INT eventUnnamed_15730(const TArray<INT> &Items);
};

UnnamedClass_15650::~UnnamedClass_15650()
{
    ConditionalDestroy();
}

INT UnnamedClass_15650::eventUnnamed_15730(const TArray<INT> &Items)
{
    struct UnnamedClass_15650_eventUnnamed_15730_Parms {
        TArray<INT> Items;
        INT ReturnValue;
    } Parms;
    Parms.Items = Items;
    ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_214)), &Parms);
    return Parms.ReturnValue;
}
