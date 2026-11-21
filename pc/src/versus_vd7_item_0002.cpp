// w4_item_0002.cpp -- Versus work item 0002 (AActor animation natives and PlayAnim)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;

struct FGuid;

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[1];
};

struct FName
{
    INT Index;

    static FNameEntry **Names;

    const TCHAR *operator*() const { return Names[Index]->Name; }
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FString : public FArray
{
public:
    FString(const FString &Other);
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
};

struct FFrame
{
    BYTE unk_0[0xc];
    BYTE *Code;
};

struct FStateFrame
{
    BYTE unk_0[0x24];
    INT LatentAction;
};

#define RESULT_DECL void *const Result
#define P_FINISH Stack.Code++

class FUnknown
{
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown
{
public:
    virtual ~UObject();
    virtual void UObjSlot4();
    virtual void UObjSlot5();
    virtual void UObjSlot6();
    virtual void UObjSlot7();
    virtual void UObjSlot8();
    virtual void Destroy();
    virtual void UObjSlot10();
    virtual void UObjSlot11();
    virtual void UObjSlot12();
    virtual void UObjSlot13();
    virtual void UObjSlot14();
    virtual void UObjSlot15();
    virtual void UObjSlot16();
    virtual void UObjSlot17();
    virtual void UObjSlot18();
    virtual void UObjSlot19();
    virtual void UObjSlot20();
    virtual void UObjSlot21();

    INT Index;
    BYTE unk_8[0x4];
    FStateFrame *StateFrame;
    BYTE unk_10[0xc];
    DWORD ObjectFlags;
    FName Name;
    class UClass *Class;

    const TCHAR *GetName() const { return *Name; }
    FStateFrame *GetStateFrame() const { return StateFrame; }
};

class AActor;
class UMeshInstance;

class UMesh : public UObject
{
public:
    UMeshInstance *MeshGetInstance(const AActor *Owner);
};

class UMeshInstance : public UObject
{
public:
    virtual void MeshInstSlot22();
    virtual void MeshInstSlot23();
    virtual void MeshInstSlot24();
    virtual void MeshInstSlot25();
    virtual void MeshInstSlot26();
    virtual void MeshInstSlot27();
    virtual void MeshInstSlot28();
    virtual void MeshInstSlot29();
    virtual void MeshInstSlot30();
    virtual void MeshInstSlot31();
    virtual void MeshInstSlot32();
    virtual void MeshInstSlot33();
    virtual void MeshInstSlot34();
    virtual void MeshInstSlot35();
    virtual void MeshInstSlot36();
    virtual void PlayAnim(INT Channel, FName SequenceName, FLOAT Rate, FLOAT TweenTime,
                          UBOOL bLoop, UBOOL bBackwards, UBOOL bContinueAtFrame, INT Extra);
};

class AActor : public UObject
{
public:
    virtual void ActorSlot22();
    virtual void ActorSlot23();
    virtual void ActorSlot24();
    virtual void ActorSlot25();
    virtual void ActorSlot26();
    virtual void ActorSlot27();
    virtual void ActorSlot28();
    virtual void ActorSlot29();
    virtual void ActorSlot30();
    virtual void ActorSlot31();
    virtual void ActorSlot32();
    virtual void ActorSlot33();
    virtual void ActorSlot34();
    virtual void ActorSlot35();
    virtual void ActorSlot36();
    virtual void ActorSlot37();
    virtual void ActorSlot38();
    virtual void ActorSlot39();
    virtual void ActorSlot40();
    virtual void ActorSlot41();
    virtual void ActorSlot42();
    virtual void ActorSlot43();
    virtual void ActorSlot44();
    virtual void ActorSlot45();
    virtual void ActorSlot46();
    virtual void ActorSlot47();
    virtual void ActorSlot48();
    virtual void ActorSlot49();
    virtual void ActorSlot50();
    virtual UBOOL CheckAnimFinished(INT Channel);
    virtual void ActorSlot52();
    virtual void ActorSlot53();
    virtual void ActorSlot54();
    virtual void ActorSlot55();
    virtual void ActorSlot56();
    virtual void ActorSlot57();
    virtual void ActorSlot58();
    virtual void ActorSlot59();
    virtual void ActorSlot60();
    virtual void ActorSlot61();
    virtual void ActorSlot62();
    virtual void ActorSlot63();
    virtual void ActorSlot64();
    virtual void ActorSlot65();
    virtual void ActorSlot66();
    virtual void ActorSlot67();
    virtual void ActorSlot68();
    virtual void ActorSlot69();
    virtual void ActorSlot70();
    virtual void ActorSlot71();
    virtual void ActorSlot72();
    virtual void PlayAnim(INT Channel, FName SequenceName, FLOAT Rate, FLOAT TweenTime,
                          UBOOL bLoop, UBOOL bBackwards, UBOOL bContinueAtFrame, INT Extra);

    BYTE unk_28[0x194];
    UMesh *Mesh;
    BYTE unk_1c0[0x14];
    UMeshInstance *MeshInstance;
    BYTE unk_1d8[0x20];
    FLOAT LatentFloat;
    BYTE unk_1fc[0xb0];
    BYTE RepAnimFlags;
    BYTE unk_2ad[0x3f];
    BITFIELD unk_2ec_0 : 2;
    BITFIELD bNetDirty : 1;
    BITFIELD unk_2ec_3 : 7;
    BITFIELD bReplicateAnimations : 1;

    void execPollFinishAnim(FFrame &Stack, RESULT_DECL);
    void execGetMeshName(FFrame &Stack, RESULT_DECL);
};

// Empty wide string literal placed in writable .data/.bss by VC7.0 in retail.
extern const TCHAR EmptyMeshName[];

// AActor::execPollFinishAnim (RVA 0x1234a0)
// Polls CheckAnimFinished for the latent animation channel stored in LatentFloat.
void AActor::execPollFinishAnim(FFrame &Stack, RESULT_DECL)
{
    if (CheckAnimFinished((INT)LatentFloat))
    {
        GetStateFrame()->LatentAction = 0;
    }
}

// AActor::execGetMeshName (RVA 0x1234f0)
// Returns the Mesh object's name as an FString, or an empty string if Mesh is null.
void AActor::execGetMeshName(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;

    if (Mesh)
    {
        *(FString *)Result = FString(Mesh->GetName());
    }
    else
    {
        *(FString *)Result = FString(EmptyMeshName);
    }
}

// AActor::PlayAnim (RVA 0x123590)
// Plays an animation on MeshInstance, updating animation replication flags if enabled.
void AActor::PlayAnim(INT Channel, FName SequenceName, FLOAT Rate, FLOAT TweenTime,
                      UBOOL bLoop, UBOOL bBackwards, UBOOL bContinueAtFrame, INT Extra)
{
    if (Mesh)
    {
        Mesh->MeshGetInstance(this);
        if (bReplicateAnimations)
        {
            if (RepAnimFlags & 0x80)
            {
                RepAnimFlags = (BYTE)bLoop;
            }
            else
            {
                RepAnimFlags = (BYTE)bLoop | 0x80;
            }
            bNetDirty = 1;
        }
        MeshInstance->PlayAnim(Channel, SequenceName, Rate, TweenTime,
                               bLoop, bBackwards, bContinueAtFrame, Extra);
    }
}
