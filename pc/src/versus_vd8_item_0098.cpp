// Work item 0098: Versus RVA 0x14fae0-0x14fbe3 (2 functions, VC7.0 /GL /LTCG).
// BSP dynamic light vertex stream constructor (0x14fae0) and vertex builder
// (0x14fb30). Standard UE2 types (FVector, FColor, FVertexStream, FBspVertex,
// FDynamicLight, MakeCacheID, GNextCacheID) follow engine conventions; the
// unexported stream class, output vertex, and section structs
// (FBspLightVertexStream, FBspLightVertex, FBspLightSection) are neutral
// descriptive names inferred from retail vtable 0x10c033a8 and call sites.

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

#pragma pack(push, 4)

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
};

struct FColor
{
    BYTE B, G, R, A;
};

struct FBspVertex
{
    FVector Position;   // +0x00
    FVector Normal;     // +0x0c
    FLOAT U;            // +0x18
    FLOAT V;            // +0x1c
    FLOAT U2;           // +0x20
    FLOAT V2;           // +0x24
};

// 32-byte dynamic light vertex emitted by FBspLightVertexStream::GetStreamData.
struct FBspLightVertex
{
    FVector Position;   // +0x00
    FColor Color;       // +0x0c
    FLOAT U;            // +0x10
    FLOAT V;            // +0x14
    FLOAT U2;           // +0x18
    FLOAT V2;           // +0x1c
};

struct FDynamicLight
{
    BYTE unk_00[0x18];
    FVector Position;   // +0x18
};

struct FBspLightSection;

enum ECacheIDBase
{
    CID_RenderVertices = 0xe1
};

extern QWORD GNextCacheID;

inline QWORD MakeCacheID(ECacheIDBase Base)
{
    return (GNextCacheID++) * 0x100 + Base;
}

class FVertexStream
{
public:
    virtual QWORD GetCacheId() = 0;
    virtual INT GetRevision() = 0;
    virtual INT GetStride() = 0;
    virtual INT GetSize() = 0;
    virtual UBOOL HintDynamic() = 0;
    virtual UBOOL UseNPatches() = 0;
    virtual INT GetComponents(void *OutComponents) = 0;
    virtual void GetStreamData(void *Dest) = 0;
    virtual void GetRawStreamData(void **Dest, INT FirstVertex) = 0;
};

// Unexported FVertexStream subclass (vtable 0x10c033a8).
class FBspLightVertexStream : public FVertexStream
{
public:
    QWORD CacheId;              // +0x04
    FBspLightSection *Section;  // +0x0c
    FDynamicLight *Light;       // +0x10

    FBspLightVertexStream(FBspLightSection *InSection, FDynamicLight *InLight);

    virtual QWORD GetCacheId();
    virtual INT GetRevision();
    virtual INT GetStride();
    virtual INT GetSize();
    virtual UBOOL HintDynamic();
    virtual UBOOL UseNPatches();
    virtual INT GetComponents(void *OutComponents);
    virtual void GetStreamData(void *Dest);
    virtual void GetRawStreamData(void **Dest, INT FirstVertex);

    void InitVertex(FBspLightVertex *OutVertex, const FBspVertex *InVertex,
                    const FVector &AxisU, const FVector &AxisV,
                    FLOAT CircleRadius, FColor Color);
};

#pragma pack(pop)

// FBspLightVertexStream::FBspLightVertexStream (RVA 0x14fae0).
// Initializes the BSP dynamic light vertex stream and allocates a render cache id.
FBspLightVertexStream::FBspLightVertexStream(FBspLightSection *InSection, FDynamicLight *InLight)
    : Section(InSection), Light(InLight)
{
    CacheId = MakeCacheID(CID_RenderVertices);
}

// FBspLightVertexStream::InitVertex (RVA 0x14fb30).
// Projects a BSP vertex into the light's tangent-plane UV space and fills OutVertex.
void FBspLightVertexStream::InitVertex(FBspLightVertex *OutVertex, const FBspVertex *InVertex,
                                       const FVector &AxisU, const FVector &AxisV,
                                       FLOAT CircleRadius, FColor Color)
{
    OutVertex->Position = InVertex->Position;
    OutVertex->U = InVertex->U;
    OutVertex->V = InVertex->V;
    OutVertex->U2 = (((InVertex->Position - Light->Position) | AxisU)
                     * (1.0f / CircleRadius) + 1.0f) * 0.5f;
    OutVertex->V2 = (((InVertex->Position - Light->Position) | AxisV)
                     * (1.0f / CircleRadius) + 1.0f) * 0.5f;
    OutVertex->Color = Color;
}

// ---- Scaffolding for LTCG linking, not part of the unit.
void Escape(void *);

void Driver_14fae0(FBspLightSection *S1, FDynamicLight *L1,
                   FBspLightSection *S2, FDynamicLight *L2, INT Mode)
{
    switch (Mode) {
    case 0: {
        FBspLightVertexStream A(S1, L1);
        Escape(&A);
        break;
    }
    case 1: {
        FBspLightVertexStream B(S2, L1);
        Escape(&B);
        break;
    }
    case 2: {
        FBspLightVertexStream C(S1, L2);
        Escape(&C);
        break;
    }
    case 3: {
        FBspLightVertexStream D(S2, L2);
        Escape(&D);
        break;
    }
    default: {
        FBspLightVertexStream E(S1, L1);
        Escape(&E);
        break;
    }
    }
}

void Driver_14fb30(FBspLightVertexStream *Stream, FBspLightVertex *Out, const FBspVertex *In,
                   const FVector *AxisU, const FVector *AxisV, FLOAT Radius, FColor Color)
{
    Stream->InitVertex(&Out[0], &In[0], *AxisU, *AxisV, Radius, Color);
    Stream->InitVertex(&Out[1], &In[2], *AxisU, *AxisV, Radius, Color);
    Stream->InitVertex(&Out[2], &In[1], *AxisU, *AxisV, Radius, Color);
}
