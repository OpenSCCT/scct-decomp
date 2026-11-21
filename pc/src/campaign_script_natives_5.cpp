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
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector operator/(FLOAT Scale) const { FLOAT RScale = 1.0f / Scale; return FVector(X * RScale, Y * RScale, Z * RScale); }
    FVector &operator/=(FLOAT V) { FLOAT RV = 1.0f / V; X *= RV; Y *= RV; Z *= RV; return *this; }
    UBOOL IsZero() const { return X == 0.0f && Y == 0.0f && Z == 0.0f; }
    FVector SafeNormal() const;
    struct FRotator Rotation();
};

struct FCoords;
inline FVector operator*(FLOAT Scale, const FVector &V) { return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale); }

struct FColor {
    BYTE B, G, R, A;
};

struct FRotator {
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
    FVector Vector();
    FRotator operator/(FLOAT Scale) const { FLOAT RScale = 1.0f / Scale; return FRotator((INT)(Pitch * RScale), (INT)(Yaw * RScale), (INT)(Roll * RScale)); }
    FRotator &operator/=(FLOAT Scale) { FLOAT RScale = 1.0f / Scale; Pitch = (INT)(Pitch * RScale); Yaw = (INT)(Yaw * RScale); Roll = (INT)(Roll * RScale); return *this; }
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
    static FString Printf(const TCHAR *Fmt, ...);
    FString(INT InCount, const TCHAR *InSrc);
    FString(const TCHAR *In);
    FString(const FString &Other);
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
void appClipboardCopy(const TCHAR *Str);
FLOAT appAtof(const TCHAR *Str);
const TCHAR *appStrstr(const TCHAR *String, const TCHAR *Find);
INT appStrcmp(const TCHAR *A, const TCHAR *B);
INT appStricmp(const TCHAR *A, const TCHAR *B);
TCHAR *appFromAnsi(const ANSICHAR *Str);
TCHAR *appFromUnicode(const TCHAR *Str);

extern TCHAR GTrue[];
extern TCHAR GFalse[];

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    void Logf(EName Event, const TCHAR *Fmt, ...);
    void Logf(const TCHAR *Fmt, ...);
    void Log(const TCHAR *S);
};

class FExec {
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar) = 0;
};

class FStringOutputDevice : public FOutputDevice, public FString {
public:
    FStringOutputDevice(const TCHAR *InStr = (const TCHAR *)L"") : FString(InStr) {}
    void Serialize(const TCHAR *Data, EName Event);
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
    DECLARE_NATIVE(execDivide_VectorFloat)
    DECLARE_NATIVE(execDivide_RotatorFloat)
    DECLARE_NATIVE(execDivideEqual_VectorFloat)
    DECLARE_NATIVE(execDivideEqual_RotatorFloat)
    DECLARE_NATIVE(execMirrorVectorByNormal)
    DECLARE_NATIVE(execStructCmpEq)
    DECLARE_NATIVE(execStructCmpNe)
    DECLARE_NATIVE(execFloatToString)
    DECLARE_NATIVE(execVectorToString)
    DECLARE_NATIVE(execRotatorToString)
    DECLARE_NATIVE(execStringToVector)
    DECLARE_NATIVE(execStringToRotator)
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
    BYTE Pad[0x4c - 0x34];
    INT PropertiesSize;
    TArray<BYTE> Script;
    UBOOL StructCompare(const void *A, const void *B);
};

extern "C" void *__cdecl _alloca(unsigned int Size);
extern "C" void *__cdecl memset(void *Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)
#define appAlloca(size) ((size == 0) ? 0 : _alloca((size + 7) & ~7))
inline void appMemzero(void *Dest, INT Count) { memset(Dest, 0, Count); }

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
#define P_GET_VECTOR_REF(Var) FVector Var##T; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); FVector *Var = GPropAddr ? (FVector *)GPropAddr : &Var##T
#define P_GET_ROTATOR_REF(Var) FRotator Var##T; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); FRotator *Var = GPropAddr ? (FRotator *)GPropAddr : &Var##T
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

class UEngine : public UObject, public FExec {
public:
    BYTE EnginePad[0x48 - 0x2c];
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
    virtual UBOOL AnimationFinished(INT Channel);
    SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79) SLOT(80) SLOT(81)
    virtual void setPhysics(BYTE NewPhysics, AActor *NewFloor, FVector NewFloorV, INT bExtra);
    SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87) SLOT(88) SLOT(89) SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95) SLOT(96) SLOT(97) SLOT(98) SLOT(99) SLOT(100) SLOT(101) SLOT(102)
    virtual void PlayAnim(INT Channel, FName Sequence, FLOAT Rate, FLOAT TweenTime, INT bLoop, INT A, INT B, INT C);
    SLOT(104) SLOT(105) SLOT(106) SLOT(107) SLOT(108) SLOT(109) SLOT(110) SLOT(111) SLOT(112) SLOT(113) SLOT(114) SLOT(115) SLOT(116) SLOT(117) SLOT(118) SLOT(119) SLOT(120) SLOT(121) SLOT(122) SLOT(123) SLOT(124) SLOT(125) SLOT(126) SLOT(127) SLOT(128) SLOT(129) SLOT(130) SLOT(131) SLOT(132) SLOT(133)
    virtual void StopAllSoundsActor(INT Flags, FLOAT FadeTime, INT Slot);
#undef SLOT
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
    DECLARE_NATIVE(execConsoleCommand)
    DECLARE_NATIVE(execSetRelativeRotation)
    DECLARE_NATIVE(execStopAllSoundsActor)
    DECLARE_NATIVE(execInterpolateRotator)
    DECLARE_NATIVE(execSetPhysics)
    DECLARE_NATIVE(execTweenAnim)
    DECLARE_NATIVE(execPlayAnim)
    DECLARE_NATIVE(execLoopAnim)
    UBOOL SetRelativeRotation(const FRotator &NewRotation);
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
// The release build compiles out the on-screen log; the native still reads its parameter.
INT InterpolateRotatorValue(INT Current, INT Desired, FLOAT Rate);

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

FLOAT DampFloat(FLOAT Current, FLOAT Target, FLOAT Rate, FLOAT DeltaTime);
INT DampInt(INT Current, INT Target, FLOAT Rate, FLOAT DeltaTime);
FVector DampVec(const FVector &Current, const FVector &Target, FLOAT Rate, FLOAT DeltaTime);

FRotator InterpolateRotator(FLOAT Alpha, const FRotator &A, const FRotator &B);

#define P_GET_FLOAT_OPTX(Var, Def) FLOAT Var = Def; Stack.Step(Stack.Object, &Var)

class UPlayer : public UObject, public FOutputDevice, public FExec {
};

class APlayerController : public AController {
public:
    BYTE PlayerControllerPad[0x394 - 0x2b8];
    UPlayer *Player;
    DECLARE_NATIVE(execCopyToClipboard)
};

class UInteraction : public UObject {
public:
    UBOOL ConsoleCommand(FString S);
    DECLARE_NATIVE(execConsoleCommand)
};

class UCommandlet : public UObject {
public:
#define SLOT(n) virtual void CommandletSlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
#undef SLOT
    virtual INT Main(const TCHAR *Parms);
    DECLARE_NATIVE(execMain)
};

// The release build compiles out the divide-by-zero script warning.
void UObject::execDivide_VectorFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    if (B == 0.0f) {
        *(FVector *)Result = FVector(0.0f, 0.0f, 0.0f);
        return;
    }
    *(FVector *)Result = A / B;
}

void UObject::execDivide_RotatorFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    if (B == 0.0f) {
        *(FRotator *)Result = FRotator(0, 0, 0);
        return;
    }
    *(FRotator *)Result = A / B;
}

void UObject::execDivideEqual_VectorFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR_REF(A);
    P_GET_FLOAT(B);
    P_FINISH;
    if (B == 0.0f) {
        *(FVector *)Result = FVector(0.0f, 0.0f, 0.0f);
        return;
    }
    *(FVector *)Result = (*A /= B);
}

void UObject::execDivideEqual_RotatorFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR_REF(A);
    P_GET_FLOAT(B);
    P_FINISH;
    if (B == 0.0f) {
        *(FRotator *)Result = FRotator(0, 0, 0);
        return;
    }
    *(FRotator *)Result = (*A /= B);
}

void UObject::execMirrorVectorByNormal(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    B = B.SafeNormal();
    *(FVector *)Result = A - 2.0f * B * (B | A);
}

void UObject::execStructCmpEq(FFrame &Stack, RESULT_DECL)
{
    UStruct *Struct = (UStruct *)Stack.ReadObject();
    BYTE *Buffer1 = (BYTE *)appAlloca(Struct->PropertiesSize);
    BYTE *Buffer2 = (BYTE *)appAlloca(Struct->PropertiesSize);
    appMemzero(Buffer1, Struct->PropertiesSize);
    appMemzero(Buffer2, Struct->PropertiesSize);
    Stack.Step(this, Buffer1);
    Stack.Step(this, Buffer2);
    *(DWORD *)Result = Struct->StructCompare(Buffer1, Buffer2);
}

void UObject::execStructCmpNe(FFrame &Stack, RESULT_DECL)
{
    UStruct *Struct = (UStruct *)Stack.ReadObject();
    BYTE *Buffer1 = (BYTE *)appAlloca(Struct->PropertiesSize);
    BYTE *Buffer2 = (BYTE *)appAlloca(Struct->PropertiesSize);
    appMemzero(Buffer1, Struct->PropertiesSize);
    appMemzero(Buffer2, Struct->PropertiesSize);
    Stack.Step(this, Buffer1);
    Stack.Step(this, Buffer2);
    *(DWORD *)Result = !Struct->StructCompare(Buffer1, Buffer2);
}

void UObject::execFloatToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(F);
    *(FString *)Result = FString::Printf((const TCHAR *)L"%0.2f", F);
}

void UObject::execVectorToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(V);
    *(FString *)Result = FString::Printf((const TCHAR *)L"%0.2f,%0.2f,%0.2f", V.X, V.Y, V.Z);
}

void UObject::execRotatorToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR(R);
    *(FString *)Result = FString::Printf((const TCHAR *)L"%i,%i,%i", R.Pitch & 65535, R.Yaw & 65535, R.Roll & 65535);
}

void UObject::execStringToVector(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    const TCHAR *Stream = *Str;
    FVector Value(0.0f, 0.0f, 0.0f);
    Value.X = appAtof(Stream);
    Stream = appStrstr(Stream, (const TCHAR *)L",");
    if (Stream) {
        Value.Y = appAtof(++Stream);
        Stream = appStrstr(Stream, (const TCHAR *)L",");
        if (Stream)
            Value.Z = appAtof(++Stream);
    }
    *(FVector *)Result = Value;
}

void UObject::execStringToRotator(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    const TCHAR *Stream = *Str;
    FRotator Rotator(0, 0, 0);
    Rotator.Pitch = appAtoi(Stream);
    Stream = appStrstr(Stream, (const TCHAR *)L",");
    if (Stream) {
        Rotator.Yaw = appAtoi(++Stream);
        Stream = appStrstr(Stream, (const TCHAR *)L",");
        if (Stream)
            Rotator.Roll = appAtoi(++Stream);
    }
    *(FRotator *)Result = Rotator;
}
