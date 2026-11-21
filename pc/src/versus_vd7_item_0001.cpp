// Work item w4 0001: Versus RVA 0x123140-0x123435, 5 functions.
//   0x123140 AActor::execFinishAnim
//   0x123190 AActor::FinishAnim            (AActor vtable slot 50)
//   0x123250 ASPlayerController::FinishAnim (ASPlayerController vtable slot 50)
//   0x123340 AActor::AnimationFinished      (AActor vtable slot 51)
//   0x1233b0 ASPlayerController::AnimationFinished (ASPlayerController vtable slot 51)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

#define RESULT_DECL void *const Result
#define EPOLL_FinishAnim 386

enum EDrawType
{
    DT_None = 0,
    DT_Sprite = 1,
    DT_Mesh = 2,
};

enum EName
{
    NAME_None = 0,
};

struct FGuid;
struct FFrame;
struct FStateFrame;
class UObject;
class AActor;
class APawn;
class UMesh;
class UMeshInstance;

class __declspec(novtable) FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

class FUnknown
{
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

// Core.Object: 0x28 bytes, 22 virtual functions (Versus)
class UObject : public FUnknown
{
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

    INT Index;
    BYTE unk_8[0x4];
    FStateFrame *StateFrame; // 0x0c
    BYTE unk_10[0x18];
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    class UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

struct FStateFrame : public FFrame
{
    BYTE unk_14[0x10];
    INT LatentAction; // 0x24
};

#define P_GET_INT_OPTX(Var, Def) INT Var = Def; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

// Engine.Primitive: 0x50 bytes, 30 virtual functions (Versus)
class UPrimitive : public UObject
{
public:
    virtual ~UPrimitive();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();

    BYTE unk_28[0x28];
};

// Engine.Mesh: 0x54 bytes, 31 virtual functions (Versus)
class UMesh : public UPrimitive
{
public:
    virtual ~UMesh();
    virtual void VirtualSlot30();

    BYTE unk_50[0x4];

    UMeshInstance *MeshGetInstance(const AActor *Owner); // RVA 0xdf4e0
};

// Engine.MeshInstance: 0x50 bytes, 71 virtual functions (Versus)
class UMeshInstance : public UPrimitive
{
public:
    virtual ~UMeshInstance();
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
    virtual UBOOL IsAnimating(INT Channel);          // slot 51 (0xcc)
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual UBOOL IsAnimLooping(INT Channel);        // slot 55 (0xdc)
    virtual void VirtualSlot56();
    virtual UBOOL IsAnimPastLastFrame(INT Channel);  // slot 57 (0xe4)
    virtual UBOOL AnimStopLooping(INT Channel);      // slot 58 (0xe8)
};

// Engine.Actor: 0x2f8 bytes, 78 virtual functions (Versus)
class AActor : public UObject
{
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
    virtual void FinishAnim();                       // slot 50 (0xc8)
    virtual UBOOL AnimationFinished(INT Channel);    // slot 51 (0xcc)

    BYTE unk_28[0x194];
    UMesh *Mesh;                                     // 0x1bc
    BYTE unk_1c0[0x14];
    UMeshInstance *MeshInstance;                     // 0x1d4
    BYTE unk_1d8[0x20];
    FLOAT LatentFloat;                               // 0x1f8
    BYTE unk_1fc[0xdd];
    BYTE DrawType;                                   // 0x2d9
    BYTE unk_2da[0x1e];

    __forceinline UBOOL IsAnimating(INT Channel = 0) const
    {
        if (DrawType == DT_Mesh && Mesh)
        {
            Mesh->MeshGetInstance(this);
            if (MeshInstance->IsAnimating(Channel))
                return 1;
        }
        return 0;
    }

    void execFinishAnim(FFrame &Stack, RESULT_DECL);
};

// Engine.Pawn: 0x4b0 bytes (Versus)
class APawn : public AActor
{
public:
    BYTE unk_2f8[0x1b8];
};

// Engine.Controller: 0x3c4 bytes (Versus)
class AController : public AActor
{
public:
    BYTE unk_2f8[0x4];
    APawn *Pawn;                                     // 0x2fc
    BYTE unk_300[0xc4];
};

// Engine.PlayerController: 0x604 bytes (Versus)
class APlayerController : public AController
{
public:
    BYTE unk_3c4[0x240];
};

// SBase.SPlayerController (Versus)
class ASPlayerController : public APlayerController
{
public:
    virtual void FinishAnim();                       // slot 50 (0xc8)
    virtual UBOOL AnimationFinished(INT Channel);    // slot 51 (0xcc)
};

// AActor::execFinishAnim (RVA 0x123140)
void AActor::execFinishAnim(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT_OPTX(Channel, 0);
    P_FINISH;

    LatentFloat = (FLOAT)Channel;
    FinishAnim();
}

// AActor::FinishAnim (RVA 0x123190)
void AActor::FinishAnim()
{
    if (Mesh)
    {
        Mesh->MeshGetInstance(this);
        if (MeshInstance->IsAnimLooping((INT)LatentFloat))
            MeshInstance->AnimStopLooping((INT)LatentFloat);
        if (IsAnimating((INT)LatentFloat) && !MeshInstance->IsAnimPastLastFrame((INT)LatentFloat))
            StateFrame->LatentAction = EPOLL_FinishAnim;
    }
}

// ASPlayerController::FinishAnim (RVA 0x123250)
void ASPlayerController::FinishAnim()
{
    if (Pawn && Pawn->Mesh)
    {
        Pawn->Mesh->MeshGetInstance(this);
        if (Pawn->MeshInstance->IsAnimLooping((INT)LatentFloat))
            Pawn->MeshInstance->AnimStopLooping((INT)LatentFloat);
        if (Pawn->IsAnimating((INT)LatentFloat)
            && !Pawn->MeshInstance->IsAnimPastLastFrame((INT)LatentFloat))
            StateFrame->LatentAction = EPOLL_FinishAnim;
    }
}

// AActor::AnimationFinished (RVA 0x123340)
UBOOL AActor::AnimationFinished(INT Channel)
{
    if (!Mesh)
        return 1;
    Mesh->MeshGetInstance(this);
    if (IsAnimating(Channel) && !MeshInstance->IsAnimPastLastFrame(Channel))
        return 0;
    return 1;
}

// ASPlayerController::AnimationFinished (RVA 0x1233b0)
UBOOL ASPlayerController::AnimationFinished(INT Channel)
{
    if (!Pawn || !Pawn->Mesh)
        return 1;
    Pawn->Mesh->MeshGetInstance(this);
    if (Pawn->IsAnimating(Channel) && !Pawn->MeshInstance->IsAnimPastLastFrame(Channel))
        return 0;
    return 1;
}
