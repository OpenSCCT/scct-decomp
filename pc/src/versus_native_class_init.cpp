#include "versus_build.h"
#include "versus_native_class_init.h"

extern "C" void *__cdecl memcpy(void *Dest, const void *Source, unsigned int Count);

enum EStockClassFlags
{
    CLASS_Compiled = 0x02,
    CLASS_Parsed = 0x10,
    ClassFlag_00400000 = 0x00400000
};

enum ESoftBodyClassName
{
    NAME_ESBChainActor = 26,
    NAME_ESBPatchActor = 27,
    NAME_ESBRopeActor = 28,
    NAME_ESBStripDoorActor = 29,
    NAME_ESBPatch = 30,
    NAME_ESBRope = 31,
    NAME_ESBStripDoor = 32,
    NAME_ESBChain = 33
};

inline void UObject::InitNative(ENativeConstructor, UClass *InClass, FName InName,
                                FName InPackageName, DWORD InFlags)
{
    Index = -1;
    HashNext = 0;
    StateFrame = 0;
    Linker = 0;
    ObjectFlags = InFlags | RF_Native;
    Class = InClass;
    Name = InName;

    // The pending list uses the export index as its link until the registration pass.
    memcpy(&Outer, &InPackageName, sizeof(InPackageName));
    memcpy(&indexInExportMap, &GAutoRegister, sizeof(GAutoRegister));
    GAutoRegister = this;
    if (GObjInitialized && Class == &PrivateStaticClass)
        Register();
}

inline void UField::InitNative(ENativeConstructor, UClass *InClass, FName InName,
                               FName InPackageName, DWORD InFlags, UField *Super)
{
    UObject::InitNative(EC_NativeConstructor, InClass, InName, InPackageName, InFlags);
    SuperField = Super;
    Next = 0;
}

void UStruct::InitNative(ENativeConstructor, DWORD Size, FName InName, FName InPackage,
                         DWORD ObjectFlags, UStruct *Super)
{
    UField::InitNative(EC_NativeConstructor, &UClass::PrivateStaticClass, InName,
                       InPackage, ObjectFlags, Super);
    ScriptText = 0;
    CppText = 0;
    unk_4c = 0;
    unk_50 = 0;
    Children = 0;
    unk_54 = 0;
    PropertyLink = 0;
    unk_5c = 0;
    unk_60 = 0;
    ConstructorLink = 0;
    PropertiesSize = Size;
}

inline void UState::InitNative(ENativeConstructor, DWORD Size, FName InName, FName InPackage,
                               DWORD ObjectFlags, UStruct *Super)
{
    UStruct::InitNative(EC_NativeConstructor, Size, InName, InPackage, ObjectFlags, Super);
    ProbeMask = 0;
    IgnoreMask = 0;
    StateFlags = 0;
    LabelTableOffset = 0;
}

void UClass::InitNative(ENativeConstructor, DWORD Size, DWORD Flags, UClass *InBaseClass,
                        UClass *InWithinClass, FGuid InGuid, FName InName, FName InPackage,
                        FName InClassConfigName, DWORD ObjectFlags, void (*InClassConstructor)(void *),
                        StaticConstructorType InClassStaticConstructor)
{
    UState::InitNative(EC_NativeConstructor, Size, InName, InPackage, ObjectFlags,
                       InBaseClass == this ? 0 : InBaseClass);
    ClassFlags = Flags | CLASS_Compiled | CLASS_Parsed;
    if (InName.Index == NAME_ESBChainActor || InName.Index == NAME_ESBPatchActor ||
        InName.Index == NAME_ESBRopeActor || InName.Index == NAME_ESBStripDoorActor ||
        InName.Index == NAME_ESBChain || InName.Index == NAME_ESBPatch ||
        InName.Index == NAME_ESBRope || InName.Index == NAME_ESBStripDoor)
        ClassFlags |= ClassFlag_00400000;

    ClassGuid = InGuid;
    ClassWithin = InWithinClass;
    ClassConstructor = InClassConstructor;
    ClassStaticConstructor = InClassStaticConstructor;
    ClassConfigName = InClassConfigName;
}
