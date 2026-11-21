// Work item 0157: UObject state machine (UnObj.cpp / UnScript.cpp).
// RVA 0x415a0 UObject::GotoState, 0x41790 UObject::GotoLabel,
// 0x41810 UObject::execUndefined.
// Also matched here: 0x4efc0 TFieldIterator<UState,CLASS_IsAUState>::IterateToNext
// (LTCG, this in ESI). GotoState is a near miss: same length, but the compiler
// keeps the later of the two identical "return GOTOSTATE_Preempted" tails where
// retail keeps the earlier one. UState::FindField (retail 0x158d0, another
// object) is a near-miss stand-in so the call site gets retail's convention.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned __int64 QWORD;

#define NULL 0
#pragma pack(push, 4)
#define MAXWORD 0xffff

// Versus name table indices.
enum EName
{
    NAME_None       = 0,
    NAME_BeginState = 0x13c,
    NAME_EndState   = 0x13d,
    NAME_Error      = 0x24d,
    NAME_Auto       = 0x2b2,
};

enum EObjectFlags
{
    RF_StateChanged = 0x00001000,
    RF_InEndState   = 0x00002000,
};

enum EClassCastFlags { CLASS_IsAUState = 0x00040000 };
enum EStateFlags { STATE_Auto = 0x00000002 };

enum EGotoState
{
    GOTOSTATE_NotFound  = 0,
    GOTOSTATE_Success   = 1,
    GOTOSTATE_Preempted = 2,
};

class FName
{
public:
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    UBOOL operator!=(const FName &Other) const { return Index != Other.Index; }
};

template <class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
};

class UObject;
class UField;
class UStruct;
class UState;
class UClass;
class UFunction;

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event);
    virtual void Flush();
    void Logf(EName Event, const TCHAR *Fmt, ...);
};

struct FFrame : public FOutputDevice
{
    UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;
};

struct FStateFrame : public FFrame
{
    FFrame *CurrentFrame;
    UState *StateNode;
    QWORD ProbeMask;
    INT LatentAction;
};

struct FLabelEntry
{
    FName Name;
    INT iCode;
};

class UObject
{
public:
    virtual void Virtual00();
    virtual void Virtual01();
    virtual void Virtual02();
    virtual void Virtual03();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = NULL);

    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;

    DWORD GetFlags() const { return ObjectFlags; }
    void SetFlags(DWORD NewFlags) { ObjectFlags |= NewFlags; }
    void ClearFlags(DWORD NewFlags) { ObjectFlags &= ~NewFlags; }
    FName GetFName() const { return Name; }
    UClass *GetClass() const { return Class; }

    UBOOL IsProbing(FName ProbeName);
    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
    void eventBeginState() { ProcessEvent(FindFunctionChecked(NAME_BeginState), NULL); }
    void eventEndState() { ProcessEvent(FindFunctionChecked(NAME_EndState), NULL); }
    UState *FindState(FName InName);

    EGotoState GotoState(FName NewState);
    UBOOL GotoLabel(FName FindLabel);
    void execUndefined(FFrame &Stack, void *const Result);
};

class UField : public UObject
{
public:
    UField *SuperField;
    UField *Next;
};

class UStruct : public UField
{
public:
    UField *Children;
    INT PropertiesSize;
    FName FriendlyName;
    TArray<BYTE> Script;
    BYTE StructPad[0x68 - 0x48];

    // UObject and UStruct virtuals not used here (slots 5-26).
    virtual void Virtual05();
    virtual void Virtual06();
    virtual void Virtual07();
    virtual void Virtual08();
    virtual void Virtual09();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual UStruct *GetInheritanceSuper(); // slot 27
};

struct FFieldHashEntry
{
    UField *Field;
    INT iNext;
};

// Name hash of the fields a state declares.
class FFieldMap
{
public:
    INT HashCount;
    FFieldHashEntry *Hash;
    inline UField *FindRef(FName Key);
};

class UState : public UStruct
{
public:
    QWORD ProbeMask;
    QWORD IgnoreMask;
    DWORD StateFlags;
    _WORD LabelTableOffset;
    FFieldMap FuncMap;
    UState *GetSuperState() { return (UState *)SuperField; }
    UField *FindField(FFieldMap *Map, FName Name);
};

class UClass : public UState
{
public:
    DWORD ClassCastFlags;
};

template <class T, DWORD TClassCastFlags> class TFieldIterator
{
public:
    TFieldIterator(UStruct *InStruct)
        : Struct(InStruct), Field(InStruct ? InStruct->Children : NULL)
    {
        IterateToNext();
    }
    operator UBOOL() { return Field != NULL; }
    void operator++()
    {
        Field = Field->Next;
        IterateToNext();
    }
    T *operator*() { return (T *)Field; }
    T *operator->() { return (T *)Field; }
    void IterateToNext();

protected:
    UStruct *Struct;
    UField *Field;
};

template <class T, DWORD TClassCastFlags>
void TFieldIterator<T, TClassCastFlags>::IterateToNext()
{
    while (Struct)
    {
        while (Field)
        {
            if (Field->GetClass()->ClassCastFlags & TClassCastFlags)
                return;
            Field = Field->Next;
        }
        Struct = Struct->GetInheritanceSuper();
        if (Struct)
            Field = Struct->Children;
    }
}

inline UField *FFieldMap::FindRef(FName Key)
{
    if (HashCount)
    {
        FFieldHashEntry *Entry = &Hash[Key.Index & (HashCount - 1)];
        for (UField *Field = Entry->Field; Field; Field = Entry->Field)
        {
            if (Field->Name == Key)
                return Field;
            if (!Entry->iNext)
                break;
            Entry = &Hash[Entry->iNext];
        }
    }
    return NULL;
}

// Looks Name up in Map (this state's FuncMap), then in the maps of the
// super states.
UField *UState::FindField(FFieldMap *Map, FName Name)
{
    UState *State = this;
    for (;;)
    {
        UField *Found = Map->FindRef(Name);
        if (Found)
            return Found;
        UState *Super = State->GetSuperState();
        if (!Super)
            return NULL;
        State = Super;
        Map = &Super->FuncMap;
    }
}

inline UState *UObject::FindState(FName InName)
{
    UField *Found = GetClass()->FindField(&GetClass()->FuncMap, InName);
    if (Found && (Found->GetClass()->ClassCastFlags & CLASS_IsAUState))
        return (UState *)Found;
    return NULL;
}

EGotoState UObject::GotoState(FName NewState)
{
    if (StateFrame)
    {
        StateFrame->LatentAction = 0;
        UState *StateNode = NULL;
        FName OldStateName = StateFrame->StateNode != (UState *)Class ? StateFrame->StateNode->GetFName() : FName(NAME_None);
        if (NewState != NAME_Auto)
        {
            // Find regular state.
            StateNode = FindState(NewState);
        }
        else
        {
            // Find auto state.
            for (TFieldIterator<UState, CLASS_IsAUState> It(GetClass()); It && !StateNode; ++It)
                if (It->StateFlags & STATE_Auto)
                    StateNode = *It;
        }
        if (!StateNode)
        {
            // Going nowhere.
            NewState = NAME_None;
            StateNode = GetClass();
        }
        else if (NewState == NAME_Auto)
        {
            // Going to auto state.
            NewState = StateNode->GetFName();
        }

        // Send EndState notification.
        if (OldStateName != NAME_None && NewState != OldStateName && IsProbing(NAME_EndState) && !(GetFlags() & RF_InEndState))
        {
            ClearFlags(RF_StateChanged);
            SetFlags(RF_InEndState);
            eventEndState();
            ClearFlags(RF_InEndState);
            if (GetFlags() & RF_StateChanged)
                return GOTOSTATE_Preempted;
        }

        // Go there.
        StateFrame->Node = StateNode;
        StateFrame->StateNode = StateNode;
        StateFrame->Code = NULL;
        StateFrame->ProbeMask = (GetClass()->ProbeMask | StateNode->ProbeMask) & StateNode->IgnoreMask;

        // Send BeginState notification.
        if (NewState != NAME_None && NewState != OldStateName && IsProbing(NAME_BeginState))
        {
            ClearFlags(RF_StateChanged);
            eventBeginState();
            if (GetFlags() & RF_StateChanged)
                return GOTOSTATE_Preempted;
        }

        // Return result.
        SetFlags(RF_StateChanged);
        return GOTOSTATE_Success;
    }
    return GOTOSTATE_NotFound;
}

UBOOL UObject::GotoLabel(FName FindLabel)
{
    if (StateFrame)
    {
        StateFrame->LatentAction = 0;
        if (FindLabel != NAME_None)
        {
            for (UState *SourceState = StateFrame->StateNode; SourceState; SourceState = SourceState->GetSuperState())
            {
                if (SourceState->LabelTableOffset != MAXWORD)
                {
                    for (FLabelEntry *Label = (FLabelEntry *)&SourceState->Script(SourceState->LabelTableOffset); Label->Name != NAME_None; Label++)
                    {
                        if (Label->Name == FindLabel)
                        {
                            StateFrame->Node = SourceState;
                            StateFrame->Code = &SourceState->Script(Label->iCode);
                            return 1;
                        }
                    }
                }
            }
        }
        StateFrame->Code = NULL;
    }
    return 0;
}

#pragma pack(pop)

extern const TCHAR UnknownCodeToken[]; // L"Unknown code token %02X"

void UObject::execUndefined(FFrame &Stack, void *const Result)
{
    Stack.Logf(NAME_Error, UnknownCodeToken, Stack.Code[-1]);
}

// Scaffolding for the link, not part of the unit: retail reaches GotoState and
// execUndefined through tables (vtable, GNatives), so their addresses are taken.
typedef EGotoState (UObject::*GotoStateFn)(FName);
typedef void (UObject::*NativeFn)(FFrame &, void *const);
extern GotoStateFn KeepGotoState;
extern NativeFn KeepUndefined;
void Driver_415a0() { KeepGotoState = &UObject::GotoState; }
void Driver_41810() { KeepUndefined = &UObject::execUndefined; }

// Scaffolding for the LTCG link, not part of the unit: FOutputDevice::Logf
// (retail 0x11850, UnMisc.cpp) must be compiled with /GL for the linker to
// give it its register convention (this in EBX, Event in EAX).
typedef char *va_list;
extern "C" int _vsnwprintf(TCHAR *, unsigned int, const TCHAR *, va_list);
class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR Logf_Tag[];
struct FNameEntry { INT Index; DWORD Flags; };
extern UBOOL GNamesInitialized;
extern FNameEntry **GNameTable;
extern TCHAR GCmdLine[];
extern const TCHAR Logf_FlushParam[];
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);
UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param)
{
    const TCHAR *Start = Stream;
    if (*Stream)
    {
        while ((Start = appStrfind(Start + 1, Param)) != 0)
        {
            if (Start > Stream && (Start[-1] == '-' || Start[-1] == '/'))
                return 1;
        }
    }
    return 0;
}
void FOutputDevice::Logf(EName Event, const TCHAR *Fmt, ...)
{
    if (!GNamesInitialized || !(GNameTable[Event]->Flags & 0x1000))
    {
        TCHAR *TempStr = (TCHAR *)GMalloc->Malloc(0x10000, Logf_Tag);
        _vsnwprintf(TempStr, 0x8000, Fmt, (va_list)(&Fmt + 1));
        Serialize(TempStr, Event);
        GMalloc->Free(TempStr);
    }
    if (!ParseParam(GCmdLine, Logf_FlushParam))
        Flush();
}
