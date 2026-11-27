#ifndef VERSUS_NATIVE_CLASS_INIT_H
#define VERSUS_NATIVE_CLASS_INIT_H

#include "unreal_name.h"
#include "versus_registration_arrays.h"

class FArchive;
class UObject;
class UClass;
class UProperty;
class UStruct;
class UFunction;
class ULinkerLoad;
struct FStateFrame;
struct FScriptDelegate;

struct FGuid {
    DWORD A, B, C, D;

    FGuid() {}
    FGuid(DWORD InA, DWORD InB, DWORD InC, DWORD InD)
        : A(InA), B(InB), C(InC), D(InD) {}
};

enum ENativeConstructor { EC_NativeConstructor };
static const EName NAME_System = (EName)598;
typedef void (UObject::*StaticConstructorType)();

// The package registrar initializes live stock objects before they join the object table.
enum { RF_Native = 0x04000000 };
extern UObject *GAutoRegister;

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result);
    virtual void ProcessDelegate(FName DelegateName, FScriptDelegate *Delegate, void *Parms, void *Result);
    virtual void ProcessState(FLOAT DeltaSeconds);
    virtual void VirtualSlot7();
    virtual void PostLoad();
    virtual void Destroy();
    virtual void Serialize(FArchive &Ar);
    virtual UBOOL IsPendingKill();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void Register();
    virtual void VirtualSlot20();
    virtual void NetDirty(UProperty *Property);

    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;
    ULinkerLoad *Linker;
    // Register() consumes the package name and pending-list link temporarily stored here.
    INT indexInExportMap;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;
    static UClass PrivateStaticClass;

    static TArray<UObject *> GObjRegistrants;
    static void ProcessRegistrants();
    void ConditionalRegister();
    static UBOOL GObjInitialized;
    static FName StaticConfigName()
    {
        return NAME_System;
    }
    void StaticConstructor();

    void InitNative(ENativeConstructor, UClass *InClass, FName InName,
                    FName InPackage, DWORD Flags);
};

class UField : public UObject {
public:
    virtual ~UField();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual INT GetPropertiesSize();

    UField *SuperField;
    UField *Next;

    void InitNative(ENativeConstructor Ctor, UClass *InClass, FName InName,
                    FName InPackage, DWORD Flags, UField *Super);
};

// Script bytecode uses FSArray, whose allocation and growth are tagged by name.
struct FSArray {
    BYTE *Data;
    INT Num;
};

class UStruct : public UField {
public:
    virtual ~UStruct();
    virtual UStruct *GetInheritanceSuper();
    virtual void Link(FArchive &Ar, UBOOL Props);
    virtual void SerializeBin(FArchive &Ar, BYTE *Data, INT MaxReadBytes);
    virtual void VirtualSlot30();
    virtual void DestroyStructData(BYTE *Data);
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();

    UField *Children;
    INT PropertiesSize;
    FName FriendlyName;
    FSArray Script;
    class UTextBuffer *ScriptText;
    UTextBuffer *CppText;
    INT unk_4c;
    INT unk_50;
    UProperty *unk_54;
    UProperty *PropertyLink;
    UProperty *unk_5c;
    UProperty *unk_60;
    UProperty *ConstructorLink;

    void InitNative(ENativeConstructor Ctor, DWORD Size, FName InName,
                    FName InPackage, DWORD Flags, UStruct *Super);
};

struct FFieldHashEntry {
    UField *Field;
    INT Next;
};

struct FFieldHash {
    INT HashCount;
    FFieldHashEntry *Entries;
};

#pragma pack(push, 4)
class UState : public UStruct {
public:
    virtual ~UState();

    unsigned __int64 ProbeMask;
    unsigned __int64 IgnoreMask;
    DWORD StateFlags;
    _WORD LabelTableOffset;
    FFieldHash FieldHash;

    void InitNative(ENativeConstructor Ctor, DWORD Size, FName InName,
                    FName InPackage, DWORD Flags, UStruct *Super);
};

// The array destructors establish the element widths even where their names are open.
struct UnkType_4;
struct UnkType_8;
struct UnkType_C;

class UClass : public UState {
public:
    virtual ~UClass();

    DWORD ClassFlags;
    UClass *ClassWithin;
    FName ClassConfigName;
    TArray<UnkType_8> unk_94;
    TArray<UnkType_4> NetFields;
    TArray<BYTE> Defaults;
    FGuid ClassGuid;
    FString DefaultPropText;
    TArray<UnkType_C> Dependencies;
    TArray<UnkType_4> PackageImports;
    TArray<UnkType_4> unk_ec;
    TArray<UnkType_4> unk_f8;
    void (*ClassConstructor)(void *);
    StaticConstructorType ClassStaticConstructor;
    BYTE unk_10c[8];
    static UClass PrivateStaticClass;

    void InitNative(ENativeConstructor Ctor, DWORD Size, DWORD Flags, UClass *InBaseClass,
                    UClass *InWithinClass, FGuid InGuid, FName InName, FName InPackage,
                    FName InConfigName, DWORD InObjectFlags, void (*InConstructor)(void *),
                    StaticConstructorType InStaticConstructor);
};
#pragma pack(pop)

#endif
