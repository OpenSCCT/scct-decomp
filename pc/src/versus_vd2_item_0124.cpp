// Work item 0124: Versus RVA 0x1fe20-0x200b8 (Core UnName.cpp and a field
// iterator). LTCG functions with link-time register conventions:
//   0x1fe20 TFieldIterator<...>::IterateToNext   (this in ESI)
//   0x1fe80 FName::Hardcode                      (AutoName in ESI)
//   0x1ff70 FName::FName(const TCHAR*,EFindName) (this in EBX, Name in EAX)
//   0x20080 GetLocalizedPackageName              (cdecl, Name on the stack)
#include "versus_build.h"
#include "versus_name_registry.h"

inline void *operator new(unsigned int, void *Mem) { return Mem; }

extern DWORD GCRCTable[256];                    // 0x10c78cd0
inline TCHAR appToUpper(TCHAR c)
{
    return (c < 'a' || c > 'z') ? c : c + 'A' - 'a';
}
// RVA 0x1090f6b0 in retail (Data in EAX); defined only for its link convention.
__declspec(noinline) DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data) {
        TCHAR Ch = appToUpper(*Data++);
        unsigned char B = (unsigned char)Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = (unsigned char)(Ch >> 8);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
    }
    return Hash;
}
// RVA 0x1093b590 in retail (Name in EDI); defined only for its link convention.
__declspec(noinline) FNameEntry *AllocateNameEntry(const TCHAR *Name, DWORD Index, DWORD Flags, FNameEntry *HashNext)
{
    FNameEntry *NameEntry = (FNameEntry *)GMalloc->Malloc(sizeof(FNameEntry) - (64 - wcslen(Name) - 1) * sizeof(TCHAR), L"FNameEntry");
    NameEntry->Index = Index;
    NameEntry->Flags = Flags;
    NameEntry->HashNext = HashNext;
    wcscpy(NameEntry->Name, Name);
    return NameEntry;
}

// UnUnix/UnVcWin32 inline wrapper.
inline INT appStrcmp(const TCHAR *A, const TCHAR *B) { return wcscmp(A, B); }

// RVA 0x1fe80
void FName::Hardcode(FNameEntry *AutoName)
{
    // Expand the table if needed.
    for (INT i = FName_Names.Num(); i <= AutoName->Index; i++)
        FName_Names(FName_Names.AddInline(1)) = 0;

    // A name hardcoded twice: drop the duplicate entry.
    if (FName_Names(AutoName->Index) && appStrcmp(FName_Names(AutoName->Index)->Name, AutoName->Name) == 0) {
        GMalloc->Free(AutoName);
        return;
    }
    FName_Names(AutoName->Index) = AutoName;

    // Add name to name hash.
    INT iHash = appStrihash(AutoName->Name) & 4095;
    AutoName->HashNext = FName_NameHash[iHash];
    FName_NameHash[iHash] = AutoName;
}

// RVA 0x1ff70
FName::FName(const TCHAR *Name, EFindName FindType)
{
    if (!Name[0]) {
        Index = 0;
        return;
    }
    INT iHash = appStrihash(Name) & 4095;
    for (FNameEntry *Hash = FName_NameHash[iHash]; Hash; Hash = Hash->HashNext) {
        if (_wcsicmp(Name, Hash->Name) == 0) {
            Index = Hash->Index;
            if (FindType == FNAME_Intrinsic)
                FName_Names(Index)->Flags |= RF_Native;
            return;
        }
    }
    if (FindType == FNAME_Find) {
        Index = 0;
        return;
    }
    if (FName_Available.Num()) {
        Index = FName_Available(FName_Available.Num() - 1);
        FName_Available.Remove(FName_Available.Num() - 1, 1, sizeof(INT));
    } else {
        Index = FName_Names.Add(1, sizeof(FNameEntry *));
    }
    FName_Names(Index) = FName_NameHash[iHash] = AllocateNameEntry(Name, Index, 0, FName_NameHash[iHash]);
    if (FindType == FNAME_Intrinsic)
        FName_Names(Index)->Flags |= RF_Native;
}

// RVA 0x20080: maps a package name to its localization file name, falling
// back to the name itself. Neutral names (as in item 0098).
struct FLocalizedPackageRemap
{
    INT Name;               // FName index; 0 ends the table
    const TCHAR *FileName;
};
extern FLocalizedPackageRemap GLocalizedPackageRemaps[];   // 0x10c54018

__declspec(noinline) const TCHAR *GetLocalizedPackageName(FName Name)
{
    // NEAR MISS (10 bytes): retail loads Name into ESI before the table
    // pointer; the two-pointer walk itself matches.
    FLocalizedPackageRemap *Remap = GLocalizedPackageRemaps;
    for (FLocalizedPackageRemap *Next = Remap; Next->Name; Remap = ++Next)
        if (Next->Name == Name.Index)
            return Remap->FileName;
    return FName_Names(Name.Index)->Name;
}

// ---- 0x1fe20: field iterator over a class whose static class sits at
// 0x10cc8610 (neutral name: no symbol survives for it) ----
class UClass;
class UStruct;
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
    inline UBOOL IsA(UClass *SomeBase) const;
};
class UField : public UObject
{
public:
    virtual UStruct *GetInheritanceSuper();     // +0x6c
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
    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};
inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return 0;
}
class UnnamedClass_10cc8610 : public UField
{
public:
    static UClass PrivateStaticClass;   // 0x10cc8610
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template<class T> class TFieldIterator
{
public:
    UStruct *Struct;
    UField *Field;
    void IterateToNext()
    {
        while (Struct) {
            while (Field) {
                if (Field->IsA(T::StaticClass()))
                    return;
                Field = Field->Next;
            }
            Struct = Struct->GetInheritanceSuper();
            if (Struct)
                Field = Struct->Children;
        }
    }
};
template class TFieldIterator<UnnamedClass_10cc8610>;

// ---- Scaffolding for the link, not part of the unit ----
void Escape(void *);
void Driver_1fe80(FNameEntry *E) { Escape(&FName_Names); Escape(&FName_NameHash); Escape(&GMalloc); FName::Hardcode(E); }
void Driver_1ff70(FName *Out, const TCHAR *N, EFindName T) { Escape(&FName_Names); Escape(&FName_Available); Escape(&FName_NameHash); new (Out) FName(N, T); }
const TCHAR *Driver_20080(INT N) { Escape(&FName_Names); FName F; F.Index = N; return GetLocalizedPackageName(F); }
void Driver_1fe20(TFieldIterator<UnnamedClass_10cc8610> *It) { It->IterateToNext(); Escape(It); }
