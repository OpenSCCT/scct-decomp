// Work item 0098: Versus RVA 0x16ca0-0x1700c (Core UnObj.cpp, localization loading).
// All three are LTCG functions with link-time register conventions:
//   0x16ca0 LoadLocalizedProp:   Prop in ESI, KeyName in EAX, IntName in ECX, rest on the stack.
//   0x16d30 LoadLocalizedStruct: all arguments on the stack.
//   0x16f70 UObject::LoadLocalized: this in ESI.
// Names follow Unreal Engine 2 (CLASS_Localized 0x20, CPF_Localized 0x8000,
// CLASS_IsAUProperty 0x8000, format strings "%s.%s", "%s.%s[%d]", "%s[%d]").
// Built with try_ltcg.py --root "?Driver_16f70@@YAXPAVUObject@@0@Z" --flags "/O2 /Ob1 /Gy /GF-".
// Status: 0x16ca0 matches. 0x16f70 differs in 2 bytes (retail reuses EDI for
// Outer->Name, we pick EDX). 0x16d30 does not match: retail builds the
// FName(..., FNAME_Add) temporary directly in its argument slot and keeps
// SectionName in EBP; we build it in a frame temporary (only a user copy
// constructor on FName gives the in-place form, and that breaks every other copy).
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { INDEX_NONE = -1 };
enum EName { NAME_None = 0 };
enum EFindName { FNAME_Find = 0, FNAME_Add = 1, FNAME_Intrinsic = 2 };
enum { CLASS_Localized = 0x20, CLASS_IsAUProperty = 0x8000 };
enum { CPF_Localized = 0x8000 };
enum { RF_PerObjectLocalized = 0x100 };   // neutral name; retail tests ObjectFlags & 0x100
enum { RF_Native = 0x4000000 };

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[1];
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
    void Remove(INT Index, INT Count, INT ElementSize);
};

extern FArray FName_Names;               // 0x10cc9e5c: FName::Names (TArray<FNameEntry*>)
extern FArray FName_Available;           // 0x10cc9e68: FName::Available (TArray<INT>)
extern FNameEntry *FName_NameHash[4096]; // 0x10c7d4d8: FName::NameHash

class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const TCHAR *Name, EFindName FindType);
    const TCHAR *operator*() const { return ((FNameEntry **)FName_Names.Data)[Index]->Name; }
    UBOOL operator!=(EName N) const { return Index != N; }
};

class UClass;
class UStruct;
class UField;

class UObject
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26();

    INT Index;              // +0x04
    UObject *HashNext;      // +0x08
    void *StateFrame;       // +0x0c
    void *_Linker;          // +0x10
    INT _LinkerIndex;       // +0x14
    UObject *Outer;         // +0x18
    DWORD ObjectFlags;      // +0x1c
    FName Name;             // +0x20
    UClass *Class;          // +0x24

    const FName GetFName() const { return Name; }

    inline UBOOL IsA(UClass *SomeBase) const;
    void LoadLocalized();
};

class UField : public UObject
{
public:
    virtual UStruct *GetInheritanceSuper();     // +0x6c
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30();
    virtual void Slot31(); virtual void Slot32();
    UField *SuperField;     // +0x28
    UField *Next;           // +0x2c
};

class UStruct : public UField
{
public:
    UField *Children;       // +0x30
};

class UClass : public UStruct
{
public:
    BYTE Pad34[0x88 - 0x34];
    DWORD ClassFlags;       // +0x88
    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

class UProperty : public UField
{
public:
    virtual void ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags);   // +0x84
    short ArrayDim;         // +0x30
    short ElementSize;      // +0x32
    DWORD PropertyFlags;    // +0x34
    FName Category;         // +0x38
    INT Offset;             // +0x3c
};

class UStructProperty : public UProperty
{
public:
    BYTE Pad40[0x58 - 0x40];
    UStruct *Struct;        // +0x58
    static UClass PrivateStaticClass;   // 0x10cc9448
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template <class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

class TFieldIterator_UProperty
{
public:
    UStruct *Struct;
    UField *Field;
    TFieldIterator_UProperty(UStruct *InStruct) : Struct(InStruct), Field(InStruct ? InStruct->Children : 0) { IterateToNext(); }
    operator UBOOL() { return Field != 0; }
    void operator++() { Field = Field->Next; IterateToNext(); }
    UProperty *operator*() { return (UProperty *)Field; }
    void IterateToNext();
};

INT appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);
const TCHAR *Localize(const TCHAR *Section, const TCHAR *Key, const TCHAR *Package, const TCHAR *LangExt, UBOOL Optional);
// RVA 0x20080: maps a package name to the localization file name. Neutral names.
struct FLocalizedPackageRemap
{
    INT Name;               // FName index; 0 ends the table
    const TCHAR *FileName;
};
extern FLocalizedPackageRemap GLocalizedPackageRemaps[];   // 0x10c54018
const TCHAR *GetLocalizedPackageName(FName Name);

// Format strings: retail keeps these TEXT() literals in writable data.
extern const TCHAR LocalizedSectionFmt[];       // 0x10c6fa60 L"%s.%s"
extern const TCHAR LocalizedArrayKeyFmt[];      // 0x10c6fa6c L"%s.%s[%d]"
extern const TCHAR LocalizedKeyFmt[];           // 0x10c6fa80 L"%s.%s"
extern const TCHAR LocalizedArrayFmt[];         // 0x10c6fa8c L"%s[%d]"

// RVA 0x16ca0
void LoadLocalizedProp(UProperty *Prop, const TCHAR *IntName, const TCHAR *KeyName, FName Prefix, FName SectionName, BYTE *Data)
{
    if (Prop->PropertyFlags & CPF_Localized) {
        const TCHAR *Value;
        if (Prefix != NAME_None) {
            TCHAR Section[128];
            appSprintf(Section, LocalizedSectionFmt, Prefix, SectionName);
            Value = Localize(Section, KeyName, IntName, 0, 1);
        } else {
            Value = Localize(*SectionName, KeyName, IntName, 0, 1);
        }
        if (*Value)
            Prop->ImportText(Value, Data, 0);
    }
}

// RVA 0x16d30
void LoadLocalizedStruct(UStruct *Struct, const TCHAR *IntName, FName Prefix, FName SectionName, FName KeyPrefix, BYTE *Data)
{
    for (TFieldIterator_UProperty It(Struct); It; ++It) {
        UProperty *Prop = *It;
        UStruct *SubStruct = 0;
        UBOOL IsStruct = 0;
        if (Prop->IsA(UStructProperty::StaticClass())) {
            IsStruct = 1;
            SubStruct = Cast<UStructProperty>(Prop)->Struct;
        }
        if (!IsStruct && !(Prop->PropertyFlags & CPF_Localized))
            continue;
        for (INT i = 0; i < Prop->ArrayDim; i++) {
            BYTE *PropData = Data + Prop->Offset + i * Prop->ElementSize;
            TCHAR KeyName[128];
            if (KeyPrefix != NAME_None) {
                if (Prop->ArrayDim > 1)
                    appSprintf(KeyName, LocalizedArrayKeyFmt, *KeyPrefix, *Prop->Name, i);
                else
                    appSprintf(KeyName, LocalizedKeyFmt, *KeyPrefix, *Prop->Name);
                LoadLocalizedProp(Prop, IntName, KeyName, Prefix, SectionName, PropData);
            } else if (Prop->ArrayDim > 1) {
                appSprintf(KeyName, LocalizedArrayFmt, *Prop->Name, i);
                LoadLocalizedProp(Prop, IntName, KeyName, Prefix, SectionName, PropData);
            } else if (IsStruct) {
                LoadLocalizedStruct(SubStruct, IntName, Prefix, SectionName, FName(*Prop->Name, FNAME_Add), PropData);
            } else {
                LoadLocalizedProp(Prop, IntName, *Prop->Name, Prefix, SectionName, PropData);
            }
        }
    }
}

// RVA 0x16f70
void UObject::LoadLocalized()
{
    UClass *Cls = Class;
    if (!(Cls->ClassFlags & CLASS_Localized))
        return;
    if (Index != INDEX_NONE && (ObjectFlags & RF_PerObjectLocalized) && Outer->Outer) {
        const TCHAR *IntName = GetLocalizedPackageName(Outer->Outer->Name);
        LoadLocalizedStruct(Cls, IntName, NAME_None, Outer->Name, Name, (BYTE *)this);
    } else {
        const TCHAR *IntName = GetLocalizedPackageName((Index == INDEX_NONE ? Cls->Outer : Outer)->Name);
        FName Section = Index == INDEX_NONE ? Cls->GetFName() : GetFName();
        LoadLocalizedStruct(Cls, IntName, NAME_None, Section, NAME_None, (BYTE *)this);
    }
}

// ---- Callees defined so the link gives them their retail register conventions
// (each is published or bound separately; not part of this unit's match). ----

// RVA 0x20080 (plain stack argument in retail).
const TCHAR *GetLocalizedPackageName(FName Name)
{
    for (FLocalizedPackageRemap *Remap = GLocalizedPackageRemaps; Remap->Name; Remap++)
        if (Remap->Name == Name.Index)
            return Remap->FileName;
    return *Name;
}

// RVA 0x1f850: TFieldIterator<UProperty>::IterateToNext (this in ESI).
void TFieldIterator_UProperty::IterateToNext()
{
    while (Struct) {
        while (Field) {
            if (Field->Class->ClassFlags & CLASS_IsAUProperty)
                return;
            Field = Field->Next;
        }
        Struct = Struct->GetInheritanceSuper();
        if (Struct)
            Field = Struct->Children;
    }
}

class FConfigCache
{
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual const TCHAR *GetStr(const TCHAR *Section, INT Unknown, const TCHAR *Key, const TCHAR *Filename); // +0x0c
};
extern UBOOL GIsStarted;                 // 0x10c96904
extern FConfigCache *GConfig;            // 0x10c946c0
extern TCHAR GLanguage[];                // 0x10c6f868
extern TCHAR GEmptyLocalized[];          // 0x10c92658
extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);

// RVA 0x128b0: Localize (from item 0076; LangExt in EAX, Package in EBX, Key in EDI).
const TCHAR *Localize(const TCHAR *Section, const TCHAR *Key, const TCHAR *Package, const TCHAR *LangExt, UBOOL Optional)
{
    if (!GIsStarted || !GConfig)
        return Key;
    if (!LangExt)
        LangExt = GLanguage;
    TCHAR Filename[256];
    for (;;) {
        appSprintf(Filename, L"%s.%s", Package, LangExt);
        if (const TCHAR *Result = GConfig->GetStr(Section, 0, Key, Filename))
            return Result;
        if (_wcsicmp(LangExt, L"int") == 0)
            break;
        LangExt = L"int";
    }
    return Optional ? GEmptyLocalized : Key;
}

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;                 // 0x10c73bf0
extern DWORD GCRCTable[256];             // 0x10c78cd0
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);

inline TCHAR appToUpper(TCHAR c) { return (c < 'a' || c > 'z') ? c : (TCHAR)(c + 'A' - 'a'); }

// RVA 0xf6b0 (from item 0080).
DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data)
    {
        TCHAR Ch = appToUpper(*Data++);
        BYTE B = (BYTE)Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = (BYTE)(Ch >> 8);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
    }
    return Hash;
}

// RVA 0x3b590: AllocateNameEntry (Name in EDI).
FNameEntry *AllocateNameEntry(const TCHAR *Name, DWORD Index, DWORD Flags, FNameEntry *HashNext)
{
    FNameEntry *NameEntry = (FNameEntry *)GMalloc->Malloc(sizeof(FNameEntry) - sizeof(TCHAR) + (wcslen(Name) + 1) * sizeof(TCHAR), L"NameEntry");
    NameEntry->Index = Index;
    NameEntry->Flags = Flags;
    NameEntry->HashNext = HashNext;
    wcscpy(NameEntry->Name, Name);
    return NameEntry;
}

// RVA 0x1ff70: FName::FName(const TCHAR*, EFindName) (this in EBX, Name in EAX).
FName::FName(const TCHAR *Name, EFindName FindType)
{
    if (!Name[0]) {
        Index = NAME_None;
        return;
    }
    INT iHash = appStrihash(Name) & 4095;
    for (FNameEntry *Hash = FName_NameHash[iHash]; Hash; Hash = Hash->HashNext) {
        if (_wcsicmp(Name, Hash->Name) == 0) {
            Index = Hash->Index;
            if (FindType == FNAME_Intrinsic)
                ((FNameEntry **)FName_Names.Data)[Index]->Flags |= RF_Native;
            return;
        }
    }
    if (FindType == FNAME_Find) {
        Index = NAME_None;
        return;
    }
    if (FName_Available.ArrayNum) {
        Index = ((INT *)FName_Available.Data)[FName_Available.ArrayNum - 1];
        FName_Available.Remove(FName_Available.ArrayNum - 1, 1, 4);
    } else {
        Index = FName_Names.Add(1, 4);
    }
    ((FNameEntry **)FName_Names.Data)[Index] = FName_NameHash[iHash] = AllocateNameEntry(Name, Index, 0, FName_NameHash[iHash]);
    if (FindType == FNAME_Intrinsic)
        ((FNameEntry **)FName_Names.Data)[Index]->Flags |= RF_Native;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_16f70(UObject *A, UObject *B)
{
    Escape(&FName_Names);
    Escape(&GIsStarted);
    Escape(&GConfig);
    Escape((void *)&GetLocalizedPackageName);
    Escape(&GLocalizedPackageRemaps);
    A->ObjectFlags |= 0x20000000;
    if (A->ObjectFlags & RF_PerObjectLocalized)
        A->LoadLocalized();
    B->LoadLocalized();
    FName N(L"x", FNAME_Add);
    Escape(&N);
}
