#include "versus_build.h"
#include "versus_native_properties.h"

#include "versus_archive.h"

inline UNameProperty::UNameProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
    : UProperty(EC_CppProperty, InOffset, InCategory, InFlags)
{}

class USubsystem : public UObject {};
class FExec { public: virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar) = 0; };
class UInteractions : public UObject { public: static UClass PrivateStaticClass; };

struct FInputAlias {
    FName Alias;
    FString Command;
};

// RegisterEngineClasses initializes this stock UClass in place. The Core class
// record gives its 0x114-byte extent, and the shutdown table uses this C symbol.
template <class T> union FNativeClassStorage {
    DWORD Alignment;
    BYTE Bytes[sizeof(T)];
};

extern "C" { FNativeClassStorage<UClass> class_object_UInput; }
typedef char UClassStorageSizeCheck[sizeof(class_object_UInput) == 0x114 ? 1 : -1];
typedef char UClassStorageAlignmentCheck[__alignof(FNativeClassStorage<UClass>) == __alignof(UClass) ? 1 : -1];

class UInput : public USubsystem, public FExec {
public:
    enum { AliasCount = 20, KeyCount = 255 };
    FInputAlias Aliases[AliasCount];
    FString Bindings[KeyCount];
    BYTE unk_d60[0x1b5c - 0xd60];

    static UClass *StaticClass() { return reinterpret_cast<UClass *>(&class_object_UInput); }
    static void StaticInitInput();
};

typedef char UInputSizeCheck[sizeof(UInput) == 0x1b5c ? 1 : -1];

static const DWORD RF_Public = 4;
static const DWORD CPF_Config = 0x4000;
#define STRUCT_OFFSET(type, member) ((INT)&((type *)0)->member)

static const EName NAME_EInputKey = (EName)214;
static const EName NAME_Alias = (EName)446;
static const EName NAME_Command = (EName)447;
static const EName NAME_Aliases = (EName)448;
static const EName NAME_IK_None = (EName)702;
static const EName NAME_RawKeys = (EName)962;

template <class T>
inline T *FindObject(UObject *Outer, FName Package, FName Group, FName Name, UBOOL ExactClass)
{
    return static_cast<T *>(UObject::StaticFindObject(&T::PrivateStaticClass, Outer,
        Package, Group, Name, ExactClass));
}

void UInput::StaticInitInput()
{
    FArchive Ar;
    UStruct *AliasStruct = new(StaticClass(), NAME_Alias) UStruct(0);
    AliasStruct->PropertiesSize = sizeof(FInputAlias);
    new(AliasStruct, NAME_Alias, RF_Public) UNameProperty(
        EC_CppProperty, STRUCT_OFFSET(FInputAlias, Alias), NAME_None, CPF_Config);
    new(AliasStruct, NAME_Command, RF_Public) UStrProperty(
        EC_CppProperty, STRUCT_OFFSET(FInputAlias, Command), NAME_None, CPF_Config);
    AliasStruct->Link(Ar, 0);

    UStructProperty *AliasesProperty = new(StaticClass(), NAME_Aliases, RF_Public)
        UStructProperty(EC_CppProperty, STRUCT_OFFSET(UInput, Aliases), NAME_Aliases,
                        CPF_Config, AliasStruct);
    AliasesProperty->ArrayDim = AliasCount;

    UEnum *InputKeys = FindObject<UEnum>(&UInteractions::PrivateStaticClass, NAME_None,
        NAME_None, NAME_EInputKey, 0);
    for (INT Index = 0; Index < KeyCount; ++Index)
        if (InputKeys->Names(Index) != NAME_None)
            new(StaticClass(), (EName)(NAME_IK_None + Index), RF_Public)
                UStrProperty(EC_CppProperty, STRUCT_OFFSET(UInput, Bindings[Index]),
                             NAME_RawKeys, CPF_Config);
    StaticClass()->Link(Ar, 0);
    StaticClass()->GetDefaultObject()->LoadConfig(1);
}
