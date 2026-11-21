// Work item 0069: Versus RVA 0x13bc40-0x13c1ff.
// Level scene rendering list helpers and LookAt matrix construction.

typedef int INT;
typedef short SWORD;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned short TCHAR;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }
#define SMALL_NUMBER (1.e-8f)

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const
    {
        return FVector(X - V.X, Y - V.Y, Z - V.Z);
    }
    FLOAT operator|(const FVector &V) const
    {
        return X * V.X + Y * V.Y + Z * V.Z;
    }
    FVector operator^(const FVector &V) const
    {
        return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
    }
    UBOOL Normalize();
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) { X = InX; Y = InY; Z = InZ; W = InW; }
    FPlane(const FPlane &P) : FVector(P.X, P.Y, P.Z), W(P.W) {}
};

struct FMatrix
{
    union
    {
        struct { FPlane XPlane, YPlane, ZPlane, WPlane; };
        FLOAT M[4][4];
    };
    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);
};

// Published at RVA 0x4fbc0 (LTCG: this in EAX, InZ in EDX, InW in ECX, InX/InY on stack).
#pragma auto_inline(off)
FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
    : XPlane(InX), YPlane(InY), ZPlane(InZ), WPlane(InW)
{
}
#pragma auto_inline(on)

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc; // 0x10c73bf0

struct FActorListNode;
struct FDynamicActor;
class FRenderInterface;

struct FPlayerController_13bc40
{
    BYTE Pad00[0x4fc];
    INT VisionMode;                               // 0x4fc
};

struct UViewport_13bc40
{
    BYTE Pad00[0x30];
    FPlayerController_13bc40 *Actor;              // 0x30
    BYTE Pad34[0x120];
    INT Field154;                                 // 0x154
};

struct FSceneNode
{
    BYTE Pad00[0x04];
    UViewport_13bc40 *Viewport;                   // 0x04
    BYTE Pad08[0x04];
    INT Field0C;                                  // 0x0c
    BYTE Pad10[0x184];
    BYTE Field194[0x24];                          // 0x194
    FLOAT Determinant;                            // 0x1b8
};

struct FRenderResource_13bff0
{
    BYTE Pad00[0x34];
    DWORD Flags;                                  // 0x34
};

struct AActor_13bc40
{
    BYTE Pad00[0x130];
    FRenderResource_13bff0 *Resource;             // 0x130
    BYTE Pad134[0x1b3];
    BYTE Field2E7;                                // 0x2e7
};

struct FDynamicActor
{
    AActor_13bc40 *Actor;                         // 0x00
    INT Field04;                                  // 0x04
    FLOAT Determinant;                            // 0x08
    BYTE Pad0C[0x9c];
    INT FieldA8;                                  // 0xa8
    BYTE PadAC[0x18];
    INT FieldC4;                                  // 0xc4
    BYTE PadC8[0x20];
    void *FieldE8;                                // 0xe8
    BYTE PadEC[0x08];
    void *FieldF4;                                // 0xf4

    void UpdateLights_137060(FSceneNode *SceneNode);
    void Render(FSceneNode *SceneNode, void *LightList, void *ProjectorList, FRenderInterface *RI, INT Param5, FActorListNode **Param6);
};

struct FActorListNode
{
    FDynamicActor *Actor;                         // 0x00
    FActorListNode *Next;                         // 0x04
};

struct FTranslucentListNode
{
    INT bIsBsp;                                   // 0x00
    union
    {
        INT iNode;                                // 0x04
        FDynamicActor *Actor;                     // 0x04
    };
    INT Field08;                                  // 0x08
    INT Field0C;                                  // 0x0c
    INT Field10;                                  // 0x10
    INT Field14;                                  // 0x14
    FTranslucentListNode *Next;                   // 0x18
};

struct FBspNode_13bc40
{
    BYTE Pad00[0x50];
    SWORD iSection;                               // 0x50
    BYTE Pad52[0x0a];                             // total size 0x5c
};

struct UModel_13bc40
{
    BYTE Pad00[0x54];
    FBspNode_13bc40 *NodesData;                   // 0x54
};

struct FBspDrawListBase
{
    UModel_13bc40 *Model;                         // 0x00
    INT SectionIndex;                             // 0x04
    INT NumNodes;                                 // 0x08
    INT NumTriangles;                             // 0x0c
    INT *Nodes;                                   // 0x10

    FBspDrawListBase(UModel_13bc40 *InModel)
        : Model(InModel), SectionIndex(-1), NumNodes(0), NumTriangles(0), Nodes(0)
    {
    }
    ~FBspDrawListBase()
    {
        if (Nodes)
            GMalloc->Free(Nodes);
    }
};

struct FTranslucentBspDrawList : public FBspDrawListBase
{
    void *DynamicData;                            // 0x14

    FTranslucentBspDrawList(UModel_13bc40 *InModel)
        : FBspDrawListBase(InModel), DynamicData(0)
    {
    }
    ~FTranslucentBspDrawList()
    {
        if (DynamicData)
            GMalloc->Free(DynamicData);
    }
};

struct FProjectorListNode
{
    void *Item;                                   // 0x00
    FProjectorListNode *Next;                     // 0x04
};

struct FBatchState_13bc40
{
    BYTE Pad00[0x10];
    INT Count;                                    // 0x10 (offset 0x27c in FLevelRenderList)
};

struct FGlobalRenderer_10ca7068
{
    void Render_10a133e0(FSceneNode *SceneNode, FRenderInterface *RI);
};

extern FProjectorListNode *GProjectorList_10c8bc04; // 0x10c8bc04
extern INT GGlobalFlag_10c92290;                    // 0x10c92290
extern INT GGlobalMode_10c4757c;                    // 0x10c4757c
extern FGlobalRenderer_10ca7068 GRenderer_10ca7068; // 0x10ca7068

class FRenderInterface
{
public:
    virtual void PushState() = 0;                 // 0x00
    virtual void PopState() = 0;                  // 0x04
    virtual void Slot08() = 0;                    // 0x08
    virtual void Slot0C() = 0;                    // 0x0c
    virtual void Slot10() = 0;                    // 0x10
    virtual void Slot14() = 0;                    // 0x14
    virtual void Slot18() = 0;                    // 0x18
    virtual void SetCullMode(INT Mode) = 0;       // 0x1c
    virtual void Slot20() = 0;                    // 0x20
    virtual void Slot24() = 0;                    // 0x24
    virtual void Slot28(INT Arg) = 0;             // 0x28
    virtual void Slot2C() = 0;                    // 0x2c
    virtual void Slot30() = 0;                    // 0x30
    virtual void Slot34() = 0;                    // 0x34
    virtual void Slot38() = 0;                    // 0x38
    virtual void Slot3C() = 0;                    // 0x3c
    virtual void Slot40() = 0;                    // 0x40
    virtual void Slot44(BYTE A, void *B, void *C) = 0; // 0x44
    virtual void Slot48() = 0;                    // 0x48
    virtual void Slot4C() = 0;                    // 0x4c
    virtual void Slot50() = 0;                    // 0x50
    virtual void Slot54() = 0;                    // 0x54
    virtual void Slot58() = 0;                    // 0x58
    virtual void Slot5C() = 0;                    // 0x5c
    virtual void Slot60() = 0;                    // 0x60
    virtual void Slot64() = 0;                    // 0x64
    virtual void Slot68() = 0;                    // 0x68
    virtual void SetRenderPass(INT Pass) = 0;     // 0x6c
    virtual void Slot70() = 0;                    // 0x70
    virtual void Slot74() = 0;                    // 0x74
    virtual void Slot78() = 0;                    // 0x78

    BYTE Pad04[0x0c];
    INT CurrentPass;                              // 0x10
    INT Unk14;                                    // 0x14
    FRenderResource_13bff0 *ActiveResource;       // 0x18
};

// Standard calling convention callees of 0x13bc40.
void __stdcall AddBspNode_10a4e9f0(FTranslucentBspDrawList *DrawList, INT iNode, INT Arg3, INT Arg4, INT Arg5, INT Arg6, FSceneNode *SceneNode);
INT __cdecl CheckActorBatch_10a37610(struct FLevelRenderList *List, FDynamicActor *DynActor, void *Param2);
void __cdecl BuildActorBatch_10a4e040(FBatchState_13bc40 *Batch, FDynamicActor *DynActor, FSceneNode *SceneNode, FRenderInterface *RI);
void __stdcall FlushActorBatch_10a4b900(FBatchState_13bc40 *Batch, FSceneNode *SceneNode, FRenderInterface *RI);

// External sink used only by LTCG callee stubs below so they keep their retail conventions.
void ExternalSink(void *, void *, void *, INT);
void ExternalSink2(void *, void *);

// LTCG callees of 0x13bc40 (defined so the linker assigns their retail register conventions).
#pragma auto_inline(off)
void __stdcall RenderBspDrawList_10a4f5d0(FTranslucentBspDrawList *DrawList, FSceneNode *SceneNode, INT Flags, FRenderInterface *RI)
{
    ExternalSink(&DrawList, &SceneNode, &Flags, RI->CurrentPass);
}

void __stdcall RenderProjector_10a4a9c0(FRenderInterface *RI, void *Item, FSceneNode *SceneNode)
{
    RI->PushState();
    ExternalSink2(Item, SceneNode);
    RI->PopState();
    ExternalSink2(Item, RI);
}

void FDynamicActor::UpdateLights_137060(FSceneNode *SceneNode)
{
    ExternalSink(this, Actor, &SceneNode, 0);
}
#pragma auto_inline(on)

struct FLevelRenderList
{
    FSceneNode *SceneNode;                        // 0x00
    FRenderInterface *RI;                         // 0x04
    INT Field08;                                  // 0x08
    UModel_13bc40 *Model;                         // 0x0c
    BYTE Pad10[0x244];
    FTranslucentListNode *TranslucentList;        // 0x254
    FActorListNode *PostActors;                   // 0x258
    BYTE Pad25C[0x0c];
    FActorListNode *SpecialActors;                // 0x268
    FBatchState_13bc40 Batch;                     // 0x26c

    void RenderSpecialActors(FRenderInterface *InRI);
};

// RVA 0x1371d0 (LTCG: List in ESI, DynActor in EDI, bArg1/Arg2 on stack, cdecl)
#pragma auto_inline(off)
void RenderDynamicActor_1371d0(FLevelRenderList *List, FDynamicActor *DynActor, UBOOL bArg1, INT Arg2)
{
    List->RI->PushState();
    List->RI->SetCullMode(List->SceneNode->Determinant * DynActor->Determinant < 0.0f ? 1 : 0);
    if (bArg1 && DynActor->FieldE8 != 0)
        DynActor->UpdateLights_137060(List->SceneNode);
    DynActor->Render(List->SceneNode, DynActor->FieldE8, DynActor->FieldF4, List->RI, Arg2, &List->PostActors);
    List->RI->PopState();
}

// RVA 0x13bc40 (LTCG: List in EBX, SavedProjectors and Param2 on stack, cdecl)
void RenderTranslucentList(FLevelRenderList *List, FProjectorListNode *SavedProjectors, void *Param2)
{
    FSceneNode *LocalSceneNode = List->SceneNode;
    FRenderInterface *LocalRI = List->RI;

    for (FTranslucentListNode *Node = List->TranslucentList; Node != 0; Node = Node->Next)
    {
        if (Node->bIsBsp != 0)
        {
            LocalRI->PushState();
            FTranslucentBspDrawList DrawList(List->Model);
            DrawList.SectionIndex = List->Model->NodesData[Node->iNode].iSection;
            DrawList.Nodes = &Node->iNode;
            AddBspNode_10a4e9f0(&DrawList, Node->iNode, Node->Field08, Node->Field0C, Node->Field10, Node->Field14, LocalSceneNode);
            RenderBspDrawList_10a4f5d0(&DrawList, LocalSceneNode, 3, LocalRI);
            LocalRI->PopState();
        }
        else
        {
            FDynamicActor *DynActor = Node->Actor;
            if (DynActor->Actor->Field2E7 != 0 && LocalSceneNode->Viewport->Actor->VisionMode == 5)
            {
                INT SavedPass = LocalRI->CurrentPass;
                LocalRI->SetRenderPass(0);
                List->RI->Slot74();
                RenderDynamicActor_1371d0(List, DynActor, 0, 2);
                LocalRI->Slot28(0);
                LocalRI->SetRenderPass(10);
                LocalRI->Slot74();
                LocalRI->Slot44(DynActor->Actor->Field2E7, &DynActor->FieldA8, LocalSceneNode->Field194);
                RenderDynamicActor_1371d0(List, DynActor, 0, 2);
                List->RI->Slot78();
                LocalRI->SetRenderPass(11);
                RenderDynamicActor_1371d0(List, DynActor, 0, 2);
                LocalRI->Slot2C();
                LocalRI->SetRenderPass(SavedPass);
            }
            else if (DynActor->FieldC4 != 0)
            {
                GGlobalFlag_10c92290 = 1;
                GGlobalMode_10c4757c = 2;
                RenderDynamicActor_1371d0(List, DynActor, 1, 0);
                GGlobalFlag_10c92290 = 0;
            }
            else if (CheckActorBatch_10a37610(List, DynActor, Param2))
            {
                BuildActorBatch_10a4e040(&List->Batch, Node->Actor, List->SceneNode, List->RI);
                if (List->Batch.Count != 0)
                    FlushActorBatch_10a4b900(&List->Batch, LocalSceneNode, LocalRI);
            }
            else
            {
                RenderDynamicActor_1371d0(List, Node->Actor, 1, 0);
            }
        }

        if (LocalSceneNode->Viewport->Field154 == 0)
        {
            for (FProjectorListNode *Proj = GProjectorList_10c8bc04; Proj != 0; Proj = Proj->Next)
                RenderProjector_10a4a9c0(LocalRI, Proj->Item, LocalSceneNode);
        }
        GProjectorList_10c8bc04 = 0;
    }

    GProjectorList_10c8bc04 = SavedProjectors;

    for (FActorListNode *ActorNode = List->PostActors; ActorNode != 0; ActorNode = ActorNode->Next)
    {
        FDynamicActor *DynActor = ActorNode->Actor;
        List->RI->PushState();
        List->RI->SetCullMode(List->SceneNode->Determinant * DynActor->Determinant < 0.0f ? 1 : 0);
        if (DynActor->FieldE8 != 0)
            DynActor->UpdateLights_137060(List->SceneNode);
        DynActor->Render(List->SceneNode, DynActor->FieldE8, DynActor->FieldF4, List->RI, 0, &List->PostActors);
        List->RI->PopState();
    }

    if (LocalSceneNode->Field0C == 0)
    {
        LocalRI->PushState();
        GRenderer_10ca7068.Render_10a133e0(LocalSceneNode, LocalRI);
        LocalRI->PopState();
    }
}

// RVA 0x13bff0 (LTCG: InRI in EBX, this in EDI)
void FLevelRenderList::RenderSpecialActors(FRenderInterface *InRI)
{
    InRI->SetRenderPass(9);
    for (FActorListNode *Node = SpecialActors; Node; Node = Node->Next)
    {
        FDynamicActor *DynActor = Node->Actor;
        FRenderResource_13bff0 *Res = DynActor->Actor->Resource;
        if (Res && (Res->Flags & 0x100))
        {
            InRI->ActiveResource = Res;
            DynActor->Render(SceneNode, 0, 0, RI, 0, 0);
        }
    }
}

// RVA 0x13c040 (LTCG: LookAt in EAX, Eye in EDX, Up in ECX, Out on stack)
struct FLookAtMatrix : public FMatrix
{
    FLookAtMatrix(const FVector &Eye, const FVector &LookAt, const FVector &Up);
};

FLookAtMatrix::FLookAtMatrix(const FVector &Eye, const FVector &LookAt, const FVector &Up)
{
    FVector ZAxis = LookAt - Eye;
    ZAxis.Normalize();
    FVector XAxis = ZAxis ^ Up;
    XAxis.Normalize();
    FVector YAxis = XAxis ^ ZAxis;
    YAxis.Normalize();
    *(FMatrix *)this = FMatrix(
        FPlane(XAxis.X, YAxis.X, ZAxis.X, 0.0f),
        FPlane(XAxis.Y, YAxis.Y, ZAxis.Y, 0.0f),
        FPlane(XAxis.Z, YAxis.Z, ZAxis.Z, 0.0f),
        FPlane(-(XAxis | Eye), -(YAxis | Eye), -(ZAxis | Eye), 1.0f));
}

UBOOL FVector::Normalize()
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum >= SMALL_NUMBER)
    {
        FLOAT Scale = 1.f / appSqrt(SquareSum);
        X *= Scale; Y *= Scale; Z *= Scale;
        return 1;
    }
    return 0;
}
#pragma auto_inline(on)

// Scaffolding for the LTCG link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);

void Driver_13bc40(FLevelRenderList *List, FProjectorListNode *Saved, void *Param2)
{
    RenderTranslucentList(List, Saved, Param2);
    RenderTranslucentList(List + 1, Saved, Param2);
}

void Driver_13bff0(FLevelRenderList *List, FRenderInterface *RI)
{
    RI->Slot28(1);
    List->RenderSpecialActors(RI);
    RI->Slot2C();
}

void Driver_13c040(FMatrix *Out, const FVector *Eye, const FVector *LookAt, const FVector *Up, const FPlane *P)
{
    for (INT i = 0; i < 8; i++)
    {
        new (&Out[i * 4 + 0]) FMatrix(P[0], P[1], P[2], P[3]);
        new (&Out[i * 4 + 1]) FMatrix(P[4], P[5], P[6], P[7]);
        new (&Out[i * 4 + 2]) FMatrix(P[8], P[9], P[10], P[11]);
        new (&Out[i * 4 + 3]) FMatrix(P[12], P[13], P[14], P[15]);
    }
    new (&Out[0]) FLookAtMatrix(*Eye, *LookAt, *Up);
    new (&Out[1]) FLookAtMatrix(Eye[1], LookAt[1], Up[1]);
}
