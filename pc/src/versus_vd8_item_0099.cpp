// Work item w4 0099: Versus RVA 0x14fc40-0x15017e, 3 functions.
// Two FVertexStream subclasses for BSP dynamic lighting:
// - UnnamedBspPointLightStream_14fae0 (vtable 0x10c033a8): GetStreamData at 0x14fc40.
// - UnnamedBspSpotlightStream_14ff00 (vtable 0x10c03430): ctor at 0x14ff00, GetStreamData at 0x14ff80.
// Class and section struct names are neutral; UE2 math/BSP/stream types follow Engine conventions.

typedef unsigned char BYTE;
typedef short SWORD;
typedef unsigned short WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
extern "C" __declspec(dllimport) double __cdecl floor(double);

inline FLOAT appSqrt(FLOAT Value)
{
    return (FLOAT)sqrt(Value);
}

inline FLOAT Square(FLOAT A)
{
    return A * A;
}

inline FLOAT Abs(FLOAT A)
{
    return A >= 0.0f ? A : -A;
}

inline INT Clamp(INT X, INT Min, INT Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

inline INT appFloor(FLOAT F)
{
    return (INT)floor(F);
}

void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);

extern QWORD GNextCacheID; // 0x10c96930

enum ECacheIDBase
{
    CID_RenderVertices = 0xe1
};

inline QWORD MakeCacheID(ECacheIDBase Base)
{
    return GNextCacheID++ * 0x100 + Base;
}

struct FVector
{
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}

    FVector operator-(const FVector &V) const
    {
        return FVector(X - V.X, Y - V.Y, Z - V.Z);
    }

    FVector operator*(FLOAT Scale) const
    {
        return FVector(X * Scale, Y * Scale, Z * Scale);
    }

    FLOAT operator|(const FVector &V) const
    {
        return X * V.X + Y * V.Y + Z * V.Z;
    }

    FVector operator^(const FVector &V) const
    {
        return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
    }

    FVector SafeNormal() const;
    void FindBestAxisVectors(FVector &Axis1, FVector &Axis2) const;
};

extern FVector *GUnitX; // 0x10ccacc4
extern FVector *GUnitZ; // 0x10ccacbc

// RVA 0x50110 (not part of this item; defined so LTCG gives it its retail register convention).
__declspec(noinline) void FVector::FindBestAxisVectors(FVector &Axis1, FVector &Axis2) const
{
    FLOAT NX = (FLOAT)fabs(X);
    FLOAT NY = (FLOAT)fabs(Y);
    FLOAT NZ = (FLOAT)fabs(Z);

    if (NZ > NX && NZ > NY)
        Axis1 = *GUnitX;
    else
        Axis1 = *GUnitZ;

    Axis1 = (Axis1 - *this * (Axis1 | *this)).SafeNormal();
    Axis2 = Axis1 ^ *this;
}

struct FPlane : public FVector
{
    FLOAT W;

    FPlane() {}
    FPlane(FVector V, FLOAT InW) : FVector(V.X, V.Y, V.Z), W(InW) {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}

    FLOAT PlaneDot(const FVector &P) const
    {
        return X * P.X + Y * P.Y + Z * P.Z - W;
    }
};

struct FColor
{
    BYTE B, G, R, A;

    FColor() {}
    FColor(const FPlane &P);
};

// RVA 0xf8870 (not part of this item; defined so LTCG gives it its retail register convention).
__declspec(noinline) FColor::FColor(const FPlane &P)
:   B((BYTE)Clamp(appFloor(P.Z * 256.f), 0, 255))
,   G((BYTE)Clamp(appFloor(P.Y * 256.f), 0, 255))
,   R((BYTE)Clamp(appFloor(P.X * 256.f), 0, 255))
,   A((BYTE)Clamp(appFloor(P.W * 256.f), 0, 255))
{
}

struct FBspVertex
{
    FVector Position; // +0x00
    FVector Normal;   // +0x0c
    FLOAT U;          // +0x18
    FLOAT V;          // +0x1c
    FLOAT U2;         // +0x20
    FLOAT V2;         // +0x24
};

struct FBspSpotlightVertex
{
    FVector Position; // +0x00
    FVector Normal;   // +0x0c
    FLOAT U;          // +0x18
    FLOAT V;          // +0x1c
};

struct FBspDynamicLightVertex
{
    FVector Position; // +0x00
    FColor Color;     // +0x0c
    FLOAT U;          // +0x10
    FLOAT V;          // +0x14
    FLOAT LightU;     // +0x18
    FLOAT LightV;     // +0x1c
};

struct FBspNode
{
    FPlane Plane;          // +0x00
    BYTE unk_10[0x42];     // +0x10
    SWORD iVertexIndex;    // +0x52
    BYTE unk_54[0x06];     // +0x54
    BYTE NumVertices;      // +0x5a
    BYTE unk_5b;           // +0x5b
};

struct FBspSection
{
    void *Vtbl;            // +0x00
    FBspVertex *Vertices;  // +0x04
    BYTE unk_08[0x30];     // +0x08
};

template<class T> struct TArray
{
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
};

struct UModel
{
    BYTE unk_00[0x54];          // +0x00
    TArray<FBspNode> Nodes;     // +0x54
    BYTE unk_60[0x74];          // +0x60
    TArray<FBspSection> Sections; // +0xd4
};

struct AActor
{
    BYTE unk_00[0x2d2];    // +0x00
    BYTE LightEffect;      // +0x2d2
};

struct FDynamicLight
{
    AActor *Actor;         // +0x00
    INT unk_04;            // +0x04
    FPlane Color;          // +0x08
    FVector Position;      // +0x18
    FVector Direction;     // +0x24
    FLOAT Radius;          // +0x30
};

struct FBspLightSection
{
    UModel *Model;         // +0x00
    INT SectionIndex;      // +0x04
    INT NumNodes;          // +0x08
    INT NumTriangles;      // +0x0c
    INT *Nodes;            // +0x10
    FDynamicLight *Light;  // +0x14
};

#pragma pack(push, 4)

class FVertexStream
{
public:
    virtual QWORD GetCacheId();
    virtual INT GetRevision();
    virtual INT GetStride();
    virtual INT GetSize();
    virtual INT HintDynamic();
    virtual INT UseNPatches();
    virtual INT GetComponents(void *OutComponents);
    virtual void GetStreamData(void *Dest);
};

class UnnamedBspPointLightStream_14fae0 : public FVertexStream
{
public:
    QWORD CacheId;             // +0x04
    FBspLightSection *Section; // +0x0c
    FDynamicLight *Light;      // +0x10

    void InitVertex(
        FBspDynamicLightVertex *Dest,
        FBspVertex *Src,
        const FVector &AxisX,
        const FVector &AxisY,
        FLOAT PlaneRadius,
        FColor Color);
    virtual void GetStreamData(void *Dest);
};

class UnnamedBspSpotlightStream_14ff00 : public FVertexStream
{
public:
    QWORD CacheId;             // +0x04
    FBspLightSection *Section; // +0x0c
    FDynamicLight *Light;      // +0x10

    UnnamedBspSpotlightStream_14ff00(FBspLightSection *InSection, FDynamicLight *InLight);
    virtual void GetStreamData(void *Dest);
};

#pragma pack(pop)

// RVA 0x14fb30 (not part of this item; defined so LTCG gives it its retail register convention).
__declspec(noinline) void UnnamedBspPointLightStream_14fae0::InitVertex(
    FBspDynamicLightVertex *Dest,
    FBspVertex *Src,
    const FVector &AxisX,
    const FVector &AxisY,
    FLOAT PlaneRadius,
    FColor Color)
{
    Dest->Position = Src->Position;
    Dest->U = Src->U;
    Dest->V = Src->V;
    FLOAT InvRadius = 1.0f / PlaneRadius;
    Dest->LightU = (((Src->Position - Light->Position) | AxisX) * InvRadius + 1.0f) * 0.5f;
    Dest->LightV = (((Src->Position - Light->Position) | AxisY) * InvRadius + 1.0f) * 0.5f;
    Dest->Color = Color;
}

// RVA 0x14fc40: UnnamedBspPointLightStream_14fae0::GetStreamData.
void UnnamedBspPointLightStream_14fae0::GetStreamData(void *Dest)
{
    FBspDynamicLightVertex *DestVertex = (FBspDynamicLightVertex *)Dest;
    FBspVertex *SrcVertices = Section->Model->Sections(Section->SectionIndex).Vertices;
    FLOAT LightRadiusSquared = Square(Light->Radius);

    for (INT NodeIndex = 0; NodeIndex < Section->NumNodes; NodeIndex++)
    {
        FBspNode &Node = Section->Model->Nodes(Section->Nodes[NodeIndex]);
        FLOAT PlaneDist = Node.Plane.PlaneDot(Light->Position);
        FLOAT PlaneDistSquared = Square(PlaneDist);
        FLOAT PlaneRadius = appSqrt(LightRadiusSquared - PlaneDistSquared);

        FVector LightX, LightY;
        FColor Color;
        if (Light->Actor->LightEffect == 0x14)
        {
            Color = FColor(
                FPlane(
                    Light->Color * (2.0f * appSqrt(1.0f - PlaneDistSquared / LightRadiusSquared)),
                    0.0f));
        }
        else
        {
            Color = FColor(
                FPlane(
                    Light->Color * (2.0f * appSqrt(1.0f - Abs(PlaneDist) / Light->Radius)),
                    0.0f));
        }
        Color.A = 255;

        Node.Plane.FindBestAxisVectors(LightX, LightY);

        InitVertex(&DestVertex[0], &SrcVertices[Node.iVertexIndex],
                   LightX, LightY, PlaneRadius, Color);
        InitVertex(&DestVertex[1], &SrcVertices[Node.iVertexIndex + 2],
                   LightX, LightY, PlaneRadius, Color);
        InitVertex(&DestVertex[2], &SrcVertices[Node.iVertexIndex + 1],
                   LightX, LightY, PlaneRadius, Color);

        FBspDynamicLightVertex *PrevVertex = &DestVertex[1];
        for (INT TriIndex = 1; TriIndex < Node.NumVertices - 2; TriIndex++)
        {
            appMemcpy(&DestVertex[TriIndex * 3 + 0], &DestVertex[0],
                      sizeof(FBspDynamicLightVertex));
            appMemcpy(&DestVertex[TriIndex * 3 + 2], PrevVertex,
                      sizeof(FBspDynamicLightVertex));
            InitVertex(&DestVertex[TriIndex * 3 + 1],
                       &SrcVertices[Node.iVertexIndex + TriIndex + 2],
                       LightX, LightY, PlaneRadius, Color);
            PrevVertex = &DestVertex[TriIndex * 3 + 1];
        }

        DestVertex += (Node.NumVertices - 2) * 3;
    }
}

// RVA 0x14ff00: constructor of UnnamedBspSpotlightStream_14ff00.
__declspec(noinline) UnnamedBspSpotlightStream_14ff00::UnnamedBspSpotlightStream_14ff00(
    FBspLightSection *InSection,
    FDynamicLight *InLight)
{
    Section = InSection;
    Light = InLight;
    CacheId = MakeCacheID(CID_RenderVertices);
}

inline void CopySpotlightVertex(FBspSpotlightVertex *Dest, const FBspVertex *Src)
{
    Dest->Position = Src->Position;
    Dest->Normal = Src->Normal;
    Dest->U = Src->U;
    Dest->V = Src->V;
}

// RVA 0x14ff80: UnnamedBspSpotlightStream_14ff00::GetStreamData.
void UnnamedBspSpotlightStream_14ff00::GetStreamData(void *Dest)
{
    FBspSpotlightVertex *DestVertex = (FBspSpotlightVertex *)Dest;
    FBspVertex *SrcVertices = Section->Model->Sections(Section->SectionIndex).Vertices;

    for (INT NodeIndex = 0; NodeIndex < Section->NumNodes; NodeIndex++)
    {
        FBspNode *Node = &Section->Model->Nodes(Section->Nodes[NodeIndex]);
        CopySpotlightVertex(&DestVertex[0], &SrcVertices[Node->iVertexIndex]);
        CopySpotlightVertex(&DestVertex[1], &SrcVertices[Node->iVertexIndex + 2]);
        CopySpotlightVertex(&DestVertex[2], &SrcVertices[Node->iVertexIndex + 1]);

        FBspSpotlightVertex *PrevVertex = &DestVertex[1];
        for (INT TriIndex = 1; TriIndex < Node->NumVertices - 2; TriIndex++)
        {
            appMemcpy(&DestVertex[TriIndex * 3 + 0], &DestVertex[0],
                      sizeof(FBspSpotlightVertex));
            appMemcpy(&DestVertex[TriIndex * 3 + 2], PrevVertex,
                      sizeof(FBspSpotlightVertex));
            CopySpotlightVertex(&DestVertex[TriIndex * 3 + 1],
                                &SrcVertices[Node->iVertexIndex + TriIndex + 2]);
            PrevVertex = &DestVertex[TriIndex * 3 + 1];
        }

        DestVertex += (Node->NumVertices - 2) * 3;
    }
}

// Scaffolding for LTCG links, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }

UnnamedBspSpotlightStream_14ff00 *Driver_14ff00(void *Mem, FBspLightSection *S, FDynamicLight *L)
{
    UnnamedBspSpotlightStream_14ff00 *A = new (Mem) UnnamedBspSpotlightStream_14ff00(S, L);
    Escape(A);
    return new ((BYTE *)Mem + 0x20) UnnamedBspSpotlightStream_14ff00(S, L);
}
