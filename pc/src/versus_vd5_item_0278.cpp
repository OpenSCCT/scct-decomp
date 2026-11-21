// Work item w3 0278: Versus RVA 0xfcbd0-0xfd0b3.
//
// UInput (vtable 0x10c03dd0, FExec vtable at +0x28 is 0x10c03e60). The unit
// was compiled with /GL and linked with /LTCG: helpers take "this" in EAX
// (0xfd230, 0xfd290) or EBX (0xfd3b0), and FString::operator=(const TCHAR*)
// takes "this" in ESI and the string in EDI. Those helpers are defined here
// (0xfd230/0xfd290/0xfd3b0 are the real neighbours from item 0279) so the
// linker gives them the same conventions. Slot names other than Destroy are
// unknown and named by vtable slot. UInput derives from UObject and FExec
// directly here: with a USubsystem base in between, the FExec vtable store
// is scheduled differently from retail.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short TCHAR;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray();
    ~FArray();
};

template<class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
    void Empty()
    {
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
    void Shrink()
    {
        if (ArrayMax != ArrayNum) {
            ArrayMax = ArrayNum;
            Data = GMalloc->Realloc(Data, ArrayMax * sizeof(T), L"FArray");
        }
    }
};

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString();
    ~FString();
    INT Len() const { return ArrayNum ? ArrayNum - 1 : 0; }
    const TCHAR *operator*() const { return ArrayNum ? Data : L""; }
    FString &operator=(const TCHAR *Other);
    FString &operator=(const FString &Other);
};

// Hard-coded name indices; texts follow UE2 UInput::StaticInitInput where
// the use fits (0x1be "Alias", 0x1bf "Command", 0x1c0 "Aliases", 0x3c2
// "RawKeys", 0x2be.. the input key names) and are otherwise unknown.
enum EName {
    NAME_None = 0, NAME_0xd6 = 0xd6, NAME_Alias = 0x1be, NAME_Command = 0x1bf,
    NAME_Aliases = 0x1c0, NAME_FirstInputKey = 0x2be, NAME_RawKeys = 0x3c2
};
class FName {
public:
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
    UBOOL operator!=(const FName &Other) const { return Index != Other.Index; }
};

class FOutputDevice;
extern FOutputDevice *GError;

// The local archive in StaticInitInput is a plain FArchive; fields after
// ArIsPersistent are named after UE2 where the constructor values fit.
class FArchive {
public:
    virtual ~FArchive() {}
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
    UBOOL ArIsPersistent;
    UBOOL ArForEdit;
    UBOOL ArForClient;
    UBOOL ArForServer;
    UBOOL ArIsError;
    UBOOL ArIsCriticalError;
    INT Unknown34;
    INT Unknown38;
    INT Unknown3c;
    FArchive()
        : ArVer(0xaf), ArNetVer(2000), ArLicenseeVer(0)
        , ArIsLoading(0), ArIsSaving(0), ArIsTrans(0), ArIsPersistent(0)
        , ArForEdit(1), ArForClient(1), ArForServer(1)
        , ArIsError(0), ArIsCriticalError(0)
        , Unknown34(3), Unknown38(0), Unknown3c(-1)
    {}
};

class FExec {
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar) = 0;
};

class UObject;
inline void *operator new(unsigned int, void *P) { return P; }


class UClass;

class UObject {
public:
    INT Index;                // 0x04
    UObject *HashNext;        // 0x08
    void *StateFrame;         // 0x0c
    void *_Linker;            // 0x10
    INT _LinkerIndex;         // 0x14
    UObject *Outer;           // 0x18
    DWORD ObjectFlags;        // 0x1c
    FName Name;               // 0x20
    UClass *Class;            // 0x24

    UObject() {}
    static UObject *StaticFindObject(UClass *ObjectClass, UObject *InObjectPackage, FName A, FName B, FName ObjectName, UBOOL ExactClass);
    static UObject *StaticAllocateObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags, UObject *Template = 0, FOutputDevice *Error = GError, UObject *Ptr = 0, UObject *SubobjectRoot = 0);
    void LoadConfig(UBOOL Propagate = 0, UClass *Class = 0, const TCHAR *Filename = 0);
    UObject *GetOuter() const { return Outer; }
    FName GetFName() const { return Name; }

    virtual ~UObject();                   // 0
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Destroy();               // 9
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
};

class UProperty;

class UField : public UObject {
public:
    UField *SuperField;       // 0x28
    UField *Next;             // 0x2c
    UField(UField *InSuperField) : SuperField(InSuperField) {}
    virtual void AddCppProperty(UProperty *Property);   // 22
    UField *GetOuterUField() const { return (UField *)GetOuter(); }
};

class UStruct : public UField {
public:
    UField *Children;         // 0x30
    INT PropertiesSize;       // 0x34
    FName FriendlyName;       // 0x38
    void *Unknown3c;          // 0x3c
    INT Unknown40;            // 0x40
    BYTE Pad44[0x58 - 0x44];
    void *Unknown58;          // 0x58

    UStruct(UStruct *InSuperStruct)
        : UField(InSuperStruct)
        , PropertiesSize(InSuperStruct ? InSuperStruct->PropertiesSize : 0)
        , FriendlyName(GetFName())
        , Unknown3c(0)
        , Unknown40(0)
        , Unknown58(0)
    {}
    static UClass *StaticClass() { return &PrivateStaticClass; }
    void *operator new(unsigned int, UObject *Outer, FName Name, DWORD Flags = 0)
        { return StaticAllocateObject(StaticClass(), Outer, Name, Flags); }
    static UClass PrivateStaticClass;     // 0x10cc98e8
    void SetPropertiesSize(INT NewSize) { PropertiesSize = NewSize; }

    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Link(FArchive &Ar, UBOOL Props);       // 28 (0x70)
};

class UClass : public UStruct {
public:
    BYTE Pad5c[0xac - 0x5c];
    TArray<BYTE> Defaults;    // 0xac
    BYTE *GetDefaults() { return &Defaults(0); }
    UObject *GetDefaultObject() { return (UObject *)&Defaults(0); }
};

extern class UClass UEnum_PrivateStaticClass;     // 0x10cca108
class UEnum : public UField {
public:
    static UClass *StaticClass() { return &UEnum_PrivateStaticClass; }
    TArray<FName> Names;      // 0x30
};


enum ECppProperty { EC_CppProperty };
enum { RF_Public = 0x4 };
enum { CPF_Config = 0x4000 };

class UProperty : public UField {
public:
    short ArrayDim;           // 0x30
    short ElementSize;        // 0x32
    DWORD PropertyFlags;      // 0x34
    FName Category;           // 0x38
    INT Offset;               // 0x3c
    BYTE Pad40[8];
    UProperty *ConstructorLinkNext;   // 0x48
    UProperty *NextRef;               // 0x4c
    BYTE Pad50[8];

    UProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags);
};

#define DECLARE_PROPERTY_ALLOC(Cls)     static UClass *StaticClass() { return &PrivateStaticClass; }     static UClass PrivateStaticClass;     void *operator new(unsigned int, UObject *Outer, FName Name, DWORD Flags = 0)         { return StaticAllocateObject(StaticClass(), Outer, Name, Flags); }

class UNameProperty : public UProperty {
public:
    DECLARE_PROPERTY_ALLOC(UNameProperty)     // class 0x10cc8ed0
    UNameProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
        : UProperty(EC_CppProperty, InOffset, InCategory, InFlags) {}
};

class UStrProperty : public UProperty {
public:
    DECLARE_PROPERTY_ALLOC(UStrProperty)      // class 0x10cc8fe8
    UStrProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
        : UProperty(EC_CppProperty, InOffset, InCategory, InFlags) {}
};

class UStructProperty : public UProperty {
public:
    UStruct *Struct;          // 0x58
    DECLARE_PROPERTY_ALLOC(UStructProperty)   // class 0x10cc9448
    UStructProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags, UStruct *InStruct)
        : UProperty(EC_CppProperty, InOffset, InCategory, InFlags), Struct(InStruct) {}
};

struct FInputAlias {
    FName Alias;
    FString Command;
    FInputAlias();
    ~FInputAlias();
};

class UInput : public UObject, public FExec {
public:
    FInputAlias Aliases[20];          // 0x02c
    FString Bindings[255];            // 0x16c
    UEnum *InputKeys;                 // 0xd60
    UEnum *InputKeysLoaded;           // 0xd64
    BYTE Pad_d68[0xe6f - 0xd68];
    BYTE Flag_e6f;                    // 0xe6f
    BYTE Flag_e70;                    // 0xe70
    BYTE Flag_e71;                    // 0xe71
    BYTE Flag_e72;                    // 0xe72
    TArray<UObject *> BindingObjects[255];  // 0xe74
    TArray<UObject *> AliasObjects[20];     // 0x1a68
    UBOOL AliasesBuilt;               // 0x1b58

    UInput();
    static UClass *StaticClass() { return &PrivateStaticClass; }
    static UClass PrivateStaticClass;     // 0x10cbd468
    static void StaticInitInput();

    virtual void Destroy();           // 9
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();            // 28 (0x70)
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();            // 32 (0x80)
    virtual void Slot33();            // 33
    virtual void Slot34();
    virtual void ClearBindings();     // 35

    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar);

    void DestroyAliasObjects();       // 0xfd230
    void DestroyBindingObjects();     // 0xfd290
    void BuildBindingObjects();       // 0xfd3b0
};

extern UObject Object_10cbc180;
template<class T> inline T *FindObject(UObject *Outer, FName A, FName B, FName Name, UBOOL ExactClass)
{
    return (T *)UObject::StaticFindObject(T::StaticClass(), Outer, A, B, Name, ExactClass);
}

void __stdcall UInput_InitStatics_fd0c0(UInput *Input);
void __stdcall UInput_BuildAliasObjects_fd2f0(UInput *Input);
void __stdcall UInput_ParseCommands_fd500(UInput *Input, const TCHAR *Cmd, TArray<UObject *> *Out, UBOOL Binding);
// Was a function-local static flag in Slot32.
extern UBOOL UInput_Slot32_Initialized;    // 0x10c92408
extern const TCHAR UInput_EmptyString[];   // 0x10c9240c

FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

// RVA 0x54140 (Core UProperty constructor, published in item 0215). Defined
// here only so the linker gives it the retail convention (this on the stack,
// InFlags in ECX); it is not part of this unit.
#pragma auto_inline(off)
UProperty::UProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
    : UField(0)
    , ArrayDim(1)
    , PropertyFlags(InFlags)
    , Category(InCategory)
    , Offset(InOffset)
    , NextRef(0)
{
    GetOuterUField()->AddCppProperty(this);
}
#pragma auto_inline(on)

// RVA 0xfcbd0 (near: retail also resets the EH state byte to 0 after the
// inlined UStruct constructor and stores SuperField before reading Name; the
// rest of the body lines up instruction for instruction).
void UInput::StaticInitInput()
{
    FArchive ArDummy;

    // Create the alias structure.
    UStruct *AliasStruct = new(StaticClass(), NAME_Alias) UStruct(0);
    AliasStruct->SetPropertiesSize(sizeof(FInputAlias));
    new(AliasStruct, NAME_Alias, RF_Public) UNameProperty(EC_CppProperty, 0, NAME_None, CPF_Config);
    new(AliasStruct, NAME_Command, RF_Public) UStrProperty(EC_CppProperty, sizeof(FName), NAME_None, CPF_Config);
    AliasStruct->Link(ArDummy, 0);

    // Add the aliases.
    UStructProperty *AliasProp = new(StaticClass(), NAME_Aliases, RF_Public)
        UStructProperty(EC_CppProperty, (INT)&((UInput *)0)->Aliases, NAME_Aliases, CPF_Config, AliasStruct);
    AliasProp->ArrayDim = 20;

    // Add the key bindings.
    UEnum *InputKeys = FindObject<UEnum>(&Object_10cbc180, NAME_None, NAME_None, NAME_0xd6, 0);
    for (INT i = 0; i < 255; i++)
        if (InputKeys->Names(i) != NAME_None)
            new(StaticClass(), (EName)(NAME_FirstInputKey + i), RF_Public)
                UStrProperty(EC_CppProperty, (INT)&((UInput *)0)->Bindings[i], NAME_RawKeys, CPF_Config);

    StaticClass()->Link(ArDummy, 0);
    StaticClass()->GetDefaultObject()->LoadConfig(1);
}

// RVA 0xfce40
UInput::UInput()
{
    InputKeysLoaded = FindObject<UEnum>(&Object_10cbc180, NAME_None, NAME_None, NAME_0xd6, 0);
    AliasesBuilt = 0;
    Flag_e6f = 0;
    Flag_e70 = 0;
    Flag_e71 = 0;
    Flag_e72 = 0;
}

// RVA 0xfd230 (item 0279)
void UInput::DestroyAliasObjects()
{
    for (INT i = 0; i < 20; i++) {
        for (INT j = AliasObjects[i].Num() - 1; j >= 0; j--)
            if (AliasObjects[i](j))
                delete AliasObjects[i](j);
        AliasObjects[i].Empty();
    }
}

// RVA 0xfd290 (item 0279)
void UInput::DestroyBindingObjects()
{
    for (INT i = 0; i < 255; i++) {
        for (INT j = BindingObjects[i].Num() - 1; j >= 0; j--)
            if (BindingObjects[i](j))
                delete BindingObjects[i](j);
        BindingObjects[i].Empty();
    }
}

// RVA 0xfd3b0 (item 0279)
void UInput::BuildBindingObjects()
{
    for (INT i = 0; i < 255; i++) {
        if (Bindings[i].Len()) {
            UInput_ParseCommands_fd500(this, Bindings[i].Data, &BindingObjects[i], 1);
            BindingObjects[i].Shrink();
        }
    }
}

// RVA 0xfcf50
void UInput::Destroy()
{
    DestroyAliasObjects();
    DestroyBindingObjects();
    UObject::Destroy();
}

// RVA 0xfcf70
void UInput::Slot32()
{
    if (InputKeys && InputKeys->Names.Data) {
        if (!UInput_Slot32_Initialized) {
            UInput_InitStatics_fd0c0(this);
            UInput_Slot32_Initialized = 1;
        }
        if (!AliasesBuilt)
            UInput_BuildAliasObjects_fd2f0(this);
        DestroyBindingObjects();
        BuildBindingObjects();
        Slot28();
    }
}

// RVA 0xfcfd0
void UInput::Slot33()
{
    UInput *Defaults = (UInput *)Class->GetDefaults();
    for (INT i = 0; i < 20; i++) {
        Aliases[i] = Defaults->Aliases[i];
    }
    for (INT i = 0; i < 255; i++)
        Bindings[i] = Defaults->Bindings[i];
    DestroyAliasObjects();
    DestroyBindingObjects();
    AliasesBuilt = 0;
    Slot32();
}

// RVA 0xfd080
void UInput::ClearBindings()
{
    for (INT i = 0; i < 255; i++)
        if (Bindings[i].Len())
            Bindings[i] = UInput_EmptyString;
}

// Scaffolding for the link, not part of the unit. Destroy and Slot32 are
// reached through the vtable (Driver_fce40 must be a root too); Driver_fcf70
// reaches Slot32 through Slot33's tail call.
void Escape(void *);
void Driver_fcbd0() { Escape(&GError); UInput::StaticInitInput(); }
void Driver_fce40(void *Mem) { Escape(&GMalloc); new (Mem) UInput; }
void Driver_fcf50(UObject *I) { Escape(&GMalloc); I->Destroy(); }
void Driver_fcf70(UInput *I) { Escape(&GMalloc); Escape(&UInput_Slot32_Initialized); I->Slot33(); }
void Driver_fcfd0(UInput *I) { Escape(&GMalloc); I->UInput::Slot33(); }
void Driver_fd080(UInput *I) { Escape(&GMalloc); I->UInput::ClearBindings(); }
