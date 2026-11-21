// Work item 0019: AActor::execPlaySound (Versus RVA 0x125e50)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

#define RESULT_DECL void *const Result

enum EName {
    NAME_None = 0
};

enum ENetMode {
    NM_Standalone = 0,
    NM_DedicatedServer = 1,
    NM_ListenServer = 2,
    NM_Client = 3
};

enum ESoundSlot {
    SLOT_None = 0,
    SLOT_Misc = 1
};

enum EClassCastFlags {
    CLASS_IsAUFunction = 0x00080000
};

enum EFunctionFlags {
    FUNC_Simulated = 0x00000100
};

struct FName {
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
    UBOOL operator!=(EName N) const { return Index != N; }
};

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};

template<class T> struct TArray {
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

struct FGuid;
struct FFrame;
class UClass;
class UStruct;
class UFunction;
class USound;
class USkeletalMeshInstance;
class APawn;
class ALevelInfo;
class AController;
class APlayerController;
class ULevel;
class UEngine;
class UClient;
class UViewport;

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

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
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();

    INT     Index;
    BYTE    unk_08[0x1c];
    UClass *Class;

    INT GetIndex() const { return Index; }
    UClass *GetClass() const { return Class; }
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    UStruct *Node;
    UObject *Object;
    BYTE    *Code;
    BYTE    *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_UBOOL(Var) DWORD Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_UBOOL_OPTX(Var, Def) DWORD Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_BYTE_OPTX(Var, Def) BYTE Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT_OPTX(Var, Def) FLOAT Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_NAME_OPTX(Var, Def) FName Var = Def; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class UClass : public UObject {
public:
    BYTE  unk_28[0x60];
    DWORD ClassCastFlags;
};

class UStruct : public UObject {
public:
};

class UFunction : public UStruct {
public:
    enum { StaticClassCastFlag = CLASS_IsAUFunction };
    BYTE  unk_28[0x40];
    DWORD FunctionFlags;
};

template<class T> inline T *Cast(UObject *Src)
{
    return (Src && (Src->GetClass()->ClassCastFlags & T::StaticClassCastFlag)) ? (T *)Src : 0;
}

class USkeletalMeshInstance : public UObject {
public:
    INT FindAnimIndex(FName SeqName);
};

class AActor : public UObject {
public:
    virtual ~AActor();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void VirtualSlot63();
    virtual void VirtualSlot64();
    virtual void VirtualSlot65();
    virtual void VirtualSlot66();
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void VirtualSlot73();
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();

    BYTE                   unk_28[0xdc];
    AActor                *Owner;                // 0x104
    BYTE                   unk_108[0x8c];
    APawn                 *Instigator;           // 0x194
    BYTE                   unk_198[0x8];
    ALevelInfo            *Level;                // 0x1a0
    ULevel                *XLevel;               // 0x1a4
    BYTE                   unk_1a8[0x2c];
    USkeletalMeshInstance *MeshInstance;         // 0x1d4
    BYTE                   unk_1d8[0x9c];
    FLOAT                  TransientSoundVolume; // 0x274
    FLOAT                  TransientSoundRadius; // 0x278
    BYTE                   unk_27c[0x7c];

    void execPlaySound(FFrame &Stack, RESULT_DECL);
};

class APawn : public AActor {
public:
    BYTE  unk_2f8[0x148];
    FLOAT SoundDampening; // 0x440
};

class ALevelInfo : public AActor {
public:
    BYTE         unk_2f8[0x1b0];
    BYTE         NetMode;        // 0x4a8
    BYTE         unk_4a9[0x67];
    AController *ControllerList; // 0x510
};

class AController : public AActor {
public:
    virtual void CheckHearSound(AActor *SoundMaker, INT Id, USound *S, FVector &Parameters,
                                FLOAT Radius, UBOOL Attenuate, INT AnimIndex);

    BYTE         unk_2f8[0x18];
    DWORD        bIsPlayer : 1;  // 0x310
    BYTE         unk_314[0x10];
    AController *nextController; // 0x324
};

class APlayerController : public AController {
public:
};

class UViewport : public UObject {
public:
    BYTE               unk_28[0x8];
    APlayerController *Actor; // 0x30
};

class UClient : public UObject {
public:
    BYTE                unk_28[0x4];
    TArray<UViewport *> Viewports; // 0x2c
};

class UEngine : public UObject {
public:
    BYTE     unk_28[0x8];
    UClient *Client; // 0x30
};

class ULevel : public UObject {
public:
    BYTE     unk_28[0xc8];
    UEngine *Engine; // 0xf0
};

extern FLOAT GAudioDefaultRadius;

// AActor::execPlaySound
void AActor::execPlaySound(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Sound);
    P_GET_BYTE_OPTX(Slot, SLOT_Misc);
    P_GET_FLOAT_OPTX(Volume, TransientSoundVolume);
    P_GET_UBOOL(bNoOverride);
    P_GET_FLOAT_OPTX(Radius, TransientSoundRadius);
    P_GET_FLOAT_OPTX(Pitch, 1.0f);
    P_GET_UBOOL_OPTX(Attenuate, 1);
    P_GET_NAME_OPTX(AnimName, NAME_None);
    P_FINISH;

    if (!Sound)
        return;

    if (Instigator && (Instigator == this || Instigator == Owner))
        Volume *= Instigator->SoundDampening;

    INT AnimIndex = (AnimName != NAME_None) ? MeshInstance->FindAnimIndex(AnimName) : -1;

    INT Id = GetIndex() * 16 + Slot * 2 + bNoOverride;
    FVector Parameters(Volume, Radius, Pitch);

    UFunction *Func = Cast<UFunction>(Stack.Node);
    if (Level->NetMode != NM_Client && !(Func && (Func->FunctionFlags & FUNC_Simulated))) {
        for (AController *C = Level->ControllerList; C; C = C->nextController) {
            if (C->bIsPlayer)
                C->CheckHearSound(this, Id, Sound, Parameters,
                                  Radius ? Radius : GAudioDefaultRadius, Attenuate, AnimIndex);
        }
    } else {
        UClient *Client = XLevel->Engine->Client;
        if (Client) {
            for (INT i = 0; i < Client->Viewports.Num(); i++) {
                APlayerController *Actor = Client->Viewports(i)->Actor;
                if (Actor && Actor->XLevel == XLevel)
                    Actor->CheckHearSound(this, Id, Sound, Parameters, Radius, Attenuate,
                                          AnimIndex);
            }
        }
    }
}
