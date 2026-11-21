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
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
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
    BYTE          unk_20[0x4];
    class UClass *Class;

    // Destroys the object once: marks it, then calls Destroy.
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
};

#endif // UNREAL_OBJECT_H
