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
enum EName { NAME_Critical = 761, NAME_ScriptLog = 770 };

class UObject;
class UClass;
class UFunction;
class UProperty;
struct FFrame;

struct FName {
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
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
struct FColor {
    BYTE B, G, R, A;
};

struct FRotator {
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
    FVector Vector();
    FRotator operator*(FLOAT Scale) const { return FRotator((INT)(Pitch * Scale), (INT)(Yaw * Scale), (INT)(Roll * Scale)); }
    INT NormalizeAxis(INT Angle) const
    {
        Angle &= 0xFFFF;
        if (Angle > 32767)
            Angle -= 0x10000;
        return Angle;
    }
    __forceinline FRotator Normalize() const
    {
        return FRotator(NormalizeAxis(Pitch), NormalizeAxis(Yaw), NormalizeAxis(Roll));
    }
};

inline FRotator operator*(FLOAT Scale, const FRotator &R) { return FRotator((INT)(R.Pitch * Scale), (INT)(R.Yaw * Scale), (INT)(R.Roll * Scale)); }

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
    void Logf(const TCHAR *Fmt, ...);
    void Log(const TCHAR *S);
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
    DECLARE_NATIVE(execLog)
    DECLARE_NATIVE(execWarn)
    DECLARE_NATIVE(execMultiply_RotatorFloat)
    DECLARE_NATIVE(execMultiply_FloatRotator)
    DECLARE_NATIVE(execFClamp)
    DECLARE_NATIVE(execSmerp)
    DECLARE_NATIVE(execDampFloat)
    DECLARE_NATIVE(execDampInt)
    DECLARE_NATIVE(execDampVec)
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
#define P_GET_BYTE(Var) BYTE Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_INT(Var) INT Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_NAME(Var) FName Var; Var.Index = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_NAME_OPTX(Var, Def) FName Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_UBOOL_OPTX(Var, Def) DWORD Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR_OPTX(Var, Def) FVector Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR(Var) FRotator Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++; if (*Stack.Code == EX_DebugInfo) Stack.Step(Stack.Object, 0)

class USound;
class AActor;

class UAudioSubsystem : public UObject {
public:
#define SLOT(n) virtual void AudioSlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27)
    virtual UBOOL StopSound(AActor *Actor, USound *Sound, FLOAT FadeTime, INT Slot);
    SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35)
    virtual void ChangeSoundVolume(AActor *Actor, USound *Sound, FLOAT Volume, INT Slot);
#undef SLOT
};

class UEngine : public UObject {
public:
    BYTE EnginePad[0x48 - 0x28];
    UAudioSubsystem *Audio;
};

class ULevel : public UObject {
public:
    BYTE LevelPad[0x38 - 0x28];
    UEngine *Engine;
#define SLOT(n) virtual void LevelSlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
    SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34)
#undef SLOT
    virtual UBOOL DestroyActor(AActor *ThisActor, UBOOL bNetForce = 0);
};

class AActor : public UObject {
public:
    DWORD ActorField28;
    DWORD MovementFlags;
    BYTE ActorPad[0x7c - 0x30];
    ULevel *XLevel;
    BYTE ActorPad2[0xc4 - 0x80];
    FLOAT LatentFloat;
#define SLOT(n) virtual void ActorSlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
    SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38)
    SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48)
    SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58)
    SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64)
    virtual void SetBase(AActor *NewBase, FVector NewFloor, INT bNotifyActor);
    SLOT(66) SLOT(67) SLOT(68)
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
    DECLARE_NATIVE(execSetBase)
    DECLARE_NATIVE(execError)
    DECLARE_NATIVE(execMultiply_ColorFloat)
    DECLARE_NATIVE(execMultiply_FloatColor)
    DECLARE_NATIVE(execInterpolateRotatorValue)
    DECLARE_NATIVE(execStopSound)
    DECLARE_NATIVE(execChangeSoundVolume)
    ULevel *GetLevel() const { return XLevel; }
    DECLARE_NATIVE(execScreenLog)
    DECLARE_NATIVE(execSetRotation)
};

// The release build compiles out the log output; the native still reads its parameters.
void UObject::execLog(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_GET_NAME_OPTX(N, NAME_ScriptLog);
    P_GET_UBOOL_OPTX(bExtra, 0);
    P_FINISH;
}

void UObject::execWarn(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    Stack.Logf((const TCHAR *)L"%s", *S);
}

void AActor::execSetBase(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(AActor, NewBase);
    P_GET_VECTOR_OPTX(NewFloor, FVector(0.0f, 0.0f, 1.0f));
    P_FINISH;
    SetBase(NewBase, NewFloor, 1);
}

// The release build compiles out the on-screen log; the native still reads its parameter.
void AActor::execScreenLog(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
}

void AActor::execError(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    Stack.Log(*S);
    GetLevel()->DestroyActor(this);
}

void AActor::execStopSound(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Sound);
    P_GET_FLOAT(FadeTime);
    P_GET_BYTE(Slot);
    P_FINISH;
    if (Sound && GetLevel()->Engine->Audio)
        *(DWORD *)Result = GetLevel()->Engine->Audio->StopSound(this, Sound, FadeTime, Slot);
    else
        *(DWORD *)Result = 0;
}

void AActor::execChangeSoundVolume(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Sound);
    P_GET_FLOAT(Volume);
    P_GET_BYTE(Slot);
    P_FINISH;
    if (GetLevel()->Engine->Audio)
        GetLevel()->Engine->Audio->ChangeSoundVolume(this, Sound, Volume, Slot);
}

INT InterpolateRotatorValue(INT Current, INT Desired, FLOAT Rate);

void AActor::execInterpolateRotatorValue(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Current);
    P_GET_INT(Desired);
    P_GET_FLOAT(Rate);
    P_FINISH;
    *(INT *)Result = InterpolateRotatorValue(Current, Desired, Rate);
}

class APawn : public AActor {
public:
    UBOOL PickWallAdjust(FVector WallHitNormal);
    UBOOL pointReachable(FVector aPoint, INT bKnowVisible, INT bExtra);
    FLOAT findPathToward(AActor *Goal, FVector Dest, void *NodeEval, UBOOL bClearPaths, INT bExtra);
};

class AController : public AActor {
public:
    BYTE ControllerPad[0x2b4 - 0xc8];
    APawn *Pawn;
    DECLARE_NATIVE(execPickWallAdjust)
    DECLARE_NATIVE(execpointReachable)
    DECLARE_NATIVE(execFindPathTo)
};

void AController::execPickWallAdjust(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(HitNormal);
    P_FINISH;
    if (Pawn)
        *(DWORD *)Result = Pawn->PickWallAdjust(HitNormal);
}

void AController::execpointReachable(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(aPoint);
    P_FINISH;
    if (!Pawn) {
        *(DWORD *)Result = 0;
        return;
    }
    *(DWORD *)Result = Pawn->pointReachable(aPoint, 0, 0);
}

void AController::execFindPathTo(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Point);
    P_GET_UBOOL_OPTX(bClearPaths, 1);
    P_FINISH;
    if (Pawn)
        Pawn->findPathToward(0, Point, 0, bClearPaths, 0);
    *(AActor **)Result = 0;
}

void UObject::execMultiply_RotatorFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FRotator *)Result = A * B;
}

void UObject::execMultiply_FloatRotator(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FRotator *)Result = A * B;
}

void UObject::execFClamp(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(V);
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT *)Result = Clamp(V, A, B);
}

void UObject::execSmerp(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Alpha);
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT *)Result = A + (3.0f * Alpha * Alpha - 2.0f * Alpha * Alpha * Alpha) * (B - A);
}

FLOAT DampFloat(FLOAT Current, FLOAT Target, FLOAT Rate, FLOAT DeltaTime);
INT DampInt(INT Current, INT Target, FLOAT Rate, FLOAT DeltaTime);
FVector DampVec(const FVector &Current, const FVector &Target, FLOAT Rate, FLOAT DeltaTime);

void UObject::execDampFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Current);
    P_GET_FLOAT(Target);
    P_GET_FLOAT(Rate);
    P_GET_FLOAT(DeltaTime);
    P_FINISH;
    *(FLOAT *)Result = DampFloat(Current, Target, Rate, DeltaTime);
}

void UObject::execDampInt(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Current);
    P_GET_INT(Target);
    P_GET_FLOAT(Rate);
    P_GET_FLOAT(DeltaTime);
    P_FINISH;
    *(INT *)Result = DampInt(Current, Target, Rate, DeltaTime);
}

void UObject::execDampVec(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Current);
    P_GET_VECTOR(Target);
    P_GET_FLOAT(Rate);
    P_GET_FLOAT(DeltaTime);
    P_FINISH;
    *(FVector *)Result = DampVec(Current, Target, Rate, DeltaTime);
}

void AActor::execMultiply_ColorFloat(FFrame &Stack, RESULT_DECL)
{
    FColor A;
    Stack.Step(Stack.Object, &A);
    P_GET_FLOAT(B);
    P_FINISH;
    A.R = (BYTE)(A.R * B);
    A.G = (BYTE)(A.G * B);
    A.B = (BYTE)(A.B * B);
    *(FColor *)Result = A;
}

void AActor::execMultiply_FloatColor(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    FColor B;
    Stack.Step(Stack.Object, &B);
    P_FINISH;
    B.R = (BYTE)(B.R * A);
    B.G = (BYTE)(B.G * A);
    B.B = (BYTE)(B.B * A);
    *(FColor *)Result = B;
}
