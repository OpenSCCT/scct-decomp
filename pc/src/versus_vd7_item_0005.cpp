// Versus work item 0005: AActor::execStopAnimating (RVA 0x123a70)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

struct FName
{
    DWORD Index;
    FName() {}
    FName(DWORD InIndex) : Index(InIndex) {}
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};

extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    INT Num() const { return ArrayNum; }
    void Empty(INT ElementSize, INT Slack = 0)
    {
        ArrayNum = 0;
        if (ArrayMax != Slack) {
            ArrayMax = Slack;
            if (Data || ArrayMax) {
                if (ArrayMax)
                    Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, L"FArray");
                else if (Data) {
                    GMalloc->Free(Data);
                    Data = 0;
                }
            }
        }
    }
};

template <class T>
class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
    void Empty(INT Slack = 0) { FArray::Empty(sizeof(T), Slack); }
};

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

class UClass;

class UObject
{
public:
    virtual ~UObject();

    INT Index;
    DWORD HashNext;
    void *StateFrame;
    void *Linker;
    INT LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;

    UBOOL IsA(UClass *SomeBase) const;
};

class UField : public UObject
{
public:
    UField *SuperField;
    UField *Next;
};

class UClass : public UField
{
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

template <class T>
inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

struct FFrame;
typedef void (UObject::*Native)(FFrame &TheStack, void *const Result);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    class UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define RESULT_DECL void *const Result
#define P_GET_UBOOL_OPTX(var, def) UBOOL var = (def); Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

class AActor;
class UMeshInstance;

class UPrimitive : public UObject
{
public:
    virtual void VirtualSlot01();
    virtual void VirtualSlot02();
    virtual void VirtualSlot03();
    virtual void VirtualSlot04();
    virtual void VirtualSlot05();
    virtual void VirtualSlot06();
    virtual void VirtualSlot07();
    virtual void VirtualSlot08();
    virtual void VirtualSlot09();
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

    BYTE unk_28[0x2c];
};

class UMesh : public UPrimitive
{
public:
    UMeshInstance *MeshGetInstance(const AActor *Owner);
};

class UMeshInstance : public UPrimitive
{
public:
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
    virtual UBOOL StopAnimating(); // vtable offset 0xd0 (slot 52)
};

struct FAnimChannel
{
    BYTE unk_00[0x08];
    FName AnimSequence;         // +0x08
    FLOAT AnimRate;             // +0x0c
    BYTE unk_10[0x08];
    FLOAT TweenRate;            // +0x18
    BYTE unk_1c[0x34];
    FLOAT AnimBlend;            // +0x50
    BYTE unk_54[0x3c];
};

class USkeletalMeshInstance : public UMeshInstance
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }

    BYTE unk_54[0xac];
    TArray<FAnimChannel> Channels; // +0x100
    BYTE unk_10c[0x0c];
    TArray<BYTE> unk_118;          // +0x118
    TArray<BYTE> unk_124;          // +0x124

    UBOOL StopAnimating(UBOOL ClearAllButBase);
};

class AActor : public UObject
{
public:
    BYTE unk_28[0x1bc - 0x28];
    UMesh *Mesh;                   // +0x1bc
    BYTE unk_1c0[0x14];
    UMeshInstance *MeshInstance;   // +0x1d4

    void execStopAnimating(FFrame &Stack, RESULT_DECL);
};

// USkeletalMeshInstance::StopAnimating (RVA 0xb59d0, callee for LTCG convention)
UBOOL USkeletalMeshInstance::StopAnimating(UBOOL ClearAllButBase)
{
    for (INT i = 0; i < Channels.Num(); i++) {
        Channels(i).AnimRate = 0.0f;
        Channels(i).TweenRate = 0.0f;
    }
    if (ClearAllButBase) {
        unk_118.Empty();
        unk_124.Empty();
        for (INT i = 1; i < Channels.Num(); i++) {
            Channels(i).AnimBlend = 0.0f;
            Channels(i).AnimSequence = 0;
        }
    }
    return 1;
}

// AActor::execStopAnimating (RVA 0x123a70)
void AActor::execStopAnimating(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL_OPTX(ClearAllButBase, 0);
    P_FINISH;
    if (Mesh) {
        Mesh->MeshGetInstance(this);
        USkeletalMeshInstance *SkelInst = Cast<USkeletalMeshInstance>(MeshInstance);
        if (SkelInst)
            SkelInst->StopAnimating(ClearAllButBase);
        else
            MeshInstance->StopAnimating();
    }
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_123a70(AActor *A, FFrame *Stack, void *Result, USkeletalMeshInstance *S, UBOOL Clear)
{
    Escape(&GMalloc);
    Escape(GNatives);
    Escape(&USkeletalMeshInstance::PrivateStaticClass);
    void (AActor::*Exec)(FFrame &, void *const) = &AActor::execStopAnimating;
    Escape(&Exec);
    (A->*Exec)(*Stack, Result);
    Escape((void *)S->StopAnimating(Clear));
}
