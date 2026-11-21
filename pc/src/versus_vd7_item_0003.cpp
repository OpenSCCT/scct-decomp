// w4_item_0003.cpp -- AActor::PlayAnimAfter and AActor::execPlayAnimAfter (Versus)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef int UBOOL;
typedef unsigned short TCHAR;

enum EName {
    NAME_None = 0
};

struct FName {
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
};

struct FGuid;
struct FFrame;

#define RESULT_DECL void *const Result
#define DECLARE_NATIVE(Name) void Name(FFrame &Stack, RESULT_DECL);

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

    BYTE unk_4[0x24];
};

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    class UStruct *Node;
    UObject       *Object;
    BYTE          *Code;
    BYTE          *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_UBOOL(Var) DWORD Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_INT(Var) INT Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT_OPTX(Var, Def) FLOAT Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_NAME(Var) FName Var; Var.Index = 0; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class UPrimitive : public UObject {
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

class AActor;
class UMeshInstance;

class UMesh : public UPrimitive {
public:
    virtual ~UMesh();
    virtual void VirtualSlot30();

    BYTE unk_50[0x4];

    UMeshInstance *MeshGetInstance(const AActor *Owner);
};

class UMeshInstance : public UPrimitive {
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
    virtual void PlayAnimAfter(INT Channel, FName Sequence, FLOAT Rate, FLOAT TweenTime,
                               UBOOL bLoop, UBOOL bBackwards);
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
    virtual void PlayAnim(INT Channel, FName Sequence, FLOAT Rate, FLOAT TweenTime, INT bLoop,
                          INT bBackwards, INT bContinue, INT Extra);
    virtual void PlayAnimAfter(INT Channel, FName Sequence, FLOAT Rate, FLOAT TweenTime,
                               UBOOL bLoop, UBOOL bBackwards);

    BYTE           unk_28[0x194];
    UMesh         *Mesh;
    BYTE           unk_1c0[0x14];
    UMeshInstance *MeshInstance;

    DECLARE_NATIVE(execPlayAnimAfter)
};

// AActor::PlayAnimAfter
void AActor::PlayAnimAfter(INT Channel, FName Sequence, FLOAT Rate, FLOAT TweenTime, UBOOL bLoop,
                           UBOOL bBackwards)
{
    if (Mesh) {
        Mesh->MeshGetInstance(this);
        MeshInstance->PlayAnimAfter(Channel, Sequence, Rate, TweenTime, bLoop, bBackwards);
    }
}

// AActor::execPlayAnimAfter
void AActor::execPlayAnimAfter(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(Sequence);
    P_GET_FLOAT_OPTX(Rate, 1.0f);
    P_GET_FLOAT(TweenTime);
    P_GET_INT(Channel);
    P_GET_UBOOL(bBackwards);
    P_FINISH;
    PlayAnimAfter(Channel, Sequence, Rate, TweenTime, 0, bBackwards);
}
