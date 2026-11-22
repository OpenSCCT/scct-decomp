// w4_item_0089.cpp -- Static mesh batch construction, element addition, and sorted index buffer.

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;
typedef float FLOAT;
typedef DWORD UBOOL;

#pragma pack(push, 4)

struct FVector {
    FLOAT X;
    FLOAT Y;
    FLOAT Z;
};

class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Add(INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray {
public:
    TArray() {}
    ~TArray();

    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }

    INT Add(INT Count = 1) { return FArray::Add(Count, sizeof(T)); }
    INT AddItem(const T &Item)
    {
        INT Index = Add();
        (*this)(Index) = Item;
        return Index;
    }
};

enum ECacheIDBase {
    CID_RenderData = 0xe1
};

extern QWORD GNextCacheID;

inline QWORD MakeCacheID(ECacheIDBase Base)
{
    return (GNextCacheID++) * 0x100 + Base;
}

class UMaterial {
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual UBOOL RequiresSorting();   // +0x70
    virtual void Slot29();
    virtual BYTE RequiredUVStreams();  // +0x78
};

struct FStaticMeshSection {
    INT   unk_00;
    INT   unk_04;
    _WORD unk_08;
    _WORD MinVertexIndex;
    _WORD MaxVertexIndex;
    _WORD unk_0e;
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

class FVertexStream {
public:
    virtual QWORD GetCacheId() = 0;
    virtual INT   GetRevision() = 0;
    virtual INT   GetSize() = 0;
    virtual INT   GetStride() = 0;
    virtual INT   GetComponents(void *Components) = 0;
    virtual void  GetStreamData(void *Dest) = 0;
    virtual void  GetRawStreamData(void **Dest, INT FirstVertex) = 0;
};

class FIndexBuffer {
public:
    virtual QWORD GetCacheId() = 0;
    virtual INT   GetRevision() = 0;
    virtual INT   GetSize() = 0;
    virtual void  GetContents(void *Data) = 0;
};

class FStaticMeshBatchVertexStream : public FVertexStream {
public:
    FStaticMeshBatch *Batch;
    QWORD             CacheId;
    INT               Size;
    INT               NumUVs;
    INT               Stride;
    INT               Revision;

    FStaticMeshBatchVertexStream(UMaterial *InMaterial);

    virtual QWORD GetCacheId();
    virtual INT   GetRevision();
    virtual INT   GetSize();
    virtual INT   GetStride();
    virtual INT   GetComponents(void *Components);
    virtual void  GetStreamData(void *Dest);
    virtual void  GetRawStreamData(void **Dest, INT FirstVertex);
};

class FStaticMeshBatchIndexBuffer : public FIndexBuffer {
public:
    FStaticMeshBatch *Batch;
    QWORD             CacheId;
    DWORD             Size;

    FStaticMeshBatchIndexBuffer()
    {
        CacheId = MakeCacheID(CID_RenderData);
        Size = 0;
    }

    virtual QWORD GetCacheId();
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
    QWORD             CacheId;
    INT               Size;

    FStaticMeshBatchSortedIndexBuffer(
        FStaticMeshBatch *InBatch,
        INT *InElementIndices,
        INT InNumElements,
        FVector InSortDirection);

    virtual QWORD GetCacheId();
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
    for (INT i = 0; i < 8; i++) {
        if (!(RequiredUVs & (0xff << i))) {
            NumUVs = i;
            break;
        }
    }
    Stride = 28 + NumUVs * 8;
    Revision = 1;
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
