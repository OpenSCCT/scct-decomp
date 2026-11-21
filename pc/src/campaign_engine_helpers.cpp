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
enum ELoadFlags { LOAD_NoWarn = 0x0002, LOAD_Quiet = 0x2000 };
enum EName { NAME_None = 0, NAME_Critical = 761, NAME_ScriptLog = 770 };

class UObject;
class UClass;
class UFunction;
class UProperty;
struct FFrame;

struct FName {
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    UBOOL operator!=(const FName &Other) const { return Index != Other.Index; }
};

typedef double DOUBLE;
DOUBLE appSqrt(DOUBLE Value);

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
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector &operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
    FLOAT Size() const { return (FLOAT)appSqrt(X * X + Y * Y + Z * Z); }
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
    void Realloc(INT ElementSize);
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
    FString operator+(const TCHAR *Str) const;
    FString operator+(const FString &Str) const { return operator+(*Str); }
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
    UBOOL IsA(UClass *SomeBase) const;
    UFunction *FindFunctionChecked(FName InName, UBOOL Global);
    static UObject *StaticLoadObject(UClass *Class, UObject *InOuter, const TCHAR *Name, const TCHAR *Filename, DWORD LoadFlags, void *Sandbox);
    static UObject *StaticFindObject(UClass *Class, UObject *InOuter, const TCHAR *Name, UBOOL ExactClass = 0);

#define DECLARE_NATIVE(Name) void Name(FFrame &Stack, void *const Result);
};

typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

template <class T> struct TArray {
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
    INT Num() const { return ArrayNum; }
    T &Last() { return Data[ArrayNum - 1]; }
    INT AddZeroed(INT Count = 1)
    {
        INT Index = ArrayNum;
        ArrayNum += Count;
        ((FArray *)this)->Realloc(sizeof(T));
        appMemzero(Data + Index, Count * sizeof(T));
        return Index;
    }
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
    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

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
#define P_GET_BYTE_OPTX(Var, Def) BYTE Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_INT_OPTX(Var, Def) INT Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_INT(Var) INT Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_NAME(Var) FName Var; Var.Index = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_NAME_OPTX(Var, Def) FName Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_UBOOL_OPTX(Var, Def) DWORD Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR_OPTX(Var, Def) FVector Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR_OPTX(Var, Def) FRotator Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT_REF(Var) FLOAT Var##T = 0.0f; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); FLOAT *Var = GPropAddr ? (FLOAT *)GPropAddr : &Var##T
#define P_GET_NAME_REF(Var) FName Var##T; Var##T.Index = 0; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); FName *Var = GPropAddr ? (FName *)GPropAddr : &Var##T
#define P_GET_OBJECT_REF(Cls, Var) Cls *Var##T = 0; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); Cls **Var = GPropAddr ? (Cls **)GPropAddr : &Var##T
#define P_GET_VECTOR_REF(Var) FVector Var##T; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); FVector *Var = GPropAddr ? (FVector *)GPropAddr : &Var##T
#define P_GET_ROTATOR_REF(Var) FRotator Var##T; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); FRotator *Var = GPropAddr ? (FRotator *)GPropAddr : &Var##T
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_GET_STRUCT(Type, Var) Type Var; Stack.Step(Stack.Object, &Var)
#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR(Var) FRotator Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++; if (*Stack.Code == EX_DebugInfo) Stack.Step(Stack.Object, 0)

class USound;
class AActor;
class UCanvas;
class APawn;
class ALevelInfo;
class APlayerController;
class UViewport;

class UAudioSubsystem : public UObject {
public:
#define SLOT(n) virtual void AudioSlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27)
    virtual UBOOL StopSound(AActor *Actor, USound *Sound, FLOAT FadeTime, INT Slot);
    virtual UViewport *GetViewport();
    SLOT(30)
    virtual UBOOL PlaySound(AActor *Actor, USound *Sound, BYTE Slot, FLOAT Volume, INT Option4, FLOAT Option5, FLOAT Option6);
    SLOT(32) SLOT(33) SLOT(34) SLOT(35)
    virtual void ChangeSoundVolume(AActor *Actor, USound *Sound, FLOAT Volume, INT Slot);
    SLOT(37) SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48)
    virtual void AddSoundRequest(AActor *Actor, USound *Sound, BYTE Slot, FLOAT Value1, FLOAT Value2, INT Flags);
#undef SLOT
};

class UEngine : public UObject, public FExec {
public:
    BYTE EnginePad[0x48 - 0x2c];
    UAudioSubsystem *Audio;
};

class UPrimitive;
class UMaterial;

struct FCheckResult {
    FCheckResult *Next;
    AActor *Actor;
    FVector Location;
    FVector Normal;
    UPrimitive *Primitive;
    FLOAT Time;
    INT Item;
    UMaterial *Material;
    FName BoneName;
    FCheckResult(FLOAT InTime = 0.0f, FCheckResult *InNext = 0)
        : Next(InNext), Actor(0), Location(0, 0, 0), Normal(0, 0, 0), Primitive(0),
          Time(InTime), Item(-1), Material(0), BoneName(NAME_None) {}
};

class FCollisionHashBase {
public:
    virtual ~FCollisionHashBase();
    virtual void Tick();
    virtual void AddActor(AActor *Actor);
    virtual void RemoveActor(AActor *Actor);
};

class ULevel : public UObject {
public:
    TArray<AActor *> Actors;
    BYTE LevelPad[0x38 - 0x34];
    UEngine *Engine;
    BYTE LevelPad2[0x3a10 - 0x3c];
    FCollisionHashBase *Hash;
    ALevelInfo *GetLevelInfo() { return (ALevelInfo *)Actors(0); }
#define SLOT(n) virtual void LevelSlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
    SLOT(29) SLOT(30) SLOT(31) SLOT(32)
#undef SLOT
    virtual UBOOL MoveActor(AActor *Actor, FVector Delta, FRotator NewRotation, FCheckResult &Hit, UBOOL bTest = 0, UBOOL bIgnorePawns = 0, UBOOL bIgnoreBases = 0, UBOOL bNoFail = 0);
    virtual UBOOL FarMoveActor(AActor *Actor, FVector DestLocation, UBOOL bTest = 0, UBOOL bNoCheck = 0, UBOOL bAttachedMove = 0);
    virtual UBOOL DestroyActor(AActor *ThisActor, UBOOL bNetForce = 0);
    virtual void LevelSlot36();
    virtual AActor *SpawnActor(UClass *Class, FName InName, FVector Location, FRotator Rotation, AActor *Template = 0, UBOOL bNoCollisionFail = 0, UBOOL bRemoteOwned = 0, AActor *Owner = 0, APawn *Instigator = 0);
#define SLOT(n) virtual void LevelSlot##n();
    SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
    SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54)
#undef SLOT
    virtual UBOOL SingleLineCheck(FCheckResult &Hit, AActor *SourceActor, const FVector &End, const FVector &Start, DWORD TraceFlags, FVector Extent, INT Option7, INT Option8);
};

class UMeshInstance;

FLOAT PointToLineDistance(const FVector &Point, FVector &LineOrigin, FVector &LineDir);

// Runtime-initialised global vector the engine uses as a default location.
extern FVector GDefaultVector;

class UMesh : public UObject {
public:
#define SLOT(n) virtual void MeshSlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
    SLOT(29) SLOT(30) SLOT(31) SLOT(32)
#undef SLOT
    virtual UMeshInstance *MeshGetInstance(const AActor *Owner);
};

struct FMeshBone {
    FName Name;
    BYTE BonePad[0x40 - 4];
};

class USkeletalMesh : public UMesh {
public:
    BYTE SkeletalMeshPad[0x148 - 0x28];
    TArray<FMeshBone> RefSkeleton;
    BYTE SkeletalMeshPad2[0x3b0 - 0x154];
    TArray<FName> TagAliases;
    TArray<FName> TagNames;
    static UClass *PrivateStaticClass;
    static UClass *GetPrivateStaticClassUSkeletalMesh(const TCHAR *Package);
    static void InitializePrivateStaticClassUSkeletalMesh();
    static UClass *StaticClass()
    {
        if (!PrivateStaticClass)
        {
            PrivateStaticClass = GetPrivateStaticClassUSkeletalMesh(L"Engine");
            InitializePrivateStaticClassUSkeletalMesh();
        }
        return PrivateStaticClass;
    }
};

// Engine classes whose class objects are created on first use.
#define DECLARE_LAZY_CLASS(Name)                                            static UClass *PrivateStaticClass;                                      static UClass *GetPrivateStaticClass##Name(const TCHAR *Package);       static void InitializePrivateStaticClass##Name();                       static UClass *StaticClass()                                            {                                                                           if (!PrivateStaticClass)                                                {                                                                           PrivateStaticClass = GetPrivateStaticClass##Name(L"Engine");             InitializePrivateStaticClass##Name();                               }                                                                       return PrivateStaticClass;                                          }

class UMeshInstance : public UObject {
public:
#define SLOT(n) virtual void MeshInstanceSlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
    SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33)
#undef SLOT
    virtual UMesh *GetMesh();
#define SLOT(n) virtual void MeshInstanceSlot##n();
    SLOT(35) SLOT(36) SLOT(37) SLOT(38)
    SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48)
    SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58)
    SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64) SLOT(65) SLOT(66)
#undef SLOT
    virtual FName GetActiveAnimSequence(INT Channel);
    virtual FLOAT GetActiveAnimRate(INT Channel);
    virtual FLOAT GetActiveAnimFrame(INT Channel);
    virtual FLOAT GetActiveAnimBlend(INT Channel);
};

struct FBoneScaler {
    INT Bone;
    FName Name;
    FLOAT ScaleUniform;
    BYTE ScalerPad[0x3c - 0xc];
};

class USkeletalMeshInstance : public UMeshInstance {
public:
    BYTE SkeletalPad[0x9c - 0x28];
    TArray<FBoneScaler> Scalers;
    UBOOL SetBoneScale(INT Slot, FLOAT BoneScale, FName BoneName);
    void SetBoneDirection(FName BoneName, FRotator BoneTurn, FVector BoneTrans, FLOAT Alpha, INT Space);
    INT MatchRefBone(FName BoneName);
    FRotator GetBoneRotation(INT BoneIdx, INT Space);
    FCoords GetBoneCoords(INT BoneIdx, INT Space);
    void SetBoneLocation(FName BoneName, FVector BoneTrans, FLOAT Alpha, FLOAT BlendTime, INT Space);
    void SetBoneRotation(FName BoneName, FRotator BoneTurn, INT Space, FLOAT Alpha, FLOAT BlendTime, INT bAdditive, INT bExtra);
};

class AActor : public UObject {
public:
    DECLARE_NATIVE(execSetBoneScale)
    DECLARE_NATIVE(execSpawn)
    DECLARE_NATIVE(execPlaySound)
    UBOOL PlayActorSound(USound *Sound, BYTE Slot, FLOAT Volume, INT Option4, FLOAT Option5, FLOAT Option6);
    DECLARE_NATIVE(execTraceBone)
    AActor *TraceBoneCheck(FName &HitBone, FVector &HitLocation, FVector &HitNormal, const FVector &TraceEnd, const FVector &TraceStart, UMaterial **Material, INT TraceFlags, INT bOption8);
    DECLARE_NATIVE(execTrace)
    AActor *TraceCheck(FVector &HitLocation, FVector &HitNormal, const FVector &TraceEnd, const FVector &TraceStart, const FVector &Extent, UMaterial **Material, INT TraceFlags, INT bOption8, UPrimitive **Primitive, INT Mode);
    AActor *TraceMode(INT Mode, FVector &HitLocation, FVector &HitNormal, const FVector &TraceEnd, const FVector &TraceStart, const FVector &Extent, UMaterial **Material, INT TraceFlags, INT bOption8, UPrimitive **Primitive);
    DECLARE_NATIVE(execAddSoundRequest)
    DECLARE_NATIVE(execMakeNoise)
    DECLARE_NATIVE(execMove)
    DECLARE_NATIVE(execFastTrace)
    UBOOL FastTraceCheck(const FVector &TraceEnd, const FVector &TraceStart, const FVector &Extent, INT TraceFlags, UBOOL bOption);
    DECLARE_NATIVE(execDistancePointToLine)
    DECLARE_NATIVE(execAttachToBone)
    UBOOL AttachToBone(AActor *Attachment, const FName &BoneName, INT Slot, INT Option4, INT Option5, INT Option6, INT Option7, FVector RelLocation, FRotator RelRotation);
    DECLARE_NATIVE(execGetAnimParams)
    DECLARE_NATIVE(execSetBoneDirection)
    DECLARE_NATIVE(execGetBoneRotation)
    DECLARE_NATIVE(execGetBoneCoords)
    DECLARE_NATIVE(execSetBoneLocation)
    DECLARE_NATIVE(execSetBoneRotation)
    DWORD ActorField28;
    DWORD MovementFlags;
    BITFIELD ActorBits30 : 25;
    BITFIELD bCollideActors : 1;
    BITFIELD ActorBits30High : 6;
    BYTE ActorPad[0x54 - 0x34];
    FName Tag;
    BYTE ActorPad0[0x64 - 0x58];
    UMeshInstance *MeshInstance;
    BYTE ActorPad1[0x6c - 0x68];
    AActor *Owner;
    BYTE ActorPad1b[0x7c - 0x70];
    ULevel *XLevel;
    BYTE ActorPad2[0x84 - 0x80];
    APawn *Instigator;
    BYTE ActorPad2b[0xc4 - 0x88];
    FLOAT LatentFloat;
    BYTE ActorPad3[0xe8 - 0xc8];
    FVector Location;
    FRotator Rotation;
    BYTE ActorPad4[0x184 - 0x100];
    UMesh *Mesh;
    BYTE ActorPad5[0x198 - 0x188];
    FVector DrawScale3D;
#define SLOT(n) virtual void ActorSlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
    SLOT(29)
    virtual void PlayOwnedSound(USound *Sound, BYTE Slot);
    SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38)
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
    SLOT(104) SLOT(105) SLOT(106) SLOT(107) SLOT(108) SLOT(109) SLOT(110) SLOT(111) SLOT(112) SLOT(113) SLOT(114) SLOT(115) SLOT(116) SLOT(117) SLOT(118) SLOT(119) SLOT(120) SLOT(121) SLOT(122) SLOT(123) SLOT(124) SLOT(125) SLOT(126) SLOT(127) SLOT(128) SLOT(129) SLOT(130) SLOT(131)
    virtual void MakeNoise(FLOAT Loudness, INT NoiseType, const FVector &NoiseLocation, INT Option4, const FVector &Option5, INT Option6, UBOOL bOption7);
    SLOT(133)
    virtual void StopAllSoundsActor(INT Flags, FLOAT FadeTime, INT Slot);
#undef SLOT
    UBOOL SetRotation(const FRotator &NewRotation);
    UBOOL SetRelativeLocation(const FVector &NewLocation);
    UBOOL SetLocation(const FVector &NewLocation, UBOOL bNoCheck);
    void SetDrawScale3D(FVector NewScale3D);
    void ClearRenderData();
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
    BYTE PawnPad[0x2b8 - sizeof(AActor)];
    DWORD PawnFlags;
    UBOOL PickWallAdjust(FVector WallHitNormal);
    UBOOL pointReachable(FVector aPoint, INT bKnowVisible, INT bExtra);
    FLOAT findPathToward(AActor *Goal, FVector Dest, void *NodeEval, UBOOL bClearPaths, INT bExtra);
    FVector SuggestJumpVelocity(FVector Dest, FLOAT XYSpeed, FLOAT BaseZ);
};

class AController : public AActor {
public:
    DECLARE_NATIVE(execEAdjustJump)
    BYTE ControllerPad[0x2b4 - sizeof(AActor)];
    APawn *Pawn;
    BYTE ControllerPad2[0x2e8 - 0x2b8];
    FVector Destination;
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
public:
    APlayerController *Actor;
};

class UViewport : public UPlayer {
};

class ALevelInfo : public AActor {
public:
    BYTE LevelInfoPad[0x4a4 - sizeof(AActor)];
    DWORD LevelInfoFlags;
};

class APlayerController : public AController {
public:
    BYTE PlayerControllerPad[0x394 - 0x2f4];
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
class UMaterial : public UObject {
public:
    BYTE MaterialPad[0x34 - 0x28];
    UObject *Source;
    void DrawTile(UCanvas *Canvas, UObject *InSource, FLOAT XL, FLOAT YL, FLOAT U, FLOAT V, FLOAT UL, FLOAT VL);
};

class UCanvas : public UObject {
public:
    BYTE CanvasPad[0x50 - 0x28];
    FLOAT CurX, CurY;
    BYTE CanvasPad2[0x64 - 0x58];
    FColor Color;
#define SLOT(n) virtual void CanvasSlot##n();
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
    SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38)
    SLOT(39) SLOT(40) SLOT(41)
#undef SLOT
    virtual void SetDrawColor(BYTE R, BYTE G, BYTE B, BYTE A);
    virtual void DrawText(const TCHAR *Text, UBOOL CR);
    virtual void TextSize(const TCHAR *Text, FLOAT *XL, FLOAT *YL);
    DECLARE_NATIVE(execDrawText)
    DECLARE_NATIVE(execTextSize)
    DECLARE_NATIVE(execSetDrawColor)
};

class UECanvas : public UCanvas {
public:
    DECLARE_NATIVE(execBeginScene)
    DECLARE_NATIVE(execDrawActorPortal)
    DECLARE_NATIVE(execDrawCameraPortal)
    DECLARE_NATIVE(execCreateDepthMask)
    DECLARE_NATIVE(execDrawRectangle)
    DECLARE_NATIVE(execDrawLine)
    void DrawLine(INT X, INT Y, INT XL, INT YL, const FColor &InColor, INT Alpha, UMaterial *Material);
    void DrawRectangle(INT X, INT Y, INT XL, INT YL, INT Thickness, const FColor &Color, INT Alpha, UMaterial *Material);
};

// The PC build reads these console rendering natives' parameters and ignores them.
// Parameters after Slot are named by position; the script declaration is not decoded yet.
// Parameters after the sound are named by position; the script declaration is not decoded yet.
// Parameters after Material are named by position; the script declaration is not decoded yet.
// Parameters after Volume are named by position; the script declaration is not decoded yet.
// @rva 0x90230
UBOOL AActor::SetLocation(const FVector &NewLocation, UBOOL bNoCheck)
{
    return XLevel->FarMoveActor(this, NewLocation, 0, bNoCheck);
}

// @rva 0x17bcb0
UBOOL AActor::PlayActorSound(USound *Sound, BYTE Slot, FLOAT Volume, INT Option4, FLOAT Option5, FLOAT Option6)
{
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio && !(ActorField28 & 4))
        return Audio->PlaySound(this, Sound, Slot, Volume, Option4, Option5, Option6);
    return 0;
}

// @rva 0x903e0
UBOOL AActor::SetRotation(const FRotator &NewRotation)
{
    FCheckResult Hit(1.0f);
    return GetLevel()->MoveActor(this, GDefaultVector, NewRotation, Hit);
}

// @rva 0x95b50
void AActor::SetDrawScale3D(FVector NewScale3D)
{
    if (bCollideActors && GetLevel()->Hash)
        GetLevel()->Hash->RemoveActor(this);
    DrawScale3D = NewScale3D;
    if (bCollideActors && GetLevel()->Hash)
        GetLevel()->Hash->AddActor(this);
    ClearRenderData();
}

// @rva 0x17c770
UBOOL AActor::FastTraceCheck(const FVector &TraceEnd, const FVector &TraceStart, const FVector &Extent, INT TraceFlags, UBOOL bOption)
{
    FCheckResult Hit(1.0f);
    DWORD TraceType = 0x17;
    if (TraceFlags == 1)
        TraceType = 0x8017;
    else if (TraceFlags == 2)
        TraceType = 0x10017;
    else if (TraceFlags == 3)
        TraceType = 0x20017;
    else if (TraceFlags == 4)
        TraceType = 0x80017;
    else if (TraceFlags == 6)
        TraceType = 0x18017;
    if (bOption)
        TraceType |= 8;
    GetLevel()->SingleLineCheck(Hit, this, TraceEnd, TraceStart, TraceType | 0x20, Extent, 0, 0);
    return Hit.Actor == 0;
}

// @rva 0x17c5e0
AActor *AActor::TraceCheck(FVector &HitLocation, FVector &HitNormal, const FVector &TraceEnd, const FVector &TraceStart, const FVector &Extent, UMaterial **Material, INT TraceFlags, INT bOption8, UPrimitive **Primitive, INT Mode)
{
    FCheckResult Hit(1.0f);
    if (Mode > 0 && Mode < 3)
        return TraceMode(Mode, HitLocation, HitNormal, TraceEnd, TraceStart, Extent, Material, TraceFlags, bOption8, Primitive);
    DWORD TraceType = 0x17;
    if (TraceFlags == 1)
        TraceType = 0x8017;
    else if (TraceFlags == 2)
        TraceType = 0x10017;
    else if (TraceFlags == 3)
        TraceType = 0x20017;
    else if (TraceFlags == 4)
        TraceType = 0x80017;
    else if (TraceFlags == 5)
        TraceType = 0x400017;
    else if (TraceFlags == 6)
        TraceType = 0x18017;
    if (bOption8)
        TraceType |= 8;
    if (Material)
        TraceType |= 0x80;
    GetLevel()->SingleLineCheck(Hit, this, TraceEnd, TraceStart, TraceType, Extent, 0, 0);
    HitLocation = Hit.Location;
    HitNormal = Hit.Normal;
    if (Material)
        *Material = Hit.Material;
    if (Primitive)
        *Primitive = Hit.Primitive;
    return Hit.Actor;
}

class AEGameplayColl : public AActor {
public:
    DECLARE_LAZY_CLASS(AEGameplayColl)
};

// @rva 0x183f00
AActor *AActor::TraceBoneCheck(FName &HitBone, FVector &HitLocation, FVector &HitNormal, const FVector &TraceEnd, const FVector &TraceStart, UMaterial **Material, INT TraceFlags, INT bOption8)
{
    DWORD TraceType;
    if (bOption8)
    {
        if (MovementFlags & 0x40)
        {
            ((APawn *)this)->PawnFlags &= ~0x100;
            TraceType = 0x840100;
        }
        else
            TraceType = 0x40100;
    }
    else
        TraceType = 0x20100;
    if (TraceFlags)
        TraceType |= 0x1000;
    if (Material)
        TraceType |= 0x80;
    FCheckResult Hit(1.0f);
    GetLevel()->SingleLineCheck(Hit, this, TraceEnd, TraceStart, TraceType, GDefaultVector, 0, 0);
    if (Hit.Actor)
    {
        HitLocation = Hit.Location;
        HitNormal = Hit.Normal;
        HitBone = Hit.BoneName;
        if (Material)
            *Material = Hit.Material;
        if (TraceFlags)
        {
            if (Hit.Actor->IsA(AEGameplayColl::StaticClass()))
                return Hit.Actor->Owner;
        }
    }
    return Hit.Actor;
}

// @rva 0xd0e30
UBOOL USkeletalMeshInstance::SetBoneScale(INT Slot, FLOAT BoneScale, FName BoneName)
{
    if (Slot < 0 || Slot > 256)
        return 0;
    while (Scalers.Num() <= Slot)
    {
        Scalers.AddZeroed();
        Scalers(Scalers.Num() - 1).Bone = -1;
    }
    if (BoneScale != 1.0f && BoneName != NAME_None)
    {
        INT BoneIdx = MatchRefBone(BoneName);
        if (BoneIdx >= 0)
        {
            Scalers(Slot).Bone = BoneIdx;
            Scalers(Slot).Name = BoneName;
            Scalers(Slot).ScaleUniform = BoneScale;
        }
    }
    else
    {
        Scalers(Slot).Bone = -1;
        Scalers(Slot).Name = NAME_None;
    }
    return 1;
}

// @rva 0xd0850
INT USkeletalMeshInstance::MatchRefBone(FName StartBoneName)
{
    USkeletalMesh *Mesh = (USkeletalMesh *)GetMesh();
    INT Bone = -1;
    if (StartBoneName != NAME_None)
    {
        for (INT t = 0; t < Mesh->TagAliases.Num(); t++)
        {
            if (StartBoneName == Mesh->TagAliases(t))
            {
                StartBoneName = Mesh->TagNames(t);
                break;
            }
        }
        for (INT p = 0; p < ((USkeletalMesh *)GetMesh())->RefSkeleton.Num(); p++)
        {
            if (((USkeletalMesh *)GetMesh())->RefSkeleton(p).Name == StartBoneName)
            {
                Bone = p;
                break;
            }
        }
    }
    return Bone;
}

// @rva 0x332090
void UECanvas::DrawLine(INT X, INT Y, INT XL, INT YL, const FColor &InColor, INT Alpha, UMaterial *Material)
{
    if (!Material)
        return;
    Color.R = InColor.R;
    Color.G = InColor.G;
    Color.B = InColor.B;
    if (Alpha == -1)
        Color.A = InColor.A;
    else
        Color.A = Alpha;
    CurX = X;
    CurY = Y;
    Material->DrawTile(this, Material->Source, XL, YL, 0.0f, 0.0f, 1.0f, 1.0f);
}

// @rva 0x3fc980
FLOAT DampFloat(FLOAT Current, FLOAT Target, FLOAT Rate, FLOAT DeltaTime)
{
    FLOAT MaxDelta = Rate * DeltaTime;
    return Clamp(Target - Current, -MaxDelta, MaxDelta) + Current;
}

// @rva 0x3fc9d0
INT DampInt(INT Current, INT Target, FLOAT Rate, FLOAT DeltaTime)
{
    FLOAT MaxDelta = Rate * DeltaTime;
    return (INT)Clamp((FLOAT)Target - Current, -MaxDelta, MaxDelta) + Current;
}

// @rva 0x3fca20
FVector DampVec(const FVector &Current, const FVector &Target, FLOAT Rate, FLOAT DeltaTime)
{
    FLOAT MaxDelta = Rate * DeltaTime;
    FVector Delta = Target - Current;
    FLOAT Size = Delta.Size();
    if (Size > MaxDelta)
        Delta *= MaxDelta / Size;
    return Delta + Current;
}

// @rva 0x332110
void UECanvas::DrawRectangle(INT X, INT Y, INT XL, INT YL, INT Thickness, const FColor &Color, INT Alpha, UMaterial *Material)
{
    DrawLine(X, Y, XL, Thickness, Color, Alpha, Material);
    DrawLine(X, Y + YL - Thickness, XL, Thickness, Color, Alpha, Material);
    DrawLine(X, Y + Thickness, Thickness, YL - 2 * Thickness, Color, Alpha, Material);
    DrawLine(X + XL - Thickness, Y + Thickness, Thickness, YL - 2 * Thickness, Color, Alpha, Material);
}
