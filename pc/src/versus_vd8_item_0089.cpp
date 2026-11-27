#include "versus_build.h"
#include "versus_material.h"
#include "versus_arrays.h"
#include "versus_render_streams.h"
#include "unreal_math.h"

extern unsigned __int64 GCacheCounter;
enum ECacheIDBase { CID_RenderData = 0xe1 };
inline unsigned __int64 MakeCacheID(ECacheIDBase Base)
{
    return GCacheCounter++ * 256 + Base;
}

#pragma pack(push, 4)
struct FStaticMeshSection {
    INT   unk_00;
    UBOOL IsStrip;
    _WORD FirstIndex;
    _WORD MinVertexIndex;
    _WORD MaxVertexIndex;
    _WORD NumTriangles;
    _WORD NumPrimitives;
    _WORD unk_12;
};

class UStaticMesh {
public:
    BYTE unk_00[0x50];
    TArray<FStaticMeshSection> Sections;
};

class AActor {
public:
    BYTE unk_00[0x100];
    UStaticMesh *StaticMesh;
};

class FStaticMeshBatch;

struct FStaticMeshBatchElement {
    AActor *Actor;
    INT     SectionIndex;
    INT     FirstIndex;
    INT     NumPrimitives;
    _WORD   MinVertexIndex;
    _WORD   MaxVertexIndex;
};

class FStaticMeshBatchVertexStream : public FVertexStream {
public:
    FStaticMeshBatch *Batch;
    unsigned __int64 CacheId;
    INT               Size;
    INT               NumUVs;
    INT               Stride;
    INT               Revision;

    FStaticMeshBatchVertexStream(UMaterial *InMaterial);

    virtual unsigned __int64 GetCacheId();
    virtual INT   GetRevision();
    virtual INT   GetStride();
    virtual INT   GetSize();
    virtual INT   HintDynamic();
    virtual INT   UseNPatches();
    virtual INT   GetComponents(FVertexComponent *Components);
    virtual void  GetStreamData(void *Dest);
    virtual void  GetRawStreamData(void **Dest, INT FirstVertex);
};

class FStaticMeshBatchIndexBuffer : public FIndexBuffer {
public:
    FStaticMeshBatch *Batch;
    unsigned __int64 CacheId;
    DWORD             Size;

    FStaticMeshBatchIndexBuffer()
    {
        CacheId = MakeCacheID(CID_RenderData);
        Size = 0;
    }

    virtual unsigned __int64 GetCacheId();
    virtual INT   GetRevision();
    virtual INT   GetSize();
    virtual void  GetContents(void *Data);
};

class FStaticMeshBatch {
public:
    UMaterial                      *Material;
    UBOOL                           Sorted;
    TArray<FStaticMeshBatchElement> Elements;
    FStaticMeshBatchVertexStream    Vertices;
    FStaticMeshBatchIndexBuffer     Indices;

    FStaticMeshBatch(UMaterial *InMaterial, UBOOL InDisableSorting);
    INT AddElement(AActor *Actor, INT SectionIndex);
};

class FStaticMeshBatchSortedIndexBuffer : public FIndexBuffer {
public:
    FStaticMeshBatch *Batch;
    INT              *ElementIndices;
    INT               NumElements;
    FVector           SortDirection;
    unsigned __int64 CacheId;
    INT               Size;

    FStaticMeshBatchSortedIndexBuffer(
        FStaticMeshBatch *InBatch,
        INT *InElementIndices,
        INT InNumElements,
        FVector InSortDirection);

    virtual unsigned __int64 GetCacheId();
    virtual INT   GetRevision();
    virtual INT   GetSize();
    virtual void  GetContents(void *Data);
};

#pragma pack(pop)

// FStaticMeshBatchVertexStream::FStaticMeshBatchVertexStream (RVA 0x14aba0, callee of 0x14b1f0)
FStaticMeshBatchVertexStream::FStaticMeshBatchVertexStream(UMaterial *InMaterial)
{
    CacheId = MakeCacheID(CID_RenderData);
    Size = 0;
    BYTE RequiredUVs = InMaterial->RequiredUVStreams();
    BYTE Mask = 0xff;
    for (INT i = 0; i < 8; i++, Mask <<= 1) {
        if (!(RequiredUVs & Mask)) {
            NumUVs = i;
            break;
        }
    }
    Revision = 1;
    Stride = 28 + NumUVs * 8;
}

// FStaticMeshBatch::FStaticMeshBatch (RVA 0x14b1f0)
FStaticMeshBatch::FStaticMeshBatch(UMaterial *InMaterial, UBOOL InDisableSorting)
    : Vertices(InMaterial)
{
    Material = InMaterial;
    Sorted = InMaterial->RequiresSorting() && !InDisableSorting;
}

// FStaticMeshBatch::AddElement (RVA 0x14b2b0)
INT FStaticMeshBatch::AddElement(AActor *Actor, INT SectionIndex)
{
    FStaticMeshSection &Section = Actor->StaticMesh->Sections(SectionIndex);
    if (!Section.NumPrimitives)
        return -1;

    FStaticMeshBatchElement Element;
    Element.Actor = Actor;
    Element.SectionIndex = SectionIndex;
    Element.FirstIndex = Indices.Size / sizeof(_WORD);
    Element.NumPrimitives = Section.NumPrimitives;
    Element.MinVertexIndex = (_WORD)(Vertices.Size / Vertices.Stride);
    Element.MaxVertexIndex =
        Element.MinVertexIndex - Section.MinVertexIndex + Section.MaxVertexIndex;

    INT ElementIndex = Elements.AddItem(Element);
    Indices.Size += Section.NumPrimitives * 3 * sizeof(_WORD);
    Vertices.Size += (Section.MaxVertexIndex - Section.MinVertexIndex + 1) * Vertices.Stride;
    return ElementIndex;
}

// FStaticMeshBatchSortedIndexBuffer::FStaticMeshBatchSortedIndexBuffer (RVA 0x14b370)
FStaticMeshBatchSortedIndexBuffer::FStaticMeshBatchSortedIndexBuffer(
    FStaticMeshBatch *InBatch,
    INT *InElementIndices,
    INT InNumElements,
    FVector InSortDirection)
{
    Batch = InBatch;
    ElementIndices = InElementIndices;
    NumElements = InNumElements;
    SortDirection = InSortDirection;
    Size = 0;
    for (INT i = 0; i < NumElements; i++)
        Size += Batch->Elements(ElementIndices[i]).NumPrimitives * 3 * sizeof(_WORD);
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);

void *operator new(unsigned int, void *Ptr) { return Ptr; }

void Driver_14b1f0(FStaticMeshBatch *Batch, UMaterial *Material, UBOOL DisableSorting)
{
    new (Batch) FStaticMeshBatch(Material, DisableSorting);
    Escape(Batch);
}

INT Driver_14b2b0(FStaticMeshBatch *Batch, AActor *Actor, INT SectionIndex)
{
    Escape(Batch);
    return Batch->AddElement(Actor, SectionIndex);
}

void Driver_14b370(
    FStaticMeshBatch *Batch,
    INT *ElementIndices,
    INT NumElements,
    FVector SortDirection)
{
    FStaticMeshBatchSortedIndexBuffer Buf(Batch, ElementIndices, NumElements, SortDirection);
    Escape(&Buf);
}
