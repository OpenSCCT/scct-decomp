// Engine declarations shared by the Campaign UnrealScript natives. Layouts and
// virtual slots are those the retail natives use; names follow Unreal Engine 2.
typedef int INT;
typedef unsigned int DWORD;
typedef unsigned short _WORD;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef int UBOOL;
typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef DWORD BITFIELD;
enum EName { NAME_Critical = 761 };

class UObject;
class UClass;
class UFunction;
class UProperty;
struct FFrame;

struct FName {
    INT Index;
};

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator^(const FVector &V) const { return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
    UBOOL IsZero() const { return X == 0.0f && Y == 0.0f && Z == 0.0f; }
    FVector SafeNormal() const;
    struct FRotator Rotation();
};

struct FCoords;
struct FRotator {
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
    FVector Vector();
};

struct FCoords {
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords &operator/=(const FRotator &R);
    FCoords operator/(const FRotator &R) const { return FCoords(*this) /= R; }
};

struct FGlobalMath {
    FCoords UnitCoords;
};
extern FGlobalMath GMath;

inline FVector FRotator::Vector()
{
    return (GMath.UnitCoords / *this).XAxis;
}

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString &operator=(const TCHAR *Other);
};

TCHAR *appFromAnsi(const ANSICHAR *Str);
TCHAR *appFromUnicode(const TCHAR *Str);

extern TCHAR GTrue[];
extern TCHAR GFalse[];

class FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    void Logf(EName Event, const TCHAR *Fmt, ...);
};

struct FStateFrame;

class UObject {
public:
    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;

    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void CallFunction(FFrame &Stack, void *const Result, UFunction *Function);

    const TCHAR *GetName() const;
    UClass *GetClass() const { return Class; }
    UFunction *FindFunctionChecked(FName InName, UBOOL Global);

#define DECLARE_NATIVE(Name) void Name(FFrame &Stack, void *const Result);
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
};

typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

template <class T> struct TArray {
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
};

class UField : public UObject {
public:
    UField *SuperField;
    UField *Next;
    UField *HashNext;
};

class UProperty : public UField {
public:
    BYTE Pad[0x44 - 0x34];
    _WORD Offset;
#define SLOT(n) virtual void PropertySlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
    SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38)
#undef SLOT
    virtual void CopyCompleteValue(void *Dest, void *Src, UObject *Obj = 0);
};

class UBoolProperty : public UProperty {
public:
    BYTE Pad2[0x54 - 0x48];
    BITFIELD BitMask;
};

class UStruct : public UField {
public:
    BYTE Pad[0x50 - 0x34];
    TArray<BYTE> Script;
};

class UClass : public UStruct {
public:
    BYTE Pad2[0x29c - 0x5c];
    TArray<BYTE> Defaults;
};

struct FFrame : public FOutputDevice {
    UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;
    void Step(UObject *Context, void *const Result)
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

struct FStateFrame : public FFrame {
    BYTE Pad[0x28 - 0x14];
    INT LatentAction;
};

extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;

#define RESULT_DECL void *const Result
#define EX_DebugInfo 0x42
#define P_GET_UBOOL(Var) DWORD Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_INT(Var) INT Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_NAME(Var) FName Var; Var.Index = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR(Var) FRotator Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++; if (*Stack.Code == EX_DebugInfo) Stack.Step(Stack.Object, 0)

class AActor : public UObject {
public:
    DWORD ActorField28;
    DWORD MovementFlags;
    BYTE ActorPad[0xc4 - 0x30];
    FLOAT LatentFloat;
#define SLOT(n) virtual void ActorSlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
    SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38)
    SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48)
    SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58)
    SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68)
    SLOT(69) SLOT(70) SLOT(71)
#undef SLOT
    virtual UBOOL AnimationFinished(INT Channel);
    UBOOL SetRotation(const FRotator &NewRotation);
    UBOOL SetRelativeLocation(const FVector &NewLocation);
    UBOOL SetLocation(const FVector &NewLocation, UBOOL bNoCheck);
    void SetDrawScale3D(FVector NewScale3D);
    UBOOL MoveSmooth(FVector Delta);
    DECLARE_NATIVE(execSetRelativeLocation)
    DECLARE_NATIVE(execSetLocation)
    DECLARE_NATIVE(execSetDrawScale3D)
    DECLARE_NATIVE(execMoveSmooth)
    DECLARE_NATIVE(execPollFinishAnim)
    DECLARE_NATIVE(execSetRotation)
};

void UObject::execJumpIfNot(FFrame &Stack, RESULT_DECL)
{
    INT wOffset = Stack.ReadWord();
    UBOOL Value = 0;
    Stack.Step(Stack.Object, &Value);
    if (!Value)
        Stack.Code = &Stack.Node->Script(wOffset);
}

void UObject::execVirtualFunction(FFrame &Stack, RESULT_DECL)
{
    CallFunction(Stack, Result, FindFunctionChecked(Stack.ReadName(), 0));
}

void UObject::execGlobalFunction(FFrame &Stack, RESULT_DECL)
{
    CallFunction(Stack, Result, FindFunctionChecked(Stack.ReadName(), 1));
}

void UObject::execStringConst(FFrame &Stack, RESULT_DECL)
{
    *(FString *)Result = appFromAnsi((ANSICHAR *)Stack.Code);
    while (*Stack.Code)
        Stack.Code++;
    Stack.Code++;
}

void UObject::execUnicodeStringConst(FFrame &Stack, RESULT_DECL)
{
    *(FString *)Result = appFromUnicode((TCHAR *)Stack.Code);
    while (*(_WORD *)Stack.Code)
        Stack.Code += sizeof(_WORD);
    Stack.Code += sizeof(_WORD);
}

void UObject::execBoolToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(B);
    *(FString *)Result = B ? GTrue : GFalse;
}

void UObject::execInstanceVariable(FFrame &Stack, RESULT_DECL)
{
    GProperty = (UProperty *)Stack.ReadObject();
    GPropAddr = (BYTE *)this + GProperty->Offset;
    GPropObject = this;
    if (Result)
        GProperty->CopyCompleteValue(Result, GPropAddr);
}

void UObject::execDefaultVariable(FFrame &Stack, RESULT_DECL)
{
    GProperty = (UProperty *)Stack.ReadObject();
    GPropAddr = &GetClass()->Defaults(GProperty->Offset);
    GPropObject = 0;
    if (Result)
        GProperty->CopyCompleteValue(Result, GPropAddr);
}

void UObject::execLetBool(FFrame &Stack, RESULT_DECL)
{
    GPropAddr = 0;
    GProperty = 0;
    GPropObject = 0;
    Stack.Step(Stack.Object, 0);
    BITFIELD *BoolAddr = (BITFIELD *)GPropAddr;
    UBoolProperty *BoolProperty = (UBoolProperty *)GProperty;
    INT NewValue = 0;
    Stack.Step(Stack.Object, &NewValue);
    if (BoolAddr) {
        if (NewValue)
            *BoolAddr |= BoolProperty->BitMask;
        else
            *BoolAddr &= ~BoolProperty->BitMask;
    }
}

void UObject::execCross_VectorVector(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector *)Result = A ^ B;
}

void UObject::execNormal(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_FINISH;
    *(FVector *)Result = A.SafeNormal();
}

void AActor::execPollFinishAnim(FFrame &Stack, RESULT_DECL)
{
    if (AnimationFinished((INT)LatentFloat))
        StateFrame->LatentAction = 0;
}

void AActor::execSetRotation(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR(NewRotation);
    P_FINISH;
    *(DWORD *)Result = SetRotation(NewRotation);
}

void AActor::execSetRelativeLocation(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(NewLocation);
    P_FINISH;
    *(DWORD *)Result = SetRelativeLocation(NewLocation);
}

void AActor::execSetLocation(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(NewLocation);
    P_GET_UBOOL(bNoCheck);
    P_FINISH;
    *(DWORD *)Result = SetLocation(NewLocation, bNoCheck);
}

void AActor::execSetDrawScale3D(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(NewScale3D);
    P_FINISH;
    SetDrawScale3D(NewScale3D);
}

void AActor::execMoveSmooth(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Delta);
    P_FINISH;
    MovementFlags &= ~0x02000000;
    *(DWORD *)Result = MoveSmooth(Delta);
}

void UObject::execVectorToRotator(FFrame &Stack, RESULT_DECL)
{
    FVector V(0.0f, 0.0f, 0.0f);
    Stack.Step(Stack.Object, &V);
    *(FRotator *)Result = V.Rotation();
}

void UObject::execRotatorToVector(FFrame &Stack, RESULT_DECL)
{
    FRotator R(0, 0, 0);
    Stack.Step(Stack.Object, &R);
    *(FVector *)Result = R.Vector();
}
