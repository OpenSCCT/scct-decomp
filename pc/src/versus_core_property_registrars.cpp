#include "versus_build.h"
#include "versus_native_properties.h"

class USubsystem : public UObject {};

class UFactory : public UObject {
public:
    BYTE unk_28[8];
    FString Description;
    FString InContextCommand;
    FString OutOfContextCommand;
    TArray<FString> Formats;
    BYTE unk_60[8];

    void StaticConstructor();
};

class USystem : public USubsystem {
public:
    BYTE unk_28[8];
    INT PurgeCacheDays;
    FString SavePath;
    FString CachePath;
    FString CacheExt;
    UBOOL useAlternateTimer;
    TArray<FString> Paths;
    INT Platform;
    TArray<FString> SpecificPackage;
    INT unk_78;
    INT unk_7c;
    INT unk_80;

    void StaticConstructor();
};

typedef char UFactorySizeCheck[sizeof(UFactory) == 0x68 ? 1 : -1];
typedef char USystemSizeCheck[sizeof(USystem) == 0x84 ? 1 : -1];

#define STRUCT_OFFSET(type, member) ((INT)&((type *)0)->member)
static const DWORD RF_Public = 4;
static const DWORD CPF_Config = 0x4000;
static const EName NAME_Formats = (EName)44;
static const EName NAME_StrProperty0 = (EName)45;
static const EName NAME_Description = (EName)46;
static const EName NAME_InContextCommand = (EName)47;
static const EName NAME_OutOfContextCommand = (EName)48;
static const EName NAME_PurgeCacheDays = (EName)49;
static const EName NAME_SavePath = (EName)50;
static const EName NAME_CachePath = (EName)51;
static const EName NAME_CacheExt = (EName)52;
static const EName NAME_Paths = (EName)53;
static const EName NAME_Platform = (EName)54;
static const EName NAME_SpecificPackage = (EName)55;
static const EName NAME_useAlternateTimer = (EName)260;
static const EName NAME_Options = (EName)960;

void UFactory::StaticConstructor()
{
    new (GetClass(), NAME_Description, RF_Public) UStrProperty(EC_CppProperty, STRUCT_OFFSET(UFactory, Description), NAME_None, 0);
    new (GetClass(), NAME_InContextCommand, RF_Public) UStrProperty(EC_CppProperty, STRUCT_OFFSET(UFactory, InContextCommand), NAME_None, 0);
    new (GetClass(), NAME_OutOfContextCommand, RF_Public) UStrProperty(EC_CppProperty, STRUCT_OFFSET(UFactory, OutOfContextCommand), NAME_None, 0);
    UArrayProperty *FormatsProperty = new (GetClass(), NAME_Formats, RF_Public) UArrayProperty(EC_CppProperty, STRUCT_OFFSET(UFactory, Formats), NAME_None, 0);
    FormatsProperty->Inner = new (FormatsProperty, NAME_StrProperty0, RF_Public) UStrProperty;
}

void USystem::StaticConstructor()
{
    new (GetClass(), NAME_PurgeCacheDays, RF_Public) UIntProperty(EC_CppProperty, STRUCT_OFFSET(USystem, PurgeCacheDays), NAME_Options, CPF_Config);
    new (GetClass(), NAME_SavePath, RF_Public) UStrProperty(EC_CppProperty, STRUCT_OFFSET(USystem, SavePath), NAME_Options, CPF_Config);
    new (GetClass(), NAME_CachePath, RF_Public) UStrProperty(EC_CppProperty, STRUCT_OFFSET(USystem, CachePath), NAME_Options, CPF_Config);
    new (GetClass(), NAME_CacheExt, RF_Public) UStrProperty(EC_CppProperty, STRUCT_OFFSET(USystem, CacheExt), NAME_Options, CPF_Config);
    new (GetClass(), NAME_useAlternateTimer, RF_Public) UBoolProperty(EC_CppProperty, STRUCT_OFFSET(USystem, useAlternateTimer), NAME_Options, CPF_Config);
    UArrayProperty *PathsProperty = new (GetClass(), NAME_Paths, RF_Public) UArrayProperty(EC_CppProperty, STRUCT_OFFSET(USystem, Paths), NAME_Options, CPF_Config);
    PathsProperty->Inner = new (PathsProperty, NAME_StrProperty0, RF_Public) UStrProperty;
    new (GetClass(), NAME_Platform, RF_Public) UIntProperty(EC_CppProperty, STRUCT_OFFSET(USystem, Platform), NAME_Options, CPF_Config);
    UArrayProperty *PackageProperty = new (GetClass(), NAME_SpecificPackage, RF_Public) UArrayProperty(EC_CppProperty, STRUCT_OFFSET(USystem, SpecificPackage), NAME_Options, CPF_Config);
    PackageProperty->Inner = new (PackageProperty, NAME_StrProperty0, RF_Public) UStrProperty;
    unk_7c = 0;
    unk_78 = -1;
    unk_80 = -1;
}
