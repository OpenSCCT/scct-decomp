// Work item 0135: UAnimNotify_* Notify handlers and a 0x90-element TArray.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

enum EName { NAME_None = 0, ENGINE_Notify = 0x1669 };

struct FName
{
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
    UBOOL operator!=(EName Other) const { return Index != Other; }
    const TCHAR *operator*() const;
};

// FName::Names entries carry the text at +0xc.
struct FNameEntry
{
    INT Pad[3];
    TCHAR Name[64];
};
// FName::Names, a TArray<FNameEntry*> (0x10cc9e5c).
struct FNameEntryArray
{
    FNameEntry **Data;
    INT ArrayNum;
    INT ArrayMax;
    FNameEntry *&operator()(INT i) { return Data[i]; }
};
extern FNameEntryArray FName_Names;
inline const TCHAR *FName::operator*() const { return FName_Names(Index)->Name; }

struct FVector { FLOAT X, Y, Z; };

class UObject;
class UFunction;
class USound;
class AActor;
class UMeshInstance;

class UObject
{
public:
    virtual ~UObject();
    virtual void VSlot1();
    virtual void VSlot2();
    virtual void VSlot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    virtual void ProcessDelegate(FName DelegateName, void *Delegate, void *Parms, void *Result = 0);
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
    UFunction *FindFunction(FName InName);
    INT Index;                 // +0x04
    INT HashNext;              // +0x08
    struct FStateFrame *StateFrame; // +0x0c
    INT Linker;                // +0x10
    INT LinkerIndex;           // +0x14
    UObject *Outer;            // +0x18
    DWORD ObjectFlags;         // +0x1c
    FName Name;                // +0x20
    class UClass *Class;       // +0x24
    INT Pad28;                 // +0x28
};

// Name-keyed hash of a struct's fields: entries are {field, next index}.
struct FFieldHashEntry
{
    UObject *Field;
    INT Next;
};
struct FFieldHash
{
    INT HashCount;
    FFieldHashEntry *Entries;
};

class UField : public UObject
{
public:
    UField *Next;              // +0x2c
};

class UStruct : public UField
{
public:
    UField *Children;          // +0x30
    char Pad34[0x80 - 0x34];
    FFieldHash FieldHash;      // +0x80
    UStruct *GetSuperStruct() { return (UStruct *)Pad28; }
};

class UClass : public UStruct
{
public:
    DWORD ClassCastFlags;      // +0x88
};
enum { CASTCLASS_UFunction = 0x80000 };

class UFunction : public UField
{
public:
    char Pad30[0x68 - 0x30];
    DWORD FunctionFlags;       // +0x68
};
enum { FUNC_Delegate = 0x100000 };

class UProperty : public UField
{
public:
    char Pad30[0x3c - 0x30];
    INT Offset;                // +0x3c
};
class UDelegateProperty : public UProperty {};

struct FStateFrame
{
    INT Pad[6];
    UStruct *StateNode;        // +0x18
};

class UAudioSubsystem
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual UBOOL PlaySound(AActor *Actor, INT Id, USound *Sound, const FVector &Location,
                            FLOAT Volume, FLOAT Radius, FLOAT Pitch, INT Flags, INT Unk1, INT Unk2, INT Bone);
    virtual void StopSound(AActor *Actor, USound *Sound);
};

class UEngine
{
public:
    char Pad[0x34];
    UAudioSubsystem *Audio;
};

class ULevel
{
public:
    char Pad[0xf0];
    UEngine *Engine;
};

class AActor : public UObject
{
public:
    char Pad0[0x80 - 0x2c];
    FVector Location;
    char Pad1[0x1a4 - 0x8c];
    ULevel *XLevel;
};

class UMeshInstance : public UObject
{
public:
    INT MatchRefBone(FName BoneName);
};

// Global default sound radius (0x10c71b00).
extern FLOAT GAudioDefaultRadius;

class UAnimNotify : public UObject
{
public:
    virtual void Notify(UMeshInstance *Instance, AActor *Owner);
};

class UAnimNotify_Sound : public UAnimNotify
{
public:
    USound *Sound;   // 0x2c
    FLOAT Volume;    // 0x30
    INT Radius;      // 0x34
    FName Bone;      // 0x38
    void Notify(UMeshInstance *Instance, AActor *Owner);
};

void UAnimNotify_Sound::Notify(UMeshInstance *Instance, AActor *Owner)
{
    INT BoneIndex = Bone.GetIndex() ? Instance->MatchRefBone(Bone) : -1;
    if (Sound && Owner && Owner->XLevel->Engine->Audio)
    {
        Owner->XLevel->Engine->Audio->PlaySound(Owner, 0, Sound, Owner->Location, Volume,
            Radius ? (FLOAT)Radius : GAudioDefaultRadius, 1.0f, 0, 0, 0, BoneIndex);
    }
}

class UAnimNotify_StopSound : public UAnimNotify
{
public:
    USound *Sound;   // 0x2c
    void Notify(UMeshInstance *Instance, AActor *Owner);
};

void UAnimNotify_StopSound::Notify(UMeshInstance *Instance, AActor *Owner)
{
    if (Sound && Owner && Owner->XLevel->Engine->Audio)
        Owner->XLevel->Engine->Audio->StopSound(Owner, Sound);
}

class UAnimNotify_Scripted : public UAnimNotify
{
public:
    void eventNotify(AActor *Owner)
    {
        struct { AActor *Owner; } Parms;
        Parms.Owner = Owner;
        ProcessEvent(FindFunctionChecked(ENGINE_Notify), &Parms);
    }
    void Notify(UMeshInstance *Instance, AActor *Owner);
};

void UAnimNotify_Scripted::Notify(UMeshInstance *Instance, AActor *Owner)
{
    eventNotify(Owner);
}

// ---------------------------------------------------------------------------
// RVA 0xc0b90: UAnimNotify_Script::Notify (link-time-optimised object: its
// callees FindFieldInHash and FindField<UDelegateProperty> take arguments in
// registers).

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FString();                                    // RVA 0x48b0
    static FString Printf(const TCHAR *Fmt, ...);  // RVA 0x11b20
    const TCHAR *operator*() const { return ArrayNum ? Data : L""; }
};

// Imported (slot 0x10bdf3a0).
__declspec(dllimport) INT appStricmp(const TCHAR *A, const TCHAR *B);
// Text "__%s__Delegate" (retail keeps it in writable data).
extern const TCHAR DelegateNameFormat[];

// RVA 0x158d0 (published unit versus_vd2_item_0091.cpp).
UObject *__stdcall FindFieldInHash(UStruct *Struct, FFieldHash *Hash, FName InName)
{
    for (;;) {
        if (Hash->HashCount) {
            FFieldHashEntry *Entry = &Hash->Entries[(Hash->HashCount - 1) & InName.GetIndex()];
            for (UObject *Field = Entry->Field; Field; Field = Entry->Field) {
                if (Field->Name.Index == InName.Index)
                    return Field;
                if (!Entry->Next)
                    break;
                Entry = &Hash->Entries[Entry->Next];
            }
        }
        UStruct *Super = (UStruct *)Struct->Pad28;
        if (!Super)
            return 0;
        Struct = Super;
        Hash = &Struct->FieldHash;
    }
}

template <class T> class TFieldIterator
{
public:
    TFieldIterator(UStruct *InStruct) : Struct(InStruct), Field(InStruct ? InStruct->Children : 0) { IterateToNext(); }
    operator UBOOL() { return Field != 0; }
    void operator++() { Field = Field->Next; IterateToNext(); }
    T *operator->() { return (T *)Field; }
    T *operator*() { return (T *)Field; }
    __declspec(noinline) void IterateToNext()      // RVA 0xc2380
    {
        while (Struct) {
            while (Field) {
                if (Field->Class->ClassCastFlags & 0x4000)
                    return;
                Field = Field->Next;
            }
            Struct = (UStruct *)Struct->Pad28;
            if (Struct)
                Field = Struct->Children;
        }
    }
    UStruct *Struct;
    UField *Field;
};

// RVA 0xc2150.
template <class T> __declspec(noinline) T *FindField(UStruct *Owner, const TCHAR *FieldName)
{
    for (TFieldIterator<T> It(Owner); It; ++It)
        if (appStricmp(*It->Name, FieldName) == 0)
            return *It;
    return 0;
}

class UAnimNotify_Script : public UAnimNotify
{
public:
    FName NotifyName;   // 0x2c
    void Notify(UMeshInstance *Instance, AActor *Owner);
};

template <class T> inline T *Cast(UObject *Src)
{
    return Src && (Src->Class->ClassCastFlags & CASTCLASS_UFunction) ? (T *)Src : 0;
}

inline UFunction *UObject::FindFunction(FName InName)
{
    UObject *Found = 0;
    if (StateFrame && StateFrame->StateNode)
        Found = FindFieldInHash(StateFrame->StateNode, &StateFrame->StateNode->FieldHash, InName);
    if (!Found)
        Found = FindFieldInHash(Class, &Class->FieldHash, InName);
    return Cast<UFunction>(Found);
}

__declspec(noinline) void UAnimNotify_Script::Notify(UMeshInstance *Instance, AActor *Owner)
{
    if (NotifyName != NAME_None)
    {
        UFunction *Function = Owner->FindFunction(NotifyName);
        if (Function)
        {
            if (Function->FunctionFlags & FUNC_Delegate)
            {
                UDelegateProperty *DelegateProperty = FindField<UDelegateProperty>(Owner->Class,
                    *FString::Printf(DelegateNameFormat, *NotifyName));
                void *ScriptDelegate = (BYTE *)Owner + DelegateProperty->Offset;
                Owner->ProcessDelegate(NotifyName, ScriptDelegate, 0, 0);
            }
            else
            {
                Owner->ProcessEvent(Function, 0, 0);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// Link-time-optimised array helpers (0xc0ce0, 0xc0d50).

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);   // RVA 0x119c0
    void Realloc(INT ElementSize)
    {
        Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, L"FArray");
    }
    void Shrink(INT ElementSize)
    {
        if (ArrayMax != ArrayNum)
        {
            ArrayMax = ArrayNum;
            Realloc(ElementSize);
        }
    }
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    __declspec(noinline) ~TArray() { Remove(0, ArrayNum); }
    __declspec(noinline) void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    __declspec(noinline) void Shrink() { FArray::Shrink(sizeof(T)); }
};

// 0x28-byte element whose destructor is retail 0xc39d0 (name unknown).
struct UnnamedElement_c39d0
{
    INT Pad[10];
    ~UnnamedElement_c39d0();
};

// 0x90-byte element (name unknown).
struct UnnamedElement_90
{
    INT Pad[0x24];
};

// RVA 0xc0ce0: TArray<UnnamedElement_c39d0>::~TArray (this on the stack).
template class TArray<UnnamedElement_c39d0>;
// RVA 0xc0d50: TArray<UnnamedElement_90>::Shrink (this in ESI).
template class TArray<UnnamedElement_90>;

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_c0d50(TArray<UnnamedElement_90> *A)
{
    Escape(&GMalloc);
    A->Shrink();
}
void *operator new(unsigned int Size);
void Driver_c0b90()
{
    Escape(&FName_Names);
    // Retail reaches Notify only through the vtable; building an object emits it.
    Escape(new UAnimNotify_Script);
}
void Driver_c0ce0(TArray<UnnamedElement_c39d0> *A)
{
    Escape(&GMalloc);
    A->~TArray();
}
