// unreal_object.h -- UObject, the root of the engine's object classes
#ifndef UNREAL_OBJECT_H
#define UNREAL_OBJECT_H

#include "unreal_types.h"
#include "unreal_name.h"

struct FGuid;
struct FFrame;
struct FStateFrame;

// UObject::ObjectFlags bits. The names are open: no symbol evidence names these bits.
enum {
    ObjectFlag_00800000 = 0x00800000,   // ConditionalDestroy has run for this object
    ObjectFlag_80000000 = 0x80000000    // cleared when ConditionalDestroy runs
};

// UObject::StaticLoadObject flags
enum ELoadFlags {
    LOAD_NoWarn = 0x0002,
    LOAD_Quiet  = 0x2000
};

// A script native reads its parameters from the bytecode and writes its result.
#define RESULT_DECL void *const Result
#define DECLARE_NATIVE(Name) void Name(FFrame &Stack, RESULT_DECL);

// The COM-style root of UObject: three __stdcall methods at the head of every object vtable.
class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

// Core.Object: 0x28 bytes. 22 virtual functions in the Versus executable, 24 in Campaign.
// Slots 0 to 3 and 9 hold the same functions in both; CallFunction is slot 18 in Campaign.
// The other slots are not identified yet. Both executables read Index and ObjectFlags
// (ConditionalDestroy); the Campaign natives read StateFrame and Class.
class UObject : public FUnknown {
public:
    virtual ~UObject();
#ifdef SCCT_VERSUS
    virtual void VirtualSlot4();
#else
    virtual void ProcessEvent(class UFunction *Function, void *Parms, void *Result = 0);
#endif
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
#ifdef SCCT_VERSUS
    virtual void VirtualSlot13();
#else
    // Jumps to a label of the state code. Named from execGotoLabel's error message; the other
    // two parameters are not identified.
    virtual UBOOL GotoLabel(FName Label, INT Option2, INT Option3);
#endif
#ifdef SCCT_VERSUS
    virtual void VirtualSlot14();
#else
    virtual void InitExecution();
#endif
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
#ifdef SCCT_VERSUS
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
#else
    virtual void CallFunction(FFrame &Stack, RESULT_DECL, class UFunction *Function);
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
#endif

    INT           Index;        // -1 while the object is not in the object table
    BYTE          unk_8[0x4];
    FStateFrame  *StateFrame;   // script execution state, when the object runs state code
    BYTE          unk_10[0xc];
    DWORD         ObjectFlags;  // ObjectFlag_ bits
#ifdef SCCT_VERSUS
    BYTE          unk_20[0x4];
#else
    FName         Name;         // the object's name; execGetStateName returns the state's
#endif
    class UClass *Class;

    // Destroys the object once: marks it, then calls Destroy.
#ifndef SCCT_VERSUS
    // Out of line in Campaign: every destructor calls it.
    INT ConditionalDestroy();
    // Objects return their memory to GMalloc (defined in unreal_class.h).
    void operator delete(void *Object);
#else
    INT ConditionalDestroy()
    {
        if (Index != -1 && !(ObjectFlags & ObjectFlag_00800000)) {
            ObjectFlags = (ObjectFlags & ~(ObjectFlag_80000000 | ObjectFlag_00800000))
                | ObjectFlag_00800000;
            Destroy();
            return 1;
        }
        return 0;
    }
#endif

    const TCHAR *GetName() const;
    class UClass *GetClass() const { return Class; }
    UBOOL IsA(class UClass *SomeBase) const;
    class UFunction *FindFunctionChecked(FName InName, UBOOL Global);
    static UObject *StaticLoadObject(class UClass *Class, UObject *InOuter, const TCHAR *Name,
                                     const TCHAR *Filename, DWORD LoadFlags, void *Sandbox);
    static UObject *StaticFindObject(class UClass *Class, UObject *InOuter, const TCHAR *Name,
                                     UBOOL ExactClass = 0);

    // Campaign natives, in the order of their units
    DECLARE_NATIVE(execJumpIfNot)
    DECLARE_NATIVE(execVirtualFunction)
    DECLARE_NATIVE(execGlobalFunction)
    DECLARE_NATIVE(execStringConst)
    DECLARE_NATIVE(execUnicodeStringConst)
    DECLARE_NATIVE(execBoolToString)
    DECLARE_NATIVE(execInstanceVariable)
    DECLARE_NATIVE(execDefaultVariable)
    DECLARE_NATIVE(execLetBool)
    DECLARE_NATIVE(execCross_VectorVector)
    DECLARE_NATIVE(execNormal)
    DECLARE_NATIVE(execVectorToRotator)
    DECLARE_NATIVE(execRotatorToVector)
    DECLARE_NATIVE(execAssert)
    DECLARE_NATIVE(execObjectToString)
    DECLARE_NATIVE(execVectorToBool)
    DECLARE_NATIVE(execLen)
    DECLARE_NATIVE(execStringToInt)
    DECLARE_NATIVE(execStringToByte)
    DECLARE_NATIVE(execStringToFloat)
    DECLARE_NATIVE(execAsc)
    DECLARE_NATIVE(execEatString)
    DECLARE_NATIVE(execEqualEqual_StringString)
    DECLARE_NATIVE(execNotEqual_StringString)
    DECLARE_NATIVE(execLess_StringString)
    DECLARE_NATIVE(execGreater_StringString)
    DECLARE_NATIVE(execLessEqual_StringString)
    DECLARE_NATIVE(execGreaterEqual_StringString)
    DECLARE_NATIVE(execComplementEqual_StringString)
    DECLARE_NATIVE(execStringToBool)
    DECLARE_NATIVE(execCaps)
    DECLARE_NATIVE(execInStr)
    DECLARE_NATIVE(execLog)
    DECLARE_NATIVE(execWarn)
    DECLARE_NATIVE(execMultiply_RotatorFloat)
    DECLARE_NATIVE(execMultiply_FloatRotator)
    DECLARE_NATIVE(execFClamp)
    DECLARE_NATIVE(execSmerp)
    DECLARE_NATIVE(execDampFloat)
    DECLARE_NATIVE(execDampInt)
    DECLARE_NATIVE(execDampVec)
    DECLARE_NATIVE(execDivide_VectorFloat)
    DECLARE_NATIVE(execDivideEqual_VectorFloat)
    DECLARE_NATIVE(execMirrorVectorByNormal)
    DECLARE_NATIVE(execDivide_RotatorFloat)
    DECLARE_NATIVE(execDivideEqual_RotatorFloat)
    DECLARE_NATIVE(execFloatToString)
    DECLARE_NATIVE(execStringToVector)
    DECLARE_NATIVE(execStringToRotator)
    DECLARE_NATIVE(execVectorToString)
    DECLARE_NATIVE(execRotatorToString)
    DECLARE_NATIVE(execStructCmpEq)
    DECLARE_NATIVE(execStructCmpNe)
    DECLARE_NATIVE(execDynamicLoadObject)
    DECLARE_NATIVE(execFindObject)
#ifndef SCCT_VERSUS
    // Campaign-only declarations: keeping them out of the Versus build leaves its translation
    // units, and the compiler's numbering of their EH data, unchanged.
    FName GetFName() const { return Name; }
    // Named after the natives that call them; no symbol evidence names these.
    void SaveConfig(DWORD Flags = 0x1000, const TCHAR *Filename = 0);
    static void ResetConfig(class UClass *Class, const TCHAR *Section, INT Option3);

    DECLARE_NATIVE(execNothing)
    DECLARE_NATIVE(execIterator)
    DECLARE_NATIVE(execEndFunctionParms)
    DECLARE_NATIVE(execFinalFunction)
    DECLARE_NATIVE(execFRand)
    DECLARE_NATIVE(execLocalFRand)
    DECLARE_NATIVE(execSaveConfig)
    DECLARE_NATIVE(execResetConfig)
    DECLARE_NATIVE(execVRand)
    DECLARE_NATIVE(execLocalVariable)
    DECLARE_NATIVE(execNativeParm)
    DECLARE_NATIVE(execDynArrayLength)
    DECLARE_NATIVE(execSubtract_PreFloat)
    DECLARE_NATIVE(execBoolVariable)
    DECLARE_NATIVE(execGetStateName)
    DECLARE_NATIVE(execNotEqual_ObjectObject)
    DECLARE_NATIVE(execEqualEqual_ObjectObject)
    DECLARE_NATIVE(execNotEqual_NameName)
    DECLARE_NATIVE(execEqualEqual_NameName)
    DECLARE_NATIVE(execNotEqual_FloatFloat)
    DECLARE_NATIVE(execEqualEqual_FloatFloat)
    DECLARE_NATIVE(execPow)
    DECLARE_NATIVE(execMultiplyMultiply_FloatFloat)
    DECLARE_NATIVE(execPercent_FloatFloat)
    DECLARE_NATIVE(execDivide_FloatFloat)
    DECLARE_NATIVE(execXorXor_BoolBool)
    DECLARE_NATIVE(execAcos)
    DECLARE_NATIVE(execAbs)
    DECLARE_NATIVE(execRand)
    DECLARE_NATIVE(execRotatorToBool)
    DECLARE_NATIVE(execChr)
    DECLARE_NATIVE(execDynamicCast)
    DECLARE_NATIVE(execIsA)
    DECLARE_NATIVE(execIsInState)
    DECLARE_NATIVE(execNameToString)
    DECLARE_NATIVE(execGotoLabel)
    DECLARE_NATIVE(execComplementEqual_FloatFloat)
    DECLARE_NATIVE(execDivideEqual_FloatFloat)
    DECLARE_NATIVE(execDivideEqual_IntFloat)
    DECLARE_NATIVE(execClassIsChildOf)
    DECLARE_NATIVE(execIntToString)
    DECLARE_NATIVE(execByteToString)
    DECLARE_NATIVE(execRotRand)
    DECLARE_NATIVE(execMetaCast)
    DECLARE_NATIVE(execAndAnd_BoolBool)
    DECLARE_NATIVE(execOrOr_BoolBool)
    DECLARE_NATIVE(execMid)
    DECLARE_NATIVE(execCase)
    DECLARE_NATIVE(execContext)
    DECLARE_NATIVE(execClassContext)
    DECLARE_NATIVE(execStaticSaveConfig)
#endif
};

// A class of package Package whose class object is created on first use.
#define DECLARE_LAZY_CLASS_IN(Name, Package)                                        \
    static class UClass *PrivateStaticClass;                                        \
    static class UClass *GetPrivateStaticClass##Name(const TCHAR *InPackage);       \
    static void InitializePrivateStaticClass##Name();                               \
    static class UClass *StaticClass()                                              \
    {                                                                               \
        if (!PrivateStaticClass)                                                    \
        {                                                                           \
            PrivateStaticClass = GetPrivateStaticClass##Name(Package);              \
            InitializePrivateStaticClass##Name();                                   \
        }                                                                           \
        return PrivateStaticClass;                                                  \
    }

// A class of the Engine package whose class object is created on first use.
#define DECLARE_LAZY_CLASS(Name) DECLARE_LAZY_CLASS_IN(Name, L"Engine")

#endif // UNREAL_OBJECT_H
