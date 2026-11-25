// unreal_script.h -- the script interpreter's frame and the helpers script natives use
#ifndef UNREAL_SCRIPT_H
#define UNREAL_SCRIPT_H

#include "unreal_types.h"
#include "unreal_name.h"
#include "unreal_object.h"

// A sink for text; FFrame is one so that script errors can be logged through it.
class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    void Logf(EName Event, const TCHAR *Fmt, ...);
    void Logf(const TCHAR *Fmt, ...);
    void Log(const TCHAR *S);
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];       // indexed by bytecode token

#define EX_DebugInfo 0x42       // bytecode token of a debugger line record

// The state of one executing script function.
struct FFrame : public FOutputDevice {
    class UStruct *Node;        // the function or state being executed
    UObject       *Object;      // the object it executes on
    BYTE          *Code;        // next bytecode to read
    BYTE          *Locals;

    // Executes one bytecode expression and stores its value in Result.
    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
    INT ReadWord()
    {
        INT Result = *(_WORD *)Code;
        Code += sizeof(_WORD);
        return Result;
    }
#ifndef SCCT_VERSUS
    // The EX_Skip token and the byte count of its optional operand.
    _WORD ReadSkipCount()
    {
        Code++;
        _WORD Count = *(_WORD *)Code;
        Code += sizeof(Count);
        return Count;
    }
#endif
    UObject *ReadObject()
    {
        UObject *Result = *(UObject **)Code;
        Code += sizeof(INT);
        return Result;
    }
    FName ReadName()
    {
        FName Result = *(FName *)Code;
        Code += sizeof(FName);
        return Result;
    }
};

// The frame of an object that runs state code.
struct FStateFrame : public FFrame {
#ifdef SCCT_VERSUS
    BYTE unk_14[0x14];
#else
    BYTE          unk_14[0x8];
    class UState *StateNode;    // the state the object is in
    BYTE          unk_20[0x8];
#endif
    INT  LatentAction;          // native index of the latent function in progress, or 0
};

// the property the last variable expression addressed
extern BYTE            *GPropAddr;
extern UObject         *GPropObject;
extern class UProperty *GProperty;

// Parameter readers of a script native. P_FINISH steps over the end-of-parameters token; the
// Campaign interpreter also executes a debugger line record that follows it.
#define P_GET_UBOOL(Var) DWORD Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_UBOOL_OPTX(Var, Def) DWORD Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_BYTE(Var) BYTE Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_INT(Var) INT Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT_OPTX(Var, Def) FLOAT Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_NAME(Var) FName Var; Var.Index = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_NAME_OPTX(Var, Def) FName Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR_OPTX(Var, Def) FVector Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR(Var) FRotator Var; Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR_OPTX(Var, Def) FRotator Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_BYTE_OPTX(Var, Def) BYTE Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_INT_OPTX(Var, Def) INT Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_STRUCT(Type, Var) Type Var; Stack.Step(Stack.Object, &Var)
// An out parameter: Var points at the script variable, or at a local when the expression
// was not a variable.
#define P_GET_FLOAT_REF(Var) \
    FLOAT Var##T = 0.0f; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); \
    FLOAT *Var = GPropAddr ? (FLOAT *)GPropAddr : &Var##T
#define P_GET_INT_REF(Var) \
    INT Var##T = 0; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); \
    INT *Var = GPropAddr ? (INT *)GPropAddr : &Var##T
#define P_GET_NAME_REF(Var) \
    FName Var##T; Var##T.Index = 0; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); \
    FName *Var = GPropAddr ? (FName *)GPropAddr : &Var##T
#define P_GET_OBJECT_REF(Cls, Var) \
    Cls *Var##T = 0; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); \
    Cls **Var = GPropAddr ? (Cls **)GPropAddr : &Var##T
#define P_GET_VECTOR_REF(Var) \
    FVector Var##T; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); \
    FVector *Var = GPropAddr ? (FVector *)GPropAddr : &Var##T
#define P_GET_ROTATOR_REF(Var) \
    FRotator Var##T; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); \
    FRotator *Var = GPropAddr ? (FRotator *)GPropAddr : &Var##T
#ifdef SCCT_VERSUS
#define P_FINISH Stack.Code++
#else
#define P_FINISH Stack.Code++; if (*Stack.Code == EX_DebugInfo) Stack.Step(Stack.Object, 0)
#endif

#endif // UNREAL_SCRIPT_H
