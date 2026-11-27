// Legacy name-based animation notifications in skeletal and vertex mesh packages.
#include "versus_build.h"
#include "versus_animation_sequence.h"

class UClass;
class FOutputDevice;
extern FOutputDevice *GError;
extern UObject *GObjTransientPkg;
enum { RF_Public = 4, RF_PerObjectLocalized = 0x100, RF_DebugPostLoad = 0x20000000 };
enum { CLASS_Localized = 0x20 };

// Core.Object layout for localized loading and construction in this package.
class UObject {
public:
    virtual DWORD __stdcall QueryInterface(const struct FGuid &, void **);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
    virtual ~UObject();
    virtual void ProcessEvent(class UFunction *, void *, void *);
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void PostLoad();
    INT Index;
    UObject *HashNext;
    class FStateFrame *StateFrame;
    class ULinkerLoad *Linker;
    INT LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;
    const FName GetFName() const { return Name; }
    void LoadLocalized();
    static UObject *StaticAllocateObject(UClass *Class, UObject *Outer, FName Name, DWORD Flags,
                                         UObject *Template, FOutputDevice *Error, UObject *Placement,
                                         UObject *SubobjectRoot);
};
class UField : public UObject {
public:
    UField *SuperField;
    UField *Next;
};
class UStruct : public UField {
public:
    UField *Children;
    BYTE unk_34[0x68-0x34];
};
class UState : public UStruct {
public:
    BYTE unk_68[0x88-0x68];
};
class UClass : public UState {
public:
    DWORD ClassFlags;
    BYTE unk_8c[0x104-0x8c];
    void (*ClassConstructor)(void *);
    BYTE unk_108[0x114-0x108];
};
class UAnimNotify : public UObject {
public:
    BYTE unk_28[4];
};
class UAnimNotify_Script : public UAnimNotify {
public:
    FName NotifyName;
    static UClass PrivateStaticClass;
};

inline UObject *ConstructObject(UClass *Class, UObject *Outer, FName Name, DWORD Flags) {
    if (Outer == (UObject *)-1)
        Outer = GObjTransientPkg;
    UObject *Result = UObject::StaticAllocateObject(Class, Outer, Name, Flags, 0, GError, 0, 0);
    if (Result)
        Class->ClassConstructor(Result);
    return Result;
}

void FMeshAnimSeq::UpdateOldNotifies(UObject *Outer)
{
    for (INT i = 0; i < Notifys.Num(); ++i) {
        if (Notifys(i).Function != NAME_None) {
            UAnimNotify_Script *notify = (UAnimNotify_Script *)ConstructObject(
                &UAnimNotify_Script::PrivateStaticClass, Outer, NAME_None, RF_Public);
            notify->NotifyName = Notifys(i).Function;
            Notifys(i).NotifyObject = notify;
            Notifys(i).Function = NAME_None;
        }
    }
}

const TCHAR *GetLocalizedPackageName(FName Name);
void LoadLocalizedStruct(UStruct *Type, const TCHAR *PackageName, FName Prefix,
                         FName SectionName, FName KeyPrefix, BYTE *Data);
void UObject::LoadLocalized()
{
    UClass *Cls = Class;
    if (!(Cls->ClassFlags & CLASS_Localized))
        return;
    if (Index != -1 && (ObjectFlags & RF_PerObjectLocalized) && Outer->Outer) {
        UObject *SectionOuter = Outer;
        const TCHAR *IntName = GetLocalizedPackageName(SectionOuter->Outer->GetFName());
        FName Section = SectionOuter->GetFName();
        LoadLocalizedStruct(Cls, IntName, NAME_None, Section, GetFName(), (BYTE *)this);
    } else {
        const TCHAR *IntName = GetLocalizedPackageName((Index == -1 ? Cls->Outer : Outer)->GetFName());
        FName Section = Index == -1 ? Cls->GetFName() : GetFName();
        LoadLocalizedStruct(Cls, IntName, NAME_None, Section, NAME_None, (BYTE *)this);
    }
}

inline void UObject::PostLoad()
{
    ObjectFlags |= RF_DebugPostLoad;
    if (ObjectFlags & RF_PerObjectLocalized)
        LoadLocalized();
}

class UMeshAnimation : public UObject {
public:
    virtual ~UMeshAnimation();
    INT InternalVersion;
    TArray<struct FNamedBone> RefBones;
    TArray<struct MotionChunk> Moves;
    TArray<FMeshAnimSeq> AnimSeqs;
    virtual void PostLoad();
};

void UMeshAnimation::PostLoad()
{
    UObject::PostLoad();
    for (INT i = 0; i < AnimSeqs.Num(); ++i)
        AnimSeqs(i).UpdateOldNotifies(Outer);
}
class UPrimitive : public UObject {
public:
    BYTE unk_28[0x50-0x28];
};
class UMesh : public UPrimitive {
public:
    class UMeshInstance *DefaultInstance;  // +0x50
};
class ULodMesh : public UMesh {
public:
    BYTE unk_54[0xf4-0x54];
};
class UVertMesh : public ULodMesh {
public:
    BYTE unk_f4[0x118-0xf4];
    TArray<FMeshAnimSeq> AnimSeqs;
    virtual void PostLoad();
};

void UVertMesh::PostLoad()
{
    UObject::PostLoad();
    for (INT i = 0; i < AnimSeqs.Num(); ++i)
        AnimSeqs(i).UpdateOldNotifies(Outer);
}

// Complete Versus name-table record. The shared FNameEntry declaration contains its prefix.
struct FStoredNameEntry {
    FNameEntry Header;
    FStoredNameEntry *HashNext;
    TCHAR Name[1];
};
extern TArray<FStoredNameEntry *> FName_Names;

struct FLocalizedPackageRemap {
    INT Name;
    const TCHAR *FileName;
};
extern FLocalizedPackageRemap GLocalizedPackageRemaps[];

const TCHAR *GetLocalizedPackageName(FName Name)
{
    for (FLocalizedPackageRemap *Remap = GLocalizedPackageRemaps; Remap->Name; ++Remap)
        if (Remap->Name == Name.Index)
            return Remap->FileName;
    return FName_Names(Name.Index)->Name;
}
