// Work item 0195: Versus RVA 0xe3c80-0xe3db3 (VC7.0 /GL, linked /LTCG).
// FActorSceneNode methods (UE2 Engine/UnScene.cpp):
//   0xe3c80: FActorSceneNode::FActorSceneNode
//   0xe3cb0: FActorSceneNode::Render
//   0xe3d90: FActorSceneNode::`scalar deleting destructor'

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
inline void operator delete(void *Ptr, const TCHAR *Tag) { GMalloc->Free(Ptr); }
inline void operator delete(void *Ptr) { GMalloc->Free(Ptr); }

struct FVector { FLOAT X, Y, Z; };
struct FRotator { INT Pitch, Yaw, Roll; };
struct FMatrix { FLOAT M[4][4]; };

// FMemStack / FMemMark (UE2 Core/UnMem.h).
class FMemStack
{
public:
    struct FTaggedMemory
    {
        FTaggedMemory *Next;
        INT DataSize;
        BYTE Data[1];
    };

    BYTE *Top;
    BYTE *End;
    INT DefaultChunkSize;
    FTaggedMemory *TopChunk;

    static FTaggedMemory *UnusedChunks;

    __declspec(noinline) void FreeChunks(FTaggedMemory *NewTopChunk);
};
extern FMemStack GMem;

class FMemMark
{
public:
    FMemMark(FMemStack &InMem)
    {
        Mem = &InMem;
        Top = Mem->Top;
        SavedChunk = Mem->TopChunk;
    }
    void Pop()
    {
        if (SavedChunk != Mem->TopChunk)
            Mem->FreeChunks(SavedChunk);
        Mem->Top = Top;
    }
private:
    FMemStack *Mem;
    BYTE *Top;
    FMemStack::FTaggedMemory *SavedChunk;
};

enum ETransformType
{
    TT_LocalToWorld = 0,
    TT_WorldToCamera = 1,
    TT_CameraToScreen = 2
};

class FRenderInterface;

class FRenderDeviceProxy
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void SetTransform(FRenderInterface *RI, ETransformType Type, const FMatrix &Matrix); // +0x18
};

class FRenderInterface
{
public:
    virtual void PushState();  // +0x00
    virtual void PopState();   // +0x04
    BYTE Pad04[0x14 - 0x04];
    FRenderDeviceProxy *Proxy; // +0x14

    inline void SetTransform(ETransformType Type, const FMatrix &Matrix)
    {
        Proxy->SetTransform(this, Type, Matrix);
    }
};

class FRenderTarget
{
public:
    void Touch();
};
class FSceneNode;
class FDynamicActor;
class AActor;

struct FDynamicActorNode
{
    FDynamicActor *Actor;
    FDynamicActorNode *Next;
};

class FDynamicActor
{
public:
    AActor *Actor;
    INT Revision;
    BYTE Pad08[0xf8 - 0x08];

    __declspec(noinline) FDynamicActor(AActor *InActor);
    void Render(FSceneNode *SceneNode, void *Lights, void *Projectors,
                FRenderInterface *RI, INT Mode, FDynamicActorNode **OutList);
};

class AActor
{
public:
    BYTE Pad000[0x12c];
    FDynamicActor *ActorRenderData; // +0x12c
    void *Field130;                 // +0x130
    INT Revision;                   // +0x134
    BYTE Pad138[0x1a0 - 0x138];
    AActor *Level;                  // +0x1a0
    BYTE Pad1A4[0x2e8 - 0x1a4];
    DWORD Flags2E8;                 // +0x2e8
    BYTE Pad2EC[0x3c4 - 0x2ec];
    FMatrix Matrix3C4;              // +0x3c4
    BYTE Pad404[0x5f0 - 0x404];
    DWORD Flags5F0;                 // +0x5f0

    __declspec(noinline) FDynamicActor *GetActorRenderData();
    __declspec(noinline) void RebuildActorRenderData();
};

class UViewport
{
public:
    BYTE Pad00[0x30];
    AActor *Actor;                  // +0x30
};

class FSceneNode
{
public:
    UViewport *Viewport;            // +0x04
    FRenderTarget *RenderTarget;    // +0x08
    FSceneNode *Parent;             // +0x0c
    INT Recursion;                  // +0x10
    FMatrix WorldToCamera;          // +0x14
    FMatrix CameraToWorld;          // +0x54
    FMatrix CameraToScreen;         // +0x94
    BYTE PadD4[0x1c0 - 0xd4];
    INT Field1C0;                   // +0x1c0

    FSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget)
        : Viewport(InViewport), RenderTarget(InRenderTarget), Parent(0), Recursion(0) {}
    virtual ~FSceneNode() {}
    virtual FSceneNode *GetLodSceneNode();
    virtual void Render(FRenderInterface *RI, UBOOL bParam) = 0;
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Slot10();
    virtual UBOOL FilterActor(AActor *InActor);
    virtual void Slot12();
};

class FLevelSceneNode : public FSceneNode
{
public:
    __declspec(noinline) FLevelSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget);
};

class FCameraSceneNode : public FLevelSceneNode
{
public:
    AActor *CameraActor;            // +0x1c4
    BYTE Pad1C8[0x1e8 - 0x1c8];

    __declspec(noinline) FCameraSceneNode(
        UViewport *InViewport,
        FRenderTarget *InRenderTarget,
        AActor *InCameraActor,
        const FVector &InCameraLocation,
        const FRotator &InCameraRotation,
        FLOAT InCameraFOV
    );
    virtual void Render(FRenderInterface *RI, UBOOL bParam);
};

class FActorSceneNode : public FCameraSceneNode
{
public:
    AActor *Actor;                  // +0x1e8

    __declspec(noinline) FActorSceneNode(
        UViewport *InViewport,
        FRenderTarget *InRenderTarget,
        AActor *InActor,
        AActor *InCameraActor,
        FVector InCameraLocation,
        FRotator InCameraRotation,
        FLOAT InCameraFOV
    );
    virtual FSceneNode *GetLodSceneNode();
    virtual void Render(FRenderInterface *RI, UBOOL bParam);
    virtual UBOOL FilterActor(AActor *InActor);
};

// RVA 0xe3c80
FActorSceneNode::FActorSceneNode(
    UViewport *InViewport,
    FRenderTarget *InRenderTarget,
    AActor *InActor,
    AActor *InCameraActor,
    FVector InCameraLocation,
    FRotator InCameraRotation,
    FLOAT InCameraFOV
) : FCameraSceneNode(InViewport, InRenderTarget, InCameraActor, InCameraLocation, InCameraRotation, InCameraFOV),
    Actor(InActor)
{
}

// RVA 0xe3cb0
void FActorSceneNode::Render(FRenderInterface *RI, UBOOL bParam)
{
    FMemMark Mark(GMem);

    RI->PushState();

    if (Viewport->Actor->Flags5F0 & 0x200)
        RI->SetTransform(TT_WorldToCamera, Viewport->Actor->Matrix3C4);
    else
        RI->SetTransform(TT_WorldToCamera, WorldToCamera);

    RI->SetTransform(TT_CameraToScreen, CameraToScreen);

    FDynamicActorNode *TempList;
    Actor->GetActorRenderData()->Render(this, 0, 0, RI, 2, &TempList);

    RI->PopState();
    Mark.Pop();
}

// RVA 0xe3d90 is the compiler-generated scalar deleting destructor of FActorSceneNode.

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit.
void Escape(void *);
extern const TCHAR NewTag_90c90[];

FLevelSceneNode::FLevelSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget)
    : FSceneNode(InViewport, InRenderTarget)
{
    InRenderTarget->Touch();
    AActor *A = InViewport->Actor;
    Field1C0 = A->Revision;
    Escape(A->Level);
    Escape(A->ActorRenderData);
}

void FMemStack::FreeChunks(FTaggedMemory *NewTopChunk)
{
    while (TopChunk != NewTopChunk)
    {
        FTaggedMemory *RemoveChunk = TopChunk;
        TopChunk = TopChunk->Next;
        RemoveChunk->Next = UnusedChunks;
        UnusedChunks = RemoveChunk;
    }
    if (TopChunk)
    {
        Top = TopChunk->Data;
        End = Top + TopChunk->DataSize;
    }
    else
    {
        Top = 0;
        End = 0;
    }
}

FDynamicActor *AActor::GetActorRenderData()
{
    if (!ActorRenderData)
        ActorRenderData = new(NewTag_90c90) FDynamicActor(this);
    if (ActorRenderData->Revision != Revision)
        RebuildActorRenderData();
    return ActorRenderData;
}

void ComputePoint(INT A, const FVector *Loc, AActor *Level);
void FinishCamera(FCameraSceneNode *Node, const FRotator *Rot, FLOAT FOV);

FCameraSceneNode::FCameraSceneNode(
    UViewport *InViewport,
    FRenderTarget *InRenderTarget,
    AActor *InCameraActor,
    const FVector &InCameraLocation,
    const FRotator &InCameraRotation,
    FLOAT InCameraFOV
) : FLevelSceneNode(InViewport, InRenderTarget)
{
    Escape(&InViewport);
    ComputePoint(Field1C0, &InCameraLocation, InCameraActor->Level);
    Escape((void *)&InCameraLocation.X);
    Escape((void *)&InCameraLocation.Y);
    Escape((void *)&InCameraLocation.Z);
    CameraActor = InCameraActor;
    ComputePoint(Field1C0, &InCameraLocation, InCameraActor->Level);
    FinishCamera(this, &InCameraRotation, InCameraFOV);
}

#pragma inline_depth(0)
void Driver_e3c80(
    UViewport *VP,
    FRenderTarget *RT,
    AActor *Act,
    AActor *CamAct,
    FVector Loc,
    FRotator Rot,
    FLOAT FOV,
    FRenderInterface *RI,
    UBOOL Flag,
    FMemStack *M,
    FMemStack::FTaggedMemory *Chunk
)
{
    Escape(&GMalloc);
    Escape(&GMem);
    Escape(&FMemStack::UnusedChunks);
    M->FreeChunks(Chunk);
    Escape(Act->GetActorRenderData());
    Escape(Act->GetActorRenderData());

    FActorSceneNode Node(VP, RT, Act, CamAct, Loc, Rot, FOV);
    Node.Render(RI, Flag);
    Escape(&Node);

    FActorSceneNode *HeapNode = new(NewTag_90c90) FActorSceneNode(VP, RT, Act, CamAct, Loc, Rot, FOV);
    delete HeapNode;
}
#pragma inline_depth()
