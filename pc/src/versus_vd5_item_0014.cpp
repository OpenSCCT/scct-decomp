// Work item w3 0014: Versus RVA 0x3f530, the static-link registration of the
// Core package's native classes (one IMPLEMENT_CLASS-style in-place UClass
// construction per class), followed by filling a 256-entry byte table.
// Called directly from start-up code at 0xad8b.
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned char BYTE;

enum ENativeConstructor { EC_NativeConstructor };

// Hard-coded name indices (EName). Values from the retail pushes; names follow
// UE2's UnNames.h where the class evidence supports them.
enum EName
{
    NAME_ByteProperty       = 1,
    NAME_IntProperty        = 2,
    NAME_BoolProperty       = 3,
    NAME_FloatProperty      = 4,
    NAME_ObjectProperty     = 5,
    NAME_NameProperty       = 6,
    NAME_Property7          = 7,    // StringProperty/DelegateProperty slot
    NAME_ClassProperty      = 8,
    NAME_ArrayProperty      = 9,
    NAME_StructProperty     = 10,
    NAME_StrProperty        = 13,
    NAME_MapProperty        = 14,
    NAME_FixedArrayProperty = 15,
    NAME_Name13             = 0x13,
    NAME_Core               = 0x14,
    NAME_Name22             = 0x22,
    NAME_Name23             = 0x23,
    NAME_ObjectExporterT3D  = 0x24,
    NAME_Struct             = 0x56,
    NAME_State              = 0x66,
    NAME_Function           = 0x67,
    NAME_Enum               = 0x75,
    NAME_Field              = 0x96,
    NAME_Object             = 0x97,
    NAME_TextBuffer         = 0x98,
    NAME_Linker             = 0x99,
    NAME_LinkerLoad         = 0x9a,
    NAME_LinkerSave         = 0x9b,
    NAME_Subsystem          = 0x9c,
    NAME_Factory            = 0x9d,
    NAME_TextBufferFactory  = 0x9e,
    NAME_Exporter           = 0x9f,
    NAME_Property           = 0xa1,
    NAME_System             = 0x256,
    NAME_Const              = 0x281,
    NAME_Package            = 0x2a2,
    NAME_Class              = 0x2a5,
};

struct FName
{
    INT Index;
    FName(EName N) : Index(N) {}
};

struct FGuid
{
    DWORD A, B, C, D;
    FGuid(DWORD InA, DWORD InB, DWORD InC, DWORD InD) : A(InA), B(InB), C(InC), D(InD) {}
};

class UObject;
typedef void (UObject::*StaticConstructorType)();

class UClass
{
public:
    UClass(ENativeConstructor, DWORD InSize, DWORD InClassFlags, UClass *InBaseClass, UClass *InWithinClass,
           FGuid InGuid, FName InNameString, FName InPackageName, FName InClassConfigName, DWORD InFlags,
           void (*InClassConstructor)(void *), StaticConstructorType InClassStaticConstructor);
    BYTE Pad[0x118];
};

#define RF_Native_Flags 0x4084004

class UObject
{
public:
    static UClass PrivateStaticClass;
    static FName StaticConfigName() { return NAME_System; }
    static void InternalConstructor(void *X);
    void StaticConstructor();
};

// Each native class: its static UClass, its InternalConstructor (placement
// new helper) and, where it has its own, a StaticConstructor.
#define DECLARE_NATIVE(TClass, TSuper) \
    class TClass : public TSuper \
    { \
    public: \
        static UClass PrivateStaticClass; \
        static void InternalConstructor(void *X); \
        void StaticConstructor(); \
    };

// Classes whose names are not supported by the evidence keep neutral names.
DECLARE_NATIVE(UExporter, UObject)
DECLARE_NATIVE(UField, UObject)
DECLARE_NATIVE(UStruct, UField)
DECLARE_NATIVE(UConst, UField)
DECLARE_NATIVE(UnnamedClass_10cc83e0, UObject)
DECLARE_NATIVE(UTextBuffer, UObject)
DECLARE_NATIVE(UEnum, UField)
DECLARE_NATIVE(ULinker, UObject)
DECLARE_NATIVE(ULinkerLoad, ULinker)
DECLARE_NATIVE(ULinkerSave, ULinker)
DECLARE_NATIVE(USubsystem, UObject)
DECLARE_NATIVE(UnnamedClass_10cca680, UObject)
DECLARE_NATIVE(UPackage, UObject)
DECLARE_NATIVE(UFactory, UObject)
DECLARE_NATIVE(UTextBufferFactory, UFactory)
DECLARE_NATIVE(UnnamedClass_10cca9c8, UObject)
DECLARE_NATIVE(UProperty, UField)
DECLARE_NATIVE(UByteProperty, UProperty)
DECLARE_NATIVE(UIntProperty, UProperty)
DECLARE_NATIVE(UnnamedProperty_10cc8958, UProperty)
DECLARE_NATIVE(UBoolProperty, UProperty)
DECLARE_NATIVE(UFloatProperty, UProperty)
DECLARE_NATIVE(UObjectProperty, UProperty)
DECLARE_NATIVE(UClassProperty, UObjectProperty)
DECLARE_NATIVE(UNameProperty, UProperty)
DECLARE_NATIVE(UStrProperty, UProperty)
DECLARE_NATIVE(UFixedArrayProperty, UProperty)
DECLARE_NATIVE(UArrayProperty, UProperty)
DECLARE_NATIVE(UMapProperty, UProperty)
DECLARE_NATIVE(UStructProperty, UProperty)
DECLARE_NATIVE(USystem, USubsystem)
DECLARE_NATIVE(UState, UStruct)
DECLARE_NATIVE(UClassClass, UState)          // the UClass class itself
DECLARE_NATIVE(UFunction, UStruct)
DECLARE_NATIVE(UObjectExporterT3D, UExporter)

inline void *operator new(unsigned int, void *Mem) { return Mem; }

// Static-link class registration: the executable constructs each native
// class's static UClass in place, package by package, from its start-up code
// (called at 0xad8b next to the other packages' registrants). Sizes are the
// retail sizeof values.
#define IMPLEMENT_NATIVE(TClass, Size, Flags, TBase, TWithin, Name, TStatic) \
    new(&TClass::PrivateStaticClass) UClass(EC_NativeConstructor, Size, Flags, \
        &TBase::PrivateStaticClass, &TWithin::PrivateStaticClass, FGuid(0, 0, 0, 0), \
        Name, NAME_Core, TClass::StaticConfigName(), RF_Native_Flags, TClass::InternalConstructor, \
        (StaticConstructorType)&TStatic::StaticConstructor);

// 256-entry byte table filled at start-up (0x10c814d8; neutral name).
extern BYTE GByteTable_10c814d8[256];

// Neutral name: no symbol survives for this function.
void RegisterCoreClasses_3f530()
{

    IMPLEMENT_NATIVE(UExporter,               0x40,  0x1,     UObject,          UObject,   NAME_Exporter,          UExporter)
    IMPLEMENT_NATIVE(UConst,                  0x3c,  0x0,     UField,           UStruct,   NAME_Const,             UObject)
    IMPLEMENT_NATIVE(UnnamedClass_10cc83e0,   0x70,  0x8,     UObject,          UObject,   NAME_Name13,            UObject)
    IMPLEMENT_NATIVE(UObject,                 0x28,  0x1,     UObject,          UObject,   NAME_Object,            UObject)
    IMPLEMENT_NATIVE(UTextBuffer,             0x40,  0x0,     UObject,          UObject,   NAME_TextBuffer,        UObject)
    IMPLEMENT_NATIVE(UEnum,                   0x3c,  0x0,     UField,           UStruct,   NAME_Enum,              UObject)
    IMPLEMENT_NATIVE(ULinker,                 0xa4,  0x8,     UObject,          UObject,   NAME_Linker,            UObject)
    IMPLEMENT_NATIVE(ULinkerLoad,             0x4fc, 0x8,     ULinker,          UObject,   NAME_LinkerLoad,        UObject)
    IMPLEMENT_NATIVE(ULinkerSave,             0x100, 0x8,     ULinker,          UObject,   NAME_LinkerSave,        UObject)
    IMPLEMENT_NATIVE(USubsystem,              0x28,  0x9,     UObject,          UObject,   NAME_Subsystem,         UObject)
    IMPLEMENT_NATIVE(UnnamedClass_10cca680,   0x1dc, 0x29,    UObject,          UObject,   NAME_Name22,            UObject)
    IMPLEMENT_NATIVE(UPackage,                0x34,  0x0,     UObject,          UObject,   NAME_Package,           UObject)
    IMPLEMENT_NATIVE(UTextBufferFactory,      0x68,  0x0,     UFactory,         UObject,   NAME_TextBufferFactory, UTextBufferFactory)
    IMPLEMENT_NATIVE(UnnamedClass_10cca9c8,   0x2c,  0x9,     UObject,          UObject,   NAME_Name23,            UObject)
    IMPLEMENT_NATIVE(UProperty,               0x58,  0x8001,  UField,           UField,    NAME_Property,          UObject)
    IMPLEMENT_NATIVE(UByteProperty,           0x5c,  0x8000,  UProperty,        UField,    NAME_ByteProperty,      UObject)
    IMPLEMENT_NATIVE(UIntProperty,            0x58,  0x8000,  UProperty,        UField,    NAME_IntProperty,       UObject)
    IMPLEMENT_NATIVE(UnnamedProperty_10cc8958,0x5c,  0x8000,  UProperty,        UField,    NAME_Property7,         UObject)
    IMPLEMENT_NATIVE(UBoolProperty,           0x5c,  0x28000, UProperty,        UField,    NAME_BoolProperty,      UObject)
    IMPLEMENT_NATIVE(UFloatProperty,          0x58,  0x8000,  UProperty,        UField,    NAME_FloatProperty,     UObject)
    IMPLEMENT_NATIVE(UObjectProperty,         0x5c,  0x18000, UProperty,        UField,    NAME_ObjectProperty,    UObject)
    IMPLEMENT_NATIVE(UClassProperty,          0x60,  0x0,     UObjectProperty,  UField,    NAME_ClassProperty,     UObject)
    IMPLEMENT_NATIVE(UNameProperty,           0x58,  0x8000,  UProperty,        UField,    NAME_NameProperty,      UObject)
    IMPLEMENT_NATIVE(UStrProperty,            0x58,  0x8000,  UProperty,        UField,    NAME_StrProperty,       UObject)
    IMPLEMENT_NATIVE(UFixedArrayProperty,     0x60,  0x8000,  UProperty,        UField,    NAME_FixedArrayProperty,UObject)
    IMPLEMENT_NATIVE(UArrayProperty,          0x5c,  0x8000,  UProperty,        UField,    NAME_ArrayProperty,     UObject)
    IMPLEMENT_NATIVE(UMapProperty,            0x60,  0x8000,  UProperty,        UField,    NAME_MapProperty,       UObject)
    IMPLEMENT_NATIVE(UStructProperty,         0x5c,  0x8000,  UProperty,        UField,    NAME_StructProperty,    UObject)
    IMPLEMENT_NATIVE(USystem,                 0x84,  0x4,     USubsystem,       UObject,   NAME_System,            USystem)
    IMPLEMENT_NATIVE(UStruct,                 0x68,  0x0,     UField,           UObject,   NAME_Struct,            UObject)
    IMPLEMENT_NATIVE(UField,                  0x30,  0x1,     UObject,          UObject,   NAME_Field,             UObject)
    IMPLEMENT_NATIVE(UState,                  0x88,  0x40000, UStruct,          UObject,   NAME_State,             UObject)
    IMPLEMENT_NATIVE(UClassClass,             0x114, 0x0,     UState,           UPackage,  NAME_Class,             UObject)
    IMPLEMENT_NATIVE(UFunction,               0x7c,  0x80000, UStruct,          UState,    NAME_Function,          UObject)
    IMPLEMENT_NATIVE(UObjectExporterT3D,      0x40,  0x0,     UExporter,        UObject,   NAME_ObjectExporterT3D, UObjectExporterT3D)
    IMPLEMENT_NATIVE(UFactory,                0x68,  0x1,     UObject,          UObject,   NAME_Factory,           UFactory)

    for (INT i = 0; i < 256; i++)
        GByteTable_10c814d8[i] = (BYTE)((1 << (i & 7)) | (BYTE)(i * 7));
}
