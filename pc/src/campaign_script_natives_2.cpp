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

template <class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
    INT Num() const { return ArrayNum; }
};

class FString : public FArray {
public:
    FString() {}
    ~FString()
    {
        ArrayNum = 0;
        ArrayMax = 0;
        Data = GMalloc->Realloc(Data, 0, (const TCHAR *)L"FArray::_WORD");
        Remove(0, ArrayNum, sizeof(TCHAR));
    }
    FString &operator=(const TCHAR *Other);
    FString &operator=(const FString &Other);
    FString Caps() const;
    FString(INT InCount, const TCHAR *InSrc);
    FString(const TCHAR *In);
    FString Left(INT Count) const { return FString(Clamp(Count, 0, Len()), **this); }
    FString Right(INT Count) const { return FString(**this + Len() - Clamp(Count, 0, Len())); }
    FString Mid(INT Start, INT Count = 0x7fffffff) const
    {
        DWORD End = Start + Count;
        Start = Clamp((DWORD)Start, (DWORD)0, (DWORD)Len());
        End = Clamp((DWORD)End, (DWORD)Start, (DWORD)Len());
        return FString(End - Start, **this + Start);
    }
    INT InStr(const TCHAR *SubStr, UBOOL Right = 0) const;
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : (const TCHAR *)L""; }
    INT Len() const { return ArrayNum ? ArrayNum - 1 : 0; }
};

INT appAtoi(const TCHAR *Str);
FLOAT appAtof(const TCHAR *Str);
INT appStrcmp(const TCHAR *A, const TCHAR *B);
INT appStricmp(const TCHAR *A, const TCHAR *B);
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
#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
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

void UObject::execAssert(FFrame &Stack, RESULT_DECL)
{
    INT wLine = Stack.ReadWord();
    UBOOL Value = 0;
    Stack.Step(Stack.Object, &Value);
    if (!Value)
        Stack.Logf(NAME_Critical, (const TCHAR *)L"Assertion failed, line %i", wLine);
}

void UObject::execObjectToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UObject, A);
    *(FString *)Result = A ? A->GetName() : (const TCHAR *)L"None";
}

void UObject::execVectorToBool(FFrame &Stack, RESULT_DECL)
{
    FVector V(0.0f, 0.0f, 0.0f);
    Stack.Step(Stack.Object, &V);
    *(DWORD *)Result = V.IsZero() ? 0 : 1;
}

void UObject::execLen(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    *(INT *)Result = S.Len();
}

void UObject::execStringToInt(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    *(INT *)Result = appAtoi(*Str);
}

void UObject::execStringToByte(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    *(BYTE *)Result = appAtoi(*Str);
}

void UObject::execStringToFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    *(FLOAT *)Result = appAtof(*Str);
}

void UObject::execAsc(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    *(INT *)Result = **S;
}

void UObject::execEatString(FFrame &Stack, RESULT_DECL)
{
    FString String;
    Stack.Step(this, &String);
}

void UObject::execEqualEqual_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) == 0;
}

void UObject::execNotEqual_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) != 0;
}

void UObject::execLess_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) < 0;
}

void UObject::execGreater_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) > 0;
}

void UObject::execLessEqual_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) <= 0;
}

void UObject::execGreaterEqual_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) >= 0;
}

void UObject::execComplementEqual_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStricmp(*A, *B) == 0;
}

void UObject::execStringToBool(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    if (appStricmp(*Str, (const TCHAR *)L"True") == 0 || appStricmp(*Str, GTrue) == 0)
        *(INT *)Result = 1;
    else if (appStricmp(*Str, (const TCHAR *)L"False") == 0 || appStricmp(*Str, GFalse) == 0)
        *(INT *)Result = 0;
    else
        *(INT *)Result = appAtoi(*Str) ? 1 : 0;
}

void UObject::execCaps(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_FINISH;
    *(FString *)Result = A.Caps();
}

void UObject::execInStr(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_GET_STR(T);
    P_FINISH;
    *(INT *)Result = S.InStr(*T);
}
