// w4_item_0097.cpp -- Versus BSP draw list rendering (RVA 0x14f5d0)

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned short TCHAR;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;
typedef int INT;
typedef DWORD UBOOL;
typedef float FLOAT;

#define NULL 0
#define INDEX_NONE -1

#define PF_TwoSided    0x00000100
#define PF_Unlit       0x00400000
#define PF_SpecialPoly 0x04000000

enum ERenderMode {
    REN_DynLight = 5,
};

enum ECullMode {
    CM_CW   = 0,
    CM_CCW  = 1,
    CM_None = 2,
};

enum EPrimitiveType {
    PT_TriangleList = 0,
};

enum EVertexShader {
    VS_FixedFunction = 0,
};

struct FVector {
    FLOAT X, Y, Z;

    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};

struct FPlane : public FVector {
    FLOAT W;

    FPlane() {}
    FPlane(const FPlane &P) : FVector(P), W(P.W) {}
    FPlane(FVector V, FLOAT InW) : FVector(V), W(InW) {}
};

struct FSphere : public FPlane {
    FSphere() {}
    FSphere(FVector V, FLOAT InW) : FPlane(V, InW) {}
};

// Global pointer to zero vector (0x10ccacc0, initialized to a zero FVector in BSS).
extern FVector *GDefaultVectorPtr;

class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);
    void Remove(INT Index, INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        ((T *)Data)[Index] = Item;
        return Index;
    }
    T Pop()
    {
        T Result = ((T *)Data)[ArrayNum - 1];
        Remove(ArrayNum - 1, 1, sizeof(T));
        return Result;
    }
};

template<class ElementType> class TList {
public:
    ElementType         Element;
    TList<ElementType> *Next;
};

class FString;
class UMaterial;
class AActor;
struct FHitCause;

struct HHitProxy {
    INT        Size;
    HHitProxy *Parent;

    virtual const TCHAR *GetName() const;
    virtual UBOOL IsA(const TCHAR *Str) const;
    virtual void Click(const FHitCause &Cause);
    virtual AActor *GetActor();
};

struct HBspSurf : public HHitProxy {
    INT iSurf;

    HBspSurf(INT InSurf) : iSurf(InSurf) {}
    virtual const TCHAR *GetName() const;
    virtual UBOOL IsA(const TCHAR *Str) const;
};

class FBaseTexture {};
class FVertexStream {};
class FIndexBuffer;
class FRenderInterface;

// Sub-interface at FRenderInterface + 0x14 handling lighting, material and vertex streams.
class FRenderPipeline {
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void EnableLighting(
        FRenderInterface *RI,
        UBOOL UseDynamic,
        UBOOL UseStatic,
        FBaseTexture *LightmapTexture,
        UBOOL Modulate2X,
        FSphere LitSphere);
    virtual void VirtualSlot6();
    virtual void SetVertexStreams(
        FRenderInterface *RI,
        EVertexShader Shader,
        FVertexStream **Streams,
        INT NumStreams);
    virtual void VirtualSlot8();
    virtual void SetMaterial(
        FRenderInterface *RI,
        UMaterial *Material,
        FString *ErrorString);
};

class FRenderInterface {
public:
    virtual void PushState();
    virtual void PopState();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void PushHit(const BYTE *Data, INT Count);
    virtual void PopHit(INT Count, UBOOL bForce);
    virtual void SetCullMode(ECullMode CullMode);
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
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual INT  SetDynamicIndexBuffer(FIndexBuffer *IndexBuffer, INT BaseVertexIndex);
    virtual void DrawPrimitive(
        EPrimitiveType PrimitiveType,
        INT FirstIndex,
        INT NumPrimitives,
        INT MinIndex,
        INT MaxIndex);

    BYTE             unk_04[0x10];
    FRenderPipeline *Pipeline;
};

class APlayerController {
public:
    BYTE unk_00[0x4fc];
    INT  RendMap;
};

class UViewport {
public:
    BYTE               unk_00[0x30];
    APlayerController *Actor;
    BYTE               unk_34[0x10c];
    FRenderInterface  *RI;
    BYTE               unk_144[0x10];
    UBOOL              bHitTesting;
    BYTE               unk_158[0x10];
    TArray<INT>        HitSizes;

    UBOOL HitTesting() { return bHitTesting; }
    void PushHit(const HHitProxy &Hit, INT Size)
    {
        ((HHitProxy &)Hit).Size = Size;
        HitSizes.AddItem(Size);
        RI->PushHit((const BYTE *)&Hit, Size);
    }
    void PopHit(UBOOL bForce)
    {
        INT Size = HitSizes.Pop();
        RI->PopHit(Size, bForce);
    }
};

class FLevelSceneNode {
public:
    BYTE       unk_00[0x4];
    UViewport *Viewport;
};

struct FBspNode {
    BYTE unk_00[0x2c];
    INT  iSurf;
    BYTE unk_30[0x2a];
    BYTE NumVertices;
    BYTE unk_5b;
};

struct FBspVertexStream : public FVertexStream {
    BYTE unk_00[0x20];
};

struct FBspSection {
    FBspVertexStream Vertices;
    UMaterial       *Material;
    DWORD            PolyFlags;
    INT              iLightMapTexture;
    BYTE             unk_2c[0xc];
};

struct FStaticLightMapTexture : public FBaseTexture {
    BYTE unk_00[0x5c];
};

struct FLightMapTexture {
    BYTE                   unk_00[0x14];
    FStaticLightMapTexture StaticTexture;
};

class UModel {
public:
    BYTE                     unk_00[0x54];
    TArray<FBspNode>         Nodes;
    BYTE                     unk_60[0x74];
    TArray<FBspSection>      Sections;
    TArray<FLightMapTexture> LightMapTextures;
};

class AProjector {
public:
    BYTE unk_00[0x2d2];
    BYTE unk_2d2;
};

struct FProjectorRenderInfo {
    AProjector *Projector;
};

struct FBspProjectorDrawList {
    BYTE                  unk_00[0x14];
    FProjectorRenderInfo *ProjectorInfo;

    void Render(FLevelSceneNode *SceneNode, FRenderInterface *RI);
};

class FBspDrawList;

#pragma pack(push, 4)
extern QWORD GNextCacheID;

inline QWORD MakeCacheID(BYTE Base)
{
    return Base + 0x100 * GNextCacheID++;
}

class FIndexBuffer {
public:
    virtual QWORD GetCacheId();
    virtual INT   GetRevision();
    virtual INT   GetSize();
    virtual void  GetContents(void *Data);
    virtual INT   GetIndexSize();
    virtual void  VirtualSlot5();
    virtual void  VirtualSlot6();
    virtual void  VirtualSlot7();
};

class FBspNodeIndexBuffer : public FIndexBuffer {
public:
    FBspDrawList *DrawList;
    QWORD         CacheId;
    WORD          MinIndex;
    WORD          MaxIndex;

    FBspNodeIndexBuffer(FBspDrawList *InDrawList);
};
#pragma pack(pop)

class FBspDrawList {
public:
    UModel                         *Model;
    INT                             SectionIndex;
    INT                             NumNodes;
    INT                             NumTriangles;
    INT                            *Nodes;
    TList<FBspProjectorDrawList *> *Projectors;

    void Render(FLevelSceneNode *SceneNode, FRenderInterface *RI, DWORD Flags);
};

// FBspNodeIndexBuffer::FBspNodeIndexBuffer (RVA 0x14f4a0)
FBspNodeIndexBuffer::FBspNodeIndexBuffer(FBspDrawList *InDrawList)
    : DrawList(InDrawList)
    , CacheId(MakeCacheID(0xe2))
    , MinIndex(0x7fff)
    , MaxIndex(0)
{
}

// FBspDrawList::Render (RVA 0x14f5d0)
void FBspDrawList::Render(FLevelSceneNode *SceneNode, FRenderInterface *RI, DWORD Flags)
{
    if (NumTriangles > 0) {
        FBspSection *Section = &Model->Sections(SectionIndex);

        RI->PushState();

        if (Flags & 1) {
            UBOOL bNotHitTesting = !SceneNode->Viewport->HitTesting();
            FBaseTexture *LightMap = NULL;
            if (SceneNode->Viewport->Actor &&
                SceneNode->Viewport->Actor->RendMap == REN_DynLight &&
                !(Section->PolyFlags & PF_Unlit) &&
                Section->iLightMapTexture != INDEX_NONE &&
                Section->iLightMapTexture < Model->LightMapTextures.Num()) {
                LightMap = &Model->LightMapTextures(Section->iLightMapTexture).StaticTexture;
            }

            RI->Pipeline->EnableLighting(
                RI, 0, 0, LightMap, 0, FSphere(*GDefaultVectorPtr, 0.0f));
            RI->Pipeline->SetMaterial(RI, Section->Material, NULL);

            FVertexStream *Streams[1] = { &Section->Vertices };
            RI->Pipeline->SetVertexStreams(RI, VS_FixedFunction, Streams, 1);

            FBspNodeIndexBuffer IndexBuffer(this);
            INT BaseIndex = RI->SetDynamicIndexBuffer(&IndexBuffer, 0);

            if (Section->PolyFlags & (PF_TwoSided | PF_SpecialPoly)) {
                RI->SetCullMode(CM_None);
            }

            if (bNotHitTesting) {
                RI->DrawPrimitive(
                    PT_TriangleList,
                    BaseIndex,
                    NumTriangles,
                    IndexBuffer.MinIndex,
                    IndexBuffer.MaxIndex);
            } else {
                INT FirstIndex = 0;
                for (INT NodeIndex = 0; NodeIndex < NumNodes; NodeIndex++) {
                    FBspNode *Node = &Model->Nodes(Nodes[NodeIndex]);
                    if (SceneNode->Viewport->HitTesting()) {
                        SceneNode->Viewport->PushHit(HBspSurf(Node->iSurf), sizeof(HBspSurf));
                    }
                    RI->DrawPrimitive(
                        PT_TriangleList,
                        BaseIndex + FirstIndex,
                        Node->NumVertices - 2,
                        IndexBuffer.MinIndex,
                        IndexBuffer.MaxIndex);
                    if (SceneNode->Viewport->HitTesting()) {
                        SceneNode->Viewport->PopHit(0);
                    }
                    FirstIndex += (Node->NumVertices - 2) * 3;
                }
            }
        }

        if (!SceneNode->Viewport->HitTesting() &&
            (Flags & 2) &&
            SceneNode->Viewport->Actor &&
            SceneNode->Viewport->Actor->RendMap == REN_DynLight &&
            !(Section->PolyFlags & PF_Unlit) &&
            Projectors) {
            for (TList<FBspProjectorDrawList *> *ProjectorList = Projectors;
                 ProjectorList;
                 ProjectorList = ProjectorList->Next) {
                if (ProjectorList->Element->ProjectorInfo->Projector->unk_2d2 != 0x16) {
                    ProjectorList->Element->Render(SceneNode, RI);
                }
            }
        }

        RI->PopState();
    }
}

// Scaffolding for the LTCG link, not part of the unit: callees given bodies so the
// linker sees them inside the LTCG module with their retail calling conventions.
void Escape(void *);
INT ExternalProjectorWork(void *Self, void *SceneNode, INT Acc);
INT ExternalStep(INT Value);

__declspec(noinline) void FBspProjectorDrawList::Render(
    FLevelSceneNode *SceneNode, FRenderInterface *RI)
{
    INT Acc = ExternalStep(1);
    for (INT i = 0; i < 8; i++) {
        Acc += ExternalStep(Acc);
    }
    RI->PushState();
    ExternalProjectorWork(this, SceneNode, Acc);
    RI->PopState();
}

void Driver_14f5d0(
    FBspDrawList *DrawList, FLevelSceneNode *SceneNode, FRenderInterface *RI, DWORD Flags)
{
    Escape(&GDefaultVectorPtr);
    Escape(&GNextCacheID);
    DrawList->Render(SceneNode, RI, Flags);
    FBspNodeIndexBuffer Buf(DrawList);
    RI->SetDynamicIndexBuffer(&Buf, 0);
}
